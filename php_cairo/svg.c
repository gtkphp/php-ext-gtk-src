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
#include <cairo/cairo-svg.h>

#include "php_gtk.h"
#include "php_cairo/surface.h"
#include "svg.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_svg_class_entry;// struct
zend_object_handlers  php_cairo_svg_handlers;



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

#if CAIRO_VERSION >= 10200
/* {{{ proto php_cairo_surface_t cairo_svg_surface_create(char filename, double width_in_points, double height_in_points)
   Creates a SVG surface of the specified size in points to be written t... */
PHP_FUNCTION(cairo_svg_surface_create)
{
    char *filename;
    size_t filename_len;
    double width_in_points;
    double height_in_points;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_STRING(filename, filename_len);
        Z_PARAM_DOUBLE(width_in_points);
        Z_PARAM_DOUBLE(height_in_points);
    ZEND_PARSE_PARAMETERS_END();

    cairo_surface_t *ret = cairo_svg_surface_create(filename, width_in_points, height_in_points);
    php_cairo_surface_t *php_ret = php_cairo_surface_t_new();
    php_ret->ptr = ret;
    zend_object *z_ret = &php_ret->std;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto php_cairo_surface_t cairo_svg_surface_create_for_stream(cairo_write_func_t write_func, void closure, double width_in_points, double height_in_points)
   Creates a SVG surface of the specified size in points to be written i... */
PHP_FUNCTION(cairo_svg_surface_create_for_stream)
{
    zval *zwrite_func;
    zval *zclosure;
    double width_in_points;
    double height_in_points;
#if 0
    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwrite_func, php_cairo_write_func_t_class_entry, 0, 0);
        Z_PARAM_ZVAL(zclosure);
        Z_PARAM_DOUBLE(width_in_points);
        Z_PARAM_DOUBLE(height_in_points);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_write_func_t *php_write_func = ZVAL_IS_PHP_CAIRO_WRITE_FUNC_T(zwrite_func)? ZVAL_GET_PHP_CAIRO_WRITE_FUNC_T(zwrite_func): NULL;
    DECL_PHP_CAIRO_WRITE_FUNC_T(write_func);

    cairo_surface_t *ret = cairo_svg_surface_create_for_stream(write_func, closure, width_in_points, height_in_points);
    php_cairo_surface_t *php_ret = php_cairo_surface_t_new();
    php_ret->ptr = ret;
    zend_object *z_ret = &php_ret->std;
    RETURN_OBJ(z_ret);
#endif
}/* }}} */
#endif
#if CAIRO_VERSION >= 11600
/* {{{ proto int cairo_svg_surface_get_document_unit(php_cairo_surface_t surface)
   Get the unit of the SVG surface. */
PHP_FUNCTION(cairo_svg_surface_get_document_unit)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    int ret = cairo_svg_surface_get_document_unit(surface);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto void cairo_svg_surface_set_document_unit(php_cairo_surface_t surface, int unit)
   Use the specified unit for the width and height of the generated SVG ... */
PHP_FUNCTION(cairo_svg_surface_set_document_unit)
{
    zval *zsurface;
    zend_long zunit;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 0, 0);
        Z_PARAM_LONG(zunit);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);
    cairo_svg_unit_t unit = zunit;

    cairo_svg_surface_set_document_unit(surface, unit);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10200
/* {{{ proto void cairo_svg_surface_restrict_to_version(php_cairo_surface_t surface, int version)
   Restricts the generated SVG file to version . */
PHP_FUNCTION(cairo_svg_surface_restrict_to_version)
{
    zval *zsurface;
    zend_long zversion;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 0, 0);
        Z_PARAM_LONG(zversion);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);
    cairo_svg_version_t version = zversion;

    cairo_svg_surface_restrict_to_version(surface, version);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_svg_get_versions(int versions, int num_versions)
   Used to retrieve the list of supported versions. */
PHP_FUNCTION(cairo_svg_get_versions)
{
    zend_long zversions;
    zend_long num_versions;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_LONG(zversions);
        Z_PARAM_LONG(num_versions);
    ZEND_PARSE_PARAMETERS_END();

    cairo_svg_version_t *versions;// = zversions;

    cairo_svg_get_versions(&versions, &num_versions);
    RETURN_NULL();
}/* }}} */
/* {{{ proto char cairo_svg_version_to_string(int version)
   Get the string representation of the given version id. */
PHP_FUNCTION(cairo_svg_version_to_string)
{
    zend_long zversion;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(zversion);
    ZEND_PARSE_PARAMETERS_END();

    cairo_svg_version_t version = zversion;

    const char *z_ret = cairo_svg_version_to_string(version);

    RETURN_STR(z_ret);
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
