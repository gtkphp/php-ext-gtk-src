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


#include <gdk/gdk.h>
#include "php_gtk.h"
#include "php_gobject/object.h"

#include "pixbuf.h"

#include "php_glib/error.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;

zend_class_entry     *php_gdk_pixbuf_class_entry;
//HashTable             php_gdk_pixbuf_prop_handlers;
zend_object_handlers  php_gdk_pixbuf_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry php_gdk_pixbuf_methods[] = {
    PHP_ME(gdk_pixbuf, __construct, arginfo_gdk_pixbuf___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/
static void  php_gdk_pixbuf_unset_property(zval *object, zval *member, void **cache_slot);
static zval* php_gdk_pixbuf_write_property(zend_object *object, zend_string *member_str, zval *value, void **cache_slot);
static zval* php_gdk_pixbuf_read_property(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv);
static char* php_gdk_pixbuf_dump(php_gdk_pixbuf *list, int tab);

static void
php_gdk_pixbuf_unset_dimension(zval *object, zval *offset) {
    //php_gobject *list = ZVAL_GET_PHP_GDK_PIXBUF(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
        // @TODO
        //zend_hash_index_del(list->prop_handler, );
        // php_gobject
        break;
    case IS_STRING:
        php_gdk_pixbuf_unset_property(object, offset, &cache);
        break;
    default:
        break;
    }
}

static void
php_gdk_pixbuf_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_gdk_pixbuf_write_property(object, &member, value, &cache);
}

static zval*
php_gdk_pixbuf_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
        return NULL;
    }

    php_gdk_pixbuf *intern = ZVAL_GET_PHP_GDK_PIXBUF(object);
    php_gdk_pixbuf *list;
    void *cache=NULL;

    if (Z_TYPE_P(offset)==IS_LONG) {
        ZVAL_NULL(rv);
        return rv;
    } else if (Z_TYPE_P(offset)==IS_STRING) {
        return php_gdk_pixbuf_read_property(object, offset, type, &cache, rv);
    } else {
        // error
    }

    return rv;
} /* }}} end php_g_hash_table_read_dimension */

static int
php_gdk_pixbuf_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

/* updates *count to hold the number of elements present and returns SUCCESS.
 * Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_gdk_pixbuf_count_elements(zval *object, zend_long *count) {

    *count = 0;

    return SUCCESS;
}

static int
php_gdk_pixbuf_cast_object(zval *readobj, zval *retval, int type)
{
    php_gdk_pixbuf *pixbuf = ZVAL_GET_PHP_GDK_PIXBUF(readobj);
    switch (type) {
    case _IS_BOOL:
        if (NULL==pixbuf->ptr) {
            ZVAL_FALSE(retval);
        } else {
            ZVAL_TRUE(retval);
        }
        break;
    default:
        g_print("Unsupported type in php_gdk_pixbuf_cast_object(%d)\n", type);
        ZVAL_NULL(retval);
        return FAILURE;
    }

    return SUCCESS;
}

static HashTable*
php_gdk_pixbuf_get_properties(zval *object){
    php_gdk_pixbuf  *self =  ZVAL_GET_PHP_GDK_PIXBUF(object);
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(self);
    HashTable *props = gobject->properties;
    if (props==NULL) {
        ALLOC_HASHTABLE(gobject->properties);
        props = gobject->properties;
    } else {
        // TODO: rebuild the props( update)
        return props;// Else leaks : zend_hash_next_index_insert
    }

    /*
    zend_long length = php_gdk_pixbuf_length(self);

    zend_hash_init(props, length, NULL, ZVAL_PTR_DTOR, 1);

    zval data;

    php_gdk_pixbuf *it;
    for(it=php_gdk_pixbuf_first(self); it; it = it->next){
        ZVAL_COPY(&data, &it->data);
        zend_hash_next_index_insert(props, &data);
    }
    */

    return props;
}

static HashTable*
php_gdk_pixbuf_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_gdk_pixbuf  *obj =  ZVAL_GET_PHP_GDK_PIXBUF(object);
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(obj);
    HashTable   *debug_info,
                *std_props;
    zend_string *string_key = NULL;
    zval *value;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    ZEND_HASH_FOREACH_STR_KEY_VAL(gobject->std.properties, string_key, value) {
        zend_hash_add(debug_info, string_key, value);
    } ZEND_HASH_FOREACH_END();

    /*
    zval prev; ZVAL_SET_PHP_GDK_PIXBUF(&prev, obj->prev);
    zend_hash_str_update(debug_info, "prev", sizeof("prev")-1, &prev);

    zval data; ZVAL_COPY(&data, &obj->data);
    zend_hash_str_update(debug_info, "data", sizeof("data")-1, &data);

    zval next; ZVAL_SET_PHP_GDK_PIXBUF(&next, obj->next);
    zend_hash_str_update(debug_info, "next", sizeof("next")-1, &next);
    */

    return debug_info;
}
/* }}} */

static void
php_gdk_pixbuf_unset_property(zval *object, zval *member, void **cache_slot) {
    php_gdk_pixbuf *obj = ZVAL_GET_PHP_GDK_PIXBUF(object);
    zend_string *member_str = zval_get_string(member);
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    //zend_string_release(member_str);
}

/* {{{ php_gdk_pixbuf_write_property */
static zval*
php_gdk_pixbuf_write_property(zend_object *object, zend_string *member_str, zval *value, void **cache_slot)
{
    php_gdk_pixbuf *obj = ZOBJ_TO_PHP_GDK_PIXBUF(object);
    TRACE("%s(%s)\n", __FUNCTION__, member_str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->write_property(object, member_str, value, cache_slot);

    //zend_string_release(member_str);
}
/* }}} */

static zval zval_ret;
/* {{{ gtk_read_property */
static zval*
php_gdk_pixbuf_read_property(zend_object *object, zend_string *member_str, int type, void **cache_slot, zval *rv)
{
    php_gdk_pixbuf *obj = ZOBJ_TO_PHP_GDK_PIXBUF(object);
    zval *retval;
    TRACE("%s(%s)\n", __FUNCTION__, member_str->val);

    /*
    if (zend_string_equals_literal(member_str, "next")) {
        if (NULL==obj->next) {
            ZVAL_NULL(&zval_ret);
            return &zval_ret;
        }
        ZVAL_OBJ(&zval_ret, &obj->next->std);
        return &zval_ret;
    }
    if (zend_string_equals_literal(member_str, "prev")) {
        if (NULL==obj->prev) {
            ZVAL_NULL(&zval_ret);
            return &zval_ret;
        }
        ZVAL_OBJ(&zval_ret, &obj->prev->std);
        return &zval_ret;
    }
    if (zend_string_equals_literal(member_str, "data")) {
        ZVAL_COPY(&zval_ret, &obj->data);
        return &zval_ret;
    }
    */

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    retval = std_hnd->read_property(object, member_str, type, cache_slot, rv);

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ php_gdk_pixbuf_free_object */
static void
php_gdk_pixbuf_free_object(zend_object *object)
{
    php_gdk_pixbuf *intern = ZOBJ_TO_PHP_GDK_PIXBUF(object);
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(intern);
    TRACE("php_gdk_pixbuf_free_object(\"%s\") / %d\n", intern->data.value.str->val, object->gc.refcount);

    if (gobject->ptr && G_IS_OBJECT(gobject->ptr)) {
        g_clear_object(&gobject->ptr);
    }

    if (gobject->properties!=NULL) {
        zend_hash_destroy(gobject->properties);
        efree(gobject->properties);
        gobject->properties=NULL;
    }

    zend_object_std_dtor(&gobject->std);
    //efree(intern);
}
/* }}} php_gdk_pixbuf_free_object */

static void
php_gdk_pixbuf_dtor_object(zend_object *obj) {
    php_gdk_pixbuf *intern = ZOBJ_TO_PHP_GDK_PIXBUF(obj);
    TRACE("php_gdk_pixbuf_dtor_object(\"%s\") / %d\n", intern->data.value.str->val, obj->gc.refcount);

    /*
    if (!ZVAL_IS_NULL(&intern->data)) {
        Z_TRY_DELREF_P(&intern->data);
        //zval_ptr_dtor(&intern->data);
        //g_print("zend_string: %p\n", intern->data.value.str);
        //g_print("            (%d)\n", intern->data.value.str->gc.refcount);
        //zend_string_release(intern->data.value.str);
        ZVAL_NULL(&intern->data);
    }

    if (intern->next) {
        zend_object_release(&intern->next->std);
        intern->next=NULL;
    }

    if (intern->prev!=NULL) {
        zend_object_release(&intern->prev->std);
        intern->prev=NULL;
    }
    */

}

/* {{{ php_gdk_pixbuf_create_object */
static zend_object*
php_gdk_pixbuf_create_object(zend_class_entry *class_type)
{
    php_gdk_pixbuf *intern = ecalloc(1, sizeof(php_gdk_pixbuf) + zend_object_properties_size(class_type));
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(intern);

    zend_object_std_init(&gobject->std, class_type);
    object_properties_init(&gobject->std, class_type);

    gobject->ptr = NULL;// new GObject ?
    gobject->properties = NULL;

    gobject->std.handlers = &php_gdk_pixbuf_handlers;

    TRACE("php_gdk_pixbuf_create_object(%p) / %d\n", &gobject->std, gobject->std.gc.refcount);
    return &gobject->std;
}
/* }}} php_gdk_pixbuf_create_object */

/*
static void php_gdk_pixbuf_dtor_prop_handler(zval *zv)
{
    free(Z_PTR_P(zv));
}
*/

static zend_object_handlers*
php_gdk_pixbuf_get_handlers()
{
    memcpy(&php_gdk_pixbuf_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_gdk_pixbuf_handlers.offset = PHP_GDK_PIXBUF_OFFSET;
    //php_gdk_pixbuf_handlers.clone_obj;
    //php_gdk_pixbuf_handlers.compare;
    //php_gdk_pixbuf_handlers.compare_objects;
    //php_gdk_pixbuf_handlers.get_constructor;
    php_gdk_pixbuf_handlers.dtor_obj = php_gdk_pixbuf_dtor_object;
    php_gdk_pixbuf_handlers.free_obj = php_gdk_pixbuf_free_object;
    php_gdk_pixbuf_handlers.read_property = php_gdk_pixbuf_read_property;
    php_gdk_pixbuf_handlers.write_property = php_gdk_pixbuf_write_property;
/*
    php_gdk_pixbuf_handlers.unset_property = php_gdk_pixbuf_unset_property;
    //php_gdk_pixbuf_handlers.get_property_ptr_ptr = php_gdk_pixbuf_get_property_ptr_ptr;

    php_gdk_pixbuf_handlers.get_debug_info = php_gdk_pixbuf_get_debug_info;
    php_gdk_pixbuf_handlers.get_properties = php_gdk_pixbuf_get_properties;//get_properties_for TODO php 8.0
    //php_gdk_pixbuf_handlers.set = php_gdk_pixbuf_set;
    php_gdk_pixbuf_handlers.cast_object = php_gdk_pixbuf_cast_object;

    php_gdk_pixbuf_handlers.count_elements = php_gdk_pixbuf_count_elements;
    php_gdk_pixbuf_handlers.has_dimension = php_gdk_pixbuf_has_dimension;
    php_gdk_pixbuf_handlers.read_dimension = php_gdk_pixbuf_read_dimension;
    php_gdk_pixbuf_handlers.unset_dimension = php_gdk_pixbuf_unset_dimension;
    php_gdk_pixbuf_handlers.write_dimension = php_gdk_pixbuf_write_dimension;
*/

    return &php_gdk_pixbuf_handlers;
}



/*----------------------------------------------------------------------+
| PHP_MINIT                                                            |
+----------------------------------------------------------------------*/
/*{{{ php_gdk_pixbuf_class_init */
zend_class_entry*
php_gdk_pixbuf_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gdk_pixbuf_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "GdkPixbuf", php_gdk_pixbuf_methods);
    php_gdk_pixbuf_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_gdk_pixbuf_class_entry->create_object = php_gdk_pixbuf_create_object;
    //ce->serialize;
    /*
    zend_hash_init(&php_gdk_pixbuf_prop_handlers, 0, NULL, php_gdk_pixbuf_dtor_prop_handler, 1);
    php_gdk_pixbuf_register_prop_handler(&php_gdk_pixbuf_prop_handlers, "prev", sizeof("prev")-1, php_gdk_pixbuf_read_prev, php_gdk_pixbuf_write_prev);
    php_gdk_pixbuf_register_prop_handler(&php_gdk_pixbuf_prop_handlers, "data", sizeof("data")-1, php_gdk_pixbuf_read_data, php_gdk_pixbuf_write_data);
    php_gdk_pixbuf_register_prop_handler(&php_gdk_pixbuf_prop_handlers, "next", sizeof("next")-1, php_gdk_pixbuf_read_next, php_gdk_pixbuf_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_gdk_pixbuf_prop_handlers);
    */

    return php_gdk_pixbuf_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/


/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
php_gdk_pixbuf*
php_gdk_pixbuf_create(GdkPixbuf *pixbuf) {
    zend_object *object = php_gdk_pixbuf_create_object(php_gdk_pixbuf_class_entry);
    php_gdk_pixbuf *intern = ZOBJ_TO_PHP_GDK_PIXBUF(object);
    intern->ptr = pixbuf;

    return intern;
}


php_gdk_pixbuf*
php_gdk_pixbuf_new_from_file(zend_string *filename, zval *error) {
    zend_object *obj = php_gdk_pixbuf_create_object(php_gdk_pixbuf_class_entry);
    php_gdk_pixbuf *intern = ZOBJ_TO_PHP_GDK_PIXBUF(obj);
    GError *err = NULL;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename->val, &err);
    if (err) {
        php_g_error *e = php_g_error_new(err);
        ZVAL_OBJ(error, &e->std);
        zend_object_release(obj);
        return NULL;
    }

    intern->ptr = pixbuf;

    return intern;
}



/*----------------------------------------------------------------------+
| PHP_METHOD                                                           |
+----------------------------------------------------------------------*/

/* {{{ GObject::__construct() */
PHP_METHOD(gdk_pixbuf, __construct)
{
    zval *data=NULL;

    /*
    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();
    */

    zend_object *zobj = Z_OBJ_P(getThis());
    php_gdk_pixbuf *self = ZOBJ_TO_PHP_GDK_PIXBUF(zobj);

}
/* }}} */

/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/

/* {{{ proto GObject gdk_pixbuf_show_all(GObject list, mixed data) */
PHP_FUNCTION(gdk_pixbuf_new_from_file)
{
    zval *zfilename = NULL;
    zval *zerror = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 2)
        Z_PARAM_ZVAL(zfilename)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL_EX2(zerror, 0, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    zend_string *filename = Z_TYPE_P(zfilename)==IS_STRING ? zfilename->value.str : NULL;
    php_gdk_pixbuf *pixbuf = php_gdk_pixbuf_new_from_file(filename, zerror);

    if (NULL==pixbuf) {
        RETURN_NULL();
    }

    RETURN_OBJ(&pixbuf->std);
}/* }}} */

