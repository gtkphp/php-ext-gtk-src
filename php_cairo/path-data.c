/*
+----------------------------------------------------------------------+
| PHP Version 7                                                        |
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

#include "php_cairo/cairo.h"
#include "path-data.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;

zend_class_entry     *php_cairo_path_data_t_class_entry;
zend_object_handlers  php_cairo_path_data_t_handlers;


/*----------------------------------------------------------------------+
| Internal                                                             |
+----------------------------------------------------------------------*/

static const zend_function_entry php_cairo_path_data_t_methods[] = {
    PHP_ME(cairo_path_data_t, __construct, arginfo_cairo_path_data_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/


/* {{{ php_cairo_path_data_t_create_object */
static zend_object*
php_cairo_path_data_t_create_object(zend_class_entry *class_type)
{
    php_cairo_path_data_t *intern = ecalloc(1, sizeof(php_cairo_path_data_t) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;
    intern->is_owner = 0;

    intern->std.handlers = &php_cairo_path_data_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_path_data_t_create_object */


static void
php_cairo_path_data_t_dtor_object(zend_object *obj) {
    //php_cairo_path_data_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(obj);

}

/* {{{ php_cairo_path_t_free_object */
static void
php_cairo_path_data_t_free_object(zend_object *object)
{
    php_cairo_path_data_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(object);

    if (intern->ptr!=NULL && intern->is_owner==1) {
        efree(intern->ptr);
        intern->ptr = NULL;
        intern->is_owner = 0;
    }

    zend_object_std_dtor(&intern->std);
    //efree(intern);
}
/* }}} php_cairo_path_t_free_object */


/* {{{ gtk_read_property */
static zval*
php_cairo_path_data_t_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_cairo_path_data_t *obj = ZVAL_GET_PHP_CAIRO_PATH_DATA_T(object);
    zend_string *member_str = zval_get_string(member);
    char *str = member_str->val;
    zval *retval;
    //php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (member_str->len==1 && str[0]=='x') {
        ZVAL_DOUBLE(rv, obj->ptr->point.x);
        return rv;
    }
    if (member_str->len==1 && str[0]=='y') {
        ZVAL_DOUBLE(rv, obj->ptr->point.y);
        return rv;
    }

    if (member_str->len==4 && str[0]=='t' && str[1]=='y' && str[2]=='p' && str[3]=='e') {
        ZVAL_LONG(rv, obj->ptr->header.type);
        return rv;
    }
    if (member_str->len==6 && str[0]=='l' && str[1]=='e' && str[2]=='n' && str[3]=='g' && str[4]=='t' && str[5]=='h') {
        ZVAL_LONG(rv, obj->ptr->header.length);
        return rv;
    }


    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    retval = std_hnd->read_property(object, member, type, cache_slot, rv);

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ php_cairo_path_data_t_write_property */
static void
php_cairo_path_data_t_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_cairo_path_data_t *obj = ZVAL_GET_PHP_CAIRO_PATH_DATA_T(object);
    zend_string *member_str = zval_get_string(member);
    char *str = member_str->val;
    //php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);


    if (member_str->len==1 && str[0]=='x') {
        if (Z_TYPE_P(value)==IS_DOUBLE) {
            obj->ptr->point.x = value->value.dval;
        } else {
            g_print("float expected\n");
        }
        return;
    }
    if (member_str->len==1 && str[0]=='y') {
        if (Z_TYPE_P(value)==IS_DOUBLE) {
            obj->ptr->point.x = value->value.dval;
        } else {
            g_print("float expected\n");
        }
        return;
    }

    if (member_str->len==4 && str[0]=='t' && str[1]=='y' && str[2]=='p' && str[3]=='e') {
        if (Z_TYPE_P(value)==IS_LONG) {
            obj->ptr->header.type = value->value.lval;
        } else {
            g_print("int expected\n");
        }
        return;
    }
    if (member_str->len==6 && str[0]=='l' && str[1]=='e' && str[2]=='n' && str[3]=='g' && str[4]=='t' && str[5]=='h') {
        if (Z_TYPE_P(value)==IS_LONG) {
            obj->ptr->header.length = value->value.lval;
        } else {
            g_print("int expected\n");
        }
        return;
    }


    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->write_property(object, member, value, cache_slot);

    zend_string_release(member_str);
}
/* }}} */

static void
php_cairo_path_data_t_unset_property(zval *object, zval *member, void **cache_slot) {
    php_cairo_path_data_t *obj = ZVAL_GET_PHP_CAIRO_PATH_DATA_T(object);
    zend_string *member_str = zval_get_string(member);
    php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);


    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}


static HashTable*
php_cairo_path_data_t_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_cairo_path_data_t  *obj =  ZVAL_GET_PHP_CAIRO_PATH_DATA_T(object);
    HashTable   *debug_info,
    *std_props;
    zend_string *string_key = NULL;
    zval *value;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    ZEND_HASH_FOREACH_STR_KEY_VAL(obj->std.properties, string_key, value) {
        zend_hash_add(debug_info, string_key, value);
    } ZEND_HASH_FOREACH_END();


    zval value_x;
    zval value_y;
    zval value_type;
    zval value_length;

    if (obj->is_header) {
        ZVAL_LONG(&value_type, obj->ptr->header.type);
        zend_hash_str_update(debug_info, "type", sizeof("type")-1, &value_type);
        ZVAL_LONG(&value_length, obj->ptr->header.length);
        zend_hash_str_update(debug_info, "length", sizeof("length")-1, &value_length);
    } else {
        ZVAL_DOUBLE(&value_x, obj->ptr->point.x);
        zend_hash_str_update(debug_info, "x", sizeof("x")-1, &value_x);
        ZVAL_DOUBLE(&value_y, obj->ptr->point.y);
        zend_hash_str_update(debug_info, "y", sizeof("y")-1, &value_y);
    }

    return debug_info;
}
/* }}} */


static HashTable*
php_cairo_path_data_t_get_properties(zval *object){
    php_cairo_path_data_t  *self =  ZVAL_GET_PHP_CAIRO_PATH_DATA_T(object);


    return NULL;
}


static zend_object_handlers*
php_cairo_path_data_t_get_handlers()
{
    memcpy(&php_cairo_path_data_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_path_data_t_handlers.offset = PHP_CAIRO_PATH_DATA_T_OFFSET;

    php_cairo_path_data_t_handlers.dtor_obj = php_cairo_path_data_t_dtor_object;
    php_cairo_path_data_t_handlers.free_obj = php_cairo_path_data_t_free_object;
    php_cairo_path_data_t_handlers.read_property = php_cairo_path_data_t_read_property;
    php_cairo_path_data_t_handlers.write_property = php_cairo_path_data_t_write_property;
    php_cairo_path_data_t_handlers.unset_property = php_cairo_path_data_t_unset_property;
    //php_cairo_path_data_t_handlers.get_property_ptr_ptr = php_cairo_path_data_t_get_property_ptr_ptr;

    php_cairo_path_data_t_handlers.get_debug_info = php_cairo_path_data_t_get_debug_info;


    return &php_cairo_path_data_t_handlers;
}



/*----------------------------------------------------------------------+
| PHP_MINIT                                                            |
+----------------------------------------------------------------------*/

/*{{{ php_cairo_path_data_t_class_init */
zend_class_entry*
php_cairo_path_data_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_path_data_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_path_data_t", php_cairo_path_data_t_methods);
    php_cairo_path_data_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_path_data_t_class_entry->create_object = php_cairo_path_data_t_create_object;

    return php_cairo_path_data_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
void
php_cairo_path_data_t_create_header(cairo_path_data_t *data, zval *rv)
{
    zend_object *zobj = php_cairo_path_data_t_create_object(php_cairo_path_data_t_class_entry);
    php_cairo_path_data_t *t = ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(zobj);
    t->ptr = data;// adpte ref
    t->is_header = 1;

    ZVAL_OBJ(rv, zobj);
}

void
php_cairo_path_data_t_create_point(cairo_path_data_t *data, zval *rv)
{
    zend_object *zobj = php_cairo_path_data_t_create_object(php_cairo_path_data_t_class_entry);
    php_cairo_path_data_t *t = ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(zobj);
    t->ptr = data;// adpte ref
    t->is_header = 0;

    ZVAL_OBJ(rv, zobj);
}

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

/* {{{ cairo_path_t::__construct() */
PHP_METHOD(cairo_path_data_t, __construct)
{
    zval *x;
    zval *y;

    ZEND_PARSE_PARAMETERS_START(1,2)
        Z_PARAM_ZVAL(x)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(y)
    ZEND_PARSE_PARAMETERS_END();

    zend_object *zobj = Z_OBJ_P(getThis());
    php_cairo_path_data_t *self = ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(zobj);
    self->ptr = emalloc(sizeof(cairo_path_data_t));
    self->is_owner = 1;

    switch (EX_NUM_ARGS()) {
    case 1:
        if (Z_TYPE_P(x)==IS_LONG) {
            self->is_header = 1;
            self->ptr->header.type = x->value.lval;
            switch(x->value.lval){
            case CAIRO_PATH_MOVE_TO:
            case CAIRO_PATH_LINE_TO:
                self->ptr->header.length = 2;
                break;
            case CAIRO_PATH_CURVE_TO:
                self->ptr->header.length = 4;
                break;
            case CAIRO_PATH_CLOSE_PATH:
                self->ptr->header.length = 1;
                break;
            }
        } else {
            //error please use CAIRO_PATH_DATA_TYPE
        }
        break;
    case 2:
        self->is_header = 0;
        if (Z_TYPE_P(x)==IS_DOUBLE && Z_TYPE_P(y)==IS_DOUBLE) {
            self->ptr->point.x = x->value.dval;
            self->ptr->point.y = y->value.dval;
        } else {
            //error please use CAIRO_PATH_DATA_TYPE
        }
        break;
    default:
        break;
    }

}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/
