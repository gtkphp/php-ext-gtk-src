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

#ifndef PHP_GDK_PIXBUF_H
#define PHP_GDK_PIXBUF_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#define PHP_GDK_PIXBUF(ptr)           ((php_gdk_pixbuf*)(ptr))
#define PHP_GDK_PIXBUF_CLASS          php_gdk_pixbuf_class_entry
#define PHP_GDK_PIXBUF_OFFSET         (sizeof(php_gdk_pixbuf) - sizeof(zend_object))

#define PHP_GDK_PIXBUF_TO_PHP_G_OBJECT(ptr)   PHP_GOBJECT_OBJECT(ptr)

#define ZOBJ_IS_PHP_GDK_PIXBUF(obj)   ((obj)!=NULL && instanceof_function(obj->ce, php_gdk_pixbuf_class_entry))
#define ZOBJ_TO_PHP_GDK_PIXBUF(std)   PHP_GDK_PIXBUF( ((void*)(std))-PHP_GDK_PIXBUF_OFFSET )

#define ZVAL_IS_PHP_GDK_PIXBUF(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GDK_PIXBUF((val)->value.obj))
#define ZVAL_GET_PHP_GDK_PIXBUF(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GDK_PIXBUF((val)->value.obj))

#define ZVAL_SET_PHP_GDK_PIXBUF(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

extern zend_class_entry* php_gdk_pixbuf_class_entry;

#define PHP_GDK_PIXBUF_FE() \
    PHP_GTK_FE(gdk_pixbuf_new_from_file, arginfo_gdk_pixbuf_new_from_file)

#define PHP_GDK_PIXBUF_MINIT_FUNCTION(container_ce, parent_ce) \
    php_gdk_pixbuf_class_init(container_ce, parent_ce)

#define PHP_GDK_PIXBUF_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GDK_PIXBUF_RSHUTDOWN_FUNCTION() {\
}

typedef php_gobject_object php_gdk_pixbuf;

php_gdk_pixbuf *php_gdk_pixbuf_new_from_file(zend_string *filename, zval *error);

php_gdk_pixbuf *php_gdk_pixbuf_create(GdkPixbuf *pixbuf);
zend_class_entry *php_gdk_pixbuf_class_init(zend_class_entry *container_ce, zend_class_entry *ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_pixbuf_new_from_file, 0, 0, 1)
    ZEND_ARG_INFO(0, filename)
    ZEND_ARG_INFO(1, error)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gdk_pixbuf_new_from_file);


ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_pixbuf___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(gdk_pixbuf, __construct);


#endif	/* PHP_GDK_PIXBUF_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
