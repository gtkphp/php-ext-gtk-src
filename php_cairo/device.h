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

#ifndef PHP_CAIRO_DEVICE_T_H
#define PHP_CAIRO_DEVICE_T_H


#define PHP_CAIRO_DEVICE_T(ptr)           ((php_cairo_device_t*)(ptr))
#define PHP_CAIRO_DEVICE_T_CLASS          php_cairo_device_t_class_entry
#define PHP_CAIRO_DEVICE_T_OFFSET         (sizeof(php_cairo_device_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_DEVICE_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_device_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_DEVICE_T(std)   PHP_CAIRO_DEVICE_T( ((void*)(std))-PHP_CAIRO_DEVICE_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_DEVICE_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_DEVICE_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_DEVICE_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_DEVICE_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_DEVICE_T(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)


#define PHP_CAIRO_DEVICE_T_PTR(intern)       (intern)->ptr

#define DECL_PHP_CAIRO_DEVICE_T(name) \
    cairo_device_t *name = php_##name ? PHP_CAIRO_DEVICE_T_PTR(php_##name) : NULL;




#if CAIRO_VERSION >= 11000
#define PHP_CAIRO_DEVICE_T_FE_11000()  \
    PHP_GTK_FE(cairo_device_reference,        arginfo_cairo_device_reference)  \
    PHP_GTK_FE(cairo_device_destroy,        arginfo_cairo_device_destroy)  \
    PHP_GTK_FE(cairo_device_status,        arginfo_cairo_device_status)  \
    PHP_GTK_FE(cairo_device_finish,        arginfo_cairo_device_finish)  \
    PHP_GTK_FE(cairo_device_flush,        arginfo_cairo_device_flush)  \
    PHP_GTK_FE(cairo_device_get_type,        arginfo_cairo_device_get_type)  \
    PHP_GTK_FE(cairo_device_get_reference_count,        arginfo_cairo_device_get_reference_count)  \
    PHP_GTK_FE(cairo_device_acquire,        arginfo_cairo_device_acquire)  \
    PHP_GTK_FE(cairo_device_release,        arginfo_cairo_device_release)  \

#else
#define PHP_CAIRO_DEVICE_T_FE_11000()
#endif


#if CAIRO_VERSION >= 11200
#define PHP_CAIRO_DEVICE_T_FE_11200()  \
    PHP_GTK_FE(cairo_device_observer_elapsed,        arginfo_cairo_device_observer_elapsed)  \
    PHP_GTK_FE(cairo_device_observer_fill_elapsed,        arginfo_cairo_device_observer_fill_elapsed)  \
    PHP_GTK_FE(cairo_device_observer_glyphs_elapsed,        arginfo_cairo_device_observer_glyphs_elapsed)  \
    PHP_GTK_FE(cairo_device_observer_mask_elapsed,        arginfo_cairo_device_observer_mask_elapsed)  \
    PHP_GTK_FE(cairo_device_observer_paint_elapsed,        arginfo_cairo_device_observer_paint_elapsed)  \
    PHP_GTK_FE(cairo_device_observer_stroke_elapsed,        arginfo_cairo_device_observer_stroke_elapsed)  \

#else
#define PHP_CAIRO_DEVICE_T_FE_11200()
#endif


#define PHP_CAIRO_DEVICE_T_FE() \
    PHP_CAIRO_DEVICE_T_FE_11000() \
    PHP_CAIRO_DEVICE_T_FE_11200() \


#define PHP_CAIRO_DEVICE_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_device_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_DEVICE_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_DEVICE_T_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_cairo_device_t_class_entry;


typedef struct _php_cairo_device_t php_cairo_device_t;
struct _php_cairo_device_t {
    cairo_device_t *ptr;

    zend_object std;
};

zend_class_entry*
php_cairo_device_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);
php_cairo_device_t*
php_cairo_device_t_new();


ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_device_t___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_device_t, __construct);

#if CAIRO_VERSION >= 11000
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_device_reference, ZEND_RETURN_VALUE, 1, cairo_device_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_reference);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_destroy, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_destroy);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_status, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_status);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_finish, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_finish);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_flush, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_flush);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_get_type, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_get_type);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_get_reference_count, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_get_reference_count);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_acquire, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_acquire);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_release, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_release);
#endif
#if CAIRO_VERSION >= 11200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_observer_elapsed, ZEND_RETURN_VALUE, 1, IS_DOUBLE, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_observer_elapsed);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_observer_fill_elapsed, ZEND_RETURN_VALUE, 1, IS_DOUBLE, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_observer_fill_elapsed);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_observer_glyphs_elapsed, ZEND_RETURN_VALUE, 1, IS_DOUBLE, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_observer_glyphs_elapsed);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_observer_mask_elapsed, ZEND_RETURN_VALUE, 1, IS_DOUBLE, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_observer_mask_elapsed);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_observer_paint_elapsed, ZEND_RETURN_VALUE, 1, IS_DOUBLE, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_observer_paint_elapsed);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_device_observer_stroke_elapsed, ZEND_RETURN_VALUE, 1, IS_DOUBLE, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, cairo_device_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_device_observer_stroke_elapsed);
#endif


#endif	/* PHP_CAIRO_DEVICE_T_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
