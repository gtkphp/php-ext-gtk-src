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

#include "php_gtk.h"
#include "php_cairo/status.h"
#include "php_cairo/surface.h"
#include "php_cairo/path.h"
#include "php_cairo/extend.h"
#include "php_cairo/filter.h"
#include "php_cairo/matrix.h"
#include "php_cairo/pattern-type.h"

#include "php_cairo/pattern.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_pattern_t_class_entry;// struct
zend_object_handlers  php_cairo_pattern_t_handlers;







/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_pattern_t_methods[] = {
    PHP_ME(cairo_pattern_t, __construct, arginfo_cairo_pattern_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_pattern_t_create_object */
static zend_object*
php_cairo_pattern_t_create_object(zend_class_entry *class_type)
{
    php_cairo_pattern_t *intern = zend_object_alloc(sizeof(php_cairo_pattern_t), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;
    intern->callback = NULL;

    intern->std.handlers = &php_cairo_pattern_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_pattern_t_create_object */


static void
php_cairo_pattern_t_dtor_object(zend_object *obj) {
    //php_cairo_pattern_t *intern = ZOBJ_TO_PHP_CAIRO_PATTERN_T(obj);

}

/* {{{ php_cairo_pattern_t_free_object */
static void
php_cairo_pattern_t_free_object(zend_object *object)
{
    php_cairo_pattern_t *intern = ZOBJ_TO_PHP_CAIRO_PATTERN_T(object);

    if (intern->ptr) {
        cairo_pattern_destroy(intern->ptr);
        intern->ptr = NULL;
    }
    if (intern->callback) {
        efree(intern->callback);
        intern->callback = NULL;
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_pattern_t_free_object */





/* {{{ php_cairo_pattern_t_get_debug_info */
static HashTable*
php_cairo_pattern_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_pattern_t  *intern = ZOBJ_TO_PHP_CAIRO_PATTERN_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_pattern_t_get_handlers()
{
    memcpy(&php_cairo_pattern_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_pattern_t_handlers.offset = PHP_CAIRO_PATTERN_T_OFFSET;
    php_cairo_pattern_t_handlers.dtor_obj = php_cairo_pattern_t_dtor_object;
    php_cairo_pattern_t_handlers.free_obj = php_cairo_pattern_t_free_object;


    php_cairo_pattern_t_handlers.get_debug_info = php_cairo_pattern_t_get_debug_info;


    return &php_cairo_pattern_t_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_pattern_t_class_init */
zend_class_entry*
php_cairo_pattern_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_pattern_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_pattern_t", php_cairo_pattern_t_methods);
    php_cairo_pattern_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_pattern_t_class_entry->create_object = php_cairo_pattern_t_create_object;

    return php_cairo_pattern_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
php_cairo_pattern_t*
php_cairo_pattern_t_new() {
    zend_object *zobj = php_cairo_pattern_t_create_object(php_cairo_pattern_t_class_entry);
    return ZOBJ_TO_PHP_CAIRO_PATTERN_T(zobj);
}

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

 /* {{{ cairo_pattern_t::__construct() */
PHP_METHOD(cairo_pattern_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_pattern_t *self = ZOBJ_TO_PHP_CAIRO_PATTERN_T(zobj);


}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

#if CAIRO_VERSION >= 10000
/* {{{ proto void cairo_pattern_add_color_stop_rgb(php_cairo_pattern_t pattern, double offset, double red, double green, double blue)
   Adds an opaque color stop to a gradient pattern. */
PHP_FUNCTION(cairo_pattern_add_color_stop_rgb)
{
    zval *zpattern;
    double offset;
    double red;
    double green;
    double blue;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(offset);
        Z_PARAM_DOUBLE(red);
        Z_PARAM_DOUBLE(green);
        Z_PARAM_DOUBLE(blue);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_pattern_add_color_stop_rgb(pattern, offset, red, green, blue);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_pattern_add_color_stop_rgba(php_cairo_pattern_t pattern, double offset, double red, double green, double blue, double alpha)
   Adds a translucent color stop to a gradient pattern. */
PHP_FUNCTION(cairo_pattern_add_color_stop_rgba)
{
    zval *zpattern;
    double offset;
    double red;
    double green;
    double blue;
    double alpha;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(offset);
        Z_PARAM_DOUBLE(red);
        Z_PARAM_DOUBLE(green);
        Z_PARAM_DOUBLE(blue);
        Z_PARAM_DOUBLE(alpha);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_pattern_add_color_stop_rgba(pattern, offset, red, green, blue, alpha);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10400
/* {{{ proto int cairo_pattern_get_color_stop_count(php_cairo_pattern_t pattern, int count)
   Gets the number of color stops specified in the given gradient pattern. */
PHP_FUNCTION(cairo_pattern_get_color_stop_count)
{
    zval *zpattern;
    zval *zcount=NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zcount, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);
    zend_long count = zcount->value.lval;

    int ret = cairo_pattern_get_color_stop_count(pattern, &count);

    ZVAL_LONG(zcount, count);
    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto int cairo_pattern_get_color_stop_rgba(php_cairo_pattern_t pattern, int index, double offset, double red, double green, double blue, double alpha)
   Gets the color and offset information at the given index for a gradie... */
PHP_FUNCTION(cairo_pattern_get_color_stop_rgba)
{
    zval *zpattern;
    zend_long index;
    zval *zoffset;
    zval *zred;
    zval *zgreen;
    zval *zblue;
    zval *zalpha;

    ZEND_PARSE_PARAMETERS_START(7, 7)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_LONG(index);
        Z_PARAM_ZVAL_EX2(zoffset, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zred, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zgreen, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zblue, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zalpha, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);
    double offset = zoffset->value.dval;
    double red = zred->value.dval;
    double green = zgreen->value.dval;
    double blue = zblue->value.dval;
    double alpha = zalpha->value.dval;

    int ret = cairo_pattern_get_color_stop_rgba(pattern, index, &offset, &red, &green, &blue, &alpha);

    ZVAL_DOUBLE(zoffset, offset);
    ZVAL_DOUBLE(zred, red);
    ZVAL_DOUBLE(zgreen, green);
    ZVAL_DOUBLE(zblue, blue);
    ZVAL_DOUBLE(zalpha, alpha);
    RETURN_LONG(ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10000
/* {{{ proto php_cairo_pattern_t cairo_pattern_create_rgb(double red, double green, double blue)
   Creates a new cairo_pattern_t corresponding to an opaque color. */
PHP_FUNCTION(cairo_pattern_create_rgb)
{
    double red;
    double green;
    double blue;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_DOUBLE(red);
        Z_PARAM_DOUBLE(green);
        Z_PARAM_DOUBLE(blue);
    ZEND_PARSE_PARAMETERS_END();

    cairo_pattern_t *ret = cairo_pattern_create_rgb(red, green, blue);
    zend_object *z_ret = php_cairo_pattern_t_create_object(php_cairo_pattern_t_class_entry);
    php_cairo_pattern_t *php_ret = ZOBJ_TO_PHP_CAIRO_PATTERN_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto php_cairo_pattern_t cairo_pattern_create_rgba(double red, double green, double blue, double alpha)
   Creates a new cairo_pattern_t corresponding to a translucent color. */
PHP_FUNCTION(cairo_pattern_create_rgba)
{
    double red;
    double green;
    double blue;
    double alpha;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_DOUBLE(red);
        Z_PARAM_DOUBLE(green);
        Z_PARAM_DOUBLE(blue);
        Z_PARAM_DOUBLE(alpha);
    ZEND_PARSE_PARAMETERS_END();

    cairo_pattern_t *ret = cairo_pattern_create_rgba(red, green, blue, alpha);
    zend_object *z_ret = php_cairo_pattern_t_create_object(php_cairo_pattern_t_class_entry);
    php_cairo_pattern_t *php_ret = ZOBJ_TO_PHP_CAIRO_PATTERN_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10400
/* {{{ proto int cairo_pattern_get_rgba(php_cairo_pattern_t pattern, double red, double green, double blue, double alpha)
   Gets the solid color for a solid color pattern. */
PHP_FUNCTION(cairo_pattern_get_rgba)
{
    zval *zpattern;
    zval *zred;
    zval *zgreen;
    zval *zblue;
    zval *zalpha;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zred, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zgreen, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zblue, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zalpha, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);
    double red = zred->value.dval;
    double green = zgreen->value.dval;
    double blue = zblue->value.dval;
    double alpha = zalpha->value.dval;

    int ret = cairo_pattern_get_rgba(pattern, &red, &green, &blue, &alpha);

    ZVAL_DOUBLE(zred, red);
    ZVAL_DOUBLE(zgreen, green);
    ZVAL_DOUBLE(zblue, blue);
    ZVAL_DOUBLE(zalpha, alpha);
    RETURN_LONG(ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10000
/* {{{ proto php_cairo_pattern_t cairo_pattern_create_for_surface(php_cairo_surface_t surface)
   Create a new cairo_pattern_t for the given surface. */
PHP_FUNCTION(cairo_pattern_create_for_surface)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_pattern_t *ret = cairo_pattern_create_for_surface(surface);
    zend_object *z_ret = php_cairo_pattern_t_create_object(php_cairo_pattern_t_class_entry);
    php_cairo_pattern_t *php_ret = ZOBJ_TO_PHP_CAIRO_PATTERN_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10400
/* {{{ proto int cairo_pattern_get_surface(php_cairo_pattern_t pattern, php_cairo_surface_t surface)
   Gets the surface of a surface pattern. */
PHP_FUNCTION(cairo_pattern_get_surface)
{
    zval *zpattern;
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zsurface, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);
    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): php_cairo_surface_t_new();
    DECL_PHP_CAIRO_SURFACE_T(surface);

    int ret = cairo_pattern_get_surface(pattern, &php_surface->ptr);
    cairo_surface_reference(php_surface->ptr);

    ZVAL_OBJ(zsurface, &php_surface->std);
    RETURN_LONG(ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10000
/* {{{ proto php_cairo_pattern_t cairo_pattern_create_linear(double x0, double y0, double x1, double y1)
   Create a new linear gradient cairo_pattern_t along the line defined b... */
PHP_FUNCTION(cairo_pattern_create_linear)
{
    double x0;
    double y0;
    double x1;
    double y1;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_DOUBLE(x0);
        Z_PARAM_DOUBLE(y0);
        Z_PARAM_DOUBLE(x1);
        Z_PARAM_DOUBLE(y1);
    ZEND_PARSE_PARAMETERS_END();

    cairo_pattern_t *ret = cairo_pattern_create_linear(x0, y0, x1, y1);
    zend_object *z_ret = php_cairo_pattern_t_create_object(php_cairo_pattern_t_class_entry);
    php_cairo_pattern_t *php_ret = ZOBJ_TO_PHP_CAIRO_PATTERN_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10400
/* {{{ proto int cairo_pattern_get_linear_points(php_cairo_pattern_t pattern, double x0, double y0, double x1, double y1)
   Gets the gradient endpoints for a linear gradient. */
PHP_FUNCTION(cairo_pattern_get_linear_points)
{
    zval *zpattern;
    zval *zx0;
    zval *zy0;
    zval *zx1;
    zval *zy1;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zx0, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zy0, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zx1, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zy1, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);
    double x0 = zx0->value.dval;
    double y0 = zy0->value.dval;
    double x1 = zx1->value.dval;
    double y1 = zy1->value.dval;

    int ret = cairo_pattern_get_linear_points(pattern, &x0, &y0, &x1, &y1);

    ZVAL_DOUBLE(zx0, x0);
    ZVAL_DOUBLE(zy0, y0);
    ZVAL_DOUBLE(zx1, x1);
    ZVAL_DOUBLE(zy1, y1);
    RETURN_LONG(ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10000
/* {{{ proto php_cairo_pattern_t cairo_pattern_create_radial(double cx0, double cy0, double radius0, double cx1, double cy1, double radius1)
   Creates a new radial gradient cairo_pattern_t between the two circles... */
PHP_FUNCTION(cairo_pattern_create_radial)
{
    double cx0;
    double cy0;
    double radius0;
    double cx1;
    double cy1;
    double radius1;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_DOUBLE(cx0);
        Z_PARAM_DOUBLE(cy0);
        Z_PARAM_DOUBLE(radius0);
        Z_PARAM_DOUBLE(cx1);
        Z_PARAM_DOUBLE(cy1);
        Z_PARAM_DOUBLE(radius1);
    ZEND_PARSE_PARAMETERS_END();

    cairo_pattern_t *ret = cairo_pattern_create_radial(cx0, cy0, radius0, cx1, cy1, radius1);
    zend_object *z_ret = php_cairo_pattern_t_create_object(php_cairo_pattern_t_class_entry);
    php_cairo_pattern_t *php_ret = ZOBJ_TO_PHP_CAIRO_PATTERN_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10400
/* {{{ proto int cairo_pattern_get_radial_circles(php_cairo_pattern_t pattern, double x0, double y0, double r0, double x1, double y1, double r1)
   Gets the gradient endpoint circles for a radial gradient, each specif... */
PHP_FUNCTION(cairo_pattern_get_radial_circles)
{
    zval *zpattern;
    zval *zx0;
    zval *zy0;
    zval *zr0;
    zval *zx1;
    zval *zy1;
    zval *zr1;

    ZEND_PARSE_PARAMETERS_START(7, 7)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zx0, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zy0, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zr0, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zx1, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zy1, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zr1, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);
    double x0 = zx0->value.dval;
    double y0 = zy0->value.dval;
    double r0 = zr0->value.dval;
    double x1 = zx1->value.dval;
    double y1 = zy1->value.dval;
    double r1 = zr1->value.dval;

    int ret = cairo_pattern_get_radial_circles(pattern, &x0, &y0, &r0, &x1, &y1, &r1);

    ZVAL_DOUBLE(zx0, x0);
    ZVAL_DOUBLE(zy0, y0);
    ZVAL_DOUBLE(zr0, r0);
    ZVAL_DOUBLE(zx1, x1);
    ZVAL_DOUBLE(zy1, y1);
    ZVAL_DOUBLE(zr1, r1);
    RETURN_LONG(ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 11200
/* {{{ proto php_cairo_pattern_t cairo_pattern_create_mesh()
   Create a new mesh pattern. */
PHP_FUNCTION(cairo_pattern_create_mesh)
{


    cairo_pattern_t *ret = cairo_pattern_create_mesh();
    zend_object *z_ret = php_cairo_pattern_t_create_object(php_cairo_pattern_t_class_entry);
    php_cairo_pattern_t *php_ret = ZOBJ_TO_PHP_CAIRO_PATTERN_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto void cairo_mesh_pattern_begin_patch(php_cairo_pattern_t pattern)
   Begin a patch in a mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_begin_patch)
{
    zval *zpattern;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_mesh_pattern_begin_patch(pattern);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_mesh_pattern_end_patch(php_cairo_pattern_t pattern)
   Indicates the end of the current patch in a mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_end_patch)
{
    zval *zpattern;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_mesh_pattern_end_patch(pattern);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_mesh_pattern_move_to(php_cairo_pattern_t pattern, double x, double y)
   Define the first point of the current patch in a mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_move_to)
{
    zval *zpattern;
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x);
        Z_PARAM_DOUBLE(y);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_mesh_pattern_move_to(pattern, x, y);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_mesh_pattern_line_to(php_cairo_pattern_t pattern, double x, double y)
   Adds a line to the current patch from the current point to position (... */
PHP_FUNCTION(cairo_mesh_pattern_line_to)
{
    zval *zpattern;
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x);
        Z_PARAM_DOUBLE(y);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_mesh_pattern_line_to(pattern, x, y);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_mesh_pattern_curve_to(php_cairo_pattern_t pattern, double x1, double y1, double x2, double y2, double x3, double y3)
   Adds a cubic Bézier spline to the current patch from the current poi... */
PHP_FUNCTION(cairo_mesh_pattern_curve_to)
{
    zval *zpattern;
    double x1;
    double y1;
    double x2;
    double y2;
    double x3;
    double y3;

    ZEND_PARSE_PARAMETERS_START(7, 7)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x1);
        Z_PARAM_DOUBLE(y1);
        Z_PARAM_DOUBLE(x2);
        Z_PARAM_DOUBLE(y2);
        Z_PARAM_DOUBLE(x3);
        Z_PARAM_DOUBLE(y3);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_mesh_pattern_curve_to(pattern, x1, y1, x2, y2, x3, y3);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_mesh_pattern_set_control_point(php_cairo_pattern_t pattern, int point_num, double x, double y)
   Set an internal control point of the current patch. */
PHP_FUNCTION(cairo_mesh_pattern_set_control_point)
{
    zval *zpattern;
    zend_long point_num;
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_LONG(point_num);
        Z_PARAM_DOUBLE(x);
        Z_PARAM_DOUBLE(y);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_mesh_pattern_set_control_point(pattern, point_num, x, y);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_mesh_pattern_set_corner_color_rgb(php_cairo_pattern_t pattern, int corner_num, double red, double green, double blue)
   Sets the color of a corner of the current patch in a mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_set_corner_color_rgb)
{
    zval *zpattern;
    zend_long corner_num;
    double red;
    double green;
    double blue;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_LONG(corner_num);
        Z_PARAM_DOUBLE(red);
        Z_PARAM_DOUBLE(green);
        Z_PARAM_DOUBLE(blue);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_mesh_pattern_set_corner_color_rgb(pattern, corner_num, red, green, blue);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_mesh_pattern_set_corner_color_rgba(php_cairo_pattern_t pattern, int corner_num, double red, double green, double blue, double alpha)
   Sets the color of a corner of the current patch in a mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_set_corner_color_rgba)
{
    zval *zpattern;
    zend_long corner_num;
    double red;
    double green;
    double blue;
    double alpha;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_LONG(corner_num);
        Z_PARAM_DOUBLE(red);
        Z_PARAM_DOUBLE(green);
        Z_PARAM_DOUBLE(blue);
        Z_PARAM_DOUBLE(alpha);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_mesh_pattern_set_corner_color_rgba(pattern, corner_num, red, green, blue, alpha);
    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_mesh_pattern_get_patch_count(php_cairo_pattern_t pattern, int count)
   Gets the number of patches specified in the given mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_get_patch_count)
{
    zval *zpattern;
    zval *zcount;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zcount, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);
    zend_long count = zcount->value.lval;

    int ret = cairo_mesh_pattern_get_patch_count(pattern, &count);

    ZVAL_LONG(zcount, count);
    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto php_cairo_path_t cairo_mesh_pattern_get_path(php_cairo_pattern_t pattern, int patch_num)
   Gets path defining the patch patch_num for a mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_get_path)
{
    zval *zpattern;
    zend_long patch_num;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_LONG(patch_num);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_path_t *ret = cairo_mesh_pattern_get_path(pattern, patch_num);
    php_cairo_path_t *php_ret = php_cairo_path_t_new(ret);
    zend_object *z_ret = &php_ret->std;
    cairo_path_destroy(ret);

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto int cairo_mesh_pattern_get_control_point(php_cairo_pattern_t pattern, int patch_num, int point_num, double x, double y)
   Gets the control point point_num of patch patch_num for a mesh pattern. */
PHP_FUNCTION(cairo_mesh_pattern_get_control_point)
{
    zval *zpattern;
    zend_long patch_num;
    zend_long point_num;
    zval *zx;
    zval *zy;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_LONG(patch_num);
        Z_PARAM_LONG(point_num);
        Z_PARAM_ZVAL_EX2(zx, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zy, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);
    double x = zx->value.dval;
    double y = zy->value.dval;

    int ret = cairo_mesh_pattern_get_control_point(pattern, patch_num, point_num, &x, &y);

    ZVAL_DOUBLE(zx, x);
    ZVAL_DOUBLE(zy, y);
    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto int cairo_mesh_pattern_get_corner_color_rgba(php_cairo_pattern_t pattern, int patch_num, int corner_num, double red, double green, double blue, double alpha)
   Gets the color information in corner corner_num of patch patch_num fo... */
PHP_FUNCTION(cairo_mesh_pattern_get_corner_color_rgba)
{
    zval *zpattern;
    zend_long patch_num;
    zend_long corner_num;
    zval *zred;
    zval *zgreen;
    zval *zblue;
    zval *zalpha;

    ZEND_PARSE_PARAMETERS_START(7, 7)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_LONG(patch_num);
        Z_PARAM_LONG(corner_num);
        Z_PARAM_ZVAL_EX2(zred, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zgreen, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zblue, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zalpha, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);
    double red = zred->value.dval;
    double green = zgreen->value.dval;
    double blue = zblue->value.dval;
    double alpha = zalpha->value.dval;

    int ret = cairo_mesh_pattern_get_corner_color_rgba(pattern, patch_num, corner_num, &red, &green, &blue, &alpha);

    ZVAL_DOUBLE(zred, red);
    ZVAL_DOUBLE(zgreen, green);
    ZVAL_DOUBLE(zblue, blue);
    ZVAL_DOUBLE(zalpha, alpha);
    RETURN_LONG(ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10000
/* {{{ proto php_cairo_pattern_t cairo_pattern_reference(php_cairo_pattern_t pattern)
   Increases the reference count on pattern by one. */
PHP_FUNCTION(cairo_pattern_reference)
{
    zval *zpattern;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_pattern_t *ret = cairo_pattern_reference(pattern);
    zend_object *z_ret = php_cairo_pattern_t_create_object(php_cairo_pattern_t_class_entry);
    php_cairo_pattern_t *php_ret = ZOBJ_TO_PHP_CAIRO_PATTERN_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto int cairo_pattern_status(php_cairo_pattern_t pattern)
   Checks whether an error has previously occurred for this pattern. */
PHP_FUNCTION(cairo_pattern_status)
{
    zval *zpattern;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    int ret = cairo_pattern_status(pattern);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto void cairo_pattern_set_extend(php_cairo_pattern_t pattern, int extend)
   Sets the mode to be used for drawing outside the area of a pattern. */
PHP_FUNCTION(cairo_pattern_set_extend)
{
    zval *zpattern;
    zend_long zextend;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_LONG(zextend);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);
    cairo_extend_t extend = zextend;

    cairo_pattern_set_extend(pattern, extend);
    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_pattern_get_extend(php_cairo_pattern_t pattern)
   Gets the current extend mode for a pattern. */
PHP_FUNCTION(cairo_pattern_get_extend)
{
    zval *zpattern;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    int ret = cairo_pattern_get_extend(pattern);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto void cairo_pattern_set_filter(php_cairo_pattern_t pattern, int filter)
   Sets the filter to be used for resizing when using this pattern. */
PHP_FUNCTION(cairo_pattern_set_filter)
{
    zval *zpattern;
    zend_long zfilter;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_LONG(zfilter);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);
    cairo_filter_t filter = zfilter;

    cairo_pattern_set_filter(pattern, filter);
    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_pattern_get_filter(php_cairo_pattern_t pattern)
   Gets the current filter for a pattern. */
PHP_FUNCTION(cairo_pattern_get_filter)
{
    zval *zpattern;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    int ret = cairo_pattern_get_filter(pattern);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto void cairo_pattern_set_matrix(php_cairo_pattern_t pattern, php_cairo_matrix_t matrix)
   Sets the pattern's transformation matrix to matrix . */
PHP_FUNCTION(cairo_pattern_set_matrix)
{
    zval *zpattern;
    zval *zmatrix;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);
    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_pattern_set_matrix(pattern, matrix);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_pattern_get_matrix(php_cairo_pattern_t pattern, php_cairo_matrix_t matrix)
   Stores the pattern's transformation matrix into matrix . */
PHP_FUNCTION(cairo_pattern_get_matrix)
{
    zval *zpattern;
    zval *zmatrix;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zmatrix, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);
    php_cairo_matrix_t *php_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zmatrix): php_cairo_matrix_t_new();
    DECL_PHP_CAIRO_MATRIX_T(matrix);

    cairo_pattern_get_matrix(pattern, matrix);
    ZVAL_OBJ(zmatrix, &php_matrix->std);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10200
/* {{{ proto int cairo_pattern_get_type(php_cairo_pattern_t pattern)
   Get the pattern's type. See cairo_pattern_type_t for available types. */
PHP_FUNCTION(cairo_pattern_get_type)
{
    zval *zpattern;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    int ret = cairo_pattern_get_type(pattern);

    RETURN_LONG(ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10400
/* {{{ proto int cairo_pattern_get_reference_count(php_cairo_pattern_t pattern)
   Returns the current reference count of pattern . */
PHP_FUNCTION(cairo_pattern_get_reference_count)
{
    zval *zpattern;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    int ret = cairo_pattern_get_reference_count(pattern);

    RETURN_LONG(ret);
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
