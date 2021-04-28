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

#include "rectangle.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_gdk_rectangle_class_entry;
zend_object_handlers  php_gdk_rectangle_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry php_gdk_rectangle_methods[] = {
    PHP_ME(gdk_rectangle, __construct, arginfo_gdk_rectangle___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/



/* {{{ php_gdk_rectangle_create_object */
static zend_object*
php_gdk_rectangle_create_object(zend_class_entry *class_type)
{
    php_gdk_rectangle *intern = ecalloc(1, sizeof(php_gdk_rectangle) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_gdk_rectangle_handlers;

    TRACE("php_gdk_rectangle_create_object(%p) / %d\n", &intern->std, intern->std.gc.refcount);
    return &intern->std;
}
/* }}} php_gdk_rectangle_create_object */


static void
php_gdk_rectangle_dtor_object(zend_object *obj) {
    php_gdk_rectangle *intern = ZOBJ_TO_PHP_GDK_RECTANGLE(obj);

}

/* {{{ php_gdk_rectangle_free_object */
static void
php_gdk_rectangle_free_object(zend_object *object)
{
    php_gdk_rectangle *intern = ZOBJ_TO_PHP_GDK_RECTANGLE(object);
    TRACE("php_gdk_rectangle_free_object(\e[1;31m\"%s\"\e[0;m) / %d\n", intern->data.value.str->val, object->gc.refcount);

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
/* }}} php_gdk_rectangle_free_object */



//rename by binarysearch_access_properties.phtml



static void
php_gdk_rectangle_getter_x(php_gdk_rectangle *intern, zval *rvalue) {
    ZVAL_LONG(rvalue, intern->ptr->x);
}

static void
php_gdk_rectangle_setter_x(php_gdk_rectangle *intern, zval *value) {
    if (Z_TYPE_P(value)==IS_LONG)
        intern->ptr->x = value->value.lval;
    else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        int allow_errors = -1;
        zend_long lval;
        if (!strict_types && Z_TYPE_P(value)==IS_STRING
         && is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), NULL, &lval, allow_errors) ) {
            intern->ptr->x = lval;
            return;
        }
        zend_string *type = zend_zval_get_type(value);
        zend_internal_type_error(1, "Cannot assign %s to property \\gdk_rectangle::$x of type int,", type->val);
    }
}




static void
php_gdk_rectangle_getter_y(php_gdk_rectangle *intern, zval *rvalue) {
    ZVAL_LONG(rvalue, intern->ptr->y);
}

static void
php_gdk_rectangle_setter_y(php_gdk_rectangle *intern, zval *value) {
    if (Z_TYPE_P(value)==IS_LONG)
        intern->ptr->y = value->value.lval;
    else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        int allow_errors = -1;
        zend_long lval;
        if (!strict_types && Z_TYPE_P(value)==IS_STRING
         && is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), NULL, &lval, allow_errors) ) {
            intern->ptr->y = lval;
            return;
        }
        zend_string *type = zend_zval_get_type(value);
        zend_internal_type_error(1, "Cannot assign %s to property \\gdk_rectangle::$y of type int,", type->val);
    }
}




static void
php_gdk_rectangle_getter_width(php_gdk_rectangle *intern, zval *rvalue) {
    ZVAL_LONG(rvalue, intern->ptr->width);
}

static void
php_gdk_rectangle_setter_width(php_gdk_rectangle *intern, zval *value) {
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
        zend_internal_type_error(1, "Cannot assign %s to property \\gdk_rectangle::$width of type int,", type->val);
    }
}




static void
php_gdk_rectangle_getter_height(php_gdk_rectangle *intern, zval *rvalue) {
    ZVAL_LONG(rvalue, intern->ptr->height);
}

static void
php_gdk_rectangle_setter_height(php_gdk_rectangle *intern, zval *value) {
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
        zend_internal_type_error(1, "Cannot assign %s to property \\gdk_rectangle::$height of type int,", type->val);
    }
}



enum _php_gdk_rectangle_properties {
    PHP_GDK_RECTANGLE_X = 1,
    PHP_GDK_RECTANGLE_Y = 2,
    PHP_GDK_RECTANGLE_WIDTH = 3,
    PHP_GDK_RECTANGLE_HEIGHT = 4
};
//typedef enum php_gdk_rectangle_properties php_gdk_rectangle_properties;

struct PhpGdkRectangleProperty {
  const char *name;
  int code;
  void (*getter) (php_gdk_rectangle *intern, zval *value);
  void (*setter) (php_gdk_rectangle *intern, zval *rvalue);
};

static const struct PhpGdkRectangleProperty php_gdk_rectangle_properties[] = {
    {"x", PHP_GDK_RECTANGLE_X, php_gdk_rectangle_getter_x, php_gdk_rectangle_setter_x},
    {"y", PHP_GDK_RECTANGLE_Y, php_gdk_rectangle_getter_y, php_gdk_rectangle_setter_y},
    {"width", PHP_GDK_RECTANGLE_WIDTH, php_gdk_rectangle_getter_width, php_gdk_rectangle_setter_width},
    {"height", PHP_GDK_RECTANGLE_HEIGHT, php_gdk_rectangle_getter_height, php_gdk_rectangle_setter_height}
};

const struct PhpGdkRectangleProperty*
php_gdk_rectangle_properties_lookup (const char *str, size_t len)
{
    if (len == 1) {
        //case: "x", "y"
        if (str[0] == 'x') {
            //case: "x"
            return &php_gdk_rectangle_properties[0];
        } else if (str[0] == 'y') {
            //case: "y"
            return &php_gdk_rectangle_properties[1];
        } else {
            // NOTFOUND
        }
    } else if (len == 5) {
        //case: "width"
        if (str[0] == 'w' && str[1] == 'i' && str[2] == 'd' && str[3] == 't'
         && str[4] == 'h') {
            //case: "width"
            return &php_gdk_rectangle_properties[2];
        } else {
            // NOTFOUND
        }
    } else if (len == 6) {
        //case: "height"
        if (str[0] == 'h' && str[1] == 'e' && str[2] == 'i' && str[3] == 'g'
         && str[4] == 'h' && str[5] == 't') {
            //case: "height"
            return &php_gdk_rectangle_properties[3];
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
php_gdk_rectangle_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_gdk_rectangle *intern = ZVAL_GET_PHP_GDK_RECTANGLE(object);
    zend_string *member_str = member->value.str;

    struct PhpGdkRectangleProperty *cmd = php_gdk_rectangle_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        cmd->getter(intern, rv);
    } else {
        // property not found
    }

    return rv;
}
/* }}} */

/* {{{ php_gdk_rectangle_write_property */
static void
php_gdk_rectangle_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_gdk_rectangle *intern = ZVAL_GET_PHP_GDK_RECTANGLE(object);
    zend_string *member_str = member->value.str;

    struct PhpGdkRectangleProperty *cmd = php_gdk_rectangle_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        cmd->setter(intern, value);
    } else {
        // property not found
    }
}
/* }}} */

static HashTable*
php_gdk_rectangle_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_gdk_rectangle  *obj =  ZVAL_GET_PHP_GDK_RECTANGLE(object);
    HashTable   *debug_info,
    *std_props;
    zend_string *string_key = NULL;
    zval *value;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    zval zx; ZVAL_LONG(&zx, obj->ptr->x);
    zend_hash_str_update(debug_info, "x", sizeof("x")-1, &zx);

    zval zy; ZVAL_LONG(&zy, obj->ptr->y);
    zend_hash_str_update(debug_info, "y", sizeof("y")-1, &zy);

    zval zwidth; ZVAL_LONG(&zwidth, obj->ptr->width);
    zend_hash_str_update(debug_info, "width", sizeof("width")-1, &zwidth);

    zval zheight; ZVAL_LONG(&zheight, obj->ptr->height);
    zend_hash_str_update(debug_info, "height", sizeof("height")-1, &zheight);


    return debug_info;
}
/* }}} */





static void
php_gdk_rectangle_unset_property(zval *object, zval *member, void **cache_slot) {
    php_gdk_rectangle *obj = ZVAL_GET_PHP_GDK_RECTANGLE(object);
    zend_string *member_str = zval_get_string(member);
    php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}


static HashTable*
php_gdk_rectangle_get_properties(zval *object){
    php_gdk_rectangle  *self =  ZVAL_GET_PHP_GDK_RECTANGLE(object);
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

    zend_long length = php_gdk_rectangle_length(self);

    zend_hash_init(props, length, NULL, ZVAL_PTR_DTOR, 1);

    zval data;

    php_gdk_rectangle *it;
    for(it=php_gdk_rectangle_first(self); it; it = it->child){
        ZVAL_COPY(&data, &it->data);
        zend_hash_next_index_insert(props, &data);
    }
#endif
    return props;
}


static int
php_gdk_rectangle_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}


/* updates *count to hold the number of elements present and returns SUCCESS.
* Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_gdk_rectangle_count_elements(zval *object, zend_long *count) {

    *count = 0;//php_gdk_rectangle_length(ZVAL_GET_PHP_GDK_RECTANGLE(object));

    return SUCCESS;
}

static int
php_gdk_rectangle_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

static zval*
php_gdk_rectangle_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
    return NULL;
    }
#if 0
    php_gdk_rectangle *intern = ZVAL_GET_PHP_GDK_RECTANGLE(object);
    php_gdk_rectangle *list;
    void *cache=NULL;

    if (Z_TYPE_P(offset)==IS_LONG) {
        list = php_gdk_rectangle_nth(intern, offset->value.lval);
        if (list) {
            ZVAL_COPY(rv, &list->data);
        } else {
            ZVAL_NULL(rv);
            zend_error(E_USER_WARNING, "Undefined offset: %d", offset->value.lval);
        }
        return rv;
    } else if (Z_TYPE_P(offset)==IS_STRING) {
        return php_gdk_rectangle_read_property(object, offset, type, &cache, rv);
    } else {
        // error
    }
#endif
    return rv;
} /* }}} end php_g_hash_table_read_dimension */


static void
php_gdk_rectangle_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_gdk_rectangle_write_property(object, &member, value, &cache);
}

static void
php_gdk_rectangle_unset_dimension(zval *object, zval *offset) {
    //php_g_list *list = ZVAL_GET_PHP_G_LIST(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
    // @TODO
    //zend_hash_index_del(list->prop_handler, );
    // php_g_list
    break;
    case IS_STRING:
        php_gdk_rectangle_unset_property(object, offset, &cache);
    break;
    default:
    break;
    }
}


static zend_object_handlers*
php_gdk_rectangle_get_handlers()
{
    memcpy(&php_gdk_rectangle_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_gdk_rectangle_handlers.offset = PHP_GDK_RECTANGLE_OFFSET;
    //php_gdk_rectangle_handlers.clone_obj;
    //php_gdk_rectangle_handlers.compare;
    //php_gdk_rectangle_handlers.compare_objects;
    //php_gdk_rectangle_handlers.get_constructor;
    php_gdk_rectangle_handlers.dtor_obj = php_gdk_rectangle_dtor_object;
    php_gdk_rectangle_handlers.free_obj = php_gdk_rectangle_free_object;
    php_gdk_rectangle_handlers.read_property = php_gdk_rectangle_read_property;
    php_gdk_rectangle_handlers.write_property = php_gdk_rectangle_write_property;
    php_gdk_rectangle_handlers.unset_property = php_gdk_rectangle_unset_property;
    //php_gdk_rectangle_handlers.get_property_ptr_ptr = php_gdk_rectangle_get_property_ptr_ptr;

    php_gdk_rectangle_handlers.get_debug_info = php_gdk_rectangle_get_debug_info;
    php_gdk_rectangle_handlers.get_properties = php_gdk_rectangle_get_properties;//get_properties_for TODO php 8.0
    //php_gdk_rectangle_handlers.set = php_gdk_rectangle_set;
    php_gdk_rectangle_handlers.cast_object = php_gdk_rectangle_cast_object;

    php_gdk_rectangle_handlers.count_elements = php_gdk_rectangle_count_elements;
    php_gdk_rectangle_handlers.has_dimension = php_gdk_rectangle_has_dimension;
    php_gdk_rectangle_handlers.read_dimension = php_gdk_rectangle_read_dimension;
    php_gdk_rectangle_handlers.unset_dimension = php_gdk_rectangle_unset_dimension;
    php_gdk_rectangle_handlers.write_dimension = php_gdk_rectangle_write_dimension;


    return &php_gdk_rectangle_handlers;
}



/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/


/*{{{ php_gdk_rectangle_class_init */
zend_class_entry*
php_gdk_rectangle_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gdk_rectangle_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "GdkRectangle", php_gdk_rectangle_methods);
    php_gdk_rectangle_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_gdk_rectangle_class_entry->create_object = php_gdk_rectangle_create_object;
    //ce->serialize;
    /*
    zend_hash_init(&php_gdk_rectangle_prop_handlers, 0, NULL, php_gdk_rectangle_dtor_prop_handler, 1);
    php_gdk_rectangle_register_prop_handler(&php_gdk_rectangle_prop_handlers, "prev", sizeof("prev")-1, php_gdk_rectangle_read_prev, php_gdk_rectangle_write_prev);
    php_gdk_rectangle_register_prop_handler(&php_gdk_rectangle_prop_handlers, "data", sizeof("data")-1, php_gdk_rectangle_read_data, php_gdk_rectangle_write_data);
    php_gdk_rectangle_register_prop_handler(&php_gdk_rectangle_prop_handlers, "next", sizeof("next")-1, php_gdk_rectangle_read_next, php_gdk_rectangle_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_gdk_rectangle_prop_handlers);
    */

    return php_gdk_rectangle_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
php_gdk_rectangle *php_gdk_rectangle_new(void)
{
    zend_object *zobj = php_gdk_rectangle_create_object(php_gdk_rectangle_class_entry);
    php_gdk_rectangle *intern = ZOBJ_TO_PHP_GDK_RECTANGLE(zobj);
    intern->ptr = emalloc(sizeof(GdkRectangle));
    intern->ptr->x = 0;
    intern->ptr->y = 0;
    intern->ptr->width = 0;
    intern->ptr->height = 0;

    return intern;
}



/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

/* {{{ GdkRectangle::__construct() */
PHP_METHOD(gdk_rectangle, __construct)
{
    zval *data=NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    zend_object *zobj = Z_OBJ_P(getThis());
    php_gdk_rectangle *self = ZOBJ_TO_PHP_GDK_RECTANGLE(zobj);

    self->ptr = emalloc(sizeof(GdkRectangle));
    self->ptr->x = 0;
    self->ptr->y = 0;
    self->ptr->width = 0;
    self->ptr->height = 0;

}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/


