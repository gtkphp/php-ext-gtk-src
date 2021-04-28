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

#include "surface.h"
#include "image-surface.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;
extern zend_class_entry *php_cairo_surface_t_class_entry;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
| Internal                                                             |
+----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

/*{{{ php_cairo_image_surface_t_class_init */
zend_class_entry*
php_cairo_image_surface_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    return php_cairo_surface_t_class_entry;
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

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/
#if IS_IMPLEMENTED

/* {{{ proto int cairo_format_stride_for_width(mixed format, int width) */
PHP_FUNCTION(cairo_format_stride_for_width)
{
    zval *zformat = NULL;
    zval *zwidth = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zformat)
        Z_PARAM_ZVAL(zwidth)
    ZEND_PARSE_PARAMETERS_END();

    zval * *__format = zformat;
    zend_long  *__width = zwidth;
    php_cairo_image_surface_t *__ret = php_cairo_format_stride_for_width(, __format, __width);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */
#endif


/* {{{ proto mixed cairo_image_surface_create(mixed format, int width, int height) */
PHP_FUNCTION(cairo_image_surface_create)
{
    zval *zformat = NULL;
    zval *zwidth = NULL;
    zval *zheight = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zformat)
        Z_PARAM_ZVAL(zwidth)
        Z_PARAM_ZVAL(zheight)
    ZEND_PARSE_PARAMETERS_END();

    zend_long __format = zformat->value.lval;
    zend_long __width = zwidth->value.lval;
    zend_long __height = zheight->value.lval;
    cairo_surface_t *surface = cairo_image_surface_create((cairo_format_t)__format, (int)__width, (int)__height);
    zend_object *__ret = php_cairo_surface_t_create_object(php_cairo_surface_t_class_entry);
    ZOBJ_TO_PHP_CAIRO_SURFACE_T(__ret)->ptr = surface;

    RETURN_OBJ(__ret);
}/* }}} */


#if IS_IMPLEMENTED

/* {{{ proto mixed cairo_image_surface_create_for_data(mixed data, mixed format, int width, int height, int stride) */
PHP_FUNCTION(cairo_image_surface_create_for_data)
{
    zval *zdata = NULL;
    zval *zformat = NULL;
    zval *zwidth = NULL;
    zval *zheight = NULL;
    zval *zstride = NULL;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(zdata)
        Z_PARAM_ZVAL(zformat)
        Z_PARAM_ZVAL(zwidth)
        Z_PARAM_ZVAL(zheight)
        Z_PARAM_ZVAL(zstride)
    ZEND_PARSE_PARAMETERS_END();

    zval *__data = zdata;
    zval *__format = zformat;
    zend_long  *__width = zwidth;
    zend_long  *__height = zheight;
    zend_long  *__stride = zstride;
    php_cairo_image_surface_t *__ret = cairo_image_surface_create_for_data(__data, __format, __width, __height, __stride);

    RETURN_NULL();
}/* }}} */

/* {{{ proto mixed cairo_image_surface_get_data(mixed surface) */
PHP_FUNCTION(cairo_image_surface_get_data)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *__surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    unsigned char *__ret = cairo_image_surface_get_data(__surface);

    // TODO:
    //RETURN_ARR();SPL_ARRAY

    RETURN_NULL();
}/* }}} */
#endif

/* {{{ proto mixed cairo_image_surface_get_format(mixed surface) */
PHP_FUNCTION(cairo_image_surface_get_format)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *__surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    int __ret = cairo_image_surface_get_format(__surface->ptr);

    RETURN_LONG(__ret);
}/* }}} */

/* {{{ proto int cairo_image_surface_get_width(mixed surface) */
PHP_FUNCTION(cairo_image_surface_get_width)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *__surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    int __ret = cairo_image_surface_get_width(__surface->ptr);

    RETURN_LONG(__ret);
}/* }}} */

/* {{{ proto int cairo_image_surface_get_height(mixed surface) */
PHP_FUNCTION(cairo_image_surface_get_height)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *__surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    int __ret = cairo_image_surface_get_height(__surface->ptr);

    RETURN_LONG(__ret);
}/* }}} */

/* {{{ proto int cairo_image_surface_get_stride(mixed surface) */
PHP_FUNCTION(cairo_image_surface_get_stride)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *__surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    int __ret = cairo_image_surface_get_stride(__surface->ptr);

    RETURN_LONG(__ret);
}/* }}} */
