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

#include "php_cairo/font-extents.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_font_extents_t_class_entry;// struct
zend_object_handlers  php_cairo_font_extents_t_handlers;




enum _php_cairo_font_extents_t_properties {
    PHP_CAIRO_FONT_EXTENTS_T_ASCENT = 1,
    PHP_CAIRO_FONT_EXTENTS_T_DESCENT = 2,
    PHP_CAIRO_FONT_EXTENTS_T_HEIGHT = 3,
    PHP_CAIRO_FONT_EXTENTS_T_MAX_X_ADVANCE = 4,
    PHP_CAIRO_FONT_EXTENTS_T_MAX_Y_ADVANCE = 5
};
//typedef enum php_cairo_font_extents_t_properties php_cairo_font_extents_t_properties;



/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_font_extents_t_methods[] = {
    PHP_ME(cairo_font_extents_t, __construct, arginfo_cairo_font_extents_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_font_extents_t_create_object */
static zend_object*
php_cairo_font_extents_t_create_object(zend_class_entry *class_type)
{
    php_cairo_font_extents_t *intern = zend_object_alloc(sizeof(php_cairo_font_extents_t), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);


    ZVAL_DOUBLE(&intern->ascent, 0.0);
    ZVAL_DOUBLE(&intern->descent, 0.0);
    ZVAL_DOUBLE(&intern->height, 0.0);
    ZVAL_DOUBLE(&intern->max_x_advance, 0.0);
    ZVAL_DOUBLE(&intern->max_y_advance, 0.0);

    intern->std.handlers = &php_cairo_font_extents_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_font_extents_t_create_object */


static void
php_cairo_font_extents_t_dtor_object(zend_object *obj) {
    //php_cairo_font_extents_t *intern = ZOBJ_TO_PHP_CAIRO_FONT_EXTENTS_T(obj);

}

/* {{{ php_cairo_font_extents_t_free_object */
static void
php_cairo_font_extents_t_free_object(zend_object *object)
{
    php_cairo_font_extents_t *intern = ZOBJ_TO_PHP_CAIRO_FONT_EXTENTS_T(object);

    Z_TRY_DELREF(intern->ascent);
    Z_TRY_DELREF(intern->descent);
    Z_TRY_DELREF(intern->height);
    Z_TRY_DELREF(intern->max_x_advance);
    Z_TRY_DELREF(intern->max_y_advance);

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_font_extents_t_free_object */




/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_cairo_font_extents_t_setter_double(php_cairo_font_extents_t *intern, zval *value, char *name, zval *dest) {
    if (Z_TYPE_P(value)==IS_DOUBLE) {
        ZVAL_SET_DOUBLE(dest, value->value.dval);
    } else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        const char *type_name = zend_zval_type_name(value);
        if (strict_types) {
            zend_error(E_USER_NOTICE, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\cairo_font_extents_t::$%s of type float,", type_name, name);
        } else {
            int allow_errors = -1;
            zend_long lval=0;
            double dval=0;
            if (Z_TYPE_P(value)==IS_STRING) {
                zend_uchar z_type = is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), &lval, &dval, allow_errors);
                if (z_type==IS_LONG) {
                    ZVAL_SET_DOUBLE(dest, (double)lval);
                    zend_error(E_USER_NOTICE, "Implicite %s(%s) to float(%f) convertion,", type_name, value->value.str->val, (double)lval);
                    return;
                } else if(z_type==IS_DOUBLE) {
                    ZVAL_SET_DOUBLE(dest, dval);
                    zend_error(E_USER_NOTICE, "Implicite %s(%s) to float(%f) convertion,", type_name, value->value.str->val, dval);
                    return;
                }
            }
            if (Z_TYPE_P(value)==IS_LONG) {
                ZVAL_SET_DOUBLE(dest, (double)value->value.lval);
                zend_error(E_USER_NOTICE, "Implicite int(%d) to float(%f) convertion,", (int)value->value.lval, (double)value->value.lval);
                return;
            }
            zend_error(E_USER_NOTICE, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\cairo_font_extents_t::$%s of type float,", type_name, name);
        }
    }
}




struct PhpCairoFontExtentsTProperty {
  const char *name;
  int code;
  void (*setter) (php_cairo_font_extents_t *intern, zval *rvalue, char *name, zval *dest);
};

static const struct PhpCairoFontExtentsTProperty php_cairo_font_extents_t_properties[] = {
    {"ascent", PHP_CAIRO_FONT_EXTENTS_T_ASCENT, php_cairo_font_extents_t_setter_double},
    {"descent", PHP_CAIRO_FONT_EXTENTS_T_DESCENT, php_cairo_font_extents_t_setter_double},
    {"height", PHP_CAIRO_FONT_EXTENTS_T_HEIGHT, php_cairo_font_extents_t_setter_double},
    {"max_x_advance", PHP_CAIRO_FONT_EXTENTS_T_MAX_X_ADVANCE, php_cairo_font_extents_t_setter_double},
    {"max_y_advance", PHP_CAIRO_FONT_EXTENTS_T_MAX_Y_ADVANCE, php_cairo_font_extents_t_setter_double}
};


const struct PhpCairoFontExtentsTProperty*
php_cairo_font_extents_t_properties_lookup (const char *str, size_t len)
{
    if (len == 6) {
        if (str[0] == 'a' && str[1] == 's' && str[2] == 'c' && str[3] == 'e'
         && str[4] == 'n' && str[5] == 't') {
            return &php_cairo_font_extents_t_properties[0];
        } else if (str[0] == 'h' && str[1] == 'e' && str[2] == 'i' && str[3] == 'g'
         && str[4] == 'h' && str[5] == 't') {
            return &php_cairo_font_extents_t_properties[2];
        }
    } else if (len == 7) {
        if (str[0] == 'd' && str[1] == 'e' && str[2] == 's' && str[3] == 'c'
         && str[4] == 'e' && str[5] == 'n' && str[6] == 't') {
            return &php_cairo_font_extents_t_properties[1];
        }
    } else if (len == 13) {
        if (str[0] == 'm' && str[1] == 'a' && str[2] == 'x' && str[3] == '_'
         && str[4] == 'x' && str[5] == '_' && str[6] == 'a' && str[7] == 'd'
         && str[8] == 'v' && str[9] == 'a' && str[10] == 'n' && str[11] == 'c'
         && str[12] == 'e') {
            return &php_cairo_font_extents_t_properties[3];
        } else if (str[0] == 'm' && str[1] == 'a' && str[2] == 'x' && str[3] == '_'
         && str[4] == 'y' && str[5] == '_' && str[6] == 'a' && str[7] == 'd'
         && str[8] == 'v' && str[9] == 'a' && str[10] == 'n' && str[11] == 'c'
         && str[12] == 'e') {
            return &php_cairo_font_extents_t_properties[4];
        }
    }
    return 0;
}

/* {{{ php_cairo_font_extents_t_read_property */
static zval*
php_cairo_font_extents_t_read_property(zend_object *object, zend_string *member_str, int type, void **cache_slot, zval *rv)
{
    php_cairo_font_extents_t *intern = ZOBJ_TO_PHP_CAIRO_FONT_EXTENTS_T(object);

    const struct PhpCairoFontExtentsTProperty *cmd = php_cairo_font_extents_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_FONT_EXTENTS_T_ASCENT:
            ZVAL_COPY(rv, &intern->ascent);
            return rv;
            break;
        case PHP_CAIRO_FONT_EXTENTS_T_DESCENT:
            ZVAL_COPY(rv, &intern->descent);
            return rv;
            break;
        case PHP_CAIRO_FONT_EXTENTS_T_HEIGHT:
            ZVAL_COPY(rv, &intern->height);
            return rv;
            break;
        case PHP_CAIRO_FONT_EXTENTS_T_MAX_X_ADVANCE:
            ZVAL_COPY(rv, &intern->max_x_advance);
            return rv;
            break;
        case PHP_CAIRO_FONT_EXTENTS_T_MAX_Y_ADVANCE:
            ZVAL_COPY(rv, &intern->max_y_advance);
            return rv;
            break;
        default:
            //zend_internal_type_error(1, "Internal bug,");
            //zend_error(E_USER_NOTICE, "Internal bug,");
            break;
        }
    } else {
        // property not found
    }

    return rv;
}
/* }}} */

/* {{{ php_cairo_font_extents_t_write_property */
static zval*
php_cairo_font_extents_t_write_property(zend_object *object, zend_string *member_str, zval *value, void **cache_slot)
{
    php_cairo_font_extents_t *intern = ZOBJ_TO_PHP_CAIRO_FONT_EXTENTS_T(object);
    // struct
    const struct PhpCairoFontExtentsTProperty *cmd = php_cairo_font_extents_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_FONT_EXTENTS_T_ASCENT:
            cmd->setter(intern, value, member_str->val, &intern->ascent);
        break;
        case PHP_CAIRO_FONT_EXTENTS_T_DESCENT:
            cmd->setter(intern, value, member_str->val, &intern->descent);
        break;
        case PHP_CAIRO_FONT_EXTENTS_T_HEIGHT:
            cmd->setter(intern, value, member_str->val, &intern->height);
        break;
        case PHP_CAIRO_FONT_EXTENTS_T_MAX_X_ADVANCE:
            cmd->setter(intern, value, member_str->val, &intern->max_x_advance);
        break;
        case PHP_CAIRO_FONT_EXTENTS_T_MAX_Y_ADVANCE:
            cmd->setter(intern, value, member_str->val, &intern->max_y_advance);
        break;
        }
    } else {
        // property not found
    }
    return value;
}
/* }}} */

/* {{{ php_cairo_font_extents_t_get_property_ptr_ptr */
static zval*
php_cairo_font_extents_t_get_property_ptr_ptr(zend_object *object, zend_string *member_str, int type, void **cache_slot)
{
    php_cairo_font_extents_t *intern = ZOBJ_TO_PHP_CAIRO_FONT_EXTENTS_T(object);
    zval *retval = NULL;

    const struct PhpCairoFontExtentsTProperty *cmd = php_cairo_font_extents_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_FONT_EXTENTS_T_ASCENT:
            return &intern->ascent;
        case PHP_CAIRO_FONT_EXTENTS_T_DESCENT:
            return &intern->descent;
        case PHP_CAIRO_FONT_EXTENTS_T_HEIGHT:
            return &intern->height;
        case PHP_CAIRO_FONT_EXTENTS_T_MAX_X_ADVANCE:
            return &intern->max_x_advance;
        case PHP_CAIRO_FONT_EXTENTS_T_MAX_Y_ADVANCE:
            return &intern->max_y_advance;
        }
    } else {
        // Error
    }

    return retval;
}/* }}} */





/* {{{ php_cairo_font_extents_t_get_debug_info */
static HashTable*
php_cairo_font_extents_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_font_extents_t  *intern = ZOBJ_TO_PHP_CAIRO_FONT_EXTENTS_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    zval zascent; ZVAL_COPY(&zascent, &intern->ascent);
    zend_hash_str_update(debug_info, "ascent", sizeof("ascent")-1, &zascent);
    zval zdescent; ZVAL_COPY(&zdescent, &intern->descent);
    zend_hash_str_update(debug_info, "descent", sizeof("descent")-1, &zdescent);
    zval zheight; ZVAL_COPY(&zheight, &intern->height);
    zend_hash_str_update(debug_info, "height", sizeof("height")-1, &zheight);
    zval zmax_x_advance; ZVAL_COPY(&zmax_x_advance, &intern->max_x_advance);
    zend_hash_str_update(debug_info, "max_x_advance", sizeof("max_x_advance")-1, &zmax_x_advance);
    zval zmax_y_advance; ZVAL_COPY(&zmax_y_advance, &intern->max_y_advance);
    zend_hash_str_update(debug_info, "max_y_advance", sizeof("max_y_advance")-1, &zmax_y_advance);

    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_font_extents_t_get_handlers()
{
    memcpy(&php_cairo_font_extents_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_font_extents_t_handlers.offset = PHP_CAIRO_FONT_EXTENTS_T_OFFSET;
    php_cairo_font_extents_t_handlers.dtor_obj = php_cairo_font_extents_t_dtor_object;
    php_cairo_font_extents_t_handlers.free_obj = php_cairo_font_extents_t_free_object;

    php_cairo_font_extents_t_handlers.read_property = php_cairo_font_extents_t_read_property;
    php_cairo_font_extents_t_handlers.write_property = php_cairo_font_extents_t_write_property;
    php_cairo_font_extents_t_handlers.get_property_ptr_ptr = php_cairo_font_extents_t_get_property_ptr_ptr;

    php_cairo_font_extents_t_handlers.get_debug_info = php_cairo_font_extents_t_get_debug_info;


    return &php_cairo_font_extents_t_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_font_extents_t_class_init */
zend_class_entry*
php_cairo_font_extents_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_font_extents_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_font_extents_t", php_cairo_font_extents_t_methods);
    php_cairo_font_extents_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_font_extents_t_class_entry->create_object = php_cairo_font_extents_t_create_object;

    return php_cairo_font_extents_t_class_entry;
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

 /* {{{ cairo_font_extents_t::__construct() */
PHP_METHOD(cairo_font_extents_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_font_extents_t *self = ZOBJ_TO_PHP_CAIRO_FONT_EXTENTS_T(zobj);


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
