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
/* {{{ proto php_cairo_surface_t cairo_image_surface_create(int format, int width, int height)
   Creates an image surface of the specified format and dimensions. */
PHP_FUNCTION(cairo_image_surface_create)
{
    zend_long zformat;
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_LONG(zformat);
        Z_PARAM_LONG(width);
        Z_PARAM_LONG(height);
    ZEND_PARSE_PARAMETERS_END();

    cairo_format_t format = zformat;

    cairo_surface_t *ret = cairo_image_surface_create(format, width, height);

    php_cairo_surface_t *php_ret = php_cairo_surface_t_new();
    php_ret->ptr = ret;
    RETURN_OBJ(&php_ret->std);

}/* }}} */


static void
php_cairo_image_surface_destroy_func_t(void *data){
    efree(data);
}

/* {{{ proto php_cairo_surface_t cairo_image_surface_create_for_data(unsigned char data, int format, int width, int height, int stride)
   Creates an image surface for the provided pixel data. */
PHP_FUNCTION(cairo_image_surface_create_for_data)
{
    char *data;
    size_t data_len;
    zend_long zformat;
    zend_long width;
    zend_long height;
    zend_long stride;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_STRING(data, data_len);
        Z_PARAM_LONG(zformat);
        Z_PARAM_LONG(width);
        Z_PARAM_LONG(height);
        Z_PARAM_LONG(stride);
    ZEND_PARSE_PARAMETERS_END();

    cairo_format_t format = zformat;

    unsigned char *user_data;
    user_data = emalloc(sizeof(unsigned char)*stride*height);
    memset(user_data, 0, sizeof(unsigned char)*stride*height);
    memcpy(user_data, data, data_len);
    cairo_surface_t *ret = cairo_image_surface_create_for_data(user_data, format, width, height, stride);
    php_cairo_surface_t *php_ret = php_cairo_surface_t_new();
    php_ret->ptr = ret;
    zend_object *z_ret = &php_ret->std;
    cairo_status_t status =
    cairo_surface_set_user_data (ret,
                                 &php_ret->key,
                                 (void *)user_data,
                                 php_cairo_image_surface_destroy_func_t);

    RETURN_OBJ(z_ret);
}/* }}} */

#if CAIRO_VERSION >= 10200
/* {{{ proto unsigned char cairo_image_surface_get_data(php_cairo_surface_t surface)
   Get a pointer to the data of the image surface, for direct inspection... */
PHP_FUNCTION(cairo_image_surface_get_data)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);


    cairo_surface_flush(surface);
    unsigned char *ret = cairo_image_surface_get_data(surface);
    int height = cairo_image_surface_get_height (surface);
    int stride = cairo_image_surface_get_stride(surface);
    zend_string *z_ret;
    z_ret = zend_string_init((const char*)ret, height*stride, 0);

    RETURN_STR(z_ret);
}/* }}} */
/* {{{ proto int cairo_image_surface_get_format(php_cairo_surface_t surface)
   Get the format of the surface. */
PHP_FUNCTION(cairo_image_surface_get_format)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    int ret = cairo_image_surface_get_format(surface);

    RETURN_LONG(ret);
}/* }}} */
#endif

/* {{{ proto int cairo_image_surface_get_width(php_cairo_surface_t surface)
   Get the width of the image surface in pixels. */
PHP_FUNCTION(cairo_image_surface_get_width)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    int ret = cairo_image_surface_get_width(surface);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto int cairo_image_surface_get_height(php_cairo_surface_t surface)
   Get the height of the image surface in pixels. */
PHP_FUNCTION(cairo_image_surface_get_height)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    int ret = cairo_image_surface_get_height(surface);

    RETURN_LONG(ret);
}/* }}} */

#if CAIRO_VERSION >= 10200
/* {{{ proto int cairo_image_surface_get_stride(php_cairo_surface_t surface)
   Get the stride of the image surface in bytes */
PHP_FUNCTION(cairo_image_surface_get_stride)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    int ret = cairo_image_surface_get_stride(surface);

    RETURN_LONG(ret);
}/* }}} */
#endif
