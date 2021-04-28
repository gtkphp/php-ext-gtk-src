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

#ifndef PHP_CAIRO_PATH_T_H
#define PHP_CAIRO_PATH_T_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_cairo/path-data.h"


#define PHP_CAIRO_PATH_T(ptr)           ((php_cairo_path_t*)(ptr))
#define PHP_CAIRO_PATH_T_CLASS          php_cairo_path_t_class_entry
#define PHP_CAIRO_PATH_T_OFFSET         (sizeof(php_cairo_path_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_PATH_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_path_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_PATH_T(std)   PHP_CAIRO_PATH_T( ((void*)(std))-PHP_CAIRO_PATH_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_PATH_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_PATH_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_PATH_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_PATH_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_PATH_T(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

#define PHP_CAIRO_PATH_T_FE() \
    PHP_GTK_FE(cairo_copy_path,         arginfo_cairo_copy_path) \
    PHP_GTK_FE(cairo_copy_path_flat,    arginfo_cairo_copy_path_flat) \
    PHP_GTK_FE(cairo_path_destroy,      arginfo_cairo_path_destroy) \
    PHP_GTK_FE(cairo_append_path,       arginfo_cairo_append_path) \
    PHP_GTK_FE(cairo_has_current_point, arginfo_cairo_has_current_point) \
    PHP_GTK_FE(cairo_get_current_point, arginfo_cairo_get_current_point) \
    PHP_GTK_FE(cairo_new_path,          arginfo_cairo_new_path) \
    PHP_GTK_FE(cairo_new_sub_path,      arginfo_cairo_new_sub_path) \
    PHP_GTK_FE(cairo_close_path,        arginfo_cairo_close_path) \
    PHP_GTK_FE(cairo_arc,               arginfo_cairo_arc) \
    PHP_GTK_FE(cairo_arc_negative,      arginfo_cairo_arc_negative) \
    PHP_GTK_FE(cairo_curve_to,          arginfo_cairo_curve_to) \
    PHP_GTK_FE(cairo_line_to,           arginfo_cairo_line_to) \
    PHP_GTK_FE(cairo_move_to,           arginfo_cairo_move_to) \
    PHP_GTK_FE(cairo_rectangle,         arginfo_cairo_rectangle) \
    PHP_GTK_FE(cairo_glyph_path,        arginfo_cairo_glyph_path) \
    PHP_GTK_FE(cairo_text_path,         arginfo_cairo_text_path) \
    PHP_GTK_FE(cairo_rel_curve_to,      arginfo_cairo_rel_curve_to) \
    PHP_GTK_FE(cairo_rel_line_to,       arginfo_cairo_rel_line_to) \
    PHP_GTK_FE(cairo_rel_move_to,       arginfo_cairo_rel_move_to) \
    PHP_GTK_FE(cairo_path_extents,      arginfo_cairo_path_extents) \

#define PHP_CAIRO_PATH_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_path_t_class_init(container_ce, parent_ce); \
    php_cairo_path_data_t_class_init(container_ce, NULL)

#define PHP_CAIRO_PATH_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_PATH_T_RSHUTDOWN_FUNCTION() {\
}

typedef struct _php_cairo_path_t php_cairo_path_t;
struct _php_cairo_path_t {
    /*
    zval *status;
    zval *data;
    zend_long num_data;
    */
    cairo_path_t *ptr;

    zend_object std;
};


zend_class_entry *php_cairo_path_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_path_t___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_path_t, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_copy_path, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_copy_path);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_copy_path_flat, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_copy_path_flat);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_path_destroy, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, path, cairo_path_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_path_destroy);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_append_path, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, path, cairo_path_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_append_path);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_has_current_point, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_has_current_point);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_current_point, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_REF, x)
    ZEND_ARG_INFO(ZEND_SEND_BY_REF, y)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_current_point);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_new_path, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_new_path);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_new_sub_path, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_new_sub_path);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_close_path, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_close_path);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_arc, 0, ZEND_SEND_BY_VAL, 6)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, xc, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, yc, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, radius, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, angle1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, angle2, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_arc);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_arc_negative, 0, ZEND_SEND_BY_VAL, 6)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, xc, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, yc, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, radius, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, angle1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, angle2, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_arc_negative);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_curve_to, 0, ZEND_SEND_BY_VAL, 7)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x2, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y2, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x3, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y3, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_curve_to);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_line_to, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_line_to);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_move_to, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_move_to);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_rectangle, 0, ZEND_SEND_BY_VAL, 5)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, height, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_rectangle);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_glyph_path, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, glyphs, php_cairo_glyph_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, num_glyphs, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_glyph_path);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_text_path, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, utf8, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_text_path);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_rel_curve_to, 0, ZEND_SEND_BY_VAL, 7)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dx1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dy1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dx2, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dy2, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dx3, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dy3, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_rel_curve_to);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_rel_line_to, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dy, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_rel_line_to);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_rel_move_to, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dy, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_rel_move_to);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_path_extents, 0, ZEND_SEND_BY_VAL, 5)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x2, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y2, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_path_extents);


#endif	/* PHP_CAIRO_PATH_T_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
