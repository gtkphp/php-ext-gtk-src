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

#ifndef PHP_GTK_WIDGET_H
#define PHP_GTK_WIDGET_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#define PHP_GTK_WIDGET(ptr)           ((php_gtk_widget*)(ptr))
#define PHP_GTK_WIDGET_CLASS          php_gtk_widget_class_entry
#define PHP_GTK_WIDGET_OFFSET         (sizeof(php_gtk_widget) - sizeof(zend_object))

#define PHP_GTK_WIDGET_TO_PHP_G_OBJECT(ptr)   PHP_GOBJECT_OBJECT(ptr)

#define ZOBJ_IS_PHP_GTK_WIDGET(obj)   ((obj)!=NULL && instanceof_function(obj->ce, php_gtk_widget_class_entry))
#define ZOBJ_TO_PHP_GTK_WIDGET(std)   PHP_GTK_WIDGET( ((void*)(std))-PHP_GTK_WIDGET_OFFSET )

#define ZVAL_IS_PHP_GTK_WIDGET(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GTK_WIDGET((val)->value.obj))
#define ZVAL_GET_PHP_GTK_WIDGET(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GTK_WIDGET((val)->value.obj))

#define ZVAL_SET_PHP_GTK_WIDGET(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

extern zend_class_entry* php_gtk_widget_class_entry;

#define PHP_GTK_WIDGET_FE() \
    PHP_FE(gtk_widget_get_preferred_width, arginfo_gtk_widget_get_preferred_width) \
    PHP_FE(gtk_widget_show, arginfo_gtk_widget_show) \
    PHP_FE(gtk_widget_show_all, arginfo_gtk_widget_show_all)

#define PHP_GTK_WIDGET_MINIT_FUNCTION(container_ce, parent_ce) \
    php_gtk_widget_class_init(container_ce, parent_ce)

#define PHP_GTK_WIDGET_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GTK_WIDGET_RSHUTDOWN_FUNCTION() {\
}

typedef struct _php_gtk_widget php_gtk_widget;
struct _php_gtk_widget {
    // put here members

    php_gobject_object parent_instance;
    // Keep blank
};


void php_gtk_widget_show_all(php_gtk_widget *list, zval *data);

zend_class_entry *php_gtk_widget_class_init(zend_class_entry *container_ce, zend_class_entry *ce);
// rename it by php_gobject_get_override_function_object
zend_function    *php_gtk_get_override_function(zend_object *zobject, char *name);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(gtk_widget, __construct);

// bug on user_function g_signal_connect
//ZEND_ARG_OBJ_INFO(0, widget, GtkWidget, 0)

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_preferred_width, 0, 0, 3)
    ZEND_ARG_INFO(0, widget)
    ZEND_ARG_INFO(1, minimum_width)
    ZEND_ARG_INFO(1, natural_width)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_preferred_width);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_show, 0, 0, 1)
    ZEND_ARG_INFO(0, widget)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_show);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_show_all, 0, 0, 1)
    ZEND_ARG_INFO(0, widget)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_show_all);


#endif	/* PHP_GTK_WIDGET_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
