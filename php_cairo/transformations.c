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
#include "php_cairo/cairo.h"
#include "php_cairo/matrix.h"
#include "php_cairo/transformations.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_transforms_class_entry;// struct
zend_object_handlers  php_cairo_transforms_handlers;



/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/


/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

#if CAIRO_VERSION >= 10000
/* {{{ proto void cairo_translate(php_cairo_t cr, double tx, double ty)
   Modifies the current transformation matrix (CTM) by translating the u... */
PHP_FUNCTION(cairo_translate)
{
    zval *zcr;
    double tx;
    double ty;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(tx);
        Z_PARAM_DOUBLE(ty);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_translate(cr, tx, ty);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_scale(php_cairo_t cr, double sx, double sy)
   Modifies the current transformation matrix (CTM) by scaling the X and... */
PHP_FUNCTION(cairo_scale)
{
    zval *zcr;
    double sx;
    double sy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(sx);
        Z_PARAM_DOUBLE(sy);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_scale(cr, sx, sy);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_rotate(php_cairo_t cr, double angle)
   Modifies the current transformation matrix (CTM) by rotating the user... */
PHP_FUNCTION(cairo_rotate)
{
    zval *zcr;
    double angle;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(angle);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_rotate(cr, angle);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_transform(php_cairo_t cr, php_cairo_matrix_t matrix)
   Modifies the current transformation matrix (CTM) by applying matrix a... */
PHP_FUNCTION(cairo_transform)
{
    zval *zcr;
    zval *zmatrix;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_transform(cr, matrix);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_set_matrix(php_cairo_t cr, php_cairo_matrix_t matrix)
   Modifies the current transformation matrix (CTM) by setting it equal ... */
PHP_FUNCTION(cairo_set_matrix)
{
    zval *zcr;
    zval *zmatrix;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_set_matrix(cr, matrix);
    PHP_CAIRO_MATRIX_T_SET(php_matrix, matrix);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_get_matrix(php_cairo_t cr, php_cairo_matrix_t matrix)
   Stores the current transformation matrix (CTM) into matrix . */
PHP_FUNCTION(cairo_get_matrix)
{
    zval *zcr;
    zval *zmatrix;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_get_matrix(cr, matrix);
    PHP_CAIRO_MATRIX_T_SET(php_matrix, matrix);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_identity_matrix(php_cairo_t cr)
   Resets the current transformation matrix (CTM) by setting it equal to... */
PHP_FUNCTION(cairo_identity_matrix)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_identity_matrix(cr);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_user_to_device(php_cairo_t cr, double x, double y)
   Transform a coordinate from user space to device space by multiplying... */
PHP_FUNCTION(cairo_user_to_device)
{
    zval *zcr;
    zval *zx;
    zval *zy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zx, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zy, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    double x = zx->value.dval;
    double y = zy->value.dval;

    cairo_user_to_device(cr, &x, &y);
    ZVAL_DOUBLE(zx, x);
    ZVAL_DOUBLE(zy, y);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_user_to_device_distance(php_cairo_t cr, double dx, double dy)
   Transform a distance vector from user space to device space. */
PHP_FUNCTION(cairo_user_to_device_distance)
{
    zval *zcr;
    zval *zdx;
    zval *zdy;
    //zend_bool zdx_is_null;
    //zend_bool zdy_is_null;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        //Z_PARAM_DOUBLE_EX2(zdx, zdx_is_null, 0, ZEND_SEND_BY_REF, 1);
        //Z_PARAM_DOUBLE_EX2(zdy, zdy_is_null, 0, ZEND_SEND_BY_REF, 1);
        Z_PARAM_ZVAL_EX2(zdx, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zdy, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    double dx = zdx->value.dval;
    double dy = zdy->value.dval;

    cairo_user_to_device_distance(cr, &dx, &dy);
    ZVAL_DOUBLE(zdx, dx);
    ZVAL_DOUBLE(zdy, dy);
    //ZVAL_SET_DOUBLE(zdx, dx);
    //ZVAL_SET_DOUBLE(zdy, dy);

    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_device_to_user(php_cairo_t cr, double x, double y)
   Transform a coordinate from device space to user space by multiplying... */
PHP_FUNCTION(cairo_device_to_user)
{
    zval *zcr;
    zval *zx;
    zval *zy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zx, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zy, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    double x = zx->value.dval;
    double y = zy->value.dval;

    cairo_device_to_user(cr, &x, &y);
    ZVAL_DOUBLE(zx, x);
    ZVAL_DOUBLE(zy, y);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_device_to_user_distance(php_cairo_t cr, double dx, double dy)
   Transform a distance vector from device space to user space. */
PHP_FUNCTION(cairo_device_to_user_distance)
{
    zval *zcr;
    zval *zdx;
    zval *zdy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zdx, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zdy, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    double dx = zdx->value.dval;
    double dy = zdy->value.dval;

    cairo_device_to_user_distance(cr, &dx, &dy);
    ZVAL_DOUBLE(zdx, dx);
    ZVAL_DOUBLE(zdy, dy);
    RETURN_NULL();
}/* }}} */
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
