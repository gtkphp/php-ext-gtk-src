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

#ifndef PHP_G_ERROR_H
#define PHP_G_ERROR_H


#define GLIB_VERSION (G_ENCODE_VERSION(GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION) | GLIB_MICRO_VERSION)


#define PHP_G_ERROR(ptr)           ((php_g_error*)(ptr))
#define PHP_G_ERROR_CLASS          php_g_error_class_entry
#define PHP_G_ERROR_OFFSET         (sizeof(php_g_error) - sizeof(zend_object))

#define ZOBJ_IS_PHP_G_ERROR(obj)   ((obj)!=NULL && obj->ce == php_g_error_class_entry)
#define ZOBJ_TO_PHP_G_ERROR(std)   PHP_G_ERROR( ((void*)(std))-PHP_G_ERROR_OFFSET )

#define ZVAL_IS_PHP_G_ERROR(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_G_ERROR((val)->value.obj))
#define ZVAL_GET_PHP_G_ERROR(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_G_ERROR((val)->value.obj))

#define ZVAL_SET_PHP_G_ERROR(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)


#define PHP_G_ERROR_COPY(src, dest) \
    (dest)->domain = zval_get_long(&src->domain); \
    (dest)->code = zval_get_long(&src->code); \
    (dest)->message = src->message.value.str->val;


#define PHP_G_ERROR_SET(dest, src) \
    ZVAL_SET_LONG(&(dest)->domain, (src)->domain) \
    ZVAL_SET_LONG(&(dest)->code, (src)->code) \
    ZVAL_STRING(&(dest)->message, (src)->message)


#define DECL_PHP_G_ERROR(name) \
    GError __##name; \
    GError *name = &__##name; \
    PHP_G_ERROR_COPY(php_##name, name);



#if GLIB_VERSION >= GLIB_VERSION_2_22
#define PHP_G_ERROR_FE_22200()  \
    PHP_GTK_FE(g_error_new_valist,        arginfo_g_error_new_valist)  \

#else
#define PHP_G_ERROR_FE_22200()
#endif

#if GLIB_VERSION >= GLIB_VERSION_2_16
#define PHP_G_ERROR_FE_21600()  \
    PHP_GTK_FE(g_prefix_error,        arginfo_g_prefix_error)  \
    PHP_GTK_FE(g_propagate_prefixed_error,        arginfo_g_propagate_prefixed_error)  \

#else
#define PHP_G_ERROR_FE_21600()
#endif

#if GLIB_VERSION >= GLIB_VERSION_2_18
#define PHP_G_ERROR_FE_21800()  \
    PHP_GTK_FE(g_set_error_literal,        arginfo_g_set_error_literal)  \

#else
#define PHP_G_ERROR_FE_21800()
#endif


#define PHP_G_ERROR_FE() \
    PHP_G_ERROR_FE_22200() \
    PHP_G_ERROR_FE_21600() \
    PHP_G_ERROR_FE_21800() \
    PHP_GTK_FE(g_error_new,             arginfo_g_error_new) \
    PHP_GTK_FE(g_error_new_literal,     arginfo_g_error_new_literal)  \
    PHP_GTK_FE(g_error_matches,         arginfo_g_error_matches)  \
    PHP_GTK_FE(g_set_error,             arginfo_g_set_error)  \
    PHP_GTK_FE(g_propagate_error,       arginfo_g_propagate_error)  \
    PHP_GTK_FE(g_error_copy,            arginfo_g_error_copy)  \
    PHP_GTK_FE(g_clear_error,           arginfo_g_clear_error)  \


#define PHP_G_ERROR_MINIT_FUNCTION(container_ce, parent_ce) \
    php_g_error_class_init(container_ce, parent_ce)

#define PHP_G_ERROR_MSHUTDOWN_FUNCTION() { \
}

#define PHP_G_ERROR_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_g_error_class_entry;


typedef struct _php_g_error php_g_error;
struct _php_g_error {
    zval domain;// of zend_long( typedef uint GQuark)
    zval code;// of zend_long
    zval message;// of zend_string

    zend_object std;
};

zend_class_entry*
php_g_error_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);

php_g_error *php_g_error_new(GError *gerror);


ZEND_BEGIN_ARG_INFO_EX(arginfo_g_error___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(g_error, __construct);

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_error_new, ZEND_RETURN_VALUE, 3, GError, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, domain, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, code, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, format, IS_STRING, 0)
    ZEND_ARG_VARIADIC_INFO(ZEND_SEND_BY_VAL, params)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_error_new);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_error_new_literal, ZEND_RETURN_VALUE, 3, GError, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, domain, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, code, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, message, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_error_new_literal);
#if GLIB_VERSION >= GLIB_VERSION_2_22
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_error_new_valist, ZEND_RETURN_VALUE, 4, GError, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, domain, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, code, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, format, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, args, IS_ARRAY, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_error_new_valist);
#endif
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_g_error_matches, ZEND_RETURN_VALUE, 3, _IS_BOOL, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, error, GError, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, domain, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, code, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_error_matches);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_g_set_error, ZEND_RETURN_VALUE, 4, IS_VOID, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_REF, err)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, domain, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, code, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, format, IS_STRING, 0)
    ZEND_ARG_VARIADIC_INFO(ZEND_SEND_BY_VAL, params)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_set_error);
#if GLIB_VERSION >= GLIB_VERSION_2_18
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_g_set_error_literal, ZEND_RETURN_VALUE, 4, IS_VOID, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_REF, err)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, domain, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, code, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, message, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_set_error_literal);
#endif
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_g_propagate_error, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    //ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_REF, dest, GError, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_REF, dest)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, src, GError, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_propagate_error);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_error_copy, ZEND_RETURN_VALUE, 1, GError, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, error, GError, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_error_copy);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_g_clear_error, ZEND_RETURN_VALUE, 1, IS_NULL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_REF, err, GError, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_clear_error);
#if GLIB_VERSION >= GLIB_VERSION_2_16
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_g_prefix_error, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_REF, err)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, format, IS_STRING, 0)
    ZEND_ARG_VARIADIC_INFO(ZEND_SEND_BY_VAL, params)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_prefix_error);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_g_propagate_prefixed_error, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_REF, dest)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, src, GError, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, format, IS_STRING, 0)
    ZEND_ARG_VARIADIC_INFO(ZEND_SEND_BY_VAL, params)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_propagate_prefixed_error);
#endif

#endif	/* PHP_G_ERROR_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
