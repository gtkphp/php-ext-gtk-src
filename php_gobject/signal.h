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

#include <glib-object.h>

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
    PHP_FE(g_signal_connect,                       arginfo_g_signal_connect) \
    PHP_FE(g_signal_connect_data,                  arginfo_g_signal_connect_data)


#define PHP_GOBJECT_SIGNAL_MINIT_FUNCTION(container_ce, parent_ce) \
    php_gobject_signal_class_init(container_ce, parent_ce)

#define PHP_GOBJECT_SIGNAL_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GOBJECT_SIGNAL_RSHUTDOWN_FUNCTION() {\
}

typedef struct _php_gobject_signal php_gobject_signal;
struct _php_gobject_signal {

    HashTable *properties;
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


#endif	/* PHP_GOBJECT_SIGNAL_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
