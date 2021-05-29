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

#ifndef PHP_CAIRO_TRANSFORMATIONS_H
#define PHP_CAIRO_TRANSFORMATIONS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#define PHP_CAIRO_TRANSFORMATIONS_FE() \
    PHP_GTK_FE(cairo_translate,               arginfo_cairo_translate) \
    PHP_GTK_FE(cairo_scale,                   arginfo_cairo_scale) \
    PHP_GTK_FE(cairo_rotate,                  arginfo_cairo_rotate) \
    PHP_GTK_FE(cairo_transform,               arginfo_cairo_transform) \
    PHP_GTK_FE(cairo_set_matrix,              arginfo_cairo_set_matrix) \
    PHP_GTK_FE(cairo_get_matrix,              arginfo_cairo_get_matrix) \
    PHP_GTK_FE(cairo_identity_matrix,         arginfo_cairo_identity_matrix) \
    PHP_GTK_FE(cairo_user_to_device,          arginfo_cairo_user_to_device) \
    PHP_GTK_FE(cairo_user_to_device_distance, arginfo_cairo_user_to_device_distance) \
    PHP_GTK_FE(cairo_device_to_user,          arginfo_cairo_device_to_user) \
    PHP_GTK_FE(cairo_device_to_user_distance, arginfo_cairo_device_to_user_distance) \

#define PHP_CAIRO_TRANSFORMATIONS_MINIT_FUNCTION(container_ce, parent_ce)

#define PHP_CAIRO_TRANSFORMATIONS_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_TRANSFORMATIONS_RSHUTDOWN_FUNCTION() {\
}



ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_translate, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, tx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, ty, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_translate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_scale, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, sx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, sy, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scale);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_rotate, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, angle, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_rotate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_transform, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_transform);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_matrix, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_matrix);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_matrix, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_matrix);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_identity_matrix, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_identity_matrix);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_user_to_device, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_user_to_device);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_user_to_device_distance, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dy, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_user_to_device_distance);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_device_to_user, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_to_user);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_device_to_user_distance, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dy, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_to_user_distance);



#endif	/* PHP_CAIRO_TRANSFORMATIONS_H */

/*
* Local variables:
* tab-width: 4
* c-basic-offset: 4
* End:
* vim600: noet sw=4 ts=4 fdm=marker
* vim<600: noet sw=4 ts=4
*/
