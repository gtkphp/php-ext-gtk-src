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

#ifndef PHP_GLIB_ERROR_H
#define PHP_GLIB_ERROR_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib.h>

#define PHP_GLIB_ERROR(ptr)           ((php_glib_error*)(ptr))
#define PHP_GLIB_ERROR_CLASS          php_glib_error_class_entry
#define PHP_GLIB_ERROR_OFFSET         (sizeof(php_glib_error) - sizeof(zend_object))

#define ZOBJ_IS_PHP_GLIB_ERROR(obj)   ((obj)!=NULL && obj->ce == php_glib_error_class_entry)
#define ZOBJ_TO_PHP_GLIB_ERROR(std)   PHP_GLIB_ERROR( ((void*)(std))-PHP_GLIB_ERROR_OFFSET )

#define ZVAL_IS_PHP_GLIB_ERROR(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GLIB_ERROR((val)->value.obj))
#define ZVAL_GET_PHP_GLIB_ERROR(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GLIB_ERROR((val)->value.obj))

#define ZVAL_SET_PHP_GLIB_ERROR(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

#define PHP_GLIB_ERROR_FE() \
    PHP_FE(g_error_new,                arginfo_g_error_new) \
    PHP_FE(g_error_new_literal,        arginfo_g_error_new_literal) \
    PHP_FE(g_error_free,               arginfo_g_error_free) \
    PHP_FE(g_error_copy,               arginfo_g_error_copy) \
    PHP_FE(g_error_matches,            arginfo_g_error_matches) \
    PHP_FE(g_set_error,                arginfo_g_set_error) \
    PHP_FE(g_set_error_literal,        arginfo_g_set_error_literal) \
    PHP_FE(g_propagate_error,          arginfo_g_propagate_error) \
    PHP_FE(g_clear_error,              arginfo_g_clear_error) \
    PHP_FE(g_prefix_error,             arginfo_g_prefix_error) \
    PHP_FE(g_propagate_prefixed_error, arginfo_g_propagate_prefixed_error) \

#define PHP_GLIB_ERROR_MINIT_FUNCTION(container_ce, parent_ce) \
    php_glib_error_class_init(container_ce, parent_ce)

#define PHP_GLIB_ERROR_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GLIB_ERROR_RSHUTDOWN_FUNCTION() {\
}

typedef struct _php_glib_error php_glib_error;
struct _php_glib_error {
    GError *ptr;

    zend_object std;
};

php_glib_error *php_glib_error_new(zend_long domain, zend_long code, zend_string *format, zval *args, int argc);
php_glib_error *php_glib_error_new_literal(zend_long domain, zend_long code, zend_string *message);
void php_glib_error_free(php_glib_error *error);
php_glib_error *php_glib_error_copy(php_glib_error *error);
zend_bool php_glib_error_matches(php_glib_error *error, zend_long domain, zend_long code);
void php_glib_set_error(php_glib_error **err, zend_long domain, zend_long code, zend_string *format, zval *args, int argc);
void php_glib_set_error_literal(php_glib_error **err, zval *domain, zend_long code, zend_string *message);
void php_glib_propagate_error(php_glib_error **dest, php_glib_error *src);
void php_glib_clear_error(php_glib_error *err);
void php_glib_prefix_error(php_glib_error **err, zend_string *format, zval *args, int argc);
void php_glib_propagate_prefixed_error(php_glib_error **dest, php_glib_error *src, zend_string *format, zval *args, int argc);

php_glib_error *php_glib_error_create(GError *error);

zend_class_entry *php_glib_error_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_error___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(g_error, __construct);


ZEND_BEGIN_ARG_INFO_EX(arginfo_g_error_new, 0, 0, 4)
    ZEND_ARG_INFO(0, domain)
    ZEND_ARG_INFO(0, code)
    ZEND_ARG_INFO(0, format)
    ZEND_ARG_VARIADIC_INFO(0, params)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_error_new);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_error_new_literal, 0, 0, 3)
    ZEND_ARG_INFO(0, domain)
    ZEND_ARG_INFO(0, code)
    ZEND_ARG_INFO(0, message)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_error_new_literal);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_error_free, 0, 0, 1)
    ZEND_ARG_INFO(1, error)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_error_free);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_error_copy, 0, 0, 1)
    ZEND_ARG_INFO(0, error)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_error_copy);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_error_matches, 0, 0, 3)
    ZEND_ARG_INFO(0, error)
    ZEND_ARG_INFO(0, domain)
    ZEND_ARG_INFO(0, code)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_error_matches);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_set_error, 0, 0, 5)
    ZEND_ARG_INFO(1, err)
    ZEND_ARG_INFO(0, domain)
    ZEND_ARG_INFO(0, code)
    ZEND_ARG_INFO(0, format)
    ZEND_ARG_VARIADIC_INFO(0, params)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_set_error);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_set_error_literal, 0, 0, 4)
    ZEND_ARG_INFO(0, err)
    ZEND_ARG_INFO(0, domain)
    ZEND_ARG_INFO(0, code)
    ZEND_ARG_INFO(0, message)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_set_error_literal);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_propagate_error, 0, 0, 2)
    ZEND_ARG_INFO(1, dest)
    ZEND_ARG_INFO(0, src)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_propagate_error);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_clear_error, 0, 0, 1)
    ZEND_ARG_INFO(1, err)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_clear_error);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_prefix_error, 0, 0, 3)
    ZEND_ARG_INFO(1, err)
    ZEND_ARG_INFO(0, format)
    ZEND_ARG_VARIADIC_INFO(0, params)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_prefix_error);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_propagate_prefixed_error, 0, 0, 4)
    ZEND_ARG_INFO(0, dest)
    ZEND_ARG_INFO(0, src)
    ZEND_ARG_INFO(0, format)
    ZEND_ARG_VARIADIC_INFO(0, params)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_propagate_prefixed_error);



#endif	/* PHP_GLIB_ERROR_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
