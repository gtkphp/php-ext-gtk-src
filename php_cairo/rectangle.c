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

#include "php_cairo/rectangle.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_rectangle_t_class_entry;
zend_object_handlers  php_cairo_rectangle_t_handlers;



/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_rectangle_t_methods[] = {
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


    ZVAL_DOUBLE(&intern->x, 0.0);
    ZVAL_DOUBLE(&intern->y, 0.0);
    ZVAL_DOUBLE(&intern->width, 0.0);
    ZVAL_DOUBLE(&intern->height, 0.0);

    intern->std.handlers = &php_cairo_rectangle_t_handlers;

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

    Z_TRY_DELREF(intern->x);
    Z_TRY_DELREF(intern->y);
    Z_TRY_DELREF(intern->width);
    Z_TRY_DELREF(intern->height);

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_rectangle_t_free_object */



/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_cairo_rectangle_t_setter_double(php_cairo_rectangle_t *intern, zval *value, char *name, zval *dest) {
    if (Z_TYPE_P(value)==IS_DOUBLE) {
        ZVAL_SET_DOUBLE(dest, value->value.dval);
    } else {
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
                    ZVAL_SET_DOUBLE(dest, (double)lval);
                    zend_error(E_USER_NOTICE, "Implicite %s(%s) to float(%f) convertion,", type->val, value->value.str->val, (double)lval);
                    return;
                } else if(z_type==IS_DOUBLE) {
                    ZVAL_SET_DOUBLE(dest, dval);
                    zend_error(E_USER_NOTICE, "Implicite %s(%s) to float(%f) convertion,", type->val, value->value.str->val, dval);
                    return;
                }
            }
            if (Z_TYPE_P(value)==IS_LONG) {
                ZVAL_SET_DOUBLE(dest, (double)value->value.lval);
                zend_error(E_USER_NOTICE, "Implicite int(%d) to float(%f) convertion,", value->value.lval, (double)value->value.lval);
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
  void (*setter) (php_cairo_rectangle_t *intern, zval *rvalue, char *name, zval *dest);
};

static const struct PhpCairoRectangleTProperty php_cairo_rectangle_t_properties[] = {
    {"x", PHP_CAIRO_RECTANGLE_T_X, php_cairo_rectangle_t_setter_double},
    {"y", PHP_CAIRO_RECTANGLE_T_Y, php_cairo_rectangle_t_setter_double},
    {"width", PHP_CAIRO_RECTANGLE_T_WIDTH, php_cairo_rectangle_t_setter_double},
    {"height", PHP_CAIRO_RECTANGLE_T_HEIGHT, php_cairo_rectangle_t_setter_double}
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

/* {{{ php_cairo_rectangle_t_read_property */
static zval*
php_cairo_rectangle_t_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_cairo_rectangle_t *intern = ZVAL_GET_PHP_CAIRO_RECTANGLE_T(object);
    zend_string *member_str = member->value.str;

    struct PhpCairoRectangleTProperty *cmd = php_cairo_rectangle_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_RECTANGLE_T_X:
            ZVAL_COPY(rv, &intern->x);
            break;
        case PHP_CAIRO_RECTANGLE_T_Y:
            ZVAL_COPY(rv, &intern->y);
            break;
        case PHP_CAIRO_RECTANGLE_T_WIDTH:
            ZVAL_COPY(rv, &intern->width);
            break;
        case PHP_CAIRO_RECTANGLE_T_HEIGHT:
            ZVAL_COPY(rv, &intern->height);
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

    // struct
    struct PhpCairoRectangleTProperty *cmd = php_cairo_rectangle_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_RECTANGLE_T_X:
            cmd->setter(intern, value, member_str->val, &intern->x);
        break;
        case PHP_CAIRO_RECTANGLE_T_Y:
            cmd->setter(intern, value, member_str->val, &intern->y);
        break;
        case PHP_CAIRO_RECTANGLE_T_WIDTH:
            cmd->setter(intern, value, member_str->val, &intern->width);
        break;
        case PHP_CAIRO_RECTANGLE_T_HEIGHT:
            cmd->setter(intern, value, member_str->val, &intern->height);
        break;
        }
    } else {
        // property not found
    }
}
/* }}} */

/* {{{ php_cairo_rectangle_t_get_property_ptr_ptr */
static zval *
php_cairo_rectangle_t_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) {
    php_cairo_rectangle_t  *intern = ZVAL_GET_PHP_CAIRO_RECTANGLE_T(object);
    zend_string *member_str = member->value.str;
    char *str = member_str->val;
    zval *retval = NULL;

    struct PhpCairoRectangleTProperty *cmd = php_cairo_rectangle_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_RECTANGLE_T_X:
            return &intern->x;
        case PHP_CAIRO_RECTANGLE_T_Y:
            return &intern->y;
        case PHP_CAIRO_RECTANGLE_T_WIDTH:
            return &intern->width;
        case PHP_CAIRO_RECTANGLE_T_HEIGHT:
            return &intern->height;
        }
    } else {
        // Error
    }

    return retval;
}/* }}} */





/* {{{ php_cairo_rectangle_t_get_debug_info */
static HashTable*
php_cairo_rectangle_t_get_debug_info(zval *object, int *is_temp)
{
    php_cairo_rectangle_t  *intern = ZVAL_GET_PHP_CAIRO_RECTANGLE_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    zval zx; ZVAL_COPY(&zx, &intern->x);
    zend_hash_str_update(debug_info, "x", sizeof("x")-1, &zx);
    zval zy; ZVAL_COPY(&zy, &intern->y);
    zend_hash_str_update(debug_info, "y", sizeof("y")-1, &zy);
    zval zwidth; ZVAL_COPY(&zwidth, &intern->width);
    zend_hash_str_update(debug_info, "width", sizeof("width")-1, &zwidth);
    zval zheight; ZVAL_COPY(&zheight, &intern->height);
    zend_hash_str_update(debug_info, "height", sizeof("height")-1, &zheight);

    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_rectangle_t_get_handlers()
{
    memcpy(&php_cairo_rectangle_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_rectangle_t_handlers.offset = PHP_CAIRO_RECTANGLE_T_OFFSET;
    php_cairo_rectangle_t_handlers.dtor_obj = php_cairo_rectangle_t_dtor_object;
    php_cairo_rectangle_t_handlers.free_obj = php_cairo_rectangle_t_free_object;

    php_cairo_rectangle_t_handlers.read_property = php_cairo_rectangle_t_read_property;
    php_cairo_rectangle_t_handlers.write_property = php_cairo_rectangle_t_write_property;
    php_cairo_rectangle_t_handlers.get_property_ptr_ptr = php_cairo_rectangle_t_get_property_ptr_ptr;

    php_cairo_rectangle_t_handlers.get_debug_info = php_cairo_rectangle_t_get_debug_info;


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
    zend_object *zobj = Z_OBJ_P(getThis());
    php_cairo_rectangle_t *self = ZOBJ_TO_PHP_CAIRO_RECTANGLE_T(zobj);


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
