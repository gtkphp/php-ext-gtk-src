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

#ifndef PHP_CAIRO_FONT_OPTIONS_T_H
#define PHP_CAIRO_FONT_OPTIONS_T_H


#define PHP_CAIRO_FONT_OPTIONS_T(ptr)           ((php_cairo_font_options_t*)(ptr))
#define PHP_CAIRO_FONT_OPTIONS_T_CLASS          php_cairo_font_options_t_class_entry
#define PHP_CAIRO_FONT_OPTIONS_T_OFFSET         (sizeof(php_cairo_font_options_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_FONT_OPTIONS_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_font_options_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_FONT_OPTIONS_T(std)   PHP_CAIRO_FONT_OPTIONS_T( ((void*)(std))-PHP_CAIRO_FONT_OPTIONS_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_FONT_OPTIONS_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_FONT_OPTIONS_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_FONT_OPTIONS_T(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)


#define PHP_CAIRO_FONT_OPTIONS_T_PTR(intern)       (intern)->ptr

#define DECL_PHP_CAIRO_FONT_OPTIONS_T(name) \
    cairo_font_options_t *name = php_##name ? PHP_CAIRO_FONT_OPTIONS_T_PTR(php_##name) : NULL;




#if CAIRO_VERSION >= 10000
#define PHP_CAIRO_FONT_OPTIONS_T_FE_10000()  \
    PHP_GTK_FE(cairo_font_options_create,        arginfo_cairo_font_options_create)  \
    PHP_GTK_FE(cairo_font_options_copy,        arginfo_cairo_font_options_copy)  \
    PHP_GTK_FE(cairo_font_options_destroy,        arginfo_cairo_font_options_destroy)  \
    PHP_GTK_FE(cairo_font_options_status,        arginfo_cairo_font_options_status)  \
    PHP_GTK_FE(cairo_font_options_merge,        arginfo_cairo_font_options_merge)  \
    PHP_GTK_FE(cairo_font_options_hash,        arginfo_cairo_font_options_hash)  \
    PHP_GTK_FE(cairo_font_options_equal,        arginfo_cairo_font_options_equal)  \
    PHP_GTK_FE(cairo_font_options_set_antialias,        arginfo_cairo_font_options_set_antialias)  \
    PHP_GTK_FE(cairo_font_options_get_antialias,        arginfo_cairo_font_options_get_antialias)  \
    PHP_GTK_FE(cairo_font_options_set_subpixel_order,        arginfo_cairo_font_options_set_subpixel_order)  \
    PHP_GTK_FE(cairo_font_options_get_subpixel_order,        arginfo_cairo_font_options_get_subpixel_order)  \
    PHP_GTK_FE(cairo_font_options_set_hint_style,        arginfo_cairo_font_options_set_hint_style)  \
    PHP_GTK_FE(cairo_font_options_get_hint_style,        arginfo_cairo_font_options_get_hint_style)  \
    PHP_GTK_FE(cairo_font_options_set_hint_metrics,        arginfo_cairo_font_options_set_hint_metrics)  \
    PHP_GTK_FE(cairo_font_options_get_hint_metrics,        arginfo_cairo_font_options_get_hint_metrics)  \

#else
#define PHP_CAIRO_FONT_OPTIONS_T_FE_10000()
#endif


#if CAIRO_VERSION >= 11600
#define PHP_CAIRO_FONT_OPTIONS_T_FE_11600()  \
    PHP_GTK_FE(cairo_font_options_get_variations,        arginfo_cairo_font_options_get_variations)  \
    PHP_GTK_FE(cairo_font_options_set_variations,        arginfo_cairo_font_options_set_variations)  \

#else
#define PHP_CAIRO_FONT_OPTIONS_T_FE_11600()
#endif


#define PHP_CAIRO_FONT_OPTIONS_T_FE() \
    PHP_CAIRO_FONT_OPTIONS_T_FE_10000() \
    PHP_CAIRO_FONT_OPTIONS_T_FE_11600() \


#define PHP_CAIRO_FONT_OPTIONS_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_font_options_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_FONT_OPTIONS_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_FONT_OPTIONS_T_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_cairo_font_options_t_class_entry;


typedef struct _php_cairo_font_options_t php_cairo_font_options_t;
struct _php_cairo_font_options_t {
    cairo_font_options_t *ptr;

    zend_object std;
};

zend_class_entry*
php_cairo_font_options_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);



ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_font_options_t___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_font_options_t, __construct);

#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_font_options_create, ZEND_RETURN_VALUE, 0, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_create);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_font_options_copy, ZEND_RETURN_VALUE, 1, cairo_font_options_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, original, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_copy);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_destroy, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_destroy);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_status, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_status);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_merge, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, other, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_merge);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_hash, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_hash);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_equal, ZEND_RETURN_VALUE, 2, _IS_BOOL, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, other, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_equal);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_set_antialias, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, antialias, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_set_antialias);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_get_antialias, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_get_antialias);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_set_subpixel_order, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, subpixel_order, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_set_subpixel_order);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_get_subpixel_order, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_get_subpixel_order);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_set_hint_style, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, hint_style, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_set_hint_style);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_get_hint_style, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_get_hint_style);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_set_hint_metrics, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, hint_metrics, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_set_hint_metrics);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_get_hint_metrics, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_get_hint_metrics);
#endif
#if CAIRO_VERSION >= 11600
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_get_variations, ZEND_RETURN_VALUE, 1, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_get_variations);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_options_set_variations, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, variations, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_options_set_variations);
#endif


#endif	/* PHP_CAIRO_FONT_OPTIONS_T_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
