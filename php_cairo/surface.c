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
#include "php_cairo/content.h"
#include "php_cairo/format.h"
#include "php_cairo/status.h"
#include "php_cairo/device.h"
#include "php_cairo/font-options.h"
#include "php_cairo/surface-type.h"
#include "php_cairo/rectangle-int.h"

#include "php_cairo/surface.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_surface_t_class_entry;// struct
zend_object_handlers  php_cairo_surface_t_handlers;







/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_surface_t_methods[] = {
    PHP_ME(cairo_surface_t, __construct, arginfo_cairo_surface_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_surface_t_create_object */
static zend_object*
php_cairo_surface_t_create_object(zend_class_entry *class_type)
{
    php_cairo_surface_t *intern = zend_object_alloc(sizeof(php_cairo_surface_t), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_cairo_surface_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_surface_t_create_object */


static void
php_cairo_surface_t_dtor_object(zend_object *obj) {
    //php_cairo_surface_t *intern = ZOBJ_TO_PHP_CAIRO_SURFACE_T(obj);

}

/* {{{ php_cairo_surface_t_free_object */
static void
php_cairo_surface_t_free_object(zend_object *object)
{
    php_cairo_surface_t *intern = ZOBJ_TO_PHP_CAIRO_SURFACE_T(object);

    if (intern->ptr) {
        cairo_surface_destroy(intern->ptr);
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_surface_t_free_object */





/* {{{ php_cairo_surface_t_get_debug_info */
static HashTable*
php_cairo_surface_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_surface_t  *intern = ZOBJ_TO_PHP_CAIRO_SURFACE_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_surface_t_get_handlers()
{
    memcpy(&php_cairo_surface_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_surface_t_handlers.offset = PHP_CAIRO_SURFACE_T_OFFSET;
    php_cairo_surface_t_handlers.dtor_obj = php_cairo_surface_t_dtor_object;
    php_cairo_surface_t_handlers.free_obj = php_cairo_surface_t_free_object;


    php_cairo_surface_t_handlers.get_debug_info = php_cairo_surface_t_get_debug_info;


    return &php_cairo_surface_t_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_surface_t_class_init */
zend_class_entry*
php_cairo_surface_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_surface_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_surface_t", php_cairo_surface_t_methods);
    php_cairo_surface_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_surface_t_class_entry->create_object = php_cairo_surface_t_create_object;

    return php_cairo_surface_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/
php_cairo_surface_t *
php_cairo_surface_t_new() {
    zend_object *zobj = php_cairo_surface_t_create_object(php_cairo_surface_t_class_entry);
    return ZOBJ_TO_PHP_CAIRO_SURFACE_T(zobj);
}

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

 /* {{{ cairo_surface_t::__construct() */
PHP_METHOD(cairo_surface_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_surface_t *self = ZOBJ_TO_PHP_CAIRO_SURFACE_T(zobj);


}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

#if CAIRO_VERSION >= 10000
/* {{{ proto php_cairo_surface_t cairo_surface_create_similar(php_cairo_surface_t other, int content, int width, int height)
   Create a new surface that is as compatible as possible with an existi... */
PHP_FUNCTION(cairo_surface_create_similar)
{
    zval *zother;
    zend_long zcontent;
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zother, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_LONG(zcontent);
        Z_PARAM_LONG(width);
        Z_PARAM_LONG(height);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_other = ZVAL_IS_PHP_CAIRO_SURFACE_T(zother)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zother): NULL;
    DECL_PHP_CAIRO_SURFACE_T(other);
    cairo_content_t content = zcontent;

    cairo_surface_t *ret = cairo_surface_create_similar(other, content, width, height);
    php_cairo_surface_t *php_ret = php_cairo_surface_t_new();
    php_ret->ptr = ret;
    zend_object *z_ret = &php_ret->std;

    RETURN_OBJ(z_ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 11200
/* {{{ proto php_cairo_surface_t cairo_surface_create_similar_image(php_cairo_surface_t other, int format, int width, int height)
   Create a new image surface that is as compatible as possible for uplo... */
PHP_FUNCTION(cairo_surface_create_similar_image)
{
    zval *zother;
    zend_long zformat;
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zother, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_LONG(zformat);
        Z_PARAM_LONG(width);
        Z_PARAM_LONG(height);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_other = ZVAL_IS_PHP_CAIRO_SURFACE_T(zother)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zother): NULL;
    DECL_PHP_CAIRO_SURFACE_T(other);
    cairo_format_t format = zformat;

    cairo_surface_t *ret = cairo_surface_create_similar_image(other, format, width, height);
    php_cairo_surface_t *php_ret = php_cairo_surface_t_new();
    php_ret->ptr = ret;
    zend_object *z_ret = &php_ret->std;

    RETURN_OBJ(z_ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 11000
/* {{{ proto php_cairo_surface_t cairo_surface_create_for_rectangle(php_cairo_surface_t target, double x, double y, double width, double height)
   Create a new surface that is a rectangle within the target surface. */
PHP_FUNCTION(cairo_surface_create_for_rectangle)
{
    zval *ztarget;
    double x;
    double y;
    double width;
    double height;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(ztarget, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x);
        Z_PARAM_DOUBLE(y);
        Z_PARAM_DOUBLE(width);
        Z_PARAM_DOUBLE(height);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_target = ZVAL_IS_PHP_CAIRO_SURFACE_T(ztarget)? ZVAL_GET_PHP_CAIRO_SURFACE_T(ztarget): NULL;
    DECL_PHP_CAIRO_SURFACE_T(target);

    cairo_surface_t *ret = cairo_surface_create_for_rectangle(target, x, y, width, height);
    php_cairo_surface_t *php_ret = php_cairo_surface_t_new();
    php_ret->ptr = ret;
    zend_object *z_ret = &php_ret->std;

    RETURN_OBJ(z_ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10000
/* {{{ proto int cairo_surface_status(php_cairo_surface_t surface)
   Checks whether an error has previously occurred for this surface. */
PHP_FUNCTION(cairo_surface_status)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    int ret = cairo_surface_status(surface);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto void cairo_surface_finish(php_cairo_surface_t surface)
   This function finishes the surface and drops all references to extern... */
PHP_FUNCTION(cairo_surface_finish)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_surface_finish(surface);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_surface_flush(php_cairo_surface_t surface)
   Do any pending drawing for the surface and also restore any temporary... */
PHP_FUNCTION(cairo_surface_flush)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_surface_flush(surface);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 11000
/* {{{ proto php_cairo_device_t cairo_surface_get_device(php_cairo_surface_t surface)
   This function returns the device for a surface . See cairo_device_t. */
PHP_FUNCTION(cairo_surface_get_device)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_device_t *ret = cairo_surface_get_device(surface);
    php_cairo_device_t *php_ret = php_cairo_device_t_new();
    zend_object *z_ret = &php_ret->std;
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10000
/* {{{ proto void cairo_surface_get_font_options(php_cairo_surface_t surface, php_cairo_font_options_t options)
   Retrieves the default font rendering options for the surface. */
PHP_FUNCTION(cairo_surface_get_font_options)
{
    zval *zsurface;
    zval *zoptions;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);
    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);

    cairo_surface_get_font_options(surface, options);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10200
/* {{{ proto int cairo_surface_get_content(php_cairo_surface_t surface)
   This function returns the content type of surface which indicates whe... */
PHP_FUNCTION(cairo_surface_get_content)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    int ret = cairo_surface_get_content(surface);

    RETURN_LONG(ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10000
/* {{{ proto void cairo_surface_mark_dirty(php_cairo_surface_t surface)
   Tells cairo that drawing has been done to surface using means other t... */
PHP_FUNCTION(cairo_surface_mark_dirty)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_surface_mark_dirty(surface);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_surface_mark_dirty_rectangle(php_cairo_surface_t surface, int x, int y, int width, int height)
   Like cairo_surface_mark_dirty(), but drawing has been done only to th... */
PHP_FUNCTION(cairo_surface_mark_dirty_rectangle)
{
    zval *zsurface;
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_LONG(x);
        Z_PARAM_LONG(y);
        Z_PARAM_LONG(width);
        Z_PARAM_LONG(height);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_surface_mark_dirty_rectangle(surface, x, y, width, height);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_surface_set_device_offset(php_cairo_surface_t surface, double x_offset, double y_offset)
   Sets an offset that is added to the device coordinates determined by ... */
PHP_FUNCTION(cairo_surface_set_device_offset)
{
    zval *zsurface;
    double x_offset;
    double y_offset;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x_offset);
        Z_PARAM_DOUBLE(y_offset);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_surface_set_device_offset(surface, x_offset, y_offset);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10200
/* {{{ proto void cairo_surface_get_device_offset(php_cairo_surface_t surface, double x_offset, double y_offset)
   This function returns the previous device offset set by cairo_surface... */
PHP_FUNCTION(cairo_surface_get_device_offset)
{
    zval *zsurface;
    zval *zx_offset;
    zval *zy_offset;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zx_offset, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zy_offset, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);
    double x_offset = zx_offset->value.dval;
    double y_offset = zy_offset->value.dval;

    cairo_surface_get_device_offset(surface, &x_offset, &y_offset);
    ZVAL_DOUBLE(zx_offset, x_offset);
    ZVAL_DOUBLE(zy_offset, y_offset);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 11400
/* {{{ proto void cairo_surface_get_device_scale(php_cairo_surface_t surface, double x_scale, double y_scale)
   This function returns the previous device offset set by cairo_surface... */
PHP_FUNCTION(cairo_surface_get_device_scale)
{
    zval *zsurface;
    zval *zx_scale;
    zval *zy_scale;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zx_scale, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zy_scale, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);
    double x_scale = zx_scale->value.dval;
    double y_scale = zy_scale->value.dval;

    cairo_surface_get_device_scale(surface, &x_scale, &y_scale);
    ZVAL_DOUBLE(zx_scale, x_scale);
    ZVAL_DOUBLE(zy_scale, y_scale);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_surface_set_device_scale(php_cairo_surface_t surface, double x_scale, double y_scale)
   Sets a scale that is multiplied to the device coordinates determined ... */
PHP_FUNCTION(cairo_surface_set_device_scale)
{
    zval *zsurface;
    double x_scale;
    double y_scale;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x_scale);
        Z_PARAM_DOUBLE(y_scale);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_surface_set_device_scale(surface, x_scale, y_scale);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10200
/* {{{ proto void cairo_surface_set_fallback_resolution(php_cairo_surface_t surface, double x_pixels_per_inch, double y_pixels_per_inch)
   Set the horizontal and vertical resolution for image fallbacks. */
PHP_FUNCTION(cairo_surface_set_fallback_resolution)
{
    zval *zsurface;
    double x_pixels_per_inch;
    double y_pixels_per_inch;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x_pixels_per_inch);
        Z_PARAM_DOUBLE(y_pixels_per_inch);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_surface_set_fallback_resolution(surface, x_pixels_per_inch, y_pixels_per_inch);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10800
/* {{{ proto void cairo_surface_get_fallback_resolution(php_cairo_surface_t surface, double x_pixels_per_inch, double y_pixels_per_inch)
   This function returns the previous fallback resolution set by cairo_s... */
PHP_FUNCTION(cairo_surface_get_fallback_resolution)
{
    zval *zsurface;
    zval *zx_pixels_per_inch;
    zval *zy_pixels_per_inch;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zx_pixels_per_inch, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zy_pixels_per_inch, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);
    double x_pixels_per_inch = zx_pixels_per_inch->value.dval;
    double y_pixels_per_inch = zy_pixels_per_inch->value.dval;

    cairo_surface_get_fallback_resolution(surface, &x_pixels_per_inch, &y_pixels_per_inch);
    ZVAL_DOUBLE(zx_pixels_per_inch, x_pixels_per_inch);
    ZVAL_DOUBLE(zy_pixels_per_inch, y_pixels_per_inch);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10200
/* {{{ proto int cairo_surface_get_type(php_cairo_surface_t surface)
   This function returns the type of the backend used to create a surface. */
PHP_FUNCTION(cairo_surface_get_type)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    int ret = cairo_surface_get_type(surface);

    RETURN_LONG(ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10400
/* {{{ proto int cairo_surface_get_reference_count(php_cairo_surface_t surface)
   Returns the current reference count of surface . */
PHP_FUNCTION(cairo_surface_get_reference_count)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    int ret = cairo_surface_get_reference_count(surface);

    RETURN_LONG(ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10600
/* {{{ proto void cairo_surface_copy_page(php_cairo_surface_t surface)
   Emits the current page for backends that support multiple pages, but ... */
PHP_FUNCTION(cairo_surface_copy_page)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_surface_copy_page(surface);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_surface_show_page(php_cairo_surface_t surface)
   Emits and clears the current page for backends that support multiple ... */
PHP_FUNCTION(cairo_surface_show_page)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_surface_show_page(surface);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10800
/* {{{ proto cairo_bool_t cairo_surface_has_show_text_glyphs(php_cairo_surface_t surface)
   Returns whether the surface supports sophisticated cairo_show_text_gl... */
PHP_FUNCTION(cairo_surface_has_show_text_glyphs)
{
    zval *zsurface;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_bool_t ret = cairo_surface_has_show_text_glyphs(surface);

    if (ret) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}/* }}} */
#endif
#if CAIRO_VERSION >= 11200
/* {{{ proto cairo_bool_t cairo_surface_supports_mime_type(php_cairo_surface_t surface, char mime_type)
   Return whether surface supports mime_type . */
PHP_FUNCTION(cairo_surface_supports_mime_type)
{
    zval *zsurface;
    char *mime_type;
    size_t mime_type_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_STRING(mime_type, mime_type_len);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_bool_t ret = cairo_surface_supports_mime_type(surface, mime_type);

    if (ret) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}/* }}} */

/* {{{ proto php_cairo_surface_t cairo_surface_map_to_image(php_cairo_surface_t surface, php_cairo_rectangle_int_t extents)
   Returns an image surface that is the most efficient mechanism for mod... */
PHP_FUNCTION(cairo_surface_map_to_image)
{
    zval *zsurface;
    zval *zextents;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zextents, php_cairo_rectangle_int_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);
    php_cairo_rectangle_int_t *php_extents = ZVAL_IS_PHP_CAIRO_RECTANGLE_INT_T(zextents)? ZVAL_GET_PHP_CAIRO_RECTANGLE_INT_T(zextents): NULL;
    DECL_PHP_CAIRO_RECTANGLE_INT_T(extents);

    cairo_surface_t *ret = cairo_surface_map_to_image(surface, extents);
    php_cairo_surface_t *php_ret = php_cairo_surface_t_new();
    php_ret->ptr = ret;
    zend_object *z_ret = &php_ret->std;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto void cairo_surface_unmap_image(php_cairo_surface_t surface, php_cairo_surface_t image)
   Unmaps the image surface as returned from cairo_surface_map_to_image(). */
PHP_FUNCTION(cairo_surface_unmap_image)
{
    zval *zsurface;
    zval *zimage;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zimage, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);
    php_cairo_surface_t *php_image = ZVAL_IS_PHP_CAIRO_SURFACE_T(zimage)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zimage): NULL;
    DECL_PHP_CAIRO_SURFACE_T(image);

    cairo_surface_unmap_image(surface, image);
    RETURN_NULL();
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
