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

#ifndef PHP_CAIRO_SURFACE_T_H
#define PHP_CAIRO_SURFACE_T_H


#define PHP_CAIRO_SURFACE_T(ptr)           ((php_cairo_surface_t*)(ptr))
#define PHP_CAIRO_SURFACE_T_CLASS          php_cairo_surface_t_class_entry
#define PHP_CAIRO_SURFACE_T_OFFSET         (sizeof(php_cairo_surface_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_SURFACE_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_surface_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_SURFACE_T(std)   PHP_CAIRO_SURFACE_T( ((void*)(std))-PHP_CAIRO_SURFACE_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_SURFACE_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_SURFACE_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_SURFACE_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_SURFACE_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_SURFACE_T(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)


#define PHP_CAIRO_SURFACE_T_PTR(intern)       (intern)->ptr

#define DECL_PHP_CAIRO_SURFACE_T(name) \
    cairo_surface_t *name = php_##name ? PHP_CAIRO_SURFACE_T_PTR(php_##name) : NULL;




#if CAIRO_VERSION >= 10000
#define PHP_CAIRO_SURFACE_T_FE_10000()  \
    PHP_GTK_FE(cairo_surface_create_similar,        arginfo_cairo_surface_create_similar)  \
    PHP_GTK_FE(cairo_surface_status,        arginfo_cairo_surface_status)  \
    PHP_GTK_FE(cairo_surface_finish,        arginfo_cairo_surface_finish)  \
    PHP_GTK_FE(cairo_surface_flush,        arginfo_cairo_surface_flush)  \
    PHP_GTK_FE(cairo_surface_get_font_options,        arginfo_cairo_surface_get_font_options)  \
    PHP_GTK_FE(cairo_surface_mark_dirty,        arginfo_cairo_surface_mark_dirty)  \
    PHP_GTK_FE(cairo_surface_mark_dirty_rectangle,        arginfo_cairo_surface_mark_dirty_rectangle)  \
    PHP_GTK_FE(cairo_surface_set_device_offset,        arginfo_cairo_surface_set_device_offset)  \

#else
#define PHP_CAIRO_SURFACE_T_FE_10000()
#endif


#if CAIRO_VERSION >= 11200
#define PHP_CAIRO_SURFACE_T_FE_11200()  \
    PHP_GTK_FE(cairo_surface_create_similar_image,        arginfo_cairo_surface_create_similar_image)  \
    PHP_GTK_FE(cairo_surface_supports_mime_type,        arginfo_cairo_surface_supports_mime_type)  \
    PHP_GTK_FE(cairo_surface_map_to_image,        arginfo_cairo_surface_map_to_image)  \
    PHP_GTK_FE(cairo_surface_unmap_image,        arginfo_cairo_surface_unmap_image)  \

#else
#define PHP_CAIRO_SURFACE_T_FE_11200()
#endif


#if CAIRO_VERSION >= 11000
#define PHP_CAIRO_SURFACE_T_FE_11000()  \
    PHP_GTK_FE(cairo_surface_create_for_rectangle,        arginfo_cairo_surface_create_for_rectangle)  \
    PHP_GTK_FE(cairo_surface_get_device,        arginfo_cairo_surface_get_device)  \

#else
#define PHP_CAIRO_SURFACE_T_FE_11000()
#endif


#if CAIRO_VERSION >= 10200
#define PHP_CAIRO_SURFACE_T_FE_10200()  \
    PHP_GTK_FE(cairo_surface_get_content,        arginfo_cairo_surface_get_content)  \
    PHP_GTK_FE(cairo_surface_get_device_offset,        arginfo_cairo_surface_get_device_offset)  \
    PHP_GTK_FE(cairo_surface_set_fallback_resolution,        arginfo_cairo_surface_set_fallback_resolution)  \
    PHP_GTK_FE(cairo_surface_get_type,        arginfo_cairo_surface_get_type)  \

#else
#define PHP_CAIRO_SURFACE_T_FE_10200()
#endif


#if CAIRO_VERSION >= 11400
#define PHP_CAIRO_SURFACE_T_FE_11400()  \
    PHP_GTK_FE(cairo_surface_get_device_scale,        arginfo_cairo_surface_get_device_scale)  \
    PHP_GTK_FE(cairo_surface_set_device_scale,        arginfo_cairo_surface_set_device_scale)  \

#else
#define PHP_CAIRO_SURFACE_T_FE_11400()
#endif


#if CAIRO_VERSION >= 10800
#define PHP_CAIRO_SURFACE_T_FE_10800()  \
    PHP_GTK_FE(cairo_surface_get_fallback_resolution,        arginfo_cairo_surface_get_fallback_resolution)  \
    PHP_GTK_FE(cairo_surface_has_show_text_glyphs,        arginfo_cairo_surface_has_show_text_glyphs)  \

#else
#define PHP_CAIRO_SURFACE_T_FE_10800()
#endif


#if CAIRO_VERSION >= 10400
#define PHP_CAIRO_SURFACE_T_FE_10400()  \
    PHP_GTK_FE(cairo_surface_get_reference_count,        arginfo_cairo_surface_get_reference_count)  \

#else
#define PHP_CAIRO_SURFACE_T_FE_10400()
#endif


#if CAIRO_VERSION >= 10600
#define PHP_CAIRO_SURFACE_T_FE_10600()  \
    PHP_GTK_FE(cairo_surface_copy_page,        arginfo_cairo_surface_copy_page)  \
    PHP_GTK_FE(cairo_surface_show_page,        arginfo_cairo_surface_show_page)  \

#else
#define PHP_CAIRO_SURFACE_T_FE_10600()
#endif


#define PHP_CAIRO_SURFACE_T_FE() \
    PHP_CAIRO_SURFACE_T_FE_10000() \
    PHP_CAIRO_SURFACE_T_FE_11200() \
    PHP_CAIRO_SURFACE_T_FE_11000() \
    PHP_CAIRO_SURFACE_T_FE_10200() \
    PHP_CAIRO_SURFACE_T_FE_11400() \
    PHP_CAIRO_SURFACE_T_FE_10800() \
    PHP_CAIRO_SURFACE_T_FE_10400() \
    PHP_CAIRO_SURFACE_T_FE_10600() \


#define PHP_CAIRO_SURFACE_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_surface_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_SURFACE_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_SURFACE_T_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_cairo_surface_t_class_entry;


typedef struct _php_cairo_surface_t php_cairo_surface_t;
struct _php_cairo_surface_t {
    cairo_surface_t *ptr;
    cairo_user_data_key_t key;

    zend_object std;
};

zend_class_entry*
php_cairo_surface_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);

php_cairo_surface_t *
php_cairo_surface_t_new();

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_surface_t___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_surface_t, __construct);

#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_surface_create_similar, ZEND_RETURN_VALUE, 4, cairo_surface_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, other, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, content, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, height, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_create_similar);
#endif
#if CAIRO_VERSION >= 11200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_surface_create_similar_image, ZEND_RETURN_VALUE, 4, cairo_surface_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, other, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, format, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, height, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_create_similar_image);
#endif
#if CAIRO_VERSION >= 11000
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_surface_create_for_rectangle, ZEND_RETURN_VALUE, 5, cairo_surface_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, target, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, height, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_create_for_rectangle);
#endif
#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_status, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_status);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_finish, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_finish);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_flush, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_flush);
#endif
#if CAIRO_VERSION >= 11000
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_surface_get_device, ZEND_RETURN_VALUE, 1, cairo_device_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_device);
#endif
#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_get_font_options, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_font_options);
#endif
#if CAIRO_VERSION >= 10200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_get_content, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_content);
#endif
#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_mark_dirty, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_mark_dirty);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_mark_dirty_rectangle, ZEND_RETURN_VALUE, 5, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, height, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_mark_dirty_rectangle);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_set_device_offset, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x_offset, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y_offset, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_set_device_offset);
#endif
#if CAIRO_VERSION >= 10200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_get_device_offset, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x_offset, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y_offset, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_device_offset);
#endif
#if CAIRO_VERSION >= 11400
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_get_device_scale, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x_scale, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y_scale, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_device_scale);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_set_device_scale, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x_scale, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y_scale, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_set_device_scale);
#endif
#if CAIRO_VERSION >= 10200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_set_fallback_resolution, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x_pixels_per_inch, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y_pixels_per_inch, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_set_fallback_resolution);
#endif
#if CAIRO_VERSION >= 10800
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_get_fallback_resolution, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x_pixels_per_inch, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y_pixels_per_inch, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_fallback_resolution);
#endif
#if CAIRO_VERSION >= 10200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_get_type, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_type);
#endif
#if CAIRO_VERSION >= 10400
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_get_reference_count, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_get_reference_count);
#endif
#if CAIRO_VERSION >= 10600
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_copy_page, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_copy_page);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_show_page, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_show_page);
#endif
#if CAIRO_VERSION >= 10800
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_surface_has_show_text_glyphs, ZEND_RETURN_VALUE, 1, cairo_bool_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_has_show_text_glyphs);
#endif
#if CAIRO_VERSION >= 11200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_surface_supports_mime_type, ZEND_RETURN_VALUE, 2, cairo_bool_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, mime_type, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_supports_mime_type);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_surface_map_to_image, ZEND_RETURN_VALUE, 2, cairo_surface_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, extents, cairo_rectangle_int_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_surface_map_to_image);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_surface_unmap_image, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, image, cairo_surface_t, 0)
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
