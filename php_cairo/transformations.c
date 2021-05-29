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
#include "php_cairo/matrix.h"

#include "php_cairo/transformations.h"


/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

/* {{{ proto void cairo_translate(php_cairo_t cr, int tx, int ty) */
PHP_FUNCTION(cairo_translate)
{
    zval *zcr;
    double tx;
    double ty;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(tx)
        Z_PARAM_DOUBLE(ty)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr =  php_cr==NULL ? NULL : php_cr->ptr;

    if (NULL==cr) {
        g_print("Internal Error: cairo_translate\n");
        return;
    }
    cairo_translate(cr, tx, ty);

}/* }}} */

/* {{{ proto void cairo_scale(php_cairo_t cr, int sx, int sy) */
PHP_FUNCTION(cairo_scale)
{
    zval *zcr;
    double sx;
    double sy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(sx)
        Z_PARAM_DOUBLE(sy)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr =  php_cr==NULL ? NULL : php_cr->ptr;

    if (NULL==cr) {
        g_print("Internal Error: cairo_scale\n");
        return;
    }
    cairo_scale(cr, sx, sy);

}/* }}} */

/* {{{ proto void cairo_rotate(php_cairo_t cr, int angle) */
PHP_FUNCTION(cairo_rotate)
{
    zval *zcr;
    double angle;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(angle)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr =  php_cr==NULL ? NULL : php_cr->ptr;

    if (NULL==cr) {
        g_print("Internal Error: cairo_rotate\n");
        return;
    }
    cairo_rotate(cr, angle);

}/* }}} */

/* {{{ proto void cairo_transform(php_cairo_t cr, mixed matrix) */
PHP_FUNCTION(cairo_transform)
{
    zval *zcr;
    zval *zmatrix;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr =  php_cr==NULL ? NULL : php_cr->ptr;
    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    cairo_matrix_t *matrix =  php_matrix==NULL ? NULL : php_matrix->ptr;

    if (NULL==cr) {
        g_print("Internal Error: cairo_transform\n");
        return;
    }
    cairo_transform(cr, matrix);

}/* }}} */

/* {{{ proto void cairo_set_matrix(php_cairo_t cr, mixed matrix) */
PHP_FUNCTION(cairo_set_matrix)
{
    zval *zcr;
    zval *zmatrix;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr =  php_cr==NULL ? NULL : php_cr->ptr;
    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    cairo_matrix_t *matrix =  php_matrix==NULL ? NULL : php_matrix->ptr;

    if (NULL==cr) {
        g_print("Internal Error: cairo_set_matrix\n");
        return;
    }
    cairo_set_matrix(cr, matrix);

}/* }}} */

/* {{{ proto void cairo_get_matrix(php_cairo_t cr, mixed matrix) */
PHP_FUNCTION(cairo_get_matrix)
{
    zval *zcr;
    zval *zmatrix;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr =  php_cr==NULL ? NULL : php_cr->ptr;
    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    cairo_matrix_t *matrix =  php_matrix==NULL ? NULL : php_matrix->ptr;

    if (NULL==cr) {
        g_print("Internal Error: cairo_get_matrix\n");
        return;
    }
    cairo_get_matrix(cr, matrix);

}/* }}} */

/* {{{ proto void cairo_identity_matrix(php_cairo_t cr) */
PHP_FUNCTION(cairo_identity_matrix)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr =  php_cr==NULL ? NULL : php_cr->ptr;

    if (NULL==cr) {
        g_print("Internal Error: cairo_identity_matrix\n");
        return;
    }
    cairo_identity_matrix(cr);

}/* }}} */

/* {{{ proto void cairo_user_to_device(php_cairo_t cr, int x, int y) */
PHP_FUNCTION(cairo_user_to_device)
{
    zval *zcr;
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr =  php_cr==NULL ? NULL : php_cr->ptr;

    if (NULL==cr) {
        g_print("Internal Error: cairo_user_to_device\n");
        return;
    }
    cairo_user_to_device(cr, x, y);

}/* }}} */

/* {{{ proto void cairo_user_to_device_distance(php_cairo_t cr, int dx, int dy) */
PHP_FUNCTION(cairo_user_to_device_distance)
{
    zval *zcr;
    double dx;
    double dy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(dx)
        Z_PARAM_DOUBLE(dy)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr =  php_cr==NULL ? NULL : php_cr->ptr;

    if (NULL==cr) {
        g_print("Internal Error: cairo_user_to_device_distance\n");
        return;
    }
    cairo_user_to_device_distance(cr, dx, dy);

}/* }}} */

/* {{{ proto void cairo_device_to_user(php_cairo_t cr, int x, int y) */
PHP_FUNCTION(cairo_device_to_user)
{
    zval *zcr;
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr =  php_cr==NULL ? NULL : php_cr->ptr;

    if (NULL==cr) {
        g_print("Internal Error: cairo_device_to_user\n");
        return;
    }
    cairo_device_to_user(cr, x, y);

}/* }}} */

/* {{{ proto void cairo_device_to_user_distance(php_cairo_t cr, int dx, int dy) */
PHP_FUNCTION(cairo_device_to_user_distance)
{
    zval *zcr;
    double dx;
    double dy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(dx)
        Z_PARAM_DOUBLE(dy)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr =  php_cr==NULL ? NULL : php_cr->ptr;

    if (NULL==cr) {
        g_print("Internal Error: cairo_device_to_user_distance\n");
        return;
    }
    cairo_device_to_user_distance(cr, dx, dy);

}/* }}} */


