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

#ifndef PHP_CAIRO_IMAGE_SURFACE_T_H
#define PHP_CAIRO_IMAGE_SURFACE_T_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if CAIRO_VERSION >= 10200
#define PHP_CAIRO_IMAGE_SURFACE_FE_10200() \
    PHP_GTK_FE(cairo_image_surface_get_data,        arginfo_cairo_image_surface_get_data) \
    PHP_GTK_FE(cairo_image_surface_get_format,      arginfo_cairo_image_surface_get_format) \
    PHP_GTK_FE(cairo_image_surface_get_stride,      arginfo_cairo_image_surface_get_stride)
#else
#define PHP_CAIRO_IMAGE_SURFACE_FE_10200()
#endif


#if CAIRO_VERSION >= 10000
#define PHP_CAIRO_IMAGE_SURFACE_FE_10000() \
    PHP_GTK_FE(cairo_image_surface_create,          arginfo_cairo_image_surface_create) \
    PHP_GTK_FE(cairo_image_surface_create_for_data, arginfo_cairo_image_surface_create_for_data) \
    PHP_GTK_FE(cairo_image_surface_get_width,       arginfo_cairo_image_surface_get_width) \
    PHP_GTK_FE(cairo_image_surface_get_height,      arginfo_cairo_image_surface_get_height)
#else
#define PHP_CAIRO_IMAGE_SURFACE_FE_10000()
#endif


#define PHP_CAIRO_IMAGE_SURFACE_FE() \
    PHP_CAIRO_IMAGE_SURFACE_FE_10200() \
    PHP_CAIRO_IMAGE_SURFACE_FE_10000()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_image_surface_create, ZEND_RETURN_VALUE, 3, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, format, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, height, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_create);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_image_surface_create_for_data, ZEND_RETURN_VALUE, 5, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, data, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, format, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, height, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, stride, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_create_for_data);
#if CAIRO_VERSION >= 10200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_image_surface_get_data, ZEND_RETURN_VALUE, 1, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_get_data);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_image_surface_get_format, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_get_format);
#endif
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_image_surface_get_width, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_get_width);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_image_surface_get_height, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_get_height);
#if CAIRO_VERSION >= 10200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_image_surface_get_stride, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_get_stride);
#endif


#endif	/* PHP_CAIRO_IMAGE_SURFACE_T_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
