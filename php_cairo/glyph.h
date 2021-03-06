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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef PHP_CAIRO_GLYPH_T_H
#define PHP_CAIRO_GLYPH_T_H


#define PHP_CAIRO_GLYPH_T(ptr)           ((php_cairo_glyph_t*)(ptr))
#define PHP_CAIRO_GLYPH_T_CLASS          php_cairo_glyph_t_class_entry
#define PHP_CAIRO_GLYPH_T_OFFSET         (sizeof(php_cairo_glyph_t) - sizeof(zend_object))
#define PHP_CAIRO_GLYPH_T_PTR(ptr)       php_cairo_glyph_t_get_ptr(ptr)

#define ZOBJ_IS_PHP_CAIRO_GLYPH_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_glyph_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_GLYPH_T(std)   PHP_CAIRO_GLYPH_T( ((void*)(std))-PHP_CAIRO_GLYPH_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_GLYPH_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_GLYPH_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_GLYPH_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_GLYPH_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_GLYPH_T(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

#define PHP_CAIRO_GLYPH_T_FE() \
    PHP_GTK_FE(cairo_select_font_face,         arginfo_cairo_select_font_face) \
    PHP_GTK_FE(cairo_set_font_size,            arginfo_cairo_set_font_size) \
    PHP_GTK_FE(cairo_set_font_matrix,          arginfo_cairo_set_font_matrix) \
    PHP_GTK_FE(cairo_get_font_matrix,          arginfo_cairo_get_font_matrix) \
    PHP_GTK_FE(cairo_set_font_options,         arginfo_cairo_set_font_options) \
    PHP_GTK_FE(cairo_get_font_options,         arginfo_cairo_get_font_options) \
    PHP_GTK_FE(cairo_set_font_face,            arginfo_cairo_set_font_face) \
    PHP_GTK_FE(cairo_get_font_face,            arginfo_cairo_get_font_face) \
    PHP_GTK_FE(cairo_set_scaled_font,          arginfo_cairo_set_scaled_font) \
    PHP_GTK_FE(cairo_get_scaled_font,          arginfo_cairo_get_scaled_font) \
    PHP_GTK_FE(cairo_show_text,                arginfo_cairo_show_text) \
    PHP_GTK_FE(cairo_show_glyphs,              arginfo_cairo_show_glyphs) \
    PHP_GTK_FE(cairo_show_text_glyphs,         arginfo_cairo_show_text_glyphs) \
    PHP_GTK_FE(cairo_font_extents,             arginfo_cairo_font_extents) \
    PHP_GTK_FE(cairo_text_extents,             arginfo_cairo_text_extents) \
    PHP_GTK_FE(cairo_glyph_extents,            arginfo_cairo_glyph_extents) \
    PHP_GTK_FE(cairo_toy_font_face_create,     arginfo_cairo_toy_font_face_create) \
    PHP_GTK_FE(cairo_toy_font_face_get_family, arginfo_cairo_toy_font_face_get_family) \
    PHP_GTK_FE(cairo_toy_font_face_get_slant,  arginfo_cairo_toy_font_face_get_slant) \
    PHP_GTK_FE(cairo_toy_font_face_get_weight, arginfo_cairo_toy_font_face_get_weight) \
    PHP_GTK_FE(cairo_glyph_allocate,           arginfo_cairo_glyph_allocate) \
    PHP_GTK_FE(cairo_glyph_free,               arginfo_cairo_glyph_free) \
    PHP_GTK_FE(cairo_text_cluster_allocate,    arginfo_cairo_text_cluster_allocate) \
    PHP_GTK_FE(cairo_text_cluster_free,        arginfo_cairo_text_cluster_free) \

#define PHP_CAIRO_GLYPH_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_glyph_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_GLYPH_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_GLYPH_T_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_cairo_glyph_t_class_entry;


typedef struct _php_cairo_glyph_t php_cairo_glyph_t;
struct _php_cairo_glyph_t {
    zval index;// of zend_long
    zval x;// of double
    zval y;// of double

    zend_object std;
};

zend_class_entry*
php_cairo_glyph_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);



ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_glyph_t___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_glyph_t, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_select_font_face, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, family, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, slant, cairo_font_slant_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, weight, cairo_font_weight_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_select_font_face);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_font_size, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, size, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_font_size);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_font_matrix, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_font_matrix);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_font_matrix, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_font_matrix);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_font_options, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_font_options);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_font_options, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_font_options);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_font_face, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, font_face, cairo_font_face_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_font_face);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_font_face, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_font_face);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_set_scaled_font, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_set_scaled_font);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_get_scaled_font, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_get_scaled_font);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_show_text, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, utf8, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_show_text);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_show_glyphs, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, glyphs, cairo_glyph_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, num_glyphs, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_show_glyphs);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_show_text_glyphs, 0, ZEND_SEND_BY_VAL, 8)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, utf8, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, utf8_len, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, glyphs, cairo_glyph_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, num_glyphs, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, clusters, cairo_text_cluster_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, num_clusters, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cluster_flags, cairo_text_cluster_flags_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_show_text_glyphs);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_font_extents, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, extents, cairo_font_extents_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_extents);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_text_extents, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, utf8, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, extents, cairo_text_extents_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_text_extents);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_glyph_extents, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, glyphs, cairo_glyph_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, num_glyphs, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, extents, cairo_text_extents_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_glyph_extents);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_toy_font_face_create, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, family, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, slant, cairo_font_slant_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, weight, cairo_font_weight_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_toy_font_face_create);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_toy_font_face_get_family, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, font_face, cairo_font_face_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_toy_font_face_get_family);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_toy_font_face_get_slant, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, font_face, cairo_font_face_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_toy_font_face_get_slant);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_toy_font_face_get_weight, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, font_face, cairo_font_face_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_toy_font_face_get_weight);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_glyph_allocate, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, num_glyphs, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_glyph_allocate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_glyph_free, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, glyphs, cairo_glyph_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_glyph_free);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_text_cluster_allocate, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, num_clusters, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_text_cluster_allocate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_text_cluster_free, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, clusters, cairo_text_cluster_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_text_cluster_free);


#endif	/* PHP_CAIRO_GLYPH_T_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
