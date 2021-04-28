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

#include "requisition.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_gtk_requisition_class_entry;
zend_object_handlers  php_gtk_requisition_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry php_gtk_requisition_methods[] = {
    PHP_ME(gtk_requisition, __construct, arginfo_gtk_requisition___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/



/* {{{ php_gtk_requisition_create_object */
static zend_object*
php_gtk_requisition_create_object(zend_class_entry *class_type)
{
    php_gtk_requisition *intern = ecalloc(1, sizeof(php_gtk_requisition) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_gtk_requisition_handlers;

    TRACE("php_gtk_requisition_create_object(%p) / %d\n", &intern->std, intern->std.gc.refcount);
    return &intern->std;
}
/* }}} php_gtk_requisition_create_object */


static void
php_gtk_requisition_dtor_object(zend_object *obj) {
    php_gtk_requisition *intern = ZOBJ_TO_PHP_GTK_REQUISITION(obj);

}

/* {{{ php_gtk_requisition_free_object */
static void
php_gtk_requisition_free_object(zend_object *object)
{
    php_gtk_requisition *intern = ZOBJ_TO_PHP_GTK_REQUISITION(object);
    TRACE("php_gtk_requisition_free_object(\e[1;31m\"%s\"\e[0;m) / %d\n", intern->data.value.str->val, object->gc.refcount);

    if (intern->ptr!=NULL) {
        efree(intern->ptr);
    }
    /* Used for print_r((array)my_class); get_properties
    if (intern->properties!=NULL) {
        zend_hash_destroy(intern->properties);
        efree(intern->properties);
        intern->properties=NULL;
    }
    */

    zend_object_std_dtor(&intern->std);
    //efree(intern);
}
/* }}} php_gtk_requisition_free_object */



//rename by binarysearch_access_properties.phtml



static void
php_gtk_requisition_getter_width(php_gtk_requisition *intern, zval *rvalue) {
    ZVAL_LONG(rvalue, intern->ptr->width);
}

static void
php_gtk_requisition_setter_width(php_gtk_requisition *intern, zval *value) {
    if (Z_TYPE_P(value)==IS_LONG)
        intern->ptr->width = value->value.lval;
    else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        int allow_errors = -1;
        zend_long lval;
        if (!strict_types && Z_TYPE_P(value)==IS_STRING
         && is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), NULL, &lval, allow_errors) ) {
            intern->ptr->width = lval;
            return;
        }
        zend_string *type = zend_zval_get_type(value);
        zend_internal_type_error(1, "Cannot assign %s to property \\gtk_requisition::$width of type int,", type->val);
    }
}




static void
php_gtk_requisition_getter_height(php_gtk_requisition *intern, zval *rvalue) {
    ZVAL_LONG(rvalue, intern->ptr->height);
}

static void
php_gtk_requisition_setter_height(php_gtk_requisition *intern, zval *value) {
    if (Z_TYPE_P(value)==IS_LONG)
        intern->ptr->height = value->value.lval;
    else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        int allow_errors = -1;
        zend_long lval;
        if (!strict_types && Z_TYPE_P(value)==IS_STRING
         && is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), NULL, &lval, allow_errors) ) {
            intern->ptr->height = lval;
            return;
        }
        zend_string *type = zend_zval_get_type(value);
        zend_internal_type_error(1, "Cannot assign %s to property \\gtk_requisition::$height of type int,", type->val);
    }
}



enum _php_gtk_requisition_properties {
    PHP_GTK_REQUISITION_WIDTH = 1,
    PHP_GTK_REQUISITION_HEIGHT = 2
};
//typedef enum php_gtk_requisition_properties php_gtk_requisition_properties;

struct PhpGtkRequisitionProperty {
  const char *name;
  int code;
  void (*getter) (php_gtk_requisition *intern, zval *value);
  void (*setter) (php_gtk_requisition *intern, zval *rvalue);
};

static const struct PhpGtkRequisitionProperty php_gtk_requisition_properties[] = {
    {"width", PHP_GTK_REQUISITION_WIDTH, php_gtk_requisition_getter_width, php_gtk_requisition_setter_width},
    {"height", PHP_GTK_REQUISITION_HEIGHT, php_gtk_requisition_getter_height, php_gtk_requisition_setter_height}
};

const struct PhpGtkRequisitionProperty*
php_gtk_requisition_properties_lookup (const char *str, size_t len)
{
    if (len == 5) {
        //case: "width"
        if (str[0] == 'w' && str[1] == 'i' && str[2] == 'd' && str[3] == 't'
         && str[4] == 'h') {
            //case: "width"
            return &php_gtk_requisition_properties[0];
        } else {
            // NOTFOUND
        }
    } else if (len == 6) {
        //case: "height"
        if (str[0] == 'h' && str[1] == 'e' && str[2] == 'i' && str[3] == 'g'
         && str[4] == 'h' && str[5] == 't') {
            //case: "height"
            return &php_gtk_requisition_properties[1];
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
php_gtk_requisition_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_gtk_requisition *intern = ZVAL_GET_PHP_GTK_REQUISITION(object);
    zend_string *member_str = member->value.str;

    struct PhpGtkRequisitionProperty *cmd = php_gtk_requisition_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        cmd->getter(intern, rv);
    } else {
        // property not found
    }

    return rv;
}
/* }}} */

/* {{{ php_gtk_requisition_write_property */
static void
php_gtk_requisition_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_gtk_requisition *intern = ZVAL_GET_PHP_GTK_REQUISITION(object);
    zend_string *member_str = member->value.str;

    struct PhpGtkRequisitionProperty *cmd = php_gtk_requisition_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        cmd->setter(intern, value);
    } else {
        // property not found
    }
}
/* }}} */

static HashTable*
php_gtk_requisition_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_gtk_requisition  *obj =  ZVAL_GET_PHP_GTK_REQUISITION(object);
    HashTable   *debug_info,
    *std_props;
    zend_string *string_key = NULL;
    zval *value;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    zval zwidth; ZVAL_LONG(&zwidth, obj->ptr->width);
    zend_hash_str_update(debug_info, "width", sizeof("width")-1, &zwidth);

    zval zheight; ZVAL_LONG(&zheight, obj->ptr->height);
    zend_hash_str_update(debug_info, "height", sizeof("height")-1, &zheight);


    return debug_info;
}
/* }}} */





static void
php_gtk_requisition_unset_property(zval *object, zval *member, void **cache_slot) {
    php_gtk_requisition *obj = ZVAL_GET_PHP_GTK_REQUISITION(object);
    zend_string *member_str = zval_get_string(member);
    php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}


static HashTable*
php_gtk_requisition_get_properties(zval *object){
    php_gtk_requisition  *self =  ZVAL_GET_PHP_GTK_REQUISITION(object);
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

    zend_long length = php_gtk_requisition_length(self);

    zend_hash_init(props, length, NULL, ZVAL_PTR_DTOR, 1);

    zval data;

    php_gtk_requisition *it;
    for(it=php_gtk_requisition_first(self); it; it = it->child){
        ZVAL_COPY(&data, &it->data);
        zend_hash_next_index_insert(props, &data);
    }
#endif
    return props;
}


static int
php_gtk_requisition_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}


/* updates *count to hold the number of elements present and returns SUCCESS.
* Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_gtk_requisition_count_elements(zval *object, zend_long *count) {

    *count = 0;//php_gtk_requisition_length(ZVAL_GET_PHP_GTK_REQUISITION(object));

    return SUCCESS;
}

static int
php_gtk_requisition_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

static zval*
php_gtk_requisition_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
    return NULL;
    }
#if 0
    php_gtk_requisition *intern = ZVAL_GET_PHP_GTK_REQUISITION(object);
    php_gtk_requisition *list;
    void *cache=NULL;

    if (Z_TYPE_P(offset)==IS_LONG) {
        list = php_gtk_requisition_nth(intern, offset->value.lval);
        if (list) {
            ZVAL_COPY(rv, &list->data);
        } else {
            ZVAL_NULL(rv);
            zend_error(E_USER_WARNING, "Undefined offset: %d", offset->value.lval);
        }
        return rv;
    } else if (Z_TYPE_P(offset)==IS_STRING) {
        return php_gtk_requisition_read_property(object, offset, type, &cache, rv);
    } else {
        // error
    }
#endif
    return rv;
} /* }}} end php_g_hash_table_read_dimension */


static void
php_gtk_requisition_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_gtk_requisition_write_property(object, &member, value, &cache);
}

static void
php_gtk_requisition_unset_dimension(zval *object, zval *offset) {
    //php_g_list *list = ZVAL_GET_PHP_G_LIST(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
    // @TODO
    //zend_hash_index_del(list->prop_handler, );
    // php_g_list
    break;
    case IS_STRING:
        php_gtk_requisition_unset_property(object, offset, &cache);
    break;
    default:
    break;
    }
}


static zend_object_handlers*
php_gtk_requisition_get_handlers()
{
    memcpy(&php_gtk_requisition_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_gtk_requisition_handlers.offset = PHP_GTK_REQUISITION_OFFSET;
    //php_gtk_requisition_handlers.clone_obj;
    //php_gtk_requisition_handlers.compare;
    //php_gtk_requisition_handlers.compare_objects;
    //php_gtk_requisition_handlers.get_constructor;
    php_gtk_requisition_handlers.dtor_obj = php_gtk_requisition_dtor_object;
    php_gtk_requisition_handlers.free_obj = php_gtk_requisition_free_object;
    php_gtk_requisition_handlers.read_property = php_gtk_requisition_read_property;
    php_gtk_requisition_handlers.write_property = php_gtk_requisition_write_property;
    php_gtk_requisition_handlers.unset_property = php_gtk_requisition_unset_property;
    //php_gtk_requisition_handlers.get_property_ptr_ptr = php_gtk_requisition_get_property_ptr_ptr;

    php_gtk_requisition_handlers.get_debug_info = php_gtk_requisition_get_debug_info;
    php_gtk_requisition_handlers.get_properties = php_gtk_requisition_get_properties;//get_properties_for TODO php 8.0
    //php_gtk_requisition_handlers.set = php_gtk_requisition_set;
    php_gtk_requisition_handlers.cast_object = php_gtk_requisition_cast_object;

    php_gtk_requisition_handlers.count_elements = php_gtk_requisition_count_elements;
    php_gtk_requisition_handlers.has_dimension = php_gtk_requisition_has_dimension;
    php_gtk_requisition_handlers.read_dimension = php_gtk_requisition_read_dimension;
    php_gtk_requisition_handlers.unset_dimension = php_gtk_requisition_unset_dimension;
    php_gtk_requisition_handlers.write_dimension = php_gtk_requisition_write_dimension;


    return &php_gtk_requisition_handlers;
}



/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

/*{{{ php_gtk_requisition_class_init */
zend_class_entry*
php_gtk_requisition_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gtk_requisition_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "GtkRequisition", php_gtk_requisition_methods);
    php_gtk_requisition_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_gtk_requisition_class_entry->create_object = php_gtk_requisition_create_object;
    //ce->serialize;
    /*
    zend_hash_init(&php_gtk_requisition_prop_handlers, 0, NULL, php_gtk_requisition_dtor_prop_handler, 1);
    php_gtk_requisition_register_prop_handler(&php_gtk_requisition_prop_handlers, "prev", sizeof("prev")-1, php_gtk_requisition_read_prev, php_gtk_requisition_write_prev);
    php_gtk_requisition_register_prop_handler(&php_gtk_requisition_prop_handlers, "data", sizeof("data")-1, php_gtk_requisition_read_data, php_gtk_requisition_write_data);
    php_gtk_requisition_register_prop_handler(&php_gtk_requisition_prop_handlers, "next", sizeof("next")-1, php_gtk_requisition_read_next, php_gtk_requisition_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_gtk_requisition_prop_handlers);
    */

    return php_gtk_requisition_class_entry;
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

/* {{{ GtkRequisition::__construct() */
PHP_METHOD(gtk_requisition, __construct)
{
    zval *data=NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    zend_object *zobj = Z_OBJ_P(getThis());
    php_gtk_requisition *self = ZOBJ_TO_PHP_GTK_REQUISITION(zobj);

    self->ptr = emalloc(sizeof(GtkRequisition));
    self->ptr->height = 0;
    self->ptr->width = 0;

}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/


