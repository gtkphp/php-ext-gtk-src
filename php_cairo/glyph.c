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
#include "php_cairo/font-slant.h"
#include "php_cairo/font-weight.h"
#include "php_cairo/matrix.h"
#include "php_cairo/font-options.h"
#include "php_cairo/font-face.h"
#include "php_cairo/scaled-font.h"
#include "php_cairo/text-cluster.h"
#include "php_cairo/text-cluster-flags.h"
#include "php_cairo/font-extents.h"
#include "php_cairo/text-extents.h"

#include "php_cairo/glyph.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_glyph_t_class_entry;
zend_object_handlers  php_cairo_glyph_t_handlers;



/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_glyph_t_methods[] = {
    PHP_ME(cairo_glyph_t, __construct, arginfo_cairo_glyph_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_glyph_t_create_object */
static zend_object*
php_cairo_glyph_t_create_object(zend_class_entry *class_type)
{
    php_cairo_glyph_t *intern = ecalloc(1, sizeof(php_cairo_glyph_t) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);


    ZVAL_LONG(&intern->index, 0);
    ZVAL_DOUBLE(&intern->x, 0.0);
    ZVAL_DOUBLE(&intern->y, 0.0);

    intern->std.handlers = &php_cairo_glyph_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_glyph_t_create_object */


static void
php_cairo_glyph_t_dtor_object(zend_object *obj) {
    php_cairo_glyph_t *intern = ZOBJ_TO_PHP_CAIRO_GLYPH_T(obj);

}

/* {{{ php_cairo_glyph_t_free_object */
static void
php_cairo_glyph_t_free_object(zend_object *object)
{
    php_cairo_glyph_t *intern = ZOBJ_TO_PHP_CAIRO_GLYPH_T(object);

    Z_TRY_DELREF(intern->index);
    Z_TRY_DELREF(intern->x);
    Z_TRY_DELREF(intern->y);

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_glyph_t_free_object */



/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_cairo_glyph_t_setter_int(php_cairo_glyph_t *intern, zval *value, char *name, zval *dest) {
    if (Z_TYPE_P(value)==IS_LONG) {
        ZVAL_SET_LONG(dest, value->value.lval);
    } else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        zend_string *type = zend_zval_get_type(value);
        if (strict_types) {
            zend_internal_type_error(1, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\cairo_glyph_t::$%s of type float,", type->val, name);
        } else {
            int allow_errors = -1;
            zend_long lval=0;
            double dval=0;
            if (Z_TYPE_P(value)==IS_STRING) {
                zend_uchar z_type = is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), &lval, &dval, allow_errors);
                if (z_type==IS_LONG) {
                    ZVAL_SET_LONG(dest, lval);
                    zend_error(E_USER_NOTICE, "Implicite %s(%s) to int(%d) convertion,", type->val, value->value.str->val, lval);
                    return;
                } else if(z_type==IS_DOUBLE) {
                    ZVAL_SET_LONG(dest, (int)dval);
                    zend_error(E_USER_NOTICE, "Implicite %s(%s) to int(%d) convertion,", type->val, value->value.str->val, (int)dval);
                    return;
                }
            }
            if (Z_TYPE_P(value)==IS_DOUBLE) {
                ZVAL_SET_LONG(dest, (int)value->value.dval);
                zend_error(E_USER_WARNING, "Implicite float(%f) to int(%d) convertion,", value->value.dval, (int)value->value.dval);
                return;
            }
            zend_error(E_USER_NOTICE, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\cairo_glyph_t::$%s of type int,", type->val, name);
        }
    }
}



/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_cairo_glyph_t_setter_double(php_cairo_glyph_t *intern, zval *value, char *name, zval *dest) {
    if (Z_TYPE_P(value)==IS_DOUBLE) {
        ZVAL_SET_DOUBLE(dest, value->value.dval);
    } else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        zend_string *type = zend_zval_get_type(value);
        if (strict_types) {
            zend_internal_type_error(1, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\cairo_glyph_t::$%s of type float,", type->val, name);
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
            zend_error(E_USER_NOTICE, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\cairo_glyph_t::$%s of type float,", type->val, name);
        }
    }
}




enum _php_cairo_glyph_t_properties {
    PHP_CAIRO_GLYPH_T_INDEX = 1,
    PHP_CAIRO_GLYPH_T_X = 2,
    PHP_CAIRO_GLYPH_T_Y = 3
};
//typedef enum php_cairo_glyph_t_properties php_cairo_glyph_t_properties;

struct PhpCairoGlyphTProperty {
  const char *name;
  int code;
  void (*setter) (php_cairo_glyph_t *intern, zval *rvalue, char *name, zval *dest);
};

static const struct PhpCairoGlyphTProperty php_cairo_glyph_t_properties[] = {
    {"index", PHP_CAIRO_GLYPH_T_INDEX, php_cairo_glyph_t_setter_int},
    {"x", PHP_CAIRO_GLYPH_T_X, php_cairo_glyph_t_setter_double},
    {"y", PHP_CAIRO_GLYPH_T_Y, php_cairo_glyph_t_setter_double}
};


const struct PhpCairoGlyphTProperty*
php_cairo_glyph_t_properties_lookup (const char *str, size_t len)
{
    if (len == 5) {
        if (str[0] == 'i' && str[1] == 'n' && str[2] == 'd' && str[3] == 'e'
         && str[4] == 'x') {
            return &php_cairo_glyph_t_properties[0];
        }
    } else if (len == 1) {
        if (str[0] == 'x') {
            return &php_cairo_glyph_t_properties[1];
        } else if (str[0] == 'y') {
            return &php_cairo_glyph_t_properties[2];
        }
    }
    return 0;
}

/* {{{ php_cairo_glyph_t_read_property */
static zval*
php_cairo_glyph_t_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_cairo_glyph_t *intern = ZVAL_GET_PHP_CAIRO_GLYPH_T(object);
    zend_string *member_str = member->value.str;

    struct PhpCairoGlyphTProperty *cmd = php_cairo_glyph_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_GLYPH_T_INDEX:
            ZVAL_COPY(rv, &intern->index);
            break;
        case PHP_CAIRO_GLYPH_T_X:
            ZVAL_COPY(rv, &intern->x);
            break;
        case PHP_CAIRO_GLYPH_T_Y:
            ZVAL_COPY(rv, &intern->y);
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

/* {{{ php_cairo_glyph_t_write_property */
static void
php_cairo_glyph_t_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_cairo_glyph_t *intern = ZVAL_GET_PHP_CAIRO_GLYPH_T(object);
    zend_string *member_str = member->value.str;

    // struct
    struct PhpCairoGlyphTProperty *cmd = php_cairo_glyph_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_GLYPH_T_INDEX:
            cmd->setter(intern, value, member_str->val, &intern->index);
        break;
        case PHP_CAIRO_GLYPH_T_X:
            cmd->setter(intern, value, member_str->val, &intern->x);
        break;
        case PHP_CAIRO_GLYPH_T_Y:
            cmd->setter(intern, value, member_str->val, &intern->y);
        break;
        }
    } else {
        // property not found
    }
}
/* }}} */

/* {{{ php_cairo_glyph_t_get_property_ptr_ptr */
static zval *
php_cairo_glyph_t_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) {
    php_cairo_glyph_t  *intern = ZVAL_GET_PHP_CAIRO_GLYPH_T(object);
    zend_string *member_str = member->value.str;
    char *str = member_str->val;
    zval *retval = NULL;

    struct PhpCairoGlyphTProperty *cmd = php_cairo_glyph_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_GLYPH_T_INDEX:
            return &intern->index;
        case PHP_CAIRO_GLYPH_T_X:
            return &intern->x;
        case PHP_CAIRO_GLYPH_T_Y:
            return &intern->y;
        }
    } else {
        // Error
    }

    return retval;
}/* }}} */





/* {{{ php_cairo_glyph_t_get_debug_info */
static HashTable*
php_cairo_glyph_t_get_debug_info(zval *object, int *is_temp)
{
    php_cairo_glyph_t  *intern = ZVAL_GET_PHP_CAIRO_GLYPH_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    zval zindex; ZVAL_COPY(&zindex, &intern->index);
    zend_hash_str_update(debug_info, "index", sizeof("index")-1, &zindex);
    zval zx; ZVAL_COPY(&zx, &intern->x);
    zend_hash_str_update(debug_info, "x", sizeof("x")-1, &zx);
    zval zy; ZVAL_COPY(&zy, &intern->y);
    zend_hash_str_update(debug_info, "y", sizeof("y")-1, &zy);

    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_glyph_t_get_handlers()
{
    memcpy(&php_cairo_glyph_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_glyph_t_handlers.offset = PHP_CAIRO_GLYPH_T_OFFSET;
    php_cairo_glyph_t_handlers.dtor_obj = php_cairo_glyph_t_dtor_object;
    php_cairo_glyph_t_handlers.free_obj = php_cairo_glyph_t_free_object;

    php_cairo_glyph_t_handlers.read_property = php_cairo_glyph_t_read_property;
    php_cairo_glyph_t_handlers.write_property = php_cairo_glyph_t_write_property;
    php_cairo_glyph_t_handlers.get_property_ptr_ptr = php_cairo_glyph_t_get_property_ptr_ptr;

    php_cairo_glyph_t_handlers.get_debug_info = php_cairo_glyph_t_get_debug_info;


    return &php_cairo_glyph_t_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_glyph_t_class_init */
zend_class_entry*
php_cairo_glyph_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_glyph_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_glyph_t", php_cairo_glyph_t_methods);
    php_cairo_glyph_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_glyph_t_class_entry->create_object = php_cairo_glyph_t_create_object;

    return php_cairo_glyph_t_class_entry;
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

 /* {{{ cairo_glyph_t::__construct() */
PHP_METHOD(cairo_glyph_t, __construct)
{
    zend_object *zobj = Z_OBJ_P(getThis());
    php_cairo_glyph_t *self = ZOBJ_TO_PHP_CAIRO_GLYPH_T(zobj);


}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

/* {{{ proto void cairo_select_font_face(php_cairo_t cr, string family, int slant, int weight)
   Note: The cairo_select_font_face() function call is part of what the ... */
PHP_FUNCTION(cairo_select_font_face)
{
    zval *zcr;
    char *family;
    int family_len;
    zval *zslant;
    zval *zweight;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_STRING(family, family_len)
        Z_PARAM_OBJECT_OF_CLASS_EX(zslant, php_cairo_font_slant_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zweight, php_cairo_font_weight_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_font_slant_t *php_slant = ZVAL_IS_PHP_CAIRO_FONT_SLANT_T(zslant)? ZVAL_GET_PHP_CAIRO_FONT_SLANT_T(zslant): NULL;
    DECL_PHP_CAIRO_FONT_SLANT_T(slant);
    php_cairo_font_weight_t *php_weight = ZVAL_IS_PHP_CAIRO_FONT_WEIGHT_T(zweight)? ZVAL_GET_PHP_CAIRO_FONT_WEIGHT_T(zweight): NULL;
    DECL_PHP_CAIRO_FONT_WEIGHT_T(weight);

    cairo_select_font_face(cr, family, slant, weight);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_set_font_size(php_cairo_t cr, double size)
   Sets the current font matrix to a scale by a factor of size , replaci... */
PHP_FUNCTION(cairo_set_font_size)
{
    zval *zcr;
    double size;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(size)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_set_font_size(cr, size);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_set_font_matrix(php_cairo_t cr, php_cairo_matrix_t matrix)
   Sets the current font matrix to matrix . */
PHP_FUNCTION(cairo_set_font_matrix)
{
    zval *zcr;
    zval *zmatrix;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_set_font_matrix(cr, matrix);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_get_font_matrix(php_cairo_t cr, php_cairo_matrix_t matrix)
   Stores the current font matrix into matrix . See cairo_set_font_matrix(). */
PHP_FUNCTION(cairo_get_font_matrix)
{
    zval *zcr;
    zval *zmatrix;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_get_font_matrix(cr, matrix);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_set_font_options(php_cairo_t cr, php_cairo_font_options_t options)
   Sets a set of custom font rendering options for the cairo_t. */
PHP_FUNCTION(cairo_set_font_options)
{
    zval *zcr;
    zval *zoptions;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);

    cairo_set_font_options(cr, options);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_get_font_options(php_cairo_t cr, php_cairo_font_options_t options)
   Retrieves font rendering options set via cairo_set_font_options. */
PHP_FUNCTION(cairo_get_font_options)
{
    zval *zcr;
    zval *zoptions;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);

    cairo_get_font_options(cr, options);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_set_font_face(php_cairo_t cr, php_cairo_font_face_t font_face)
   Replaces the current cairo_font_face_t object in the cairo_t with fon... */
PHP_FUNCTION(cairo_set_font_face)
{
    zval *zcr;
    zval *zfont_face;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zfont_face, php_cairo_font_face_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_font_face_t *php_font_face = ZVAL_IS_PHP_CAIRO_FONT_FACE_T(zfont_face)? ZVAL_GET_PHP_CAIRO_FONT_FACE_T(zfont_face): NULL;
    DECL_PHP_CAIRO_FONT_FACE_T(font_face);

    cairo_set_font_face(cr, font_face);
    RETURN_NULL();
}/* }}} */

/* {{{ proto php_cairo_font_face_t cairo_get_font_face(php_cairo_t cr)
   Gets the current font face for a cairo_t. */
PHP_FUNCTION(cairo_get_font_face)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_font_face_t *ret = cairo_get_font_face(cr);

    RETURN_OBJ(z_ret);
}/* }}} */

/* {{{ proto void cairo_set_scaled_font(php_cairo_t cr, php_cairo_scaled_font_t scaled_font)
   Replaces the current font face, font matrix, and font options in the ... */
PHP_FUNCTION(cairo_set_scaled_font)
{
    zval *zcr;
    zval *zscaled_font;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);

    cairo_set_scaled_font(cr, scaled_font);
    RETURN_NULL();
}/* }}} */

/* {{{ proto php_cairo_scaled_font_t cairo_get_scaled_font(php_cairo_t cr)
   Gets the current scaled font for a cairo_t. */
PHP_FUNCTION(cairo_get_scaled_font)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_scaled_font_t *ret = cairo_get_scaled_font(cr);

    RETURN_OBJ(z_ret);
}/* }}} */

/* {{{ proto void cairo_show_text(php_cairo_t cr, string utf8)
   A drawing operator that generates the shape from a string of UTF-8 ch... */
PHP_FUNCTION(cairo_show_text)
{
    zval *zcr;
    char *utf8;
    int utf8_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_STRING(utf8, utf8_len)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_show_text(cr, utf8);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_show_glyphs(php_cairo_t cr, php_cairo_glyph_t glyphs, int num_glyphs)
   A drawing operator that generates the shape from an array of glyphs, ... */
PHP_FUNCTION(cairo_show_glyphs)
{
    zval *zcr;
    zval *zglyphs;
    zend_long num_glyphs;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zglyphs, php_cairo_glyph_t_class_entry, 1, 0)
        Z_PARAM_LONG(num_glyphs)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_glyph_t *php_glyphs = ZVAL_IS_PHP_CAIRO_GLYPH_T(zglyphs)? ZVAL_GET_PHP_CAIRO_GLYPH_T(zglyphs): NULL;
    DECL_PHP_CAIRO_GLYPH_T(glyphs);

    cairo_show_glyphs(cr, glyphs, num_glyphs);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_show_text_glyphs(php_cairo_t cr, string utf8, int utf8_len, php_cairo_glyph_t glyphs, int num_glyphs, php_cairo_text_cluster_t clusters, int num_clusters, int cluster_flags)
   This operation has rendering effects similar to cairo_show_glyphs() b... */
PHP_FUNCTION(cairo_show_text_glyphs)
{
    zval *zcr;
    char *utf8;
    int utf8_len;
    zend_long utf8_len;
    zval *zglyphs;
    zend_long num_glyphs;
    zval *zclusters;
    zend_long num_clusters;
    zval *zcluster_flags;

    ZEND_PARSE_PARAMETERS_START(8, 8)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_STRING(utf8, utf8_len)
        Z_PARAM_LONG(utf8_len)
        Z_PARAM_OBJECT_OF_CLASS_EX(zglyphs, php_cairo_glyph_t_class_entry, 1, 0)
        Z_PARAM_LONG(num_glyphs)
        Z_PARAM_OBJECT_OF_CLASS_EX(zclusters, php_cairo_text_cluster_t_class_entry, 1, 0)
        Z_PARAM_LONG(num_clusters)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcluster_flags, php_cairo_text_cluster_flags_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_glyph_t *php_glyphs = ZVAL_IS_PHP_CAIRO_GLYPH_T(zglyphs)? ZVAL_GET_PHP_CAIRO_GLYPH_T(zglyphs): NULL;
    DECL_PHP_CAIRO_GLYPH_T(glyphs);
    php_cairo_text_cluster_t *php_clusters = ZVAL_IS_PHP_CAIRO_TEXT_CLUSTER_T(zclusters)? ZVAL_GET_PHP_CAIRO_TEXT_CLUSTER_T(zclusters): NULL;
    DECL_PHP_CAIRO_TEXT_CLUSTER_T(clusters);
    php_cairo_text_cluster_flags_t *php_cluster_flags = ZVAL_IS_PHP_CAIRO_TEXT_CLUSTER_FLAGS_T(zcluster_flags)? ZVAL_GET_PHP_CAIRO_TEXT_CLUSTER_FLAGS_T(zcluster_flags): NULL;
    DECL_PHP_CAIRO_TEXT_CLUSTER_FLAGS_T(cluster_flags);

    cairo_show_text_glyphs(cr, utf8, utf8_len, glyphs, num_glyphs, clusters, num_clusters, cluster_flags);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_font_extents(php_cairo_t cr, php_cairo_font_extents_t extents)
   Gets the font extents for the currently selected font. */
PHP_FUNCTION(cairo_font_extents)
{
    zval *zcr;
    zval *zextents;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zextents, php_cairo_font_extents_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_font_extents_t *php_extents = ZVAL_IS_PHP_CAIRO_FONT_EXTENTS_T(zextents)? ZVAL_GET_PHP_CAIRO_FONT_EXTENTS_T(zextents): NULL;
    DECL_PHP_CAIRO_FONT_EXTENTS_T(extents);

    cairo_font_extents(cr, extents);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_text_extents(php_cairo_t cr, string utf8, php_cairo_text_extents_t extents)
   Gets the extents for a string of text. */
PHP_FUNCTION(cairo_text_extents)
{
    zval *zcr;
    char *utf8;
    int utf8_len;
    zval *zextents;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_STRING(utf8, utf8_len)
        Z_PARAM_OBJECT_OF_CLASS_EX(zextents, php_cairo_text_extents_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_text_extents_t *php_extents = ZVAL_IS_PHP_CAIRO_TEXT_EXTENTS_T(zextents)? ZVAL_GET_PHP_CAIRO_TEXT_EXTENTS_T(zextents): NULL;
    DECL_PHP_CAIRO_TEXT_EXTENTS_T(extents);

    cairo_text_extents(cr, utf8, extents);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_glyph_extents(php_cairo_t cr, php_cairo_glyph_t glyphs, int num_glyphs, php_cairo_text_extents_t extents)
   Gets the extents for an array of glyphs. */
PHP_FUNCTION(cairo_glyph_extents)
{
    zval *zcr;
    zval *zglyphs;
    zend_long num_glyphs;
    zval *zextents;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zglyphs, php_cairo_glyph_t_class_entry, 1, 0)
        Z_PARAM_LONG(num_glyphs)
        Z_PARAM_OBJECT_OF_CLASS_EX(zextents, php_cairo_text_extents_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_glyph_t *php_glyphs = ZVAL_IS_PHP_CAIRO_GLYPH_T(zglyphs)? ZVAL_GET_PHP_CAIRO_GLYPH_T(zglyphs): NULL;
    DECL_PHP_CAIRO_GLYPH_T(glyphs);
    php_cairo_text_extents_t *php_extents = ZVAL_IS_PHP_CAIRO_TEXT_EXTENTS_T(zextents)? ZVAL_GET_PHP_CAIRO_TEXT_EXTENTS_T(zextents): NULL;
    DECL_PHP_CAIRO_TEXT_EXTENTS_T(extents);

    cairo_glyph_extents(cr, glyphs, num_glyphs, extents);
    RETURN_NULL();
}/* }}} */

/* {{{ proto php_cairo_font_face_t cairo_toy_font_face_create(string family, int slant, int weight)
   Creates a font face from a triplet of family, slant, and weight. */
PHP_FUNCTION(cairo_toy_font_face_create)
{
    char *family;
    int family_len;
    zval *zslant;
    zval *zweight;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_STRING(family, family_len)
        Z_PARAM_OBJECT_OF_CLASS_EX(zslant, php_cairo_font_slant_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zweight, php_cairo_font_weight_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_slant_t *php_slant = ZVAL_IS_PHP_CAIRO_FONT_SLANT_T(zslant)? ZVAL_GET_PHP_CAIRO_FONT_SLANT_T(zslant): NULL;
    DECL_PHP_CAIRO_FONT_SLANT_T(slant);
    php_cairo_font_weight_t *php_weight = ZVAL_IS_PHP_CAIRO_FONT_WEIGHT_T(zweight)? ZVAL_GET_PHP_CAIRO_FONT_WEIGHT_T(zweight): NULL;
    DECL_PHP_CAIRO_FONT_WEIGHT_T(weight);

    cairo_font_face_t *ret = cairo_toy_font_face_create(family, slant, weight);

    RETURN_OBJ(z_ret);
}/* }}} */

/* {{{ proto string cairo_toy_font_face_get_family(php_cairo_font_face_t font_face)
   Gets the family name of a toy font. */
PHP_FUNCTION(cairo_toy_font_face_get_family)
{
    zval *zfont_face;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zfont_face, php_cairo_font_face_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_face_t *php_font_face = ZVAL_IS_PHP_CAIRO_FONT_FACE_T(zfont_face)? ZVAL_GET_PHP_CAIRO_FONT_FACE_T(zfont_face): NULL;
    DECL_PHP_CAIRO_FONT_FACE_T(font_face);

    char ret = cairo_toy_font_face_get_family(font_face);

    RETURN_STRING(z_ret);
}/* }}} */

/* {{{ proto int cairo_toy_font_face_get_slant(php_cairo_font_face_t font_face)
   Gets the slant a toy font. */
PHP_FUNCTION(cairo_toy_font_face_get_slant)
{
    zval *zfont_face;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zfont_face, php_cairo_font_face_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_face_t *php_font_face = ZVAL_IS_PHP_CAIRO_FONT_FACE_T(zfont_face)? ZVAL_GET_PHP_CAIRO_FONT_FACE_T(zfont_face): NULL;
    DECL_PHP_CAIRO_FONT_FACE_T(font_face);

    cairo_font_slant_t ret = cairo_toy_font_face_get_slant(font_face);

    RETURN_LONG(ret);
}/* }}} */

/* {{{ proto int cairo_toy_font_face_get_weight(php_cairo_font_face_t font_face)
   Gets the weight a toy font. */
PHP_FUNCTION(cairo_toy_font_face_get_weight)
{
    zval *zfont_face;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zfont_face, php_cairo_font_face_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_face_t *php_font_face = ZVAL_IS_PHP_CAIRO_FONT_FACE_T(zfont_face)? ZVAL_GET_PHP_CAIRO_FONT_FACE_T(zfont_face): NULL;
    DECL_PHP_CAIRO_FONT_FACE_T(font_face);

    cairo_font_weight_t ret = cairo_toy_font_face_get_weight(font_face);

    RETURN_LONG(ret);
}/* }}} */

/* {{{ proto php_cairo_glyph_t cairo_glyph_allocate(int num_glyphs)
   Allocates an array of cairo_glyph_t's. */
PHP_FUNCTION(cairo_glyph_allocate)
{
    zend_long num_glyphs;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(num_glyphs)
    ZEND_PARSE_PARAMETERS_END();

    cairo_glyph_t *ret = cairo_glyph_allocate(num_glyphs);

    RETURN_OBJ(z_ret);
}/* }}} */

/* {{{ proto void cairo_glyph_free(php_cairo_glyph_t glyphs)
   Frees an array of cairo_glyph_t's allocated using cairo_glyph_allocat... */
PHP_FUNCTION(cairo_glyph_free)
{
    zval *zglyphs;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zglyphs, php_cairo_glyph_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_glyph_t *php_glyphs = ZVAL_IS_PHP_CAIRO_GLYPH_T(zglyphs)? ZVAL_GET_PHP_CAIRO_GLYPH_T(zglyphs): NULL;
    DECL_PHP_CAIRO_GLYPH_T(glyphs);

    cairo_glyph_free(glyphs);
    RETURN_NULL();
}/* }}} */

/* {{{ proto php_cairo_text_cluster_t cairo_text_cluster_allocate(int num_clusters)
   Allocates an array of cairo_text_cluster_t's. */
PHP_FUNCTION(cairo_text_cluster_allocate)
{
    zend_long num_clusters;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(num_clusters)
    ZEND_PARSE_PARAMETERS_END();

    cairo_text_cluster_t *ret = cairo_text_cluster_allocate(num_clusters);

    RETURN_OBJ(z_ret);
}/* }}} */

/* {{{ proto void cairo_text_cluster_free(php_cairo_text_cluster_t clusters)
   Frees an array of cairo_text_cluster's allocated using cairo_text_clu... */
PHP_FUNCTION(cairo_text_cluster_free)
{
    zval *zclusters;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zclusters, php_cairo_text_cluster_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_text_cluster_t *php_clusters = ZVAL_IS_PHP_CAIRO_TEXT_CLUSTER_T(zclusters)? ZVAL_GET_PHP_CAIRO_TEXT_CLUSTER_T(zclusters): NULL;
    DECL_PHP_CAIRO_TEXT_CLUSTER_T(clusters);

    cairo_text_cluster_free(clusters);
    RETURN_NULL();
}/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
