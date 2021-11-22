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

#ifndef PHP_CAIRO_PNG_T_H
#define PHP_CAIRO_PNG_T_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#define PHP_CAIRO_PNG_T_FE() \
    PHP_GTK_FE(cairo_image_surface_create_from_png,        arginfo_cairo_image_surface_create_from_png) \
    PHP_GTK_FE(cairo_image_surface_create_from_png_stream, arginfo_cairo_image_surface_create_from_png_stream) \
    PHP_GTK_FE(cairo_surface_write_to_png,                 arginfo_cairo_surface_write_to_png) \
    PHP_GTK_FE(cairo_surface_write_to_png_stream,          arginfo_cairo_surface_write_to_png_stream) \

#define PHP_CAIRO_PNG_T_MINIT_FUNCTION(container_ce, parent_ce)

#define PHP_CAIRO_PNG_T_MSHUTDOWN_FUNCTION()

#define PHP_CAIRO_PNG_T_RSHUTDOWN_FUNCTION()


zval *php_cairo_image_surface_create_from_png(zval *filename);
zval *php_cairo_image_surface_create_from_png_stream(zval *read_func, void *closure);
zval *php_cairo_surface_write_to_png(zval *surface, zval *filename);
zval *php_cairo_surface_write_to_png_stream(zval *surface, zval *write_func, void *closure);

zend_class_entry *php_cairo_png_t_class_init(zend_class_entry *ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_image_surface_create_from_png, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, filename, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_create_from_png);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_image_surface_create_from_png_stream, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, read_func)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, closure)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_create_from_png_stream);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_write_to_png, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, surface)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, filename)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_write_to_png);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_write_to_png_stream, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, surface)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, write_func)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, closure)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_write_to_png_stream);



#endif	/* PHP_CAIRO_PNG_T_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
