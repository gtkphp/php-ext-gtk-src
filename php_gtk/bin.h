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

#ifndef PHP_GTK_BIN_H
#define PHP_GTK_BIN_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#define PHP_GTK_BIN(ptr)           ((php_gtk_bin*)(ptr))
#define PHP_GTK_BIN_CLASS          php_gtk_bin_class_entry
#define PHP_GTK_BIN_OFFSET         (sizeof(php_gtk_bin) - sizeof(zend_object))

#define PHP_GTK_BIN_TO_PHP_G_OBJECT(ptr)   PHP_GOBJECT_OBJECT(ptr)

#define ZOBJ_IS_PHP_GTK_BIN(obj)   ((obj)!=NULL && obj->ce == php_gtk_bin_class_entry)
#define ZOBJ_TO_PHP_GTK_BIN(std)   PHP_GTK_BIN( ((void*)(std))-PHP_GTK_BIN_OFFSET )

#define ZVAL_IS_PHP_GTK_BIN(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GTK_BIN((val)->value.obj))
#define ZVAL_GET_PHP_GTK_BIN(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GTK_BIN((val)->value.obj))

#define ZVAL_SET_PHP_GTK_BIN(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

#define PHP_GTK_BIN_FE() \
    PHP_GTK_FE(gtk_bin_add, arginfo_gtk_bin_add)

#define PHP_GTK_BIN_MINIT_FUNCTION(container_ce, parent_ce) \
    php_gtk_bin_class_minit(container_ce, parent_ce)

#define PHP_GTK_BIN_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GTK_BIN_RSHUTDOWN_FUNCTION() {\
}

typedef php_gtk_widget php_gtk_bin;

GObject *php_gtk_bin_extends(php_gtk_bin *widget);
GType    php_gtk_bin_get_type(const char *php_class_name);

void php_gtk_bin_add(php_gtk_bin *list, zval *data);

zend_class_entry *php_gtk_bin_class_minit(zend_class_entry *container_ce, zend_class_entry *parent_ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_bin_add, 0, 0, 1)
    ZEND_ARG_INFO(0, container)
    ZEND_ARG_INFO(0, widget)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_bin_add);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_bin___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(gtk_bin, __construct);


#define _PHP_GTK_BIN_TRAIT() \
    PhpGtkContainerTrait parent_trait; \
    zend_function *add

typedef struct _PhpGtkBinTrait {
    _PHP_GTK_BIN_TRAIT();
} PhpGtkBinTrait;

typedef struct _PhpGtkBinClass {
    GtkBinClass parent_class;
    _PHP_GTK_BIN_TRAIT();
} PhpGtkBinClass;

typedef struct _PhpGtkBin {
    GtkBin parent_instance;
} PhpGtkBin;


void php_gtk_bin_init(PhpGtkBin *widget);
//void php_gtk_container_class_finalize(PhpGtkContainerClass *klass);
void php_gtk_bin_class_init(PhpGtkBinClass *klass);

GObject *php_gtk_bin_extends(php_gtk_bin *widget);
GType    php_gtk_bin_get_type(const char *php_class_name);


#endif	/* PHP_GTK_BIN_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
