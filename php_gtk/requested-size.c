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

#include "requested-size.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_gtk_requested_size_class_entry;
zend_object_handlers  php_gtk_requested_size_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry php_gtk_requested_size_methods[] = {
    PHP_ME(gtk_requested_size, __construct, arginfo_gtk_requested_size___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/



/* {{{ php_gtk_requested_size_create_object */
static zend_object*
php_gtk_requested_size_create_object(zend_class_entry *class_type)
{
    php_gtk_requested_size *intern = ecalloc(1, sizeof(php_gtk_requested_size) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_gtk_requested_size_handlers;

    TRACE("php_gtk_requested_size_create_object(%p) / %d\n", &intern->std, intern->std.gc.refcount);
    return &intern->std;
}
/* }}} php_gtk_requested_size_create_object */


static void
php_gtk_requested_size_dtor_object(zend_object *obj) {
    php_gtk_requested_size *intern = ZOBJ_TO_PHP_GTK_REQUESTED_SIZE(obj);
    TRACE("php_gtk_requested_size_dtor_object(\e[1;31m\"%s\"\e[0;m) / %d\n", intern->data.value.str->val, obj->gc.refcount);


}

/* {{{ php_gtk_requested_size_free_object */
static void
php_gtk_requested_size_free_object(zend_object *object)
{
    php_gtk_requested_size *intern = ZOBJ_TO_PHP_GTK_REQUESTED_SIZE(object);
    TRACE("php_gtk_requested_size_free_object(\e[1;31m\"%s\"\e[0;m) / %d\n", intern->data.value.str->val, object->gc.refcount);

    if (intern->ptr!=NULL) {
        efree(intern->ptr);
    }
    /*if (intern->properties!=NULL) {
        zend_hash_destroy(intern->properties);
        efree(intern->properties);
        intern->properties=NULL;
    }*/

    zend_object_std_dtor(&intern->std);
    //efree(intern);
}
/* }}} php_gtk_requested_size_free_object */



//rename by binarysearch_access_properties.phtml



static void
php_gtk_requested_size_getter_data(php_gtk_requested_size *intern, zval *rvalue) {
    ZVAL_COPY(rvalue, intern->ptr->data);
}

static void
php_gtk_requested_size_setter_data(php_gtk_requested_size *intern, zval *value) {
    ZVAL_COPY(intern->ptr->data, value);
}




static void
php_gtk_requested_size_getter_minimum_size(php_gtk_requested_size *intern, zval *rvalue) {
    ZVAL_LONG(rvalue, intern->ptr->minimum_size);
}

static void
php_gtk_requested_size_setter_minimum_size(php_gtk_requested_size *intern, zval *value) {
    if (Z_TYPE_P(value)==IS_LONG)
        intern->ptr->minimum_size = value->value.lval;
    else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        int allow_errors = -1;
        zend_long lval;
        if (!strict_types && Z_TYPE_P(value)==IS_STRING
         && is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), NULL, &lval, allow_errors) ) {
            intern->ptr->minimum_size = lval;
            return;
        }
        zend_string *type = zend_zval_get_type(value);
        zend_internal_type_error(1, "Cannot assign %s to property \\gtk_requested_size::$minimum_size of type int,", type->val);
    }
}




static void
php_gtk_requested_size_getter_natural_size(php_gtk_requested_size *intern, zval *rvalue) {
    ZVAL_LONG(rvalue, intern->ptr->natural_size);
}

static void
php_gtk_requested_size_setter_natural_size(php_gtk_requested_size *intern, zval *value) {
    if (Z_TYPE_P(value)==IS_LONG)
        intern->ptr->natural_size = value->value.lval;
    else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        int allow_errors = -1;
        zend_long lval;
        if (!strict_types && Z_TYPE_P(value)==IS_STRING
         && is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), NULL, &lval, allow_errors) ) {
            intern->ptr->natural_size = lval;
            return;
        }
        zend_string *type = zend_zval_get_type(value);
        zend_internal_type_error(1, "Cannot assign %s to property \\gtk_requested_size::$natural_size of type int,", type->val);
    }
}



enum _php_gtk_requested_size_properties {
    PHP_GTK_REQUESTED_SIZE_DATA = 1,
    PHP_GTK_REQUESTED_SIZE_MINIMUM_SIZE = 2,
    PHP_GTK_REQUESTED_SIZE_NATURAL_SIZE = 3
};
//typedef enum php_gtk_requested_size_properties php_gtk_requested_size_properties;

struct PhpGtkRequestedSizeProperty {
  const char *name;
  int code;
  void (*getter) (php_gtk_requested_size *intern, zval *value);
  void (*setter) (php_gtk_requested_size *intern, zval *rvalue);
};

static const struct PhpGtkRequestedSizeProperty php_gtk_requested_size_properties[] = {
    {"data", PHP_GTK_REQUESTED_SIZE_DATA, php_gtk_requested_size_getter_data, php_gtk_requested_size_setter_data},
    {"minimum_size", PHP_GTK_REQUESTED_SIZE_MINIMUM_SIZE, php_gtk_requested_size_getter_minimum_size, php_gtk_requested_size_setter_minimum_size},
    {"natural_size", PHP_GTK_REQUESTED_SIZE_NATURAL_SIZE, php_gtk_requested_size_getter_natural_size, php_gtk_requested_size_setter_natural_size}
};


const struct PhpGtkRequestedSizeProperty*
php_gtk_requested_size_properties_lookup (const char *str, size_t len)
{
    if (len == 4) {
        //case: "data"
        if (str[0] == 'd' && str[1] == 'a' && str[2] == 't' && str[3] == 'a'
        ) {
            //case: "data"
            return &php_gtk_requested_size_properties[0];
        } else {
            // NOTFOUND
        }
    } else if (len == 12) {
        //case: "minimum_size", "natural_size"
        if (str[0] == 'm' && str[1] == 'i' && str[2] == 'n' && str[3] == 'i'
         && str[4] == 'm' && str[5] == 'u' && str[6] == 'm' && str[7] == '_'
         && str[8] == 's' && str[9] == 'i' && str[10] == 'z' && str[11] == 'e'
        ) {
            //case: "minimum_size"
            return &php_gtk_requested_size_properties[1];
        } else if (str[0] == 'n' && str[1] == 'a' && str[2] == 't' && str[3] == 'u'
         && str[4] == 'r' && str[5] == 'a' && str[6] == 'l' && str[7] == '_'
         && str[8] == 's' && str[9] == 'i' && str[10] == 'z' && str[11] == 'e'
        ) {
            //case: "natural_size"
            return &php_gtk_requested_size_properties[2];
        } else {
            // NOTFOUND
        }
    } else {
        // NOTFOUND
    }
    return 0;
}


/* {{{ gtk_read_property */
static zval*
php_gtk_requested_size_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_gtk_requested_size *intern = ZVAL_GET_PHP_GTK_REQUESTED_SIZE(object);
    zend_string *member_str = member->value.str;

    struct PhpGtkRequestedSizeProperty *cmd = php_gtk_requested_size_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        cmd->getter(intern, rv);
    } else {
        // property not found
    }

    return rv;
}
/* }}} */

/* {{{ php_gtk_requested_size_write_property */
static void
php_gtk_requested_size_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_gtk_requested_size *intern = ZVAL_GET_PHP_GTK_REQUESTED_SIZE(object);
    zend_string *member_str = member->value.str;

    struct PhpGtkRequestedSizeProperty *cmd = php_gtk_requested_size_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        cmd->setter(intern, value);
    } else {
        // property not found
    }
}
/* }}} */

static HashTable*
php_gtk_requested_size_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_gtk_requested_size  *obj =  ZVAL_GET_PHP_GTK_REQUESTED_SIZE(object);
    HashTable   *debug_info,
    *std_props;
    zend_string *string_key = NULL;
    zval *value;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    zval zdata; if (obj->ptr->data==NULL) ZVAL_NULL(&zdata); else ZVAL_COPY(&zdata, obj->ptr->data);
    zend_hash_str_update(debug_info, "data", sizeof("data")-1, &zdata);

    zval zminimum_size; ZVAL_LONG(&zminimum_size, obj->ptr->minimum_size);
    zend_hash_str_update(debug_info, "minimum_size", sizeof("minimum_size")-1, &zminimum_size);

    zval znatural_size; ZVAL_LONG(&znatural_size, obj->ptr->natural_size);
    zend_hash_str_update(debug_info, "natural_size", sizeof("natural_size")-1, &znatural_size);


    return debug_info;
}
/* }}} */






static void
php_gtk_requested_size_unset_property(zval *object, zval *member, void **cache_slot) {
    php_gtk_requested_size *obj = ZVAL_GET_PHP_GTK_REQUESTED_SIZE(object);
    zend_string *member_str = zval_get_string(member);
    php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}


static HashTable*
php_gtk_requested_size_get_properties(zval *object){
    php_gtk_requested_size  *self =  ZVAL_GET_PHP_GTK_REQUESTED_SIZE(object);
    HashTable *props = NULL;
#if 0
    HashTable *props = self->properties;
    if (props==NULL) {
        ALLOC_HASHTABLE(self->properties);
        props = self->properties;
    } else {
        // TODO: rebuild the props( update)
        return props;// Else leaks : zend_hash_next_index_insert
    }

    zend_long length = php_gtk_requested_size_length(self);

    zend_hash_init(props, length, NULL, ZVAL_PTR_DTOR, 1);

    zval data;

    php_gtk_requested_size *it;
    for(it=php_gtk_requested_size_first(self); it; it = it->child){
        ZVAL_COPY(&data, &it->data);
        zend_hash_next_index_insert(props, &data);
    }
#endif
    return props;
}


static int
php_gtk_requested_size_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}


/* updates *count to hold the number of elements present and returns SUCCESS.
* Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_gtk_requested_size_count_elements(zval *object, zend_long *count) {

    *count = 0;//php_gtk_requested_size_length(ZVAL_GET_PHP_GTK_REQUESTED_SIZE(object));

    return SUCCESS;
}

static int
php_gtk_requested_size_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

static zval*
php_gtk_requested_size_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
    return NULL;
    }
#if 0
    php_gtk_requested_size *intern = ZVAL_GET_PHP_GTK_REQUESTED_SIZE(object);
    php_gtk_requested_size *list;
    void *cache=NULL;

    if (Z_TYPE_P(offset)==IS_LONG) {
        list = php_gtk_requested_size_nth(intern, offset->value.lval);
        if (list) {
            ZVAL_COPY(rv, &list->data);
        } else {
            ZVAL_NULL(rv);
            zend_error(E_USER_WARNING, "Undefined offset: %d", offset->value.lval);
        }
        return rv;
    } else if (Z_TYPE_P(offset)==IS_STRING) {
        return php_gtk_requested_size_read_property(object, offset, type, &cache, rv);
    } else {
        // error
    }
#endif
    return rv;
} /* }}} end php_g_hash_table_read_dimension */


static void
php_gtk_requested_size_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_gtk_requested_size_write_property(object, &member, value, &cache);
}

static void
php_gtk_requested_size_unset_dimension(zval *object, zval *offset) {
    //php_g_list *list = ZVAL_GET_PHP_G_LIST(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
    // @TODO
    //zend_hash_index_del(list->prop_handler, );
    // php_g_list
    break;
    case IS_STRING:
        php_gtk_requested_size_unset_property(object, offset, &cache);
    break;
    default:
    break;
    }
}


static zend_object_handlers*
php_gtk_requested_size_get_handlers()
{
    memcpy(&php_gtk_requested_size_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_gtk_requested_size_handlers.offset = PHP_GTK_REQUESTED_SIZE_OFFSET;
    //php_gtk_requested_size_handlers.clone_obj;
    //php_gtk_requested_size_handlers.compare;
    //php_gtk_requested_size_handlers.compare_objects;
    //php_gtk_requested_size_handlers.get_constructor;
    php_gtk_requested_size_handlers.dtor_obj = php_gtk_requested_size_dtor_object;
    php_gtk_requested_size_handlers.free_obj = php_gtk_requested_size_free_object;
    php_gtk_requested_size_handlers.read_property = php_gtk_requested_size_read_property;
    php_gtk_requested_size_handlers.write_property = php_gtk_requested_size_write_property;
    php_gtk_requested_size_handlers.unset_property = php_gtk_requested_size_unset_property;
    //php_gtk_requested_size_handlers.get_property_ptr_ptr = php_gtk_requested_size_get_property_ptr_ptr;

    php_gtk_requested_size_handlers.get_debug_info = php_gtk_requested_size_get_debug_info;
    php_gtk_requested_size_handlers.get_properties = php_gtk_requested_size_get_properties;//get_properties_for TODO php 8.0
    //php_gtk_requested_size_handlers.set = php_gtk_requested_size_set;
    php_gtk_requested_size_handlers.cast_object = php_gtk_requested_size_cast_object;

    php_gtk_requested_size_handlers.count_elements = php_gtk_requested_size_count_elements;
    php_gtk_requested_size_handlers.has_dimension = php_gtk_requested_size_has_dimension;
    php_gtk_requested_size_handlers.read_dimension = php_gtk_requested_size_read_dimension;
    php_gtk_requested_size_handlers.unset_dimension = php_gtk_requested_size_unset_dimension;
    php_gtk_requested_size_handlers.write_dimension = php_gtk_requested_size_write_dimension;


    return &php_gtk_requested_size_handlers;
}



/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

/*{{{ php_gtk_requested_size_class_init */
zend_class_entry*
php_gtk_requested_size_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gtk_requested_size_get_handlers();
    //INIT_NS_CLASS_ENTRY((*ce), "Gnome\\G", "List", php_gtk_requested_size_methods);
    INIT_CLASS_ENTRY((*container_ce), "GtkRequestedSize", php_gtk_requested_size_methods);
    php_gtk_requested_size_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_gtk_requested_size_class_entry->create_object = php_gtk_requested_size_create_object;
    //ce->serialize;
    /*
    zend_hash_init(&php_gtk_requested_size_prop_handlers, 0, NULL, php_gtk_requested_size_dtor_prop_handler, 1);
    php_gtk_requested_size_register_prop_handler(&php_gtk_requested_size_prop_handlers, "prev", sizeof("prev")-1, php_gtk_requested_size_read_prev, php_gtk_requested_size_write_prev);
    php_gtk_requested_size_register_prop_handler(&php_gtk_requested_size_prop_handlers, "data", sizeof("data")-1, php_gtk_requested_size_read_data, php_gtk_requested_size_write_data);
    php_gtk_requested_size_register_prop_handler(&php_gtk_requested_size_prop_handlers, "next", sizeof("next")-1, php_gtk_requested_size_read_next, php_gtk_requested_size_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_gtk_requested_size_prop_handlers);
    */

    return php_gtk_requested_size_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/



/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

/* {{{ GtkRequestedSize::__construct() */
PHP_METHOD(gtk_requested_size, __construct)
{
    zval *data=NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    zend_object *zobj = Z_OBJ_P(getThis());
    php_gtk_requested_size *self = ZOBJ_TO_PHP_GTK_REQUESTED_SIZE(zobj);

    self->ptr = emalloc(sizeof(GtkRequestedSize));
    self->ptr->data=NULL;
    self->ptr->minimum_size=0;
    self->ptr->natural_size=0;

}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/


