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

#ifndef PHP_GOBJECT_SIGNAL_H
#define PHP_GOBJECT_SIGNAL_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#define PHP_GOBJECT_SIGNAL(ptr)           ((php_gobject_signal*)(ptr))
#define PHP_GOBJECT_SIGNAL_CLASS          php_gobject_signal_class_entry
#define PHP_GOBJECT_SIGNAL_OFFSET         (sizeof(php_gobject_signal) - sizeof(zend_object))

#define ZOBJ_IS_PHP_GOBJECT_SIGNAL(obj)   ((obj)!=NULL && obj->ce == php_gobject_signal_class_entry)
#define ZOBJ_TO_PHP_GOBJECT_SIGNAL(std)   PHP_GOBJECT_SIGNAL( ((void*)(std))-PHP_GOBJECT_SIGNAL_OFFSET )

#define ZVAL_IS_PHP_GOBJECT_SIGNAL(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GOBJECT_SIGNAL((val)->value.obj))
#define ZVAL_GET_PHP_GOBJECT_SIGNAL(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GOBJECT_SIGNAL((val)->value.obj))

#define ZVAL_SET_PHP_GOBJECT_SIGNAL(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

#define PHP_GOBJECT_SIGNAL_FE() \
    PHP_GTK_FE(g_signal_new,                           arginfo_g_signal_new) \
    PHP_GTK_FE(g_signal_connect,                       arginfo_g_signal_connect) \
    PHP_GTK_FE(g_signal_connect_data,                  arginfo_g_signal_connect_data) \
    PHP_GTK_FE(g_signal_emit,                          arginfo_g_signal_emit) \
    PHP_GTK_FE(g_signal_emit_by_name,                  arginfo_g_signal_emit_by_name) \


#define PHP_GOBJECT_SIGNAL_MINIT_FUNCTION(container_ce, parent_ce) \
    php_gobject_signal_class_init(container_ce, parent_ce)

#define PHP_GOBJECT_SIGNAL_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GOBJECT_SIGNAL_RSHUTDOWN_FUNCTION() {\
}

typedef struct _php_gobject_signal php_gobject_signal;
struct _php_gobject_signal {

    HashTable *properties;
    // ptr
    zend_object std;
};

zend_long
php_gobject_signal_connect_data(zval *instance,
                                zend_string *detailed_signal,
                                zval *handler,
                                zval *data,
                                zval *destroy_data,
                                zend_long connect_flags);
zend_long
php_gobject_signal_connect(zval *instance,
                           zend_string *detailed_signal,
                           zval *handler,
                           zval *data);
zend_class_entry *php_gobject_signal_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_g_signal___construct, 0, 0, 0)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_METHOD(g_signal, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_signal_connect_data, 0, 0, 0)
    ZEND_ARG_INFO(0, zinstance)
    ZEND_ARG_INFO(0, zdetailed_signal)
    ZEND_ARG_INFO(0, zhandler)
    ZEND_ARG_INFO(0, zdata)
    ZEND_ARG_INFO(0, zdestroy_data)
    ZEND_ARG_INFO(0, zconnect_flags)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_signal_connect_data);


ZEND_BEGIN_ARG_INFO_EX(arginfo_g_signal_connect, 0, 0, 0)
    ZEND_ARG_INFO(0, zinstance)
    ZEND_ARG_INFO(0, zdetailed_signal)
    ZEND_ARG_INFO(0, zhandler)
    ZEND_ARG_INFO(0, zdata)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_signal_connect);


ZEND_BEGIN_ARG_INFO_EX(arginfo_g_signal_new, 0, 0, 8)
    ZEND_ARG_TYPE_INFO(0, signal_name, IS_STRING, 0)
    ZEND_ARG_INFO(0, itype) //string|int
    ZEND_ARG_TYPE_INFO(0, signal_flags, IS_LONG, 0)
    ZEND_ARG_INFO(0, class_offset)
    ZEND_ARG_INFO(0, accumulator) // ZEND_ARG_CALLABLE_INFO
    ZEND_ARG_INFO(0, accu_data)
    ZEND_ARG_TYPE_INFO(0, return_type, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, n_params, IS_LONG, 0)
    ZEND_ARG_VARIADIC_INFO(0, params)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_signal_new);
//PHP_FUNCTION(g_signal_newv);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_signal_emit, 0, 0, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, instance, GObject, 0)
    ZEND_ARG_TYPE_INFO(0, signal_id, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, detail, IS_STRING, 0)
    ZEND_ARG_VARIADIC_INFO(0, params)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_signal_emit);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_signal_emit_by_name, 0, 0, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, instance, GObject, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, signal_detail, IS_STRING, 0)
    ZEND_ARG_VARIADIC_INFO(ZEND_SEND_BY_VAL, params)
    ZEND_ARG_INFO(ZEND_SEND_BY_REF, return_value)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_signal_emit_by_name);


#endif	/* PHP_GOBJECT_SIGNAL_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
