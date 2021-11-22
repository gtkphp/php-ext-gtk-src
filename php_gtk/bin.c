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

#include <gtk/gtk.h>
#include "php_gtk.h"
#include "php_gobject/type.h"
#include "php_gobject/object.h"
#include "php_gobject/object-extends.h"

#include "widget.h"
#include "widget-extends.h"
#include "container.h"
#include "bin.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_gtk_bin_class_entry;
//HashTable             php_gtk_bin_prop_handlers;
zend_object_handlers  php_gtk_bin_handlers;

PHP_GOBJECT_DEFINE_TYPE(PhpGtkBin, php_gtk_bin, GTK_TYPE_BIN)

void php_gtk_bin_init(PhpGtkBin *widget) {

}
//static void php_gtk_bin_class_finalize(PhpGtkBinClass *klass);
void php_gtk_bin_class_init(PhpGtkBinClass *klass) {

}

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry php_gtk_bin_methods[] = {
    PHP_ME(gtk_bin, __construct, arginfo_gtk_bin___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/
static void  php_gtk_bin_unset_property(zval *object, zval *member, void **cache_slot);
static zval *php_gtk_bin_write_property(zend_object *object, zend_string *member_str, zval *value, void **cache_slot);
static zval* php_gtk_bin_read_property(zend_object *object, zend_string *member_str, int type, void **cache_slot, zval *rv);
static char* php_gtk_bin_dump(php_gtk_bin *list, int tab);

static void
php_gtk_bin_unset_dimension(zval *object, zval *offset) {
    //php_gobject *list = ZVAL_GET_PHP_GTK_BIN(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
        // @TODO
        //zend_hash_index_del(list->prop_handler, );
        // php_gobject
        break;
    case IS_STRING:
        php_gtk_bin_unset_property(object, offset, &cache);
        break;
    default:
        break;
    }
}

static void
php_gtk_bin_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_gtk_bin_write_property(object, &member, value, &cache);
}

static zval*
php_gtk_bin_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
        return NULL;
    }

    php_gtk_bin *intern = ZVAL_GET_PHP_GTK_BIN(object);
    php_gtk_bin *list;
    void *cache=NULL;

    if (Z_TYPE_P(offset)==IS_LONG) {
        ZVAL_NULL(rv);
        return rv;
    } else if (Z_TYPE_P(offset)==IS_STRING) {
        return php_gtk_bin_read_property(object, offset, type, &cache, rv);
    } else {
        // error
    }

    return rv;
} /* }}} end php_g_hash_table_read_dimension */

static int
php_gtk_bin_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

/* updates *count to hold the number of elements present and returns SUCCESS.
 * Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_gtk_bin_count_elements(zval *object, zend_long *count) {

    *count = 0;

    return SUCCESS;
}

static int
php_gtk_bin_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}

static HashTable*
php_gtk_bin_get_properties(zval *object){
    php_gtk_bin  *self =  ZVAL_GET_PHP_GTK_BIN(object);
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
    zend_long length = php_gtk_bin_length(self);

    zend_hash_init(props, length, NULL, ZVAL_PTR_DTOR, 1);

    zval data;

    php_gtk_bin *it;
    for(it=php_gtk_bin_first(self); it; it = it->next){
        ZVAL_COPY(&data, &it->data);
        zend_hash_next_index_insert(props, &data);
    }
    */

    return props;
}

static HashTable*
php_gtk_bin_get_debug_info(zend_object *object, int *is_temp) /* {{{ */
{
    php_gtk_bin  *obj =  ZOBJ_TO_PHP_GTK_BIN(object);
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
    zval prev; ZVAL_SET_PHP_GTK_BIN(&prev, obj->prev);
    zend_hash_str_update(debug_info, "prev", sizeof("prev")-1, &prev);

    zval data; ZVAL_COPY(&data, &obj->data);
    zend_hash_str_update(debug_info, "data", sizeof("data")-1, &data);

    zval next; ZVAL_SET_PHP_GTK_BIN(&next, obj->next);
    zend_hash_str_update(debug_info, "next", sizeof("next")-1, &next);
    */

    return debug_info;
}
/* }}} */

static void
php_gtk_bin_unset_property(zval *object, zval *member, void **cache_slot) {
    php_gtk_bin *obj = ZVAL_GET_PHP_GTK_BIN(object);
    zend_string *member_str = zval_get_string(member);
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}

/* {{{ php_gtk_bin_write_property */
static zval *php_gtk_bin_write_property(zend_object *object, zend_string *member_str, zval *value, void **cache_slot)
{
    php_gtk_bin *obj = ZOBJ_TO_PHP_GTK_BIN(object);
    TRACE("%s(%s)\n", __FUNCTION__, member_str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    return std_hnd->write_property(object, member_str, value, cache_slot);

    //zend_string_release(member_str);
}
/* }}} */

static zval zval_ret;
/* {{{ gtk_read_property */
static zval*
php_gtk_bin_read_property(zend_object *object, zend_string *member_str, int type, void **cache_slot, zval *rv)
{
    php_gtk_bin *obj = ZOBJ_TO_PHP_GTK_BIN(object);
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

    //zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ php_gtk_bin_free_object */
static void
php_gtk_bin_free_object(zend_object *object)
{
    php_gtk_bin *intern = ZOBJ_TO_PHP_GTK_BIN(object);
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(intern);
    TRACE("php_gtk_bin_free_object(\"%s\") / %d\n", intern->data.value.str->val, object->gc.refcount);

    if (gobject->ptr) {
        //g_object_unref(gobject->ptr);
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
/* }}} php_gtk_bin_free_object */

static void
php_gtk_bin_dtor_object(zend_object *obj) {
    php_gtk_bin *intern = ZOBJ_TO_PHP_GTK_BIN(obj);
    TRACE("php_gtk_bin_dtor_object(\"%s\") / %d\n", intern->data.value.str->val, obj->gc.refcount);

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

/* {{{ php_gtk_bin_create_object */
static zend_object*
php_gtk_bin_create_object(zend_class_entry *class_type)
{
    php_gtk_bin *intern = zend_object_alloc(sizeof(php_gtk_bin), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->properties = NULL;

    intern->std.handlers = &php_gtk_bin_handlers;

    //GType type = php_gtk_widget_get_type(class_type);
    //gobject->ptr = php_gtk_widget_new(type, NULL);
    //gobject->ptr = php_gtk_widget_factory(intern);
    intern->ptr = php_gtk_bin_extends(intern);// after handlers

    TRACE("php_gtk_bin_create_object(%p) / %d\n", &intern->std, intern->std.gc.refcount);
    return &intern->std;
}
/* }}} php_gtk_bin_create_object */

/*
static void php_gtk_bin_dtor_prop_handler(zval *zv)
{
    free(Z_PTR_P(zv));
}
*/

static zend_object_handlers*
php_gtk_bin_get_handlers()
{
    memcpy(&php_gtk_bin_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_gtk_bin_handlers.offset = PHP_GTK_BIN_OFFSET;
    //php_gtk_bin_handlers.clone_obj;
    //php_gtk_bin_handlers.compare;
    //php_gtk_bin_handlers.compare_objects;
    //php_gtk_bin_handlers.get_constructor;
    php_gtk_bin_handlers.dtor_obj = php_gtk_bin_dtor_object;
    php_gtk_bin_handlers.free_obj = php_gtk_bin_free_object;
    php_gtk_bin_handlers.read_property = php_gtk_bin_read_property;
    php_gtk_bin_handlers.write_property = php_gtk_bin_write_property;
    //php_gtk_bin_handlers.unset_property = php_gtk_bin_unset_property;
    //php_gtk_bin_handlers.get_property_ptr_ptr = php_gtk_bin_get_property_ptr_ptr;
    php_gtk_bin_handlers.get_debug_info = php_gtk_bin_get_debug_info;

/*
    php_gtk_bin_handlers.get_properties = php_gtk_bin_get_properties;//get_properties_for TODO php 8.0
    //php_gtk_bin_handlers.set = php_gtk_bin_set;
    php_gtk_bin_handlers.cast_object = php_gtk_bin_cast_object;

    php_gtk_bin_handlers.count_elements = php_gtk_bin_count_elements;
    php_gtk_bin_handlers.has_dimension = php_gtk_bin_has_dimension;
    php_gtk_bin_handlers.read_dimension = php_gtk_bin_read_dimension;
    php_gtk_bin_handlers.unset_dimension = php_gtk_bin_unset_dimension;
    php_gtk_bin_handlers.write_dimension = php_gtk_bin_write_dimension;
*/

    return &php_gtk_bin_handlers;
}



/*----------------------------------------------------------------------+
| PHP_MINIT                                                            |
+----------------------------------------------------------------------*/
/*{{{ php_gtk_bin_class_init */
zend_class_entry*
php_gtk_bin_class_minit(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gtk_bin_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "GtkBin", php_gtk_bin_methods);
    php_gtk_bin_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_gtk_bin_class_entry->create_object = php_gtk_bin_create_object;
    //php_gtk_bin_class_entry->ce_flags = ZEND_ACC_PUBLIC;ERROR!!!
    php_gtk_bin_class_entry->ce_flags |= ZEND_ACC_ABSTRACT;

    //ce->serialize;
    /*
    zend_hash_init(&php_gtk_bin_prop_handlers, 0, NULL, php_gtk_bin_dtor_prop_handler, 1);
    php_gtk_bin_register_prop_handler(&php_gtk_bin_prop_handlers, "prev", sizeof("prev")-1, php_gtk_bin_read_prev, php_gtk_bin_write_prev);
    php_gtk_bin_register_prop_handler(&php_gtk_bin_prop_handlers, "data", sizeof("data")-1, php_gtk_bin_read_data, php_gtk_bin_write_data);
    php_gtk_bin_register_prop_handler(&php_gtk_bin_prop_handlers, "next", sizeof("next")-1, php_gtk_bin_read_next, php_gtk_bin_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_gtk_bin_prop_handlers);
    */

    return php_gtk_bin_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/


/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
void
php_gtk_bin_add(php_gtk_bin *list, zval *data) {
    zend_object *new_std = php_gtk_bin_create_object(php_gtk_bin_class_entry);
    php_gtk_bin *new_list = ZOBJ_TO_PHP_GTK_BIN(new_std);

}



/*----------------------------------------------------------------------+
| PHP_METHOD                                                           |
+----------------------------------------------------------------------*/

/* {{{ GObject::__construct() */
PHP_METHOD(gtk_bin, __construct)
{

    zend_object *zobj = Z_OBJ_P(getThis());
    php_gtk_bin *self = ZOBJ_TO_PHP_GTK_BIN(zobj);

}
/* }}} */

/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/

/* {{{ proto GObject gtk_bin_add(GObject list, mixed data) */
PHP_FUNCTION(gtk_bin_add)
{
    zval *container = NULL;
    zval *widget    = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(container)
        Z_PARAM_ZVAL(widget)
    ZEND_PARSE_PARAMETERS_END();


}/* }}} */
