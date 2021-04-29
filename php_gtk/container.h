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

#ifndef PHP_GTK_CONTAINER_H
#define PHP_GTK_CONTAINER_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "widget.h"

#define PHP_GTK_CONTAINER(ptr)           ((php_gtk_container*)(ptr))
#define PHP_GTK_CONTAINER_CLASS          php_gtk_container_class_entry
#define PHP_GTK_CONTAINER_OFFSET         (sizeof(php_gtk_container) - sizeof(zend_object))

#define PHP_GTK_CONTAINER_TO_PHP_G_OBJECT(ptr)   PHP_GOBJECT_OBJECT(ptr)

#define ZOBJ_IS_PHP_GTK_CONTAINER(obj)   ((obj)!=NULL && instanceof_function(obj->ce, php_gtk_container_class_entry))
#define ZOBJ_TO_PHP_GTK_CONTAINER(std)   PHP_GTK_CONTAINER( ((void*)(std))-PHP_GTK_CONTAINER_OFFSET )

#define ZVAL_IS_PHP_GTK_CONTAINER(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GTK_CONTAINER((val)->value.obj))
#define ZVAL_GET_PHP_GTK_CONTAINER(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GTK_CONTAINER((val)->value.obj))

#define ZVAL_SET_PHP_GTK_CONTAINER(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

#define PHP_GTK_CONTAINER_FE() \
    PHP_GTK_FE(gtk_container_add,          arginfo_gtk_container_add) \
    PHP_GTK_FE(gtk_container_get_children, arginfo_gtk_container_get_children)


#define PHP_GTK_CONTAINER_MINIT_FUNCTION(container_ce, parent_ce) \
    php_gtk_container_class_init(container_ce, parent_ce)

#define PHP_GTK_CONTAINER_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GTK_CONTAINER_RSHUTDOWN_FUNCTION() {\
}

typedef struct _php_gtk_container php_gtk_container;
struct _php_gtk_container {
    // put here members

    php_gtk_widget parent_instance;
    // Keep blank
};

void php_gtk_container_add(php_gtk_container *list, zval *data);

zend_class_entry *php_gtk_container_class_init(zend_class_entry *container_ce, zend_class_entry *ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_container_add, 0, 0, 2)
    ZEND_ARG_INFO(0, container)
    ZEND_ARG_INFO(0, widget)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_container_add);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_container_get_children, 0, 0, 1)
    ZEND_ARG_INFO(0, container)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_container_get_children);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_container___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(gtk_container, __construct);


#endif	/* PHP_GTK_CONTAINER_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
