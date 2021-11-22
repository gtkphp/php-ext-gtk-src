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

#ifndef PHP_CAIRO_FONT_FACE_T_H
#define PHP_CAIRO_FONT_FACE_T_H


#define PHP_CAIRO_FONT_FACE_T(ptr)           ((php_cairo_font_face_t*)(ptr))
#define PHP_CAIRO_FONT_FACE_T_CLASS          php_cairo_font_face_t_class_entry
#define PHP_CAIRO_FONT_FACE_T_OFFSET         (sizeof(php_cairo_font_face_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_FONT_FACE_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_font_face_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_FONT_FACE_T(std)   PHP_CAIRO_FONT_FACE_T( ((void*)(std))-PHP_CAIRO_FONT_FACE_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_FONT_FACE_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_FONT_FACE_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_FONT_FACE_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_FONT_FACE_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_FONT_FACE_T(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)


#define PHP_CAIRO_FONT_FACE_T_PTR(intern)       (intern)->ptr

#define DECL_PHP_CAIRO_FONT_FACE_T(name) \
    cairo_font_face_t *name = php_##name ? PHP_CAIRO_FONT_FACE_T_PTR(php_##name) : NULL;




#if CAIRO_VERSION >= 10000
#define PHP_CAIRO_FONT_FACE_T_FE_10000()  \
    PHP_GTK_FE(cairo_font_face_status,        arginfo_cairo_font_face_status)  \

#else
#define PHP_CAIRO_FONT_FACE_T_FE_10000()
#endif


#if CAIRO_VERSION >= 10200
#define PHP_CAIRO_FONT_FACE_T_FE_10200()  \
    PHP_GTK_FE(cairo_font_face_get_type,        arginfo_cairo_font_face_get_type)  \

#else
#define PHP_CAIRO_FONT_FACE_T_FE_10200()
#endif


#if CAIRO_VERSION >= 10400
#define PHP_CAIRO_FONT_FACE_T_FE_10400()  \
    PHP_GTK_FE(cairo_font_face_get_reference_count,        arginfo_cairo_font_face_get_reference_count)  \

#else
#define PHP_CAIRO_FONT_FACE_T_FE_10400()
#endif


#define PHP_CAIRO_FONT_FACE_T_FE() \
    PHP_CAIRO_FONT_FACE_T_FE_10000() \
    PHP_CAIRO_FONT_FACE_T_FE_10200() \
    PHP_CAIRO_FONT_FACE_T_FE_10400() \


#define PHP_CAIRO_FONT_FACE_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_font_face_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_FONT_FACE_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_FONT_FACE_T_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_cairo_font_face_t_class_entry;


typedef struct _php_cairo_font_face_t php_cairo_font_face_t;
struct _php_cairo_font_face_t {
    cairo_font_face_t *ptr;

    zend_object std;
};

zend_class_entry*
php_cairo_font_face_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);
php_cairo_font_face_t*
php_cairo_font_face_t_new();


ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_font_face_t___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_font_face_t, __construct);

#if CAIRO_VERSION >= 10000
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_face_status, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, font_face, cairo_font_face_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_face_status);
#endif
#if CAIRO_VERSION >= 10200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_face_get_type, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, font_face, cairo_font_face_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_face_get_type);
#endif
#if CAIRO_VERSION >= 10400
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_font_face_get_reference_count, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, font_face, cairo_font_face_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_font_face_get_reference_count);
#endif


#endif	/* PHP_CAIRO_FONT_FACE_T_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
