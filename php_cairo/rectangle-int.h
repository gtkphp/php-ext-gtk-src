/*
+----------------------------------------------------------------------+
| PHP Version 8                                                        |
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef PHP_CAIRO_RECTANGLE_INT_T_H
#define PHP_CAIRO_RECTANGLE_INT_T_H


#define PHP_CAIRO_RECTANGLE_INT_T(ptr)           ((php_cairo_rectangle_int_t*)(ptr))
#define PHP_CAIRO_RECTANGLE_INT_T_CLASS          php_cairo_rectangle_int_t_class_entry
#define PHP_CAIRO_RECTANGLE_INT_T_OFFSET         (sizeof(php_cairo_rectangle_int_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_RECTANGLE_INT_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_rectangle_int_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_RECTANGLE_INT_T(std)   PHP_CAIRO_RECTANGLE_INT_T( ((void*)(std))-PHP_CAIRO_RECTANGLE_INT_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_RECTANGLE_INT_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_RECTANGLE_INT_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_RECTANGLE_INT_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_RECTANGLE_INT_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_RECTANGLE_INT_T(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)




#define PHP_CAIRO_RECTANGLE_INT_T_COPY(src, dest) \
    ZVAL_GET_LONG(&src->x, (dest)->x) \
    ZVAL_GET_LONG(&src->y, (dest)->y) \
    ZVAL_GET_LONG(&src->width, (dest)->width) \
    ZVAL_GET_LONG(&src->height, (dest)->height) \


#define PHP_CAIRO_RECTANGLE_INT_T_SET(dest, src) \
    ZVAL_SET_LONG(&(dest)->x, (src)->x) \
    ZVAL_SET_LONG(&(dest)->y, (src)->y) \
    ZVAL_SET_LONG(&(dest)->width, (src)->width) \
    ZVAL_SET_LONG(&(dest)->height, (src)->height) \


#define PHP_CAIRO_RECTANGLE_INT_T_PTR(intern)       php_cairo_rectangle_int_t_get_ptr(intern)

#define DECL_PHP_CAIRO_RECTANGLE_INT_T(name) \
    cairo_rectangle_int_t __##name; \
    cairo_rectangle_int_t *name = &__##name; \
    PHP_CAIRO_RECTANGLE_INT_T_COPY(php_##name, name);



#define PHP_CAIRO_RECTANGLE_INT_T_FE() \


#define PHP_CAIRO_RECTANGLE_INT_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_rectangle_int_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_RECTANGLE_INT_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_RECTANGLE_INT_T_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_cairo_rectangle_int_t_class_entry;


typedef struct _php_cairo_rectangle_int_t php_cairo_rectangle_int_t;
struct _php_cairo_rectangle_int_t {
    zval x;// of zend_long
    zval y;// of zend_long
    zval width;// of zend_long
    zval height;// of zend_long

    zend_object std;
};

zend_class_entry*
php_cairo_rectangle_int_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);
php_cairo_rectangle_int_t*
php_cairo_rectangle_int_t_new();


ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_rectangle_int_t___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_rectangle_int_t, __construct);



#endif	/* PHP_CAIRO_RECTANGLE_INT_T_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
