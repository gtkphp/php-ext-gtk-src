/*
+----------------------------------------------------------------------+
| PHP Version 8                                                        |
+----------------------------------------------------------------------+
| Copyright (c) 1997-2018 The PHP Group                                |
+----------------------------------------------------------------------+
| This source file is subject to version 3.01 of the PHP license,      |
| that is bundled with this package in the file LICENSE, and is        |
| available through the world-wide-web at the following url:           |
| http://www.php.net/license/3_01.txt                                  |
| If you did not receive a copy of the PHP license and are unable to   |
| obtain it through the world-wide-web, please send a note to          |
| license@php.net so we can mail you a copy immediately.               |
+----------------------------------------------------------------------+
| Author: No Name                                                      |
+----------------------------------------------------------------------+
*/

/* $Id$ */


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <php_ini.h>
#include <zend_interfaces.h>
#include <ext/standard/info.h>

#include <cairo/cairo.h>

#include "php_gtk.h"
#include "php_cairo/image-data.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_image_data_t_class_entry;// struct
zend_object_handlers  php_cairo_image_data_t_handlers;







/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_image_data_t_methods[] = {
    PHP_ME(cairo_image_data_t, __construct, arginfo_cairo_image_data_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_image_data_t_create_object */
static zend_object*
php_cairo_image_data_t_create_object(zend_class_entry *class_type)
{
    php_cairo_image_data_t *intern = zend_object_alloc(sizeof(php_cairo_image_data_t), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->surface = NULL;
    intern->ptr = NULL;
    intern->buffer = NULL;

    intern->std.handlers = &php_cairo_image_data_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_image_data_t_create_object */


static void
php_cairo_image_data_t_dtor_object(zend_object *obj) {
    //php_cairo_image_data_t *intern = ZOBJ_TO_PHP_CAIRO_IMAGE_DATA_T(obj);

}

/* {{{ php_cairo_image_data_t_free_object */
static void
php_cairo_image_data_t_free_object(zend_object *object)
{
    php_cairo_image_data_t *intern = ZOBJ_TO_PHP_CAIRO_IMAGE_DATA_T(object);

    if (intern->surface) {
        intern->surface = NULL;
    }
    if (intern->ptr) {
        //efree(intern->data); delete by set_user_data
    }
    if (intern->buffer) {
        intern->buffer->gc.refcount--;
        if (intern->buffer->gc.refcount==0) {
            zend_hash_destroy(intern->buffer);
            FREE_HASHTABLE(intern->buffer);
        }
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_image_data_t_free_object */



static zend_array*
php_cairo_image_data_t_get_buffer(php_cairo_image_data_t *object) {
    if (object->buffer==NULL) {
        ALLOC_HASHTABLE(object->buffer);
        zend_hash_init(object->buffer, 1, NULL, ZVAL_PTR_DTOR, 1);
    }
    return object->buffer;
}

unsigned char*
php_cairo_image_data_t_get_data(php_cairo_image_data_t *object){
    unsigned char*data = NULL;
    zend_array *buffer = php_cairo_image_data_t_get_buffer(object);
    uint32_t size = zend_array_count(buffer);

    //cairo_format_t format = cairo_image_surface_get_format(object->ptr);
    //int height = cairo_image_surface_get_height(object->ptr);
    //int width = cairo_image_surface_get_width(object->ptr);
    //int stride = cairo_format_stride_for_width (format, width);

    data = emalloc(sizeof(unsigned char)*size);
    object->ptr = data;

    int i=0;
    zval *val;
    ZEND_HASH_FOREACH_VAL(buffer, val) {
        object->ptr[i] = val->value.str->val[0];// & 0xFF;
        i++;
    } ZEND_HASH_FOREACH_END();

    return object->ptr;
}

ZEND_SET_ALIGNED(16, static const char hexconvtab[]) = "0123456789ABCDEF";

/* {{{ php_cairo_bin2hex */
static zend_string *php_cairo_bin2hex(const unsigned char *old, const size_t oldlen)
{
    zend_string *result;
    size_t i, j;

    result = zend_string_safe_alloc(oldlen, 4 * sizeof(char), 0, 0);

    for (i = j = 0; i < oldlen; i++) {
        ZSTR_VAL(result)[j++] = '\\';
        ZSTR_VAL(result)[j++] = 'x';
        ZSTR_VAL(result)[j++] = hexconvtab[old[i] >> 4];
        ZSTR_VAL(result)[j++] = hexconvtab[old[i] & 15];
    }
    ZSTR_VAL(result)[j] = '\0';

    return result;
}
/* }}} */

/* {{{ php_cairo_image_data_t_get_debug_info */
static HashTable*
php_cairo_image_data_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_image_data_t  *intern = ZOBJ_TO_PHP_CAIRO_IMAGE_DATA_T(object);
    zend_array *buffer = php_cairo_image_data_t_get_buffer(intern);
    zend_string *result;
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    // debug zend_array
    if (intern->ptr) {
        int height = cairo_image_surface_get_height (intern->surface);
        int width = cairo_image_surface_get_width (intern->surface);
        cairo_format_t format = cairo_image_surface_get_format (intern->surface);
        int stride = cairo_format_stride_for_width (format, width);
        zval val;
        int i;
        int len = stride*height;
        for (i=0; i<len; i++) {
            result = php_cairo_bin2hex((unsigned char *)&intern->ptr[i], 1);
            ZVAL_STR(&val, result);
            zend_hash_next_index_insert(debug_info, &val);
        }
    } else {
        zval *val;
        ZEND_HASH_FOREACH_VAL(buffer, val) {
            result = php_cairo_bin2hex((unsigned char *)ZSTR_VAL(val->value.str), ZSTR_LEN(val->value.str));
            ZVAL_STR(val, result);
            zend_hash_next_index_insert(debug_info, val);
        } ZEND_HASH_FOREACH_END();
    }


    return debug_info;
}
/* }}} */


static int
php_cairo_image_data_t_has_dimension(zend_object *object, zval *member, int check_empty) {

    return 0;
}


static void
php_cairo_image_data_t_write_dimension(zend_object *object, zval *offset, zval *value){
    php_cairo_image_data_t *php_data = ZOBJ_TO_PHP_CAIRO_IMAGE_DATA_T(object);
    cairo_surface_t *surface = php_data->surface;
    unsigned char *data = php_data->ptr;

    zval *index = offset;
    if (NULL==offset || ZVAL_IS_NULL(offset)) {
        // if data!=NULL => error : can't resize data
        zend_array *buffer = php_cairo_image_data_t_get_buffer(php_data);
        zend_hash_next_index_insert(buffer, value);
        return;
    }
    if (Z_TYPE_P(offset)==IS_REFERENCE) {
        index = &offset->value.ref->val;
    }

    if (Z_TYPE_P(index)==IS_LONG) {
        if (data==NULL) {
            // use buffer
        } else {
            zend_long lval = index->value.lval;
            if (Z_TYPE_P(value)==IS_LONG) {
                data[lval] = value->value.lval;
                return;
            } else if (Z_TYPE_P(value)==IS_STRING) {
                if (value->value.str->len==1) {
                    data[lval] = value->value.str->val[0];
                    return;
                }
            }
        }
    }
    // Error
}

static zval *
php_cairo_image_data_t_read_dimension(zend_object *object, zval *offset, int type, zval *rv){
    php_cairo_image_data_t *php_data = ZOBJ_TO_PHP_CAIRO_IMAGE_DATA_T(object);
    cairo_surface_t *surface = php_data->surface;
    unsigned char *data = php_data->ptr;

    zval *index = offset;
    if (Z_TYPE_P(offset)==IS_REFERENCE) {
        index = &offset->value.ref->val;
    }

    if (Z_TYPE_P(index)==IS_LONG) {
        zend_long lval = index->value.lval;
        ZVAL_LONG(rv, data[lval]);
    } else {
        // Error
    }
    return rv;
}

static zval*
php_cairo_image_data_t_get_property_ptr_ptr(zend_object *object, zend_string *member, int type, void **cache_slot) {
    php_printf("get_property_ptr_ptr\n");
    return NULL;
}

static zend_object_handlers*
php_cairo_image_data_t_get_handlers()
{
    memcpy(&php_cairo_image_data_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_image_data_t_handlers.offset = PHP_CAIRO_IMAGE_DATA_T_OFFSET;
    php_cairo_image_data_t_handlers.dtor_obj = php_cairo_image_data_t_dtor_object;
    php_cairo_image_data_t_handlers.free_obj = php_cairo_image_data_t_free_object;

    php_cairo_image_data_t_handlers.has_dimension = php_cairo_image_data_t_has_dimension;
    php_cairo_image_data_t_handlers.read_dimension = php_cairo_image_data_t_read_dimension;
    php_cairo_image_data_t_handlers.write_dimension = php_cairo_image_data_t_write_dimension;
    php_cairo_image_data_t_handlers.get_property_ptr_ptr = php_cairo_image_data_t_get_property_ptr_ptr;


    php_cairo_image_data_t_handlers.get_debug_info = php_cairo_image_data_t_get_debug_info;


    return &php_cairo_image_data_t_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_image_data_t_class_init */
zend_class_entry*
php_cairo_image_data_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_image_data_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_image_data_t", php_cairo_image_data_t_methods);
    php_cairo_image_data_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_image_data_t_class_entry->create_object = php_cairo_image_data_t_create_object;

    return php_cairo_image_data_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/
php_cairo_image_data_t *
php_cairo_image_data_t_new() {
    zend_object *zobj = php_cairo_image_data_t_create_object(php_cairo_image_data_t_class_entry);
    php_cairo_image_data_t *php_data = ZOBJ_TO_PHP_CAIRO_IMAGE_DATA_T(zobj);

    return php_data;
}

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

 /* {{{ cairo_image_data_t::__construct() */
PHP_METHOD(cairo_image_data_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_image_data_t *self = ZOBJ_TO_PHP_CAIRO_IMAGE_DATA_T(zobj);


}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
