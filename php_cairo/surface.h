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

#ifndef PHP_CAIRO_SURFACE_T_H
#define PHP_CAIRO_SURFACE_T_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#define IS_IMPLEMENTED 0



#define PHP_CAIRO_SURFACE_T(ptr)           ((php_cairo_surface_t*)(ptr))
#define PHP_CAIRO_SURFACE_T_CLASS          php_cairo_surface_t_class_entry
#define PHP_CAIRO_SURFACE_T_OFFSET         (sizeof(php_cairo_surface_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_SURFACE_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_surface_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_SURFACE_T(std)   PHP_CAIRO_SURFACE_T( ((void*)(std))-PHP_CAIRO_SURFACE_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_SURFACE_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_SURFACE_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_SURFACE_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_SURFACE_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_SURFACE_T(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

#if IS_IMPLEMENTED

#define PHP_CAIRO_SURFACE_T_FE() \
    PHP_GTK_FE(cairo_surface_create_similar,          arginfo_cairo_surface_create_similar) \
    PHP_GTK_FE(cairo_surface_create_similar_image,    arginfo_cairo_surface_create_similar_image) \
    PHP_GTK_FE(cairo_surface_create_for_rectangle,    arginfo_cairo_surface_create_for_rectangle) \
    PHP_GTK_FE(cairo_surface_reference,               arginfo_cairo_surface_reference) \
    PHP_GTK_FE(cairo_surface_destroy,                 arginfo_cairo_surface_destroy) \
    PHP_GTK_FE(cairo_surface_status,                  arginfo_cairo_surface_status) \
    PHP_GTK_FE(cairo_surface_finish,                  arginfo_cairo_surface_finish) \
    PHP_GTK_FE(cairo_surface_flush,                   arginfo_cairo_surface_flush) \
    PHP_GTK_FE(cairo_surface_get_device,              arginfo_cairo_surface_get_device) \
    PHP_GTK_FE(cairo_surface_get_font_options,        arginfo_cairo_surface_get_font_options) \
    PHP_GTK_FE(cairo_surface_get_content,             arginfo_cairo_surface_get_content) \
    PHP_GTK_FE(cairo_surface_mark_dirty,              arginfo_cairo_surface_mark_dirty) \
    PHP_GTK_FE(cairo_surface_mark_dirty_rectangle,    arginfo_cairo_surface_mark_dirty_rectangle) \
    PHP_GTK_FE(cairo_surface_set_device_offset,       arginfo_cairo_surface_set_device_offset) \
    PHP_GTK_FE(cairo_surface_get_device_offset,       arginfo_cairo_surface_get_device_offset) \
    PHP_GTK_FE(cairo_surface_get_device_scale,        arginfo_cairo_surface_get_device_scale) \
    PHP_GTK_FE(cairo_surface_set_device_scale,        arginfo_cairo_surface_set_device_scale) \
    PHP_GTK_FE(cairo_surface_set_fallback_resolution, arginfo_cairo_surface_set_fallback_resolution) \
    PHP_GTK_FE(cairo_surface_get_fallback_resolution, arginfo_cairo_surface_get_fallback_resolution) \
    PHP_GTK_FE(cairo_surface_get_type,                arginfo_cairo_surface_get_type) \
    PHP_GTK_FE(cairo_surface_set_user_data,           arginfo_cairo_surface_set_user_data) \
    PHP_GTK_FE(cairo_surface_get_user_data,           arginfo_cairo_surface_get_user_data) \
    PHP_GTK_FE(cairo_surface_copy_page,               arginfo_cairo_surface_copy_page) \
    PHP_GTK_FE(cairo_surface_show_page,               arginfo_cairo_surface_show_page) \
    PHP_GTK_FE(cairo_surface_has_show_text_glyphs,    arginfo_cairo_surface_has_show_text_glyphs) \
    PHP_GTK_FE(cairo_surface_set_mime_data,           arginfo_cairo_surface_set_mime_data) \
    PHP_GTK_FE(cairo_surface_get_mime_data,           arginfo_cairo_surface_get_mime_data) \
    PHP_GTK_FE(cairo_surface_supports_mime_type,      arginfo_cairo_surface_supports_mime_type) \
    PHP_GTK_FE(cairo_surface_map_to_image,            arginfo_cairo_surface_map_to_image) \
    PHP_GTK_FE(cairo_surface_unmap_image,             arginfo_cairo_surface_unmap_image) \


#else

#define PHP_CAIRO_SURFACE_T_FE() \
    PHP_GTK_FE(cairo_surface_destroy,                 arginfo_cairo_surface_destroy) \
    PHP_GTK_FE(cairo_surface_get_reference_count,     arginfo_cairo_surface_get_reference_count) \

#endif


extern zend_class_entry     *php_cairo_surface_t_class_entry;


#define PHP_CAIRO_SURFACE_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_surface_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_SURFACE_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_SURFACE_T_RSHUTDOWN_FUNCTION() {\
}

typedef struct _php_cairo_surface_t php_cairo_surface_t;
struct _php_cairo_surface_t {
    cairo_surface_t *ptr;

    zend_object std;
};

#if IS_IMPLEMENTED

php_cairo_surface_t*
      php_cairo_surface_create_similar(
                           php_cairo_surface_t *other,
                           zval *content,
                           zend_long width,
                           zend_long height);
php_cairo_surface_t*
      php_cairo_surface_create_similar_image(
                           php_cairo_surface_t *other,
                           zval *format,
                           zend_long width, zend_long height);
php_cairo_surface_t*
      php_cairo_surface_create_for_rectangle(
                           php_cairo_surface_t *target,
                           zval *x, zval *y,
                           zval *width, zval *height);
php_cairo_surface_t*
      php_cairo_surface_reference(php_cairo_surface_t *surface);
void  php_cairo_surface_destroy(php_cairo_surface_t *surface);
zval *php_cairo_surface_status(php_cairo_surface_t *surface);
void  php_cairo_surface_finish(php_cairo_surface_t *surface);
void  php_cairo_surface_flush(php_cairo_surface_t *surface);
zval *php_cairo_surface_get_device(php_cairo_surface_t *surface);
void  php_cairo_surface_get_font_options(php_cairo_surface_t *surface,
                                         zval *options);
zval *php_cairo_surface_get_content(php_cairo_surface_t *surface);
void  php_cairo_surface_mark_dirty(php_cairo_surface_t *surface);
void  php_cairo_surface_mark_dirty_rectangle(php_cairo_surface_t *surface,
                                             zend_long x, zend_long y,
                                             zend_long width, zend_long height);
void  php_cairo_surface_set_device_offset(php_cairo_surface_t *surface,
                                          zval *x_offset, zval *y_offset);
void  php_cairo_surface_get_device_offset(php_cairo_surface_t *surface, zval *x_offset, zval *y_offset);
void  php_cairo_surface_get_device_scale(php_cairo_surface_t *surface, zval *x_scale, zval *y_scale);
void  php_cairo_surface_set_device_scale(php_cairo_surface_t *surface, zval *x_scale, zval *y_scale);
void  php_cairo_surface_set_fallback_resolution(php_cairo_surface_t *surface, zval *x_pixels_per_inch, zval *y_pixels_per_inch);
void  php_cairo_surface_get_fallback_resolution(php_cairo_surface_t *surface, zval *x_pixels_per_inch, zval *y_pixels_per_inch);
zval *php_cairo_surface_get_type(php_cairo_surface_t *surface);
zval *php_cairo_surface_get_reference_count(php_cairo_surface_t *surface);
zval *php_cairo_surface_set_user_data(php_cairo_surface_t *surface, zval *key, void user_data, zval *destroy);
void  php_cairo_surface_get_user_data(php_cairo_surface_t *surface, zval *key);
void  php_cairo_surface_copy_page(php_cairo_surface_t *surface);
void  php_cairo_surface_show_page(php_cairo_surface_t *surface);
zval *php_cairo_surface_has_show_text_glyphs(php_cairo_surface_t *surface);
zval *php_cairo_surface_set_mime_data(php_cairo_surface_t *surface, zval *mime_type, zval *data, zval *length, zval *destroy, void closure);
void  php_cairo_surface_get_mime_data(php_cairo_surface_t *surface, zval *mime_type, zval *data, zval *length);
zval *php_cairo_surface_supports_mime_type(php_cairo_surface_t *surface, zval *mime_type);
php_cairo_surface_t*
      php_cairo_surface_map_to_image(php_cairo_surface_t *surface, zval *extents);
void  php_cairo_surface_unmap_image(php_cairo_surface_t *surface, php_cairo_surface_t *image);
#endif

zend_class_entry *php_cairo_surface_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);
zend_object *php_cairo_surface_t_create_object(zend_class_entry *class_type);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_t___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_surface_t, __construct);


#if IS_IMPLEMENTED

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_create_similar, 0, 0, 4)
    ZEND_ARG_INFO(0, other)
    ZEND_ARG_INFO(0, content)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_create_similar);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_create_similar_image, 0, 0, 4)
    ZEND_ARG_INFO(0, other)
    ZEND_ARG_INFO(0, format)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_create_similar_image);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_create_for_rectangle, 0, 0, 5)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_create_for_rectangle);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_reference, 0, 0, 1)
    ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_reference);
#endif

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_destroy, 0, 0, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_destroy);

#if 0
ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_status, 0, 0, 1)
    ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_status);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_finish, 0, 0, 1)
    ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_finish);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_flush, 0, 0, 1)
    ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_flush);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_get_device, 0, 0, 1)
    ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_device);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_get_font_options, 0, 0, 2)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_font_options);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_get_content, 0, 0, 1)
    ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_content);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_mark_dirty, 0, 0, 1)
    ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_mark_dirty);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_mark_dirty_rectangle, 0, 0, 5)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_mark_dirty_rectangle);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_set_device_offset, 0, 0, 3)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, x_offset)
    ZEND_ARG_INFO(0, y_offset)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_set_device_offset);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_get_device_offset, 0, 0, 3)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, x_offset)
    ZEND_ARG_INFO(0, y_offset)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_device_offset);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_get_device_scale, 0, 0, 3)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, x_scale)
    ZEND_ARG_INFO(0, y_scale)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_device_scale);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_set_device_scale, 0, 0, 3)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, x_scale)
    ZEND_ARG_INFO(0, y_scale)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_set_device_scale);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_set_fallback_resolution, 0, 0, 3)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, x_pixels_per_inch)
    ZEND_ARG_INFO(0, y_pixels_per_inch)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_set_fallback_resolution);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_get_fallback_resolution, 0, 0, 3)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, x_pixels_per_inch)
    ZEND_ARG_INFO(0, y_pixels_per_inch)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_fallback_resolution);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_get_type, 0, 0, 1)
    ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_type);
#endif

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_get_reference_count, 0, 0, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_reference_count);


#if 0
ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_set_user_data, 0, 0, 4)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, key)
    ZEND_ARG_INFO(0, user_data)
    ZEND_ARG_INFO(0, destroy)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_set_user_data);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_get_user_data, 0, 0, 2)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_user_data);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_copy_page, 0, 0, 1)
    ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_copy_page);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_show_page, 0, 0, 1)
    ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_show_page);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_has_show_text_glyphs, 0, 0, 1)
    ZEND_ARG_INFO(0, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_has_show_text_glyphs);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_set_mime_data, 0, 0, 6)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, mime_type)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, length)
    ZEND_ARG_INFO(0, destroy)
    ZEND_ARG_INFO(0, closure)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_set_mime_data);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_get_mime_data, 0, 0, 4)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, mime_type)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_mime_data);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_supports_mime_type, 0, 0, 2)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, mime_type)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_supports_mime_type);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_map_to_image, 0, 0, 2)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, extents)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_map_to_image);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_unmap_image, 0, 0, 2)
    ZEND_ARG_INFO(0, surface)
    ZEND_ARG_INFO(0, image)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_unmap_image);
#endif



#endif	/* PHP_CAIRO_SURFACE_T_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
