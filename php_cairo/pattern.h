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

#ifndef PHP_CAIRO_PATTERN_T_H
#define PHP_CAIRO_PATTERN_T_H


#define PHP_CAIRO_PATTERN_T(ptr)           ((php_cairo_pattern_t*)(ptr))
#define PHP_CAIRO_PATTERN_T_CLASS          php_cairo_pattern_t_class_entry
#define PHP_CAIRO_PATTERN_T_OFFSET         (sizeof(php_cairo_pattern_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_PATTERN_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_pattern_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_PATTERN_T(std)   PHP_CAIRO_PATTERN_T( ((void*)(std))-PHP_CAIRO_PATTERN_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_PATTERN_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_PATTERN_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_PATTERN_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_PATTERN_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_PATTERN_T(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)


#define PHP_CAIRO_PATTERN_T_PTR(intern)       (intern)->ptr

#define DECL_PHP_CAIRO_PATTERN_T(name) \
    cairo_pattern_t *name = php_##name ? PHP_CAIRO_PATTERN_T_PTR(php_##name) : NULL;




#if CAIRO_VERSION >= 10000
#define PHP_CAIRO_PATTERN_T_FE_10000()  \
    PHP_GTK_FE(cairo_pattern_add_color_stop_rgb,        arginfo_cairo_pattern_add_color_stop_rgb)  \
    PHP_GTK_FE(cairo_pattern_add_color_stop_rgba,        arginfo_cairo_pattern_add_color_stop_rgba)  \
    PHP_GTK_FE(cairo_pattern_create_rgb,        arginfo_cairo_pattern_create_rgb)  \
    PHP_GTK_FE(cairo_pattern_create_rgba,        arginfo_cairo_pattern_create_rgba)  \
    PHP_GTK_FE(cairo_pattern_create_for_surface,        arginfo_cairo_pattern_create_for_surface)  \
    PHP_GTK_FE(cairo_pattern_create_linear,        arginfo_cairo_pattern_create_linear)  \
    PHP_GTK_FE(cairo_pattern_create_radial,        arginfo_cairo_pattern_create_radial)  \
    PHP_GTK_FE(cairo_pattern_reference,        arginfo_cairo_pattern_reference)  \
    PHP_GTK_FE(cairo_pattern_status,        arginfo_cairo_pattern_status)  \
    PHP_GTK_FE(cairo_pattern_set_extend,        arginfo_cairo_pattern_set_extend)  \
    PHP_GTK_FE(cairo_pattern_get_extend,        arginfo_cairo_pattern_get_extend)  \
    PHP_GTK_FE(cairo_pattern_set_filter,        arginfo_cairo_pattern_set_filter)  \
    PHP_GTK_FE(cairo_pattern_get_filter,        arginfo_cairo_pattern_get_filter)  \
    PHP_GTK_FE(cairo_pattern_set_matrix,        arginfo_cairo_pattern_set_matrix)  \
    PHP_GTK_FE(cairo_pattern_get_matrix,        arginfo_cairo_pattern_get_matrix)  \

#else
#define PHP_CAIRO_PATTERN_T_FE_10000()
#endif


#if CAIRO_VERSION >= 10400
#define PHP_CAIRO_PATTERN_T_FE_10400()  \
    PHP_GTK_FE(cairo_pattern_get_color_stop_count,        arginfo_cairo_pattern_get_color_stop_count)  \
    PHP_GTK_FE(cairo_pattern_get_color_stop_rgba,        arginfo_cairo_pattern_get_color_stop_rgba)  \
    PHP_GTK_FE(cairo_pattern_get_rgba,        arginfo_cairo_pattern_get_rgba)  \
    PHP_GTK_FE(cairo_pattern_get_surface,        arginfo_cairo_pattern_get_surface)  \
    PHP_GTK_FE(cairo_pattern_get_linear_points,        arginfo_cairo_pattern_get_linear_points)  \
    PHP_GTK_FE(cairo_pattern_get_radial_circles,        arginfo_cairo_pattern_get_radial_circles)  \
    PHP_GTK_FE(cairo_pattern_get_reference_count,        arginfo_cairo_pattern_get_reference_count)  \

#else
#define PHP_CAIRO_PATTERN_T_FE_10400()
#endif


#if CAIRO_VERSION >= 11200
#define PHP_CAIRO_PATTERN_T_FE_11200()  \
    PHP_GTK_FE(cairo_pattern_create_mesh,        arginfo_cairo_pattern_create_mesh)  \
    PHP_GTK_FE(cairo_mesh_pattern_begin_patch,        arginfo_cairo_mesh_pattern_begin_patch)  \
    PHP_GTK_FE(cairo_mesh_pattern_end_patch,        arginfo_cairo_mesh_pattern_end_patch)  \
    PHP_GTK_FE(cairo_mesh_pattern_move_to,        arginfo_cairo_mesh_pattern_move_to)  \
    PHP_GTK_FE(cairo_mesh_pattern_line_to,        arginfo_cairo_mesh_pattern_line_to)  \
    PHP_GTK_FE(cairo_mesh_pattern_curve_to,        arginfo_cairo_mesh_pattern_curve_to)  \
    PHP_GTK_FE(cairo_mesh_pattern_set_control_point,        arginfo_cairo_mesh_pattern_set_control_point)  \
    PHP_GTK_FE(cairo_mesh_pattern_set_corner_color_rgb,        arginfo_cairo_mesh_pattern_set_corner_color_rgb)  \
    PHP_GTK_FE(cairo_mesh_pattern_set_corner_color_rgba,        arginfo_cairo_mesh_pattern_set_corner_color_rgba)  \
    PHP_GTK_FE(cairo_mesh_pattern_get_patch_count,        arginfo_cairo_mesh_pattern_get_patch_count)  \
    PHP_GTK_FE(cairo_mesh_pattern_get_path,        arginfo_cairo_mesh_pattern_get_path)  \
    PHP_GTK_FE(cairo_mesh_pattern_get_control_point,        arginfo_cairo_mesh_pattern_get_control_point)  \
    PHP_GTK_FE(cairo_mesh_pattern_get_corner_color_rgba,        arginfo_cairo_mesh_pattern_get_corner_color_rgba)  \

#else
#define PHP_CAIRO_PATTERN_T_FE_11200()
#endif


#if CAIRO_VERSION >= 10200
#define PHP_CAIRO_PATTERN_T_FE_10200()  \
    PHP_GTK_FE(cairo_pattern_get_type,        arginfo_cairo_pattern_get_type)  \

#else
#define PHP_CAIRO_PATTERN_T_FE_10200()
#endif


#define PHP_CAIRO_PATTERN_T_FE() \
    PHP_CAIRO_PATTERN_T_FE_10000() \
    PHP_CAIRO_PATTERN_T_FE_10400() \
    PHP_CAIRO_PATTERN_T_FE_11200() \
    PHP_CAIRO_PATTERN_T_FE_10200() \


#define PHP_CAIRO_PATTERN_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_pattern_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_PATTERN_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_PATTERN_T_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_cairo_pattern_t_class_entry;


struct _php_cairo_raster_source_pattern_callback {
    zend_fcall_info			fci_acquire;
    zend_fcall_info_cache	fcc_acquire;
    zend_fcall_info			fci_release;
    zend_fcall_info_cache	fcc_release;
    zend_fcall_info			fci_snapshot;
    zend_fcall_info_cache	fcc_snapshot;
    zend_fcall_info			fci_copy;
    zend_fcall_info_cache	fcc_copy;
    zend_fcall_info			fci_finish;
    zend_fcall_info_cache	fcc_finish;

    zval				    user_data;
    cairo_surface_t        *surface;
};
typedef struct _php_cairo_raster_source_pattern_callback php_cairo_raster_source_pattern_callback;

typedef struct _php_cairo_pattern_t php_cairo_pattern_t;
struct _php_cairo_pattern_t {
    cairo_pattern_t *ptr;
    php_cairo_raster_source_pattern_callback *callback;

    zend_object std;
};

zend_class_entry*
php_cairo_pattern_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);
php_cairo_pattern_t*
php_cairo_pattern_t_new();



ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_pattern_t___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_pattern_t, __construct);

#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_add_color_stop_rgb, ZEND_RETURN_VALUE, 5, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, offset, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, red, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, green, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, blue, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_add_color_stop_rgb);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_add_color_stop_rgba, ZEND_RETURN_VALUE, 6, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, offset, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, red, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, green, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, blue, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, alpha, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_add_color_stop_rgba);
#endif
#if CAIRO_VERSION >= 10400
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_get_color_stop_count, ZEND_RETURN_VALUE, 2, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, count, IS_LONG, 1)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_get_color_stop_count);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_get_color_stop_rgba, ZEND_RETURN_VALUE, 7, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, index, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, offset, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, red, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, green, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, blue, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, alpha, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_get_color_stop_rgba);
#endif
#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_pattern_create_rgb, ZEND_RETURN_VALUE, 3, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, red, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, green, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, blue, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_create_rgb);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_pattern_create_rgba, ZEND_RETURN_VALUE, 4, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, red, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, green, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, blue, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, alpha, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_create_rgba);
#endif
#if CAIRO_VERSION >= 10400
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_get_rgba, ZEND_RETURN_VALUE, 5, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, red, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, green, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, blue, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, alpha, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_get_rgba);
#endif
#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_pattern_create_for_surface, ZEND_RETURN_VALUE, 1, cairo_pattern_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_create_for_surface);
#endif
#if CAIRO_VERSION >= 10400
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_get_surface, ZEND_RETURN_VALUE, 2, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_REF, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_get_surface);
#endif
#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_pattern_create_linear, ZEND_RETURN_VALUE, 4, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x0, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y0, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y1, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_create_linear);
#endif
#if CAIRO_VERSION >= 10400
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_get_linear_points, ZEND_RETURN_VALUE, 5, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x0, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y0, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x1, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y1, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_get_linear_points);
#endif
#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_pattern_create_radial, ZEND_RETURN_VALUE, 6, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, cx0, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, cy0, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, radius0, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, cx1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, cy1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, radius1, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_create_radial);
#endif
#if CAIRO_VERSION >= 10400
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_get_radial_circles, ZEND_RETURN_VALUE, 7, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x0, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y0, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, r0, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x1, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y1, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, r1, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_get_radial_circles);
#endif
#if CAIRO_VERSION >= 11200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_pattern_create_mesh, ZEND_RETURN_VALUE, 0, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_create_mesh);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_mesh_pattern_begin_patch, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mesh_pattern_begin_patch);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_mesh_pattern_end_patch, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mesh_pattern_end_patch);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_mesh_pattern_move_to, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mesh_pattern_move_to);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_mesh_pattern_line_to, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mesh_pattern_line_to);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_mesh_pattern_curve_to, ZEND_RETURN_VALUE, 7, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x2, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y2, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x3, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y3, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mesh_pattern_curve_to);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_mesh_pattern_set_control_point, ZEND_RETURN_VALUE, 4, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, point_num, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mesh_pattern_set_control_point);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_mesh_pattern_set_corner_color_rgb, ZEND_RETURN_VALUE, 5, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, corner_num, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, red, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, green, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, blue, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mesh_pattern_set_corner_color_rgb);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_mesh_pattern_set_corner_color_rgba, ZEND_RETURN_VALUE, 6, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, corner_num, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, red, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, green, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, blue, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, alpha, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mesh_pattern_set_corner_color_rgba);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_mesh_pattern_get_patch_count, ZEND_RETURN_VALUE, 2, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, count, IS_LONG, 1)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mesh_pattern_get_patch_count);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_mesh_pattern_get_path, ZEND_RETURN_VALUE, 2, cairo_path_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, patch_num, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mesh_pattern_get_path);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_mesh_pattern_get_control_point, ZEND_RETURN_VALUE, 5, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, patch_num, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, point_num, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mesh_pattern_get_control_point);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_mesh_pattern_get_corner_color_rgba, ZEND_RETURN_VALUE, 7, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, patch_num, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, corner_num, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, red, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, green, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, blue, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, alpha, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mesh_pattern_get_corner_color_rgba);
#endif
#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_pattern_reference, ZEND_RETURN_VALUE, 1, cairo_pattern_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_reference);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_status, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_status);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_set_extend, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, extend, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_set_extend);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_get_extend, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_get_extend);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_set_filter, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, filter, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_set_filter);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_get_filter, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_get_filter);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_set_matrix, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_set_matrix);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_get_matrix, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_REF, matrix)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_get_matrix);
#endif
#if CAIRO_VERSION >= 10200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_get_type, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_get_type);
#endif
#if CAIRO_VERSION >= 10400
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_pattern_get_reference_count, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_get_reference_count);
#endif


#endif	/* PHP_CAIRO_PATTERN_T_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
