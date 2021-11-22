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

#ifndef PHP_CAIRO_SCALED_FONT_T_H
#define PHP_CAIRO_SCALED_FONT_T_H


#define PHP_CAIRO_SCALED_FONT_T(ptr)           ((php_cairo_scaled_font_t*)(ptr))
#define PHP_CAIRO_SCALED_FONT_T_CLASS          php_cairo_scaled_font_t_class_entry
#define PHP_CAIRO_SCALED_FONT_T_OFFSET         (sizeof(php_cairo_scaled_font_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_SCALED_FONT_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_scaled_font_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_SCALED_FONT_T(std)   PHP_CAIRO_SCALED_FONT_T( ((void*)(std))-PHP_CAIRO_SCALED_FONT_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_SCALED_FONT_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_SCALED_FONT_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_SCALED_FONT_T(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)


#define PHP_CAIRO_SCALED_FONT_T_PTR(intern)       (intern)->ptr

#define DECL_PHP_CAIRO_SCALED_FONT_T(name) \
    cairo_scaled_font_t *name = php_##name ? PHP_CAIRO_SCALED_FONT_T_PTR(php_##name) : NULL;




#if CAIRO_VERSION >= 10000
#define PHP_CAIRO_SCALED_FONT_T_FE_10000()  \
    PHP_GTK_FE(cairo_scaled_font_create,        arginfo_cairo_scaled_font_create)  \
    PHP_GTK_FE(cairo_scaled_font_reference,        arginfo_cairo_scaled_font_reference)  \
    PHP_GTK_FE(cairo_scaled_font_destroy,        arginfo_cairo_scaled_font_destroy)  \
    PHP_GTK_FE(cairo_scaled_font_status,        arginfo_cairo_scaled_font_status)  \
    PHP_GTK_FE(cairo_scaled_font_extents,        arginfo_cairo_scaled_font_extents)  \
    PHP_GTK_FE(cairo_scaled_font_glyph_extents,        arginfo_cairo_scaled_font_glyph_extents)  \

#else
#define PHP_CAIRO_SCALED_FONT_T_FE_10000()
#endif


#if CAIRO_VERSION >= 10200
#define PHP_CAIRO_SCALED_FONT_T_FE_10200()  \
    PHP_GTK_FE(cairo_scaled_font_text_extents,        arginfo_cairo_scaled_font_text_extents)  \
    PHP_GTK_FE(cairo_scaled_font_get_font_face,        arginfo_cairo_scaled_font_get_font_face)  \
    PHP_GTK_FE(cairo_scaled_font_get_font_options,        arginfo_cairo_scaled_font_get_font_options)  \
    PHP_GTK_FE(cairo_scaled_font_get_font_matrix,        arginfo_cairo_scaled_font_get_font_matrix)  \
    PHP_GTK_FE(cairo_scaled_font_get_ctm,        arginfo_cairo_scaled_font_get_ctm)  \
    PHP_GTK_FE(cairo_scaled_font_get_type,        arginfo_cairo_scaled_font_get_type)  \

#else
#define PHP_CAIRO_SCALED_FONT_T_FE_10200()
#endif


#if CAIRO_VERSION >= 10800
#define PHP_CAIRO_SCALED_FONT_T_FE_10800()  \
    PHP_GTK_FE(cairo_scaled_font_text_to_glyphs,        arginfo_cairo_scaled_font_text_to_glyphs)  \
    PHP_GTK_FE(cairo_scaled_font_get_scale_matrix,        arginfo_cairo_scaled_font_get_scale_matrix)  \

#else
#define PHP_CAIRO_SCALED_FONT_T_FE_10800()
#endif


#if CAIRO_VERSION >= 10400
#define PHP_CAIRO_SCALED_FONT_T_FE_10400()  \
    PHP_GTK_FE(cairo_scaled_font_get_reference_count,        arginfo_cairo_scaled_font_get_reference_count)  \
    PHP_GTK_FE(cairo_scaled_font_set_user_data,        arginfo_cairo_scaled_font_set_user_data)  \
    PHP_GTK_FE(cairo_scaled_font_get_user_data,        arginfo_cairo_scaled_font_get_user_data)  \

#else
#define PHP_CAIRO_SCALED_FONT_T_FE_10400()
#endif


#define PHP_CAIRO_SCALED_FONT_T_FE() \
    PHP_CAIRO_SCALED_FONT_T_FE_10000() \
    PHP_CAIRO_SCALED_FONT_T_FE_10200() \
    PHP_CAIRO_SCALED_FONT_T_FE_10800() \
    PHP_CAIRO_SCALED_FONT_T_FE_10400() \


#define PHP_CAIRO_SCALED_FONT_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_scaled_font_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_SCALED_FONT_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_SCALED_FONT_T_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_cairo_scaled_font_t_class_entry;


typedef struct _php_cairo_scaled_font_t php_cairo_scaled_font_t;
struct _php_cairo_scaled_font_t {
    cairo_scaled_font_t *ptr;

    zend_object std;
};

zend_class_entry*
php_cairo_scaled_font_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);
php_cairo_scaled_font_t*
php_cairo_scaled_font_t_new();


ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_scaled_font_t___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_scaled_font_t, __construct);

#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_scaled_font_create, ZEND_RETURN_VALUE, 4, cairo_scaled_font_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, font_face, cairo_font_face_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, font_matrix, cairo_matrix_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, ctm, cairo_matrix_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_create);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_scaled_font_reference, ZEND_RETURN_VALUE, 1, cairo_scaled_font_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_reference);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scaled_font_destroy, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_destroy);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scaled_font_status, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_status);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scaled_font_extents, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, extents, cairo_font_extents_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_extents);
#endif
#if CAIRO_VERSION >= 10200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scaled_font_text_extents, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, utf8, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, extents, cairo_text_extents_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_text_extents);
#endif
#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scaled_font_glyph_extents, ZEND_RETURN_VALUE, 4, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, glyphs, cairo_glyph_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, num_glyphs, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, extents, cairo_text_extents_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_glyph_extents);
#endif
#if CAIRO_VERSION >= 10800
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scaled_font_text_to_glyphs, ZEND_RETURN_VALUE, 10, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, utf8, IS_STRING, 0)
    ZEND_ARG_ARRAY_INFO(ZEND_SEND_BY_VAL, glyphs, 0)
    ZEND_ARG_ARRAY_INFO(ZEND_SEND_BY_VAL, clusters, 1)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, cluster_flags, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_text_to_glyphs);
#endif
#if CAIRO_VERSION >= 10200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_scaled_font_get_font_face, ZEND_RETURN_VALUE, 1, cairo_font_face_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_get_font_face);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scaled_font_get_font_options, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_get_font_options);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scaled_font_get_font_matrix, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, font_matrix, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_get_font_matrix);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scaled_font_get_ctm, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, ctm, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_get_ctm);
#endif
#if CAIRO_VERSION >= 10800
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scaled_font_get_scale_matrix, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scale_matrix, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_get_scale_matrix);
#endif
#if CAIRO_VERSION >= 10200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scaled_font_get_type, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_get_type);
#endif
#if CAIRO_VERSION >= 10400
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scaled_font_get_reference_count, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_get_reference_count);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scaled_font_set_user_data, ZEND_RETURN_VALUE, 4, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, key, cairo_user_data_key_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, user_data)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, destroy, cairo_destroy_func_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_set_user_data);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_scaled_font_get_user_data, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, scaled_font, cairo_scaled_font_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, key, cairo_user_data_key_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_scaled_font_get_user_data);
#endif


#endif	/* PHP_CAIRO_SCALED_FONT_T_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
