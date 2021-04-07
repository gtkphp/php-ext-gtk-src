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

#ifndef PHP_GOBJECT_OBJECT_H
#define PHP_GOBJECT_OBJECT_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib-object.h>

#define PHP_GOBJECT_OBJECT(ptr)           ((php_gobject_object*)(ptr))
#define PHP_GOBJECT_OBJECT_CLASS          php_gobject_object_class_entry
#define PHP_GOBJECT_OBJECT_OFFSET         (sizeof(php_gobject_object) - sizeof(zend_object))

#define ZOBJ_IS_PHP_GOBJECT_OBJECT(obj)   ((obj)!=NULL && instanceof_function(obj->ce, php_gobject_object_class_entry))
#define ZOBJ_TO_PHP_GOBJECT_OBJECT(std)   PHP_GOBJECT_OBJECT( ((void*)(std))-PHP_GOBJECT_OBJECT_OFFSET )

#define ZVAL_IS_PHP_GOBJECT_OBJECT(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GOBJECT_OBJECT((val)->value.obj))
#define ZVAL_GET_PHP_GOBJECT_OBJECT(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GOBJECT_OBJECT((val)->value.obj))

#define ZVAL_SET_PHP_GOBJECT_OBJECT(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

extern zend_class_entry *php_gobject_object_class_entry;

#define PHP_GOBJECT_OBJECT_FE() \
    PHP_FE(g_object_connect, arginfo_g_object_connect)

#define PHP_GOBJECT_OBJECT_MINIT_FUNCTION(container_ce, parent_ce) \
    php_gobject_object_class_init(container_ce, parent_ce)

#define PHP_GOBJECT_OBJECT_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GOBJECT_OBJECT_RSHUTDOWN_FUNCTION() {\
}

typedef struct _php_gobject_object php_gobject_object;
struct _php_gobject_object {
    GObject *ptr;
    HashTable *properties;

    zend_object std;
};

php_gobject_object *php_gobject_object_connect(php_gobject_object *list, zval *data);

php_gobject_object *php_gobject_object_new(GObject *object);
zend_class_entry *php_gobject_object_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_g_object_connect, 0, 0, 4)
    ZEND_ARG_INFO(0, object)
    ZEND_ARG_TYPE_INFO(0, signal_spec, IS_STRING, 0)
    ZEND_ARG_CALLABLE_INFO(0, callback, 0)
    ZEND_ARG_INFO(0, user_data)
    ZEND_ARG_VARIADIC_INFO(0, signals_callbacks)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_object_connect);


ZEND_BEGIN_ARG_INFO_EX(arginfo_g_object___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(g_object, __construct);


#endif	/* PHP_GOBJECT_OBJECT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
