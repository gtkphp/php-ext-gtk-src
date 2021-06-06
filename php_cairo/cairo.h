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

#ifndef PHP_CAIRO_T_H
#define PHP_CAIRO_T_H


#define PHP_CAIRO_T(ptr)           ((php_cairo_t*)(ptr))
#define PHP_CAIRO_T_CLASS          php_cairo_t_class_entry
#define PHP_CAIRO_T_OFFSET         (sizeof(php_cairo_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_T(std)   PHP_CAIRO_T( ((void*)(std))-PHP_CAIRO_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_T(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)


#define PHP_CAIRO_T_PTR(intern)       (intern)->ptr

#define DECL_PHP_CAIRO_T(name) \
    cairo_t *name = php_##name ? PHP_CAIRO_T_PTR(php_##name) : NULL;




#define PHP_CAIRO_T_FE() \
    PHP_GTK_FE(cairo_create,                   arginfo_cairo_create) \
    PHP_GTK_FE(cairo_reference,                arginfo_cairo_reference) \
    PHP_GTK_FE(cairo_destroy,                  arginfo_cairo_destroy) \
    PHP_GTK_FE(cairo_status,                   arginfo_cairo_status) \
    PHP_GTK_FE(cairo_save,                     arginfo_cairo_save) \
    PHP_GTK_FE(cairo_restore,                  arginfo_cairo_restore) \
    PHP_GTK_FE(cairo_get_target,               arginfo_cairo_get_target) \
    PHP_GTK_FE(cairo_push_group,               arginfo_cairo_push_group) \
    PHP_GTK_FE(cairo_push_group_with_content,  arginfo_cairo_push_group_with_content) \
    PHP_GTK_FE(cairo_pop_group,                arginfo_cairo_pop_group) \
    PHP_GTK_FE(cairo_pop_group_to_source,      arginfo_cairo_pop_group_to_source) \
    PHP_GTK_FE(cairo_get_group_target,         arginfo_cairo_get_group_target) \
    PHP_GTK_FE(cairo_set_source_rgb,           arginfo_cairo_set_source_rgb) \
    PHP_GTK_FE(cairo_set_source_rgba,          arginfo_cairo_set_source_rgba) \
    PHP_GTK_FE(cairo_set_source,               arginfo_cairo_set_source) \
    PHP_GTK_FE(cairo_set_source_surface,       arginfo_cairo_set_source_surface) \
    PHP_GTK_FE(cairo_get_source,               arginfo_cairo_get_source) \
    PHP_GTK_FE(cairo_set_antialias,            arginfo_cairo_set_antialias) \
    PHP_GTK_FE(cairo_get_antialias,            arginfo_cairo_get_antialias) \
    PHP_GTK_FE(cairo_set_dash,                 arginfo_cairo_set_dash) \
    PHP_GTK_FE(cairo_get_dash_count,           arginfo_cairo_get_dash_count) \
    PHP_GTK_FE(cairo_get_dash,                 arginfo_cairo_get_dash) \
    PHP_GTK_FE(cairo_set_fill_rule,            arginfo_cairo_set_fill_rule) \
    PHP_GTK_FE(cairo_get_fill_rule,            arginfo_cairo_get_fill_rule) \
    PHP_GTK_FE(cairo_set_line_cap,             arginfo_cairo_set_line_cap) \
    PHP_GTK_FE(cairo_get_line_cap,             arginfo_cairo_get_line_cap) \
    PHP_GTK_FE(cairo_set_line_join,            arginfo_cairo_set_line_join) \
    PHP_GTK_FE(cairo_get_line_join,            arginfo_cairo_get_line_join) \
    PHP_GTK_FE(cairo_set_line_width,           arginfo_cairo_set_line_width) \
    PHP_GTK_FE(cairo_get_line_width,           arginfo_cairo_get_line_width) \
    PHP_GTK_FE(cairo_set_miter_limit,          arginfo_cairo_set_miter_limit) \
    PHP_GTK_FE(cairo_get_miter_limit,          arginfo_cairo_get_miter_limit) \
    PHP_GTK_FE(cairo_set_operator,             arginfo_cairo_set_operator) \
    PHP_GTK_FE(cairo_get_operator,             arginfo_cairo_get_operator) \
    PHP_GTK_FE(cairo_set_tolerance,            arginfo_cairo_set_tolerance) \
    PHP_GTK_FE(cairo_get_tolerance,            arginfo_cairo_get_tolerance) \
    PHP_GTK_FE(cairo_clip,                     arginfo_cairo_clip) \
    PHP_GTK_FE(cairo_clip_preserve,            arginfo_cairo_clip_preserve) \
    PHP_GTK_FE(cairo_clip_extents,             arginfo_cairo_clip_extents) \
    PHP_GTK_FE(cairo_in_clip,                  arginfo_cairo_in_clip) \
    PHP_GTK_FE(cairo_reset_clip,               arginfo_cairo_reset_clip) \
    PHP_GTK_FE(cairo_rectangle_list_destroy,   arginfo_cairo_rectangle_list_destroy) \
    PHP_GTK_FE(cairo_copy_clip_rectangle_list, arginfo_cairo_copy_clip_rectangle_list) \
    PHP_GTK_FE(cairo_fill,                     arginfo_cairo_fill) \
    PHP_GTK_FE(cairo_fill_preserve,            arginfo_cairo_fill_preserve) \
    PHP_GTK_FE(cairo_fill_extents,             arginfo_cairo_fill_extents) \
    PHP_GTK_FE(cairo_in_fill,                  arginfo_cairo_in_fill) \
    PHP_GTK_FE(cairo_mask,                     arginfo_cairo_mask) \
    PHP_GTK_FE(cairo_mask_surface,             arginfo_cairo_mask_surface) \
    PHP_GTK_FE(cairo_paint,                    arginfo_cairo_paint) \
    PHP_GTK_FE(cairo_paint_with_alpha,         arginfo_cairo_paint_with_alpha) \
    PHP_GTK_FE(cairo_stroke,                   arginfo_cairo_stroke) \
    PHP_GTK_FE(cairo_stroke_preserve,          arginfo_cairo_stroke_preserve) \
    PHP_GTK_FE(cairo_stroke_extents,           arginfo_cairo_stroke_extents) \
    PHP_GTK_FE(cairo_in_stroke,                arginfo_cairo_in_stroke) \
    PHP_GTK_FE(cairo_copy_page,                arginfo_cairo_copy_page) \
    PHP_GTK_FE(cairo_show_page,                arginfo_cairo_show_page) \
    PHP_GTK_FE(cairo_get_reference_count,      arginfo_cairo_get_reference_count) \
    PHP_GTK_FE(cairo_set_user_data,            arginfo_cairo_set_user_data) \
    PHP_GTK_FE(cairo_get_user_data,            arginfo_cairo_get_user_data) \

#define PHP_CAIRO_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_T_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_cairo_t_class_entry;


typedef struct _php_cairo_t php_cairo_t;
struct _php_cairo_t {
    cairo_t *ptr;

    zend_object std;
};

zend_class_entry*
php_cairo_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);

php_cairo_t *
php_cairo_t_new();

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_t___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_t, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_create, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, target, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_create);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_reference, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_reference);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_destroy, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_destroy);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_status, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_status);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_save, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_save);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_restore, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_restore);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_target, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_target);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_push_group, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_push_group);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_push_group_with_content, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, content)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_push_group_with_content);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_pop_group, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pop_group);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_pop_group_to_source, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pop_group_to_source);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_group_target, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_group_target);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_source_rgb, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, red, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, green, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, blue, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_source_rgb);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_source_rgba, 0, ZEND_SEND_BY_VAL, 5)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, red, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, green, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, blue, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, alpha, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_source_rgba);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_source, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, source, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_source);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_source_surface, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_source_surface);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_source, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_source);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_antialias, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, antialias)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_antialias);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_antialias, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_antialias);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_dash, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dashes, IS_ARRAY, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, num_dashes, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, offset, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_dash);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_dash_count, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_dash_count);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_dash, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, dashes, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, offset, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_dash);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_fill_rule, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, fill_rule)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_fill_rule);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_fill_rule, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_fill_rule);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_line_cap, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, line_cap)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_line_cap);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_line_cap, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_line_cap);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_line_join, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, line_join)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_line_join);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_line_join, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_line_join);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_line_width, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_line_width);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_line_width, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_line_width);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_miter_limit, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, limit, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_miter_limit);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_miter_limit, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_miter_limit);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_operator, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, op)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_operator);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_operator, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_operator);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_tolerance, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, tolerance, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_tolerance);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_tolerance, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_tolerance);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_clip, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_clip);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_clip_preserve, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_clip_preserve);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_clip_extents, 0, ZEND_SEND_BY_VAL, 5)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x1, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y1, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x2, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y2, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_clip_extents);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_in_clip, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_in_clip);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_reset_clip, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_reset_clip);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_rectangle_list_destroy, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, rectangle_list, cairo_rectangle_list_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_rectangle_list_destroy);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_copy_clip_rectangle_list, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_copy_clip_rectangle_list);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_fill, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_fill);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_fill_preserve, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_fill_preserve);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_fill_extents, 0, ZEND_SEND_BY_VAL, 5)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x2, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y2, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_fill_extents);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_in_fill, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_in_fill);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_mask, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mask);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_mask_surface, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, surface, cairo_surface_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, surface_x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, surface_y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mask_surface);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_paint, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_paint);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_paint_with_alpha, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, alpha, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_paint_with_alpha);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_stroke, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_stroke);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_stroke_preserve, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_stroke_preserve);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_stroke_extents, 0, ZEND_SEND_BY_VAL, 5)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x1, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y1, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x2, IS_DOUBLE, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y2, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_stroke_extents);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_in_stroke, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_in_stroke);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_copy_page, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_copy_page);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_show_page, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_show_page);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_reference_count, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_reference_count);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_user_data, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, key, cairo_user_data_key_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, user_data, void, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, destroy, cairo_destroy_func_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_user_data);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_user_data, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, key, cairo_user_data_key_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_user_data);


#endif	/* PHP_CAIRO_T_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
