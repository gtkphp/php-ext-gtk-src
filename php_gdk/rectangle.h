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

#ifndef PHP_GDK_RECTANGLE_H
#define PHP_GDK_RECTANGLE_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#define PHP_GDK_RECTANGLE(ptr)           ((php_gdk_rectangle*)(ptr))
#define PHP_GDK_RECTANGLE_CLASS          php_gdk_rectangle_class_entry
#define PHP_GDK_RECTANGLE_OFFSET         (sizeof(php_gdk_rectangle) - sizeof(zend_object))

#define ZOBJ_IS_PHP_GDK_RECTANGLE(obj)   ((obj)!=NULL && obj->ce == php_gdk_rectangle_class_entry)
#define ZOBJ_TO_PHP_GDK_RECTANGLE(std)   PHP_GDK_RECTANGLE( ((void*)(std))-PHP_GDK_RECTANGLE_OFFSET )

#define ZVAL_IS_PHP_GDK_RECTANGLE(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GDK_RECTANGLE((val)->value.obj))
#define ZVAL_GET_PHP_GDK_RECTANGLE(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GDK_RECTANGLE((val)->value.obj))

#define ZVAL_SET_PHP_GDK_RECTANGLE(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

#define PHP_GDK_RECTANGLE_FE() \

#define PHP_GDK_RECTANGLE_MINIT_FUNCTION(container_ce, parent_ce) \
    php_gdk_rectangle_class_init(container_ce, parent_ce)

#define PHP_GDK_RECTANGLE_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GDK_RECTANGLE_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry *php_gdk_rectangle_class_entry;

typedef struct _php_gdk_rectangle php_gdk_rectangle;
struct _php_gdk_rectangle {
    /*
     * zend_long x;
     * zend_long y;
     * zend_long width;
     * zend_long height;
     */
    GdkRectangle *ptr;

    zend_object std;
};


php_gdk_rectangle *php_gdk_rectangle_new(void);

zend_class_entry *php_gdk_rectangle_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_rectangle___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(gdk_rectangle, __construct);



#endif	/* PHP_GDK_RECTANGLE_H */

/*
* Local variables:
* tab-width: 4
* c-basic-offset: 4
* End:
* vim600: noet sw=4 ts=4 fdm=marker
* vim<600: noet sw=4 ts=4
*/
