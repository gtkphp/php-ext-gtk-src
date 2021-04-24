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

#ifndef PHP_GTK_BUTTON_H
#define PHP_GTK_BUTTON_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "bin.h"

#define PHP_GTK_BUTTON(ptr)           ((php_gtk_button*)(ptr))
#define PHP_GTK_BUTTON_CLASS          php_gtk_button_class_entry
#define PHP_GTK_BUTTON_OFFSET         (sizeof(php_gtk_button) - sizeof(zend_object))

#define PHP_GTK_BUTTON_TO_PHP_G_OBJECT(ptr)   PHP_GOBJECT_OBJECT(ptr)

#define ZOBJ_IS_PHP_GTK_BUTTON(obj)   ((obj)!=NULL && instanceof_function(obj->ce, php_gtk_button_class_entry))
#define ZOBJ_TO_PHP_GTK_BUTTON(std)   PHP_GTK_BUTTON( ((void*)(std))-PHP_GTK_BUTTON_OFFSET )

#define ZVAL_IS_PHP_GTK_BUTTON(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GTK_BUTTON((val)->value.obj))
#define ZVAL_GET_PHP_GTK_BUTTON(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GTK_BUTTON((val)->value.obj))

#define ZVAL_SET_PHP_GTK_BUTTON(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

extern zend_class_entry *php_gtk_button_class_entry;

#define PHP_GTK_BUTTON_FE() \
    PHP_FE(gtk_button_new_with_label, arginfo_gtk_button_new_with_label)

#define PHP_GTK_BUTTON_MINIT_FUNCTION(container_ce, parent_ce) \
    php_gtk_button_class_init(container_ce, parent_ce)

#define PHP_GTK_BUTTON_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GTK_BUTTON_RSHUTDOWN_FUNCTION() {\
}

typedef struct _php_gtk_button php_gtk_button;
struct _php_gtk_button {
    // put here members

    php_gtk_bin parent_instance;
    // Keep blank
};




void php_gtk_button_new_with_label(php_gtk_button *self, zend_string *label);

zend_class_entry *php_gtk_button_class_init(zend_class_entry *container_ce, zend_class_entry *ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_button_new_with_label, 0, 0, 1)
    ZEND_ARG_INFO(0, label)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_button_new_with_label);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_button___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(gtk_button, __construct);


#endif	/* PHP_GTK_BUTTON_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
