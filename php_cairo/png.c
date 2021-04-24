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

#include "surface.h"
#include "png.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;

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
zval *
php_cairo_image_surface_create_from_png(zval *filename) {
    // TODO: implementation
}

zval *
php_cairo_image_surface_create_from_png_stream(zval *read_func, void *closure) {
    // TODO: implementation
}

zval *
php_cairo_surface_write_to_png(zval *surface, zval *filename) {
    // TODO: implementation
}

zval *
php_cairo_surface_write_to_png_stream(zval *surface, zval *write_func, void *closure) {
    // TODO: implementation
}




/*----------------------------------------------------------------------+
| PHP_METHOD                                                           |
+----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/

/* {{{ proto mixed cairo_image_surface_create_from_png(mixed filename) */
PHP_FUNCTION(cairo_image_surface_create_from_png)
{
    zval *zfilename = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zfilename)
    ZEND_PARSE_PARAMETERS_END();
#if 0
    zval * *__filename = zfilename;
    php_cairo_png_t *__ret = php_cairo_image_surface_create_from_png(, __filename);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_image_surface_create_from_png_stream(mixed read_func, void closure) */
PHP_FUNCTION(cairo_image_surface_create_from_png_stream)
{
    zval *zread_func = NULL;
    zval *zclosure = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zread_func)
        Z_PARAM_ZVAL(zclosure)
    ZEND_PARSE_PARAMETERS_END();
#if 0
    zval * *__read_func = zread_func;
    void  *__closure = zclosure;
    php_cairo_png_t *__ret = php_cairo_image_surface_create_from_png_stream(, __read_func, __closure);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_surface_write_to_png(mixed surface, mixed filename) */
PHP_FUNCTION(cairo_surface_write_to_png)
{
    zval *zsurface = NULL;
    zval *zfilename = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zfilename)
    ZEND_PARSE_PARAMETERS_END();


    php_cairo_surface_t *__surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface) ? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface) : NULL;
    char *__filename = zfilename->value.str->val;
    int __ret = cairo_surface_write_to_png(__surface->ptr, __filename);

    RETURN_LONG(__ret);
}/* }}} */

/* {{{ proto mixed cairo_surface_write_to_png_stream(mixed surface, mixed write_func, void closure) */
PHP_FUNCTION(cairo_surface_write_to_png_stream)
{
    zval *zsurface = NULL;
    zval *zwrite_func = NULL;
    zval *zclosure = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zwrite_func)
        Z_PARAM_ZVAL(zclosure)
    ZEND_PARSE_PARAMETERS_END();
#if 0
    zval * *__surface = zsurface;
    zval * *__write_func = zwrite_func;
    void  *__closure = zclosure;
    php_cairo_png_t *__ret = php_cairo_surface_write_to_png_stream(, __surface, __write_func, __closure);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */
