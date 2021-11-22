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

#ifndef PHP_CAIRO_TRANSFORMS_H
#define PHP_CAIRO_TRANSFORMS_H


#if CAIRO_VERSION >= 10000
#define PHP_CAIRO_TRANSFORMS_FE_10000()  \
    PHP_GTK_FE(cairo_translate,        arginfo_cairo_translate)  \
    PHP_GTK_FE(cairo_scale,        arginfo_cairo_scale)  \
    PHP_GTK_FE(cairo_rotate,        arginfo_cairo_rotate)  \
    PHP_GTK_FE(cairo_transform,        arginfo_cairo_transform)  \
    PHP_GTK_FE(cairo_set_matrix,        arginfo_cairo_set_matrix)  \
    PHP_GTK_FE(cairo_get_matrix,        arginfo_cairo_get_matrix)  \
    PHP_GTK_FE(cairo_identity_matrix,        arginfo_cairo_identity_matrix)  \
    PHP_GTK_FE(cairo_user_to_device,        arginfo_cairo_user_to_device)  \
    PHP_GTK_FE(cairo_user_to_device_distance,        arginfo_cairo_user_to_device_distance)  \
    PHP_GTK_FE(cairo_device_to_user,        arginfo_cairo_device_to_user)  \
    PHP_GTK_FE(cairo_device_to_user_distance,        arginfo_cairo_device_to_user_distance)  \

#else
#define PHP_CAIRO_TRANSFORMS_FE_10000()
#endif


#define PHP_CAIRO_TRANSFORMS_FE() \
    PHP_CAIRO_TRANSFORMS_FE_10000() \


#define PHP_CAIRO_TRANSFORMS_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_transforms_class_init(container_ce, parent_ce)

#define PHP_CAIRO_TRANSFORMS_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_TRANSFORMS_RSHUTDOWN_FUNCTION() {\
}


zend_class_entry*
php_cairo_transforms_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);



ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_transforms___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_transforms, __construct);

#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_translate, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, tx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, ty, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_translate);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scale, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, sx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, sy, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scale);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_rotate, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, angle, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_rotate);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_transform, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_transform);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_set_matrix, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_matrix);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_get_matrix, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_matrix);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_identity_matrix, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_identity_matrix);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_user_to_device, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_user_to_device);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_user_to_device_distance, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, dx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, dy, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_user_to_device_distance);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_to_user, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_to_user);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_to_user_distance, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, dx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, dy, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_to_user_distance);
#endif


#endif	/* PHP_CAIRO_TRANSFORMS_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
