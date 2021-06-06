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
#include "php_cairo/status.h"

#include "php_cairo/matrix.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_matrix_t_class_entry;// struct
zend_object_handlers  php_cairo_matrix_t_handlers;




enum _php_cairo_matrix_t_properties {
    PHP_CAIRO_MATRIX_T_XX = 1,
    PHP_CAIRO_MATRIX_T_YX = 2,
    PHP_CAIRO_MATRIX_T_XY = 3,
    PHP_CAIRO_MATRIX_T_YY = 4,
    PHP_CAIRO_MATRIX_T_X0 = 5,
    PHP_CAIRO_MATRIX_T_Y0 = 6
};
//typedef enum php_cairo_matrix_t_properties php_cairo_matrix_t_properties;



/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_matrix_t_methods[] = {
    PHP_ME(cairo_matrix_t, __construct, arginfo_cairo_matrix_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_matrix_t_create_object */
static zend_object*
php_cairo_matrix_t_create_object(zend_class_entry *class_type)
{
    php_cairo_matrix_t *intern = zend_object_alloc(sizeof(php_cairo_matrix_t), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);


    ZVAL_DOUBLE(&intern->xx, 0.0);
    ZVAL_DOUBLE(&intern->yx, 0.0);
    ZVAL_DOUBLE(&intern->xy, 0.0);
    ZVAL_DOUBLE(&intern->yy, 0.0);
    ZVAL_DOUBLE(&intern->x0, 0.0);
    ZVAL_DOUBLE(&intern->y0, 0.0);

    intern->std.handlers = &php_cairo_matrix_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_matrix_t_create_object */


static void
php_cairo_matrix_t_dtor_object(zend_object *obj) {
    //php_cairo_matrix_t *intern = ZOBJ_TO_PHP_CAIRO_MATRIX_T(obj);

}

/* {{{ php_cairo_matrix_t_free_object */
static void
php_cairo_matrix_t_free_object(zend_object *object)
{
    php_cairo_matrix_t *intern = ZOBJ_TO_PHP_CAIRO_MATRIX_T(object);

    Z_TRY_DELREF(intern->xx);
    Z_TRY_DELREF(intern->yx);
    Z_TRY_DELREF(intern->xy);
    Z_TRY_DELREF(intern->yy);
    Z_TRY_DELREF(intern->x0);
    Z_TRY_DELREF(intern->y0);

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_matrix_t_free_object */




/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_cairo_matrix_t_setter_double(php_cairo_matrix_t *intern, zval *value, char *name, zval *dest) {
    if (Z_TYPE_P(value)==IS_DOUBLE) {
        ZVAL_SET_DOUBLE(dest, value->value.dval);
    } else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        const char *type_name = zend_zval_type_name(value);
        if (strict_types) {
            zend_type_error("Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\cairo_matrix_t::$%s of type float,", type_name, name);
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
            zend_error(E_USER_NOTICE, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\cairo_matrix_t::$%s of type float,", type_name, name);
        }
    }
}




struct PhpCairoMatrixTProperty {
  const char *name;
  int code;
  void (*setter) (php_cairo_matrix_t *intern, zval *rvalue, char *name, zval *dest);
};

static const struct PhpCairoMatrixTProperty php_cairo_matrix_t_properties[] = {
    {"xx", PHP_CAIRO_MATRIX_T_XX, php_cairo_matrix_t_setter_double},
    {"yx", PHP_CAIRO_MATRIX_T_YX, php_cairo_matrix_t_setter_double},
    {"xy", PHP_CAIRO_MATRIX_T_XY, php_cairo_matrix_t_setter_double},
    {"yy", PHP_CAIRO_MATRIX_T_YY, php_cairo_matrix_t_setter_double},
    {"x0", PHP_CAIRO_MATRIX_T_X0, php_cairo_matrix_t_setter_double},
    {"y0", PHP_CAIRO_MATRIX_T_Y0, php_cairo_matrix_t_setter_double}
};


const struct PhpCairoMatrixTProperty*
php_cairo_matrix_t_properties_lookup (const char *str, size_t len)
{
    if (len == 2) {
        if (str[0] == 'x' && str[1] == 'x') {
            return &php_cairo_matrix_t_properties[0];
        } else if (str[0] == 'y' && str[1] == 'x') {
            return &php_cairo_matrix_t_properties[1];
        } else if (str[0] == 'x' && str[1] == 'y') {
            return &php_cairo_matrix_t_properties[2];
        } else if (str[0] == 'y' && str[1] == 'y') {
            return &php_cairo_matrix_t_properties[3];
        } else if (str[0] == 'x' && str[1] == '0') {
            return &php_cairo_matrix_t_properties[4];
        } else if (str[0] == 'y' && str[1] == '0') {
            return &php_cairo_matrix_t_properties[5];
        }
    }
    return 0;
}

/* {{{ php_cairo_matrix_t_read_property */
static zval*
php_cairo_matrix_t_read_property(zend_object *object, zend_string *member_str, int type, void **cache_slot, zval *rv)
{
    php_cairo_matrix_t *intern = ZOBJ_TO_PHP_CAIRO_MATRIX_T(object);

    const struct PhpCairoMatrixTProperty *cmd = php_cairo_matrix_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_MATRIX_T_XX:
            ZVAL_COPY(rv, &intern->xx);
            return rv;
            break;
        case PHP_CAIRO_MATRIX_T_YX:
            ZVAL_COPY(rv, &intern->yx);
            return rv;
            break;
        case PHP_CAIRO_MATRIX_T_XY:
            ZVAL_COPY(rv, &intern->xy);
            return rv;
            break;
        case PHP_CAIRO_MATRIX_T_YY:
            ZVAL_COPY(rv, &intern->yy);
            return rv;
            break;
        case PHP_CAIRO_MATRIX_T_X0:
            ZVAL_COPY(rv, &intern->x0);
            return rv;
            break;
        case PHP_CAIRO_MATRIX_T_Y0:
            ZVAL_COPY(rv, &intern->y0);
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

/* {{{ php_cairo_matrix_t_write_property */
static zval*
php_cairo_matrix_t_write_property(zend_object *object, zend_string *member_str, zval *value, void **cache_slot)
{
    php_cairo_matrix_t *intern = ZOBJ_TO_PHP_CAIRO_MATRIX_T(object);
    // struct
    const struct PhpCairoMatrixTProperty *cmd = php_cairo_matrix_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_MATRIX_T_XX:
            cmd->setter(intern, value, member_str->val, &intern->xx);
        break;
        case PHP_CAIRO_MATRIX_T_YX:
            cmd->setter(intern, value, member_str->val, &intern->yx);
        break;
        case PHP_CAIRO_MATRIX_T_XY:
            cmd->setter(intern, value, member_str->val, &intern->xy);
        break;
        case PHP_CAIRO_MATRIX_T_YY:
            cmd->setter(intern, value, member_str->val, &intern->yy);
        break;
        case PHP_CAIRO_MATRIX_T_X0:
            cmd->setter(intern, value, member_str->val, &intern->x0);
        break;
        case PHP_CAIRO_MATRIX_T_Y0:
            cmd->setter(intern, value, member_str->val, &intern->y0);
        break;
        }
    } else {
        // property not found
    }
    return value;
}
/* }}} */

/* {{{ php_cairo_matrix_t_get_property_ptr_ptr */
static zval*
php_cairo_matrix_t_get_property_ptr_ptr(zend_object *object, zend_string *member_str, int type, void **cache_slot)
{
    php_cairo_matrix_t *intern = ZOBJ_TO_PHP_CAIRO_MATRIX_T(object);
    zval *retval = NULL;

    const struct PhpCairoMatrixTProperty *cmd = php_cairo_matrix_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_MATRIX_T_XX:
            return &intern->xx;
        case PHP_CAIRO_MATRIX_T_YX:
            return &intern->yx;
        case PHP_CAIRO_MATRIX_T_XY:
            return &intern->xy;
        case PHP_CAIRO_MATRIX_T_YY:
            return &intern->yy;
        case PHP_CAIRO_MATRIX_T_X0:
            return &intern->x0;
        case PHP_CAIRO_MATRIX_T_Y0:
            return &intern->y0;
        }
    } else {
        // Error
    }

    return retval;
}/* }}} */





/* {{{ php_cairo_matrix_t_get_debug_info */
static HashTable*
php_cairo_matrix_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_matrix_t  *intern = ZOBJ_TO_PHP_CAIRO_MATRIX_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    zval zxx; ZVAL_COPY(&zxx, &intern->xx);
    zend_hash_str_update(debug_info, "xx", sizeof("xx")-1, &zxx);
    zval zyx; ZVAL_COPY(&zyx, &intern->yx);
    zend_hash_str_update(debug_info, "yx", sizeof("yx")-1, &zyx);
    zval zxy; ZVAL_COPY(&zxy, &intern->xy);
    zend_hash_str_update(debug_info, "xy", sizeof("xy")-1, &zxy);
    zval zyy; ZVAL_COPY(&zyy, &intern->yy);
    zend_hash_str_update(debug_info, "yy", sizeof("yy")-1, &zyy);
    zval zx0; ZVAL_COPY(&zx0, &intern->x0);
    zend_hash_str_update(debug_info, "x0", sizeof("x0")-1, &zx0);
    zval zy0; ZVAL_COPY(&zy0, &intern->y0);
    zend_hash_str_update(debug_info, "y0", sizeof("y0")-1, &zy0);

    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_matrix_t_get_handlers()
{
    memcpy(&php_cairo_matrix_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_matrix_t_handlers.offset = PHP_CAIRO_MATRIX_T_OFFSET;
    php_cairo_matrix_t_handlers.dtor_obj = php_cairo_matrix_t_dtor_object;
    php_cairo_matrix_t_handlers.free_obj = php_cairo_matrix_t_free_object;

    php_cairo_matrix_t_handlers.read_property = php_cairo_matrix_t_read_property;
    php_cairo_matrix_t_handlers.write_property = php_cairo_matrix_t_write_property;
    php_cairo_matrix_t_handlers.get_property_ptr_ptr = php_cairo_matrix_t_get_property_ptr_ptr;

    php_cairo_matrix_t_handlers.get_debug_info = php_cairo_matrix_t_get_debug_info;


    return &php_cairo_matrix_t_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_matrix_t_class_init */
zend_class_entry*
php_cairo_matrix_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_matrix_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_matrix_t", php_cairo_matrix_t_methods);
    php_cairo_matrix_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_matrix_t_class_entry->create_object = php_cairo_matrix_t_create_object;

    return php_cairo_matrix_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/
php_cairo_matrix_t *
php_cairo_matrix_t_new() {
    zend_object *zobj = php_cairo_matrix_t_create_object(php_cairo_matrix_t_class_entry);
    php_cairo_matrix_t *matrix = ZOBJ_TO_PHP_CAIRO_MATRIX_T(zobj);
    return matrix;
}

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

 /* {{{ cairo_matrix_t::__construct() */
PHP_METHOD(cairo_matrix_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_matrix_t *self = ZOBJ_TO_PHP_CAIRO_MATRIX_T(zobj);


}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

/* {{{ proto void cairo_matrix_init(php_cairo_matrix_t matrix, double xx, double yx, double xy, double yy, double x0, double y0)
   Sets matrix to be the affine transformation given by xx , yx , xy , y... */
PHP_FUNCTION(cairo_matrix_init)
{
    zval *zmatrix;
    double xx;
    double yx;
    double xy;
    double yy;
    double x0;
    double y0;

    ZEND_PARSE_PARAMETERS_START(7, 7)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(xx);
        Z_PARAM_DOUBLE(yx);
        Z_PARAM_DOUBLE(xy);
        Z_PARAM_DOUBLE(yy);
        Z_PARAM_DOUBLE(x0);
        Z_PARAM_DOUBLE(y0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_matrix_init(matrix, xx, yx, xy, yy, x0, y0);
    PHP_CAIRO_MATRIX_T_SET(php_matrix, matrix);

    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_matrix_init_identity(php_cairo_matrix_t matrix)
   Modifies matrix to be an identity transformation. */
PHP_FUNCTION(cairo_matrix_init_identity)
{
    zval *zmatrix;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_matrix_init_identity(matrix);
    PHP_CAIRO_MATRIX_T_SET(php_matrix, matrix);

    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_matrix_init_translate(php_cairo_matrix_t matrix, double tx, double ty)
   Initializes matrix to a transformation that translates by tx and ty i... */
PHP_FUNCTION(cairo_matrix_init_translate)
{
    zval *zmatrix;
    double tx;
    double ty;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(tx);
        Z_PARAM_DOUBLE(ty);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_matrix_init_translate(matrix, tx, ty);
    PHP_CAIRO_MATRIX_T_SET(php_matrix, matrix);

    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_matrix_init_scale(php_cairo_matrix_t matrix, double sx, double sy)
   Initializes matrix to a transformation that scales by sx and sy in th... */
PHP_FUNCTION(cairo_matrix_init_scale)
{
    zval *zmatrix;
    double sx;
    double sy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(sx);
        Z_PARAM_DOUBLE(sy);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_matrix_init_scale(matrix, sx, sy);
    PHP_CAIRO_MATRIX_T_SET(php_matrix, matrix);

    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_matrix_init_rotate(php_cairo_matrix_t matrix, double radians)
   Initialized matrix to a transformation that rotates by radians . */
PHP_FUNCTION(cairo_matrix_init_rotate)
{
    zval *zmatrix;
    double radians;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(radians);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_matrix_init_rotate(matrix, radians);
    PHP_CAIRO_MATRIX_T_SET(php_matrix, matrix);

    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_matrix_translate(php_cairo_matrix_t matrix, double tx, double ty)
   Applies a translation by tx , ty to the transformation in matrix . */
PHP_FUNCTION(cairo_matrix_translate)
{
    zval *zmatrix;
    double tx;
    double ty;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(tx);
        Z_PARAM_DOUBLE(ty);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_matrix_translate(matrix, tx, ty);
    PHP_CAIRO_MATRIX_T_SET(php_matrix, matrix);

    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_matrix_scale(php_cairo_matrix_t matrix, double sx, double sy)
   Applies scaling by sx , sy to the transformation in matrix . */
PHP_FUNCTION(cairo_matrix_scale)
{
    zval *zmatrix;
    double sx;
    double sy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(sx);
        Z_PARAM_DOUBLE(sy);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_matrix_scale(matrix, sx, sy);
    PHP_CAIRO_MATRIX_T_SET(php_matrix, matrix);

    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_matrix_rotate(php_cairo_matrix_t matrix, double radians)
   Applies rotation by radians to the transformation in matrix . */
PHP_FUNCTION(cairo_matrix_rotate)
{
    zval *zmatrix;
    double radians;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(radians);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_matrix_rotate(matrix, radians);
    PHP_CAIRO_MATRIX_T_SET(php_matrix, matrix);

    RETURN_NULL();
}/* }}} */

/* {{{ proto int cairo_matrix_invert(php_cairo_matrix_t matrix)
   Changes matrix to be the inverse of its original value. */
PHP_FUNCTION(cairo_matrix_invert)
{
    zval *zmatrix;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_status_t ret = cairo_matrix_invert(matrix);
    PHP_CAIRO_MATRIX_T_SET(php_matrix, matrix);

    RETURN_LONG(ret);
}/* }}} */

/* {{{ proto void cairo_matrix_multiply(php_cairo_matrix_t result, php_cairo_matrix_t a, php_cairo_matrix_t b)
   Multiplies the affine transformations in a and b together and stores ... */
PHP_FUNCTION(cairo_matrix_multiply)
{
    zval *zresult;
    zval *za;
    zval *zb;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL_EX2(zresult, 0, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(za, php_cairo_matrix_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zb, php_cairo_matrix_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix_t *php_result = ZVAL_IS_PHP_CAIRO_MATRIX_T(zresult)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zresult): php_cairo_matrix_t_new();
    DECL_PHP_CAIRO_MATRIX_T(result);
    php_cairo_matrix_t *php_a = ZVAL_IS_PHP_CAIRO_MATRIX_T(za)? ZVAL_GET_PHP_CAIRO_MATRIX_T(za): NULL;
    DECL_PHP_CAIRO_MATRIX_T(a);
    php_cairo_matrix_t *php_b = ZVAL_IS_PHP_CAIRO_MATRIX_T(zb)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zb): NULL;
    DECL_PHP_CAIRO_MATRIX_T(b);

    cairo_matrix_multiply(result, a, b);
    PHP_CAIRO_MATRIX_T_SET(php_result, result);

    ZVAL_OBJ(zresult, &php_result->std);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_matrix_transform_distance(php_cairo_matrix_t matrix, double dx, double dy)
   Transforms the distance vector (dx ,dy ) by matrix . */
PHP_FUNCTION(cairo_matrix_transform_distance)
{
    zval *zmatrix;
    zval *zdx;
    zval *zdy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zdx, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zdy, 0, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);
    double dx = zdx->value.dval;
    double dy = zdy->value.dval;

    cairo_matrix_transform_distance(matrix, &dx, &dy);
    ZVAL_DOUBLE(zdx, dx);
    ZVAL_DOUBLE(zdy, dy);

    ZVAL_DOUBLE(zdx, dx);
    ZVAL_DOUBLE(zdy, dy);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_matrix_transform_point(php_cairo_matrix_t matrix, double x, double y)
   Transforms the point (x , y ) by matrix . */
PHP_FUNCTION(cairo_matrix_transform_point)
{
    zval *zmatrix;
    zval *zx;
    zval *zy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zx, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zy, 0, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);
    double x = zx->value.dval;
    double y = zy->value.dval;

    cairo_matrix_transform_point(matrix, &x, &y);
    ZVAL_DOUBLE(zx, x);
    ZVAL_DOUBLE(zy, y);

    ZVAL_DOUBLE(zx, x);
    ZVAL_DOUBLE(zy, y);
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
