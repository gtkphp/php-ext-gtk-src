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

#ifndef PHP_CAIRO_SVG_H
#define PHP_CAIRO_SVG_H


#if CAIRO_VERSION >= 10200
#define PHP_CAIRO_SVG_FE_10200()  \
    PHP_GTK_FE(cairo_svg_surface_create,        arginfo_cairo_svg_surface_create)  \
    PHP_GTK_FE(cairo_svg_surface_create_for_stream,        arginfo_cairo_svg_surface_create_for_stream)  \
    PHP_GTK_FE(cairo_svg_surface_restrict_to_version,        arginfo_cairo_svg_surface_restrict_to_version)  \
    PHP_GTK_FE(cairo_svg_get_versions,        arginfo_cairo_svg_get_versions)  \
    PHP_GTK_FE(cairo_svg_version_to_string,        arginfo_cairo_svg_version_to_string)  \

#else
#define PHP_CAIRO_SVG_FE_10200()
#endif


#if CAIRO_VERSION >= 11600
#define PHP_CAIRO_SVG_FE_11600()  \
    PHP_GTK_FE(cairo_svg_surface_get_document_unit,        arginfo_cairo_svg_surface_get_document_unit)  \
    PHP_GTK_FE(cairo_svg_surface_set_document_unit,        arginfo_cairo_svg_surface_set_document_unit)  \

#else
#define PHP_CAIRO_SVG_FE_11600()
#endif


#define PHP_CAIRO_SVG_FE() \
    PHP_CAIRO_SVG_FE_10200() \
    PHP_CAIRO_SVG_FE_11600() \


#define PHP_CAIRO_SVG_MINIT_FUNCTION(container_ce, parent_ce)

#define PHP_CAIRO_SVG_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_SVG_RSHUTDOWN_FUNCTION() {\
}





ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_svg___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_svg, __construct);

#if CAIRO_VERSION >= 10200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_svg_surface_create, ZEND_RETURN_VALUE, 3, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, filename, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width_in_points, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, height_in_points, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_svg_surface_create);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_svg_surface_create_for_stream, ZEND_RETURN_VALUE, 4, cairo_surface_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, write_func, cairo_write_func_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, closure)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width_in_points, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, height_in_points, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_svg_surface_create_for_stream);
#endif
#if CAIRO_VERSION >= 11600
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_svg_surface_get_document_unit, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_svg_surface_get_document_unit);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_svg_surface_set_document_unit, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, unit, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_svg_surface_set_document_unit);
#endif
#if CAIRO_VERSION >= 10200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_svg_surface_restrict_to_version, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, version, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_svg_surface_restrict_to_version);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_svg_get_versions, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, versions, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, num_versions, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_svg_get_versions);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_svg_version_to_string, ZEND_RETURN_VALUE, 1, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, version, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_svg_version_to_string);
#endif


#endif	/* PHP_CAIRO_SVG_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
