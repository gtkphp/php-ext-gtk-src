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

#ifndef PHP_GTK_BOX_H
#define PHP_GTK_BOX_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "container.h"

#define PHP_GTK_BOX(ptr)           ((php_gtk_box*)(ptr))
#define PHP_GTK_BOX_CLASS          php_gtk_box_class_entry
#define PHP_GTK_BOX_OFFSET         (sizeof(php_gtk_box) - sizeof(zend_object))

#define PHP_GTK_BOX_TO_PHP_G_OBJECT(ptr)   PHP_GOBJECT_OBJECT(ptr)

#define ZOBJ_IS_PHP_GTK_BOX(obj)   ((obj)!=NULL && obj->ce == php_gtk_box_class_entry)
#define ZOBJ_TO_PHP_GTK_BOX(std)   PHP_GTK_BOX( ((void*)(std))-PHP_GTK_BOX_OFFSET )

#define ZVAL_IS_PHP_GTK_BOX(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GTK_BOX((val)->value.obj))
#define ZVAL_GET_PHP_GTK_BOX(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GTK_BOX((val)->value.obj))

#define ZVAL_SET_PHP_GTK_BOX(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

#define PHP_GTK_BOX_FE() \
    PHP_GTK_FE(gtk_box_new, arginfo_gtk_box_new)

#define PHP_GTK_BOX_MINIT_FUNCTION(container_ce, parent_ce) \
    php_gtk_box_class_minit(container_ce, parent_ce)

#define PHP_GTK_BOX_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GTK_BOX_RSHUTDOWN_FUNCTION() {\
}

typedef php_gtk_bin php_gtk_box;

void php_gtk_box_add(php_gtk_box *list, zval *data);


zend_class_entry *php_gtk_box_class_minit(zend_class_entry *container_ce, zend_class_entry *parent_ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_box_new, 0, 0, 2)
    ZEND_ARG_INFO(0, orientation)
    ZEND_ARG_INFO(0, spacing)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_box_new);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_box___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(gtk_box, __construct);


#define _PHP_GTK_BOX_TRAIT() \
    PhpGtkBinTrait parent_trait; \
    zend_function *add

typedef struct _PhpGtkBoxTrait {
    _PHP_GTK_BOX_TRAIT();
} PhpGtkBoxTrait;

typedef struct _PhpGtkBoxClass {
    GtkBinClass parent_class;
    _PHP_GTK_BOX_TRAIT();
} PhpGtkBoxClass;

typedef struct _PhpGtkBox {
    GtkBox parent_instance;
} PhpGtkBox;


void php_gtk_box_init(PhpGtkBox *widget);
//void php_gtk_container_class_finalize(PhpGtkContainerClass *klass);
void php_gtk_box_class_init(PhpGtkBoxClass *klass);

GObject *php_gtk_box_extends(php_gtk_box *widget);
GType    php_gtk_box_get_type(const char *php_class_name);

#endif	/* PHP_GTK_BOX_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
