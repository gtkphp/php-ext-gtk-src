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

#ifndef PHP_GTK_REQUISITION_H
#define PHP_GTK_REQUISITION_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#define PHP_GTK_REQUISITION(ptr)           ((php_gtk_requisition*)(ptr))
#define PHP_GTK_REQUISITION_CLASS          php_gtk_requisition_class_entry
#define PHP_GTK_REQUISITION_OFFSET         (sizeof(php_gtk_requisition) - sizeof(zend_object))

#define ZOBJ_IS_PHP_GTK_REQUISITION(obj)   ((obj)!=NULL && obj->ce == php_gtk_requisition_class_entry)
#define ZOBJ_TO_PHP_GTK_REQUISITION(std)   PHP_GTK_REQUISITION( ((void*)(std))-PHP_GTK_REQUISITION_OFFSET )

#define ZVAL_IS_PHP_GTK_REQUISITION(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GTK_REQUISITION((val)->value.obj))
#define ZVAL_GET_PHP_GTK_REQUISITION(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GTK_REQUISITION((val)->value.obj))

#define ZVAL_SET_PHP_GTK_REQUISITION(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

#define PHP_GTK_REQUISITION_FE() \

#define PHP_GTK_REQUISITION_MINIT_FUNCTION(container_ce, parent_ce) \
    php_gtk_requisition_class_init(container_ce, parent_ce)

#define PHP_GTK_REQUISITION_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GTK_REQUISITION_RSHUTDOWN_FUNCTION() {\
}

typedef struct _php_gtk_requisition php_gtk_requisition;
struct _php_gtk_requisition {
    /*
     * zend_long width;
     * zend_long height;
     */
    GtkRequisition *ptr;

    zend_object std;
};


zend_class_entry *php_gtk_requisition_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_requisition___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(gtk_requisition, __construct);



#endif	/* PHP_GTK_REQUISITION_H */

/*
* Local variables:
* tab-width: 4
* c-basic-offset: 4
* End:
* vim600: noet sw=4 ts=4 fdm=marker
* vim<600: noet sw=4 ts=4
*/
