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

#include "rectangle.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_rectangle_t_class_entry;
zend_object_handlers  php_cairo_rectangle_t_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry php_cairo_rectangle_t_methods[] = {
    PHP_ME(cairo_rectangle_t, __construct, arginfo_cairo_rectangle_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/



/* {{{ php_cairo_rectangle_t_create_object */
static zend_object*
php_cairo_rectangle_t_create_object(zend_class_entry *class_type)
{
    php_cairo_rectangle_t *intern = ecalloc(1, sizeof(php_cairo_rectangle_t) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_cairo_rectangle_t_handlers;

    TRACE("php_cairo_rectangle_t_create_object(%p) / %d\n", &intern->std, intern->std.gc.refcount);
    return &intern->std;
}
/* }}} php_cairo_rectangle_t_create_object */


static void
php_cairo_rectangle_t_dtor_object(zend_object *obj) {
    php_cairo_rectangle_t *intern = ZOBJ_TO_PHP_CAIRO_RECTANGLE_T(obj);

}

/* {{{ php_cairo_rectangle_t_free_object */
static void
php_cairo_rectangle_t_free_object(zend_object *object)
{
    php_cairo_rectangle_t *intern = ZOBJ_TO_PHP_CAIRO_RECTANGLE_T(object);
    TRACE("php_cairo_rectangle_t_free_object(\e[1;31m\"%s\"\e[0;m) / %d\n", intern->data.value.str->val, object->gc.refcount);

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
/* }}} php_cairo_rectangle_t_free_object */



//rename by binarysearch_access_properties.phtml



static void
php_cairo_rectangle_t_setter_double (php_cairo_rectangle_t *intern, zval *value, char *name, double *dest) {
    if (Z_TYPE_P(value)==IS_DOUBLE)
        *dest = value->value.dval;
    else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        zend_string *type = zend_zval_get_type(value);
        if (strict_types) {
            zend_internal_type_error(1, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\cairo_rectangle_t::$%s of type float,", type->val, name);
        } else {
            int allow_errors = -1;
            zend_long lval=0;
            double dval=0;
            if (Z_TYPE_P(value)==IS_STRING) {
                zend_uchar z_type = is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), &lval, &dval, allow_errors);
                if (z_type==IS_LONG) {
                    *dest = (double)lval;
                    zend_error(E_USER_NOTICE, "Implicite %s(%s) to float(%d) convertion,", type->val, value->value.str->val, *dest);
                    return;
                } else if(z_type==IS_DOUBLE) {
                    *dest = dval;
                    zend_error(E_USER_NOTICE, "Implicite %s(%s) to float(%f) convertion,", type->val, value->value.str->val, *dest);
                    return;
                }
            }
            if (Z_TYPE_P(value)==IS_LONG) {
                //TODO: convert long to double
                *dest = (double)value->value.lval;
                zend_error(E_USER_NOTICE, "Implicite int(%f) to float(%d) convertion,", value->value.lval, *dest);
                return;
            }
            zend_error(E_USER_NOTICE, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\cairo_rectangle_t::$%s of type float,", type->val, name);
        }
    }
}



enum _php_cairo_rectangle_t_properties {
    PHP_CAIRO_RECTANGLE_T_X = 1,
    PHP_CAIRO_RECTANGLE_T_Y = 2,
    PHP_CAIRO_RECTANGLE_T_WIDTH = 3,
    PHP_CAIRO_RECTANGLE_T_HEIGHT = 4
};
//typedef enum php_cairo_rectangle_t_properties php_cairo_rectangle_t_properties;

struct PhpCairoRectangleTProperty {
  const char *name;
  int code;
  void (*setter) (php_cairo_rectangle_t *intern, zval *rvalue, char *name, void *dest);
};

static const struct PhpCairoRectangleTProperty php_cairo_rectangle_t_properties[] = {
    {"x", PHP_CAIRO_RECTANGLE_T_X, php_cairo_rectangle_t_setter_double },
    {"y", PHP_CAIRO_RECTANGLE_T_Y, php_cairo_rectangle_t_setter_double },
    {"width", PHP_CAIRO_RECTANGLE_T_WIDTH, php_cairo_rectangle_t_setter_double },
    {"height", PHP_CAIRO_RECTANGLE_T_HEIGHT, php_cairo_rectangle_t_setter_double }
};

const struct PhpCairoRectangleTProperty*
php_cairo_rectangle_t_properties_lookup (const char *str, size_t len)
{
    if (len == 1) {
        if (str[0] == 'x') {
            return &php_cairo_rectangle_t_properties[0];
        } else if (str[0] == 'y') {
            return &php_cairo_rectangle_t_properties[1];
        }
    } else if (len == 5) {
        if (str[0] == 'w' && str[1] == 'i' && str[2] == 'd' && str[3] == 't'
         && str[4] == 'h') {
            return &php_cairo_rectangle_t_properties[2];
        }
    } else if (len == 6) {
        if (str[0] == 'h' && str[1] == 'e' && str[2] == 'i' && str[3] == 'g'
         && str[4] == 'h' && str[5] == 't') {
            return &php_cairo_rectangle_t_properties[3];
        }
    }
    return 0;
}


/* {{{ gtk_read_property */
static zval*
php_cairo_rectangle_t_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_cairo_rectangle_t *intern = ZVAL_GET_PHP_CAIRO_RECTANGLE_T(object);
    zend_string *member_str = member->value.str;

    struct PhpCairoRectangleTProperty *cmd = php_cairo_rectangle_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_RECTANGLE_T_X:
            ZVAL_DOUBLE(rv, intern->ptr->x);
            break;
        case PHP_CAIRO_RECTANGLE_T_Y:
            ZVAL_DOUBLE(rv, intern->ptr->y);
            break;
        case PHP_CAIRO_RECTANGLE_T_WIDTH:
            ZVAL_DOUBLE(rv, intern->ptr->width);
            break;
        case PHP_CAIRO_RECTANGLE_T_HEIGHT:
            ZVAL_DOUBLE(rv, intern->ptr->height);
            break;
        default:
            zend_internal_type_error(1, "Internal bug,");
            break;
        }
    } else {
        // property not found
    }

    return rv;
}
/* }}} */

/* {{{ php_cairo_rectangle_t_write_property */
static void
php_cairo_rectangle_t_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_cairo_rectangle_t *intern = ZVAL_GET_PHP_CAIRO_RECTANGLE_T(object);
    zend_string *member_str = member->value.str;

    struct PhpCairoRectangleTProperty *cmd = php_cairo_rectangle_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_RECTANGLE_T_X:
            cmd->setter(intern, value, member_str->val, &intern->ptr->x);
            break;
        case PHP_CAIRO_RECTANGLE_T_Y:
            cmd->setter(intern, value, member_str->val, &intern->ptr->y);
            break;
        case PHP_CAIRO_RECTANGLE_T_WIDTH:
            cmd->setter(intern, value, member_str->val, &intern->ptr->width);
            break;
        case PHP_CAIRO_RECTANGLE_T_HEIGHT:
            cmd->setter(intern, value, member_str->val, &intern->ptr->height);
            break;
        default:
            zend_internal_type_error(1, "Internal bug,");
            break;
        }
    } else {
        // property not found
    }
}
/* }}} */

static HashTable*
php_cairo_rectangle_t_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_cairo_rectangle_t  *obj =  ZVAL_GET_PHP_CAIRO_RECTANGLE_T(object);
    HashTable   *debug_info,
    *std_props;
    zend_string *string_key = NULL;
    zval *value;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    zval zx; ZVAL_DOUBLE(&zx, obj->ptr->x);
    zend_hash_str_update(debug_info, "x", sizeof("x")-1, &zx);

    zval zy; ZVAL_DOUBLE(&zy, obj->ptr->y);
    zend_hash_str_update(debug_info, "y", sizeof("y")-1, &zy);

    zval zwidth; ZVAL_DOUBLE(&zwidth, obj->ptr->width);
    zend_hash_str_update(debug_info, "width", sizeof("width")-1, &zwidth);

    zval zheight; ZVAL_DOUBLE(&zheight, obj->ptr->height);
    zend_hash_str_update(debug_info, "height", sizeof("height")-1, &zheight);


    return debug_info;
}
/* }}} */





static HashTable*
php_cairo_rectangle_t_get_properties(zval *object){
    php_cairo_rectangle_t  *self =  ZVAL_GET_PHP_CAIRO_RECTANGLE_T(object);
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

    zend_long length = php_cairo_rectangle_t_length(self);

    zend_hash_init(props, length, NULL, ZVAL_PTR_DTOR, 1);

    zval data;

    php_cairo_rectangle_t *it;
    for(it=php_cairo_rectangle_t_first(self); it; it = it->child){
        ZVAL_COPY(&data, &it->data);
        zend_hash_next_index_insert(props, &data);
    }
#endif
    return props;
}


static int
php_cairo_rectangle_t_cast_object(zval *readobj, zval *retval, int type)
{
    g_print("php_cairo_rectangle_t_cast_object\n");
    ZVAL_NULL(retval);

    return FAILURE;
}



static zend_object_handlers*
php_cairo_rectangle_t_get_handlers()
{
    memcpy(&php_cairo_rectangle_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_rectangle_t_handlers.offset = PHP_CAIRO_RECTANGLE_T_OFFSET;

    php_cairo_rectangle_t_handlers.dtor_obj = php_cairo_rectangle_t_dtor_object;
    php_cairo_rectangle_t_handlers.free_obj = php_cairo_rectangle_t_free_object;
    php_cairo_rectangle_t_handlers.read_property = php_cairo_rectangle_t_read_property;
    php_cairo_rectangle_t_handlers.write_property = php_cairo_rectangle_t_write_property;

    php_cairo_rectangle_t_handlers.get_debug_info = php_cairo_rectangle_t_get_debug_info;
    php_cairo_rectangle_t_handlers.get_properties = php_cairo_rectangle_t_get_properties;//get_properties_for TODO php 8.0
    //php_cairo_rectangle_t_handlers.set = php_cairo_rectangle_t_set;
    php_cairo_rectangle_t_handlers.cast_object = php_cairo_rectangle_t_cast_object;


    return &php_cairo_rectangle_t_handlers;
}



/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

/*{{{ php_cairo_rectangle_t_class_init */
zend_class_entry*
php_cairo_rectangle_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_rectangle_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_rectangle_t", php_cairo_rectangle_t_methods);
    php_cairo_rectangle_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_rectangle_t_class_entry->create_object = php_cairo_rectangle_t_create_object;
    //ce->serialize;
    /*
    zend_hash_init(&php_cairo_rectangle_t_prop_handlers, 0, NULL, php_cairo_rectangle_t_dtor_prop_handler, 1);
    php_cairo_rectangle_t_register_prop_handler(&php_cairo_rectangle_t_prop_handlers, "prev", sizeof("prev")-1, php_cairo_rectangle_t_read_prev, php_cairo_rectangle_t_write_prev);
    php_cairo_rectangle_t_register_prop_handler(&php_cairo_rectangle_t_prop_handlers, "data", sizeof("data")-1, php_cairo_rectangle_t_read_data, php_cairo_rectangle_t_write_data);
    php_cairo_rectangle_t_register_prop_handler(&php_cairo_rectangle_t_prop_handlers, "next", sizeof("next")-1, php_cairo_rectangle_t_read_next, php_cairo_rectangle_t_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_cairo_rectangle_t_prop_handlers);
    */

    return php_cairo_rectangle_t_class_entry;
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

/* {{{ cairo_rectangle_t::__construct() */
PHP_METHOD(cairo_rectangle_t, __construct)
{
    zval *data=NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    zend_object *zobj = Z_OBJ_P(getThis());
    php_cairo_rectangle_t *self = ZOBJ_TO_PHP_CAIRO_RECTANGLE_T(zobj);

    self->ptr = emalloc(sizeof(cairo_rectangle_t));
    self->ptr->x = 0.0;
    self->ptr->y = 0.0;
    self->ptr->width = 0.0;
    self->ptr->height = 0.0;

}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/


