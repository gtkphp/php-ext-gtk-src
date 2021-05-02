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

#ifndef PHP_CAIRO_T_H
#define PHP_CAIRO_T_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif



#define PHP_CAIRO_T(ptr)           ((php_cairo_t*)(ptr))
#define PHP_CAIRO_T_CLASS          php_cairo_t_class_entry
#define PHP_CAIRO_T_OFFSET         (sizeof(php_cairo_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_T(std)   PHP_CAIRO_T( ((void*)(std))-PHP_CAIRO_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_T(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

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

extern zend_class_entry *php_cairo_t_class_entry;

typedef struct _php_cairo_t php_cairo_t;
struct _php_cairo_t {
    cairo_t *ptr;

    zend_object std;
};
php_cairo_t *php_cairo_new(void);

php_cairo_t *php_cairo_create(zval *target);
php_cairo_t *php_cairo_reference(php_cairo_t *cr);
void php_cairo_destroy(php_cairo_t *cr);
zval *php_cairo_status(php_cairo_t *cr);
void php_cairo_save(php_cairo_t *cr);
void php_cairo_restore(php_cairo_t *cr);
zval *php_cairo_get_target(php_cairo_t *cr);
void php_cairo_push_group(php_cairo_t *cr);
void php_cairo_push_group_with_content(php_cairo_t *cr, zval *content);
zval *php_cairo_pop_group(php_cairo_t *cr);
void php_cairo_pop_group_to_source(php_cairo_t *cr);
zval *php_cairo_get_group_target(php_cairo_t *cr);
void php_cairo_set_source_rgb(php_cairo_t *cr, zval *red, zval *green, zval *blue);
void php_cairo_set_source_rgba(php_cairo_t *cr, zval *red, zval *green, zval *blue, zval *alpha);
void php_cairo_set_source(php_cairo_t *cr, zval *source);
void php_cairo_set_source_surface(php_cairo_t *cr, zval *surface, zval *x, zval *y);
zval *php_cairo_get_source(php_cairo_t *cr);
void php_cairo_set_antialias(php_cairo_t *cr, zval *antialias);
zval *php_cairo_get_antialias(php_cairo_t *cr);
void php_cairo_set_dash(php_cairo_t *cr, zval *dashes, zend_long num_dashes, zval *offset);
zend_long php_cairo_get_dash_count(php_cairo_t *cr);
void php_cairo_get_dash(php_cairo_t *cr, zval *dashes, zval *offset);
void php_cairo_set_fill_rule(php_cairo_t *cr, zval *fill_rule);
zval *php_cairo_get_fill_rule(php_cairo_t *cr);
void php_cairo_set_line_cap(php_cairo_t *cr, zval *line_cap);
zval *php_cairo_get_line_cap(php_cairo_t *cr);
void php_cairo_set_line_join(php_cairo_t *cr, zval *line_join);
zval *php_cairo_get_line_join(php_cairo_t *cr);
void php_cairo_set_line_width(php_cairo_t *cr, zval *width);
zval *php_cairo_get_line_width(php_cairo_t *cr);
void php_cairo_set_miter_limit(php_cairo_t *cr, zval *limit);
zval *php_cairo_get_miter_limit(php_cairo_t *cr);
void php_cairo_set_operator(php_cairo_t *cr, zval *op);
zval *php_cairo_get_operator(php_cairo_t *cr);
void php_cairo_set_tolerance(php_cairo_t *cr, zval *tolerance);
zval *php_cairo_get_tolerance(php_cairo_t *cr);
void php_cairo_clip(php_cairo_t *cr);
void php_cairo_clip_preserve(php_cairo_t *cr);
void php_cairo_clip_extents(php_cairo_t *cr, zval *x1, zval *y1, zval *x2, zval *y2);
zval *php_cairo_in_clip(php_cairo_t *cr, zval *x, zval *y);
void php_cairo_reset_clip(php_cairo_t *cr);
void php_cairo_rectangle_list_destroy(zval *rectangle_list);
zval *php_cairo_copy_clip_rectangle_list(php_cairo_t *cr);
void php_cairo_fill(php_cairo_t *cr);
void php_cairo_fill_preserve(php_cairo_t *cr);
void php_cairo_fill_extents(php_cairo_t *cr, zval *x1, zval *y1, zval *x2, zval *y2);
zval *php_cairo_in_fill(php_cairo_t *cr, zval *x, zval *y);
void php_cairo_mask(php_cairo_t *cr, zval *pattern);
void php_cairo_mask_surface(php_cairo_t *cr, zval *surface, zval *surface_x, zval *surface_y);
void php_cairo_paint(php_cairo_t *cr);
void php_cairo_paint_with_alpha(php_cairo_t *cr, zval *alpha);
void php_cairo_stroke(php_cairo_t *cr);
void php_cairo_stroke_preserve(php_cairo_t *cr);
void php_cairo_stroke_extents(php_cairo_t *cr, zval *x1, zval *y1, zval *x2, zval *y2);
zval *php_cairo_in_stroke(php_cairo_t *cr, zval *x, zval *y);
void php_cairo_copy_page(php_cairo_t *cr);
void php_cairo_show_page(php_cairo_t *cr);
zval *php_cairo_get_reference_count(php_cairo_t *cr);
zval *php_cairo_set_user_data(php_cairo_t *cr, zval *key, void *user_data, zval *destroy);
void php_cairo_get_user_data(php_cairo_t *cr, zval *key);

zend_class_entry *php_cairo_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_t___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_t, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_create, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, target, cairo_surface_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_create);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_reference, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_reference);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_destroy, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_destroy);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_status, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_status);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_save, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_save);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_restore, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_restore);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_target, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_target);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_push_group, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_push_group);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_push_group_with_content, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, content)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_push_group_with_content);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_pop_group, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pop_group);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_pop_group_to_source, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pop_group_to_source);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_group_target, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_group_target);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_source_rgb, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, red)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, green)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, blue)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_source_rgb);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_source_rgba, 0, ZEND_SEND_BY_VAL, 5)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, red)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, green)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, blue)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, alpha)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_source_rgba);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_source, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, source)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_source);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_source_surface, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, surface)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, x)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, y)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_source_surface);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_source, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_source);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_antialias, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, antialias)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_antialias);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_antialias, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_antialias);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_dash, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, dashes)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, num_dashes)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, offset)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_dash);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_dash_count, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_dash_count);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_dash, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, dashes)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, offset)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_dash);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_fill_rule, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, fill_rule)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_fill_rule);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_fill_rule, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_fill_rule);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_line_cap, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, line_cap)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_line_cap);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_line_cap, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_line_cap);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_line_join, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, line_join)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_line_join);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_line_join, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_line_join);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_line_width, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, width)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_line_width);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_line_width, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_line_width);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_miter_limit, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, limit)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_miter_limit);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_miter_limit, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_miter_limit);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_operator, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, op)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_operator);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_operator, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_operator);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_tolerance, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, tolerance)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_tolerance);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_tolerance, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_tolerance);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_clip, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_clip);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_clip_preserve, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_clip_preserve);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_clip_extents, 0, ZEND_SEND_BY_VAL, 5)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, x1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, y1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, x2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, y2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_clip_extents);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_in_clip, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, x)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, y)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_in_clip);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_reset_clip, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_reset_clip);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_rectangle_list_destroy, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, rectangle_list)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_rectangle_list_destroy);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_copy_clip_rectangle_list, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_copy_clip_rectangle_list);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_fill, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_fill);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_fill_preserve, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_fill_preserve);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_fill_extents, 0, ZEND_SEND_BY_VAL, 5)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, x1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, y1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, x2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, y2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_fill_extents);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_in_fill, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, x)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, y)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_in_fill);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_mask, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, pattern)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mask);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_mask_surface, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, surface)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, surface_x)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, surface_y)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_mask_surface);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_paint, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_paint);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_paint_with_alpha, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, alpha)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_paint_with_alpha);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_stroke, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_stroke);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_stroke_preserve, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_stroke_preserve);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_stroke_extents, 0, ZEND_SEND_BY_VAL, 5)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, x1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, y1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, x2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, y2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_stroke_extents);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_in_stroke, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, x)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, y)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_in_stroke);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_copy_page, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_copy_page);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_show_page, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_show_page);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_reference_count, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_reference_count);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_user_data, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, key)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, user_data)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, destroy)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_user_data);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_user_data, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, cr)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, key)
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
