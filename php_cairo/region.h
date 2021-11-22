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

#ifndef PHP_CAIRO_REGION_T_H
#define PHP_CAIRO_REGION_T_H


#define PHP_CAIRO_REGION_T(ptr)           ((php_cairo_region_t*)(ptr))
#define PHP_CAIRO_REGION_T_CLASS          php_cairo_region_t_class_entry
#define PHP_CAIRO_REGION_T_OFFSET         (sizeof(php_cairo_region_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_REGION_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_region_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_REGION_T(std)   PHP_CAIRO_REGION_T( ((void*)(std))-PHP_CAIRO_REGION_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_REGION_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_REGION_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_REGION_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_REGION_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_REGION_T(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)


#define PHP_CAIRO_REGION_T_PTR(intern)       (intern)->ptr

#define DECL_PHP_CAIRO_REGION_T(name) \
    cairo_region_t *name = php_##name ? PHP_CAIRO_REGION_T_PTR(php_##name) : NULL;




#if CAIRO_VERSION >= 11000
#define PHP_CAIRO_REGION_T_FE_11000()  \
    PHP_GTK_FE(cairo_region_create,        arginfo_cairo_region_create)  \
    PHP_GTK_FE(cairo_region_create_rectangle,        arginfo_cairo_region_create_rectangle)  \
    PHP_GTK_FE(cairo_region_create_rectangles,        arginfo_cairo_region_create_rectangles)  \
    PHP_GTK_FE(cairo_region_copy,        arginfo_cairo_region_copy)  \
    PHP_GTK_FE(cairo_region_reference,        arginfo_cairo_region_reference)  \
    PHP_GTK_FE(cairo_region_destroy,        arginfo_cairo_region_destroy)  \
    PHP_GTK_FE(cairo_region_status,        arginfo_cairo_region_status)  \
    PHP_GTK_FE(cairo_region_get_extents,        arginfo_cairo_region_get_extents)  \
    PHP_GTK_FE(cairo_region_num_rectangles,        arginfo_cairo_region_num_rectangles)  \
    PHP_GTK_FE(cairo_region_get_rectangle,        arginfo_cairo_region_get_rectangle)  \
    PHP_GTK_FE(cairo_region_is_empty,        arginfo_cairo_region_is_empty)  \
    PHP_GTK_FE(cairo_region_contains_point,        arginfo_cairo_region_contains_point)  \
    PHP_GTK_FE(cairo_region_contains_rectangle,        arginfo_cairo_region_contains_rectangle)  \
    PHP_GTK_FE(cairo_region_equal,        arginfo_cairo_region_equal)  \
    PHP_GTK_FE(cairo_region_translate,        arginfo_cairo_region_translate)  \
    PHP_GTK_FE(cairo_region_intersect,        arginfo_cairo_region_intersect)  \
    PHP_GTK_FE(cairo_region_intersect_rectangle,        arginfo_cairo_region_intersect_rectangle)  \
    PHP_GTK_FE(cairo_region_subtract,        arginfo_cairo_region_subtract)  \
    PHP_GTK_FE(cairo_region_subtract_rectangle,        arginfo_cairo_region_subtract_rectangle)  \
    PHP_GTK_FE(cairo_region_union,        arginfo_cairo_region_union)  \
    PHP_GTK_FE(cairo_region_union_rectangle,        arginfo_cairo_region_union_rectangle)  \
    PHP_GTK_FE(cairo_region_xor,        arginfo_cairo_region_xor)  \
    PHP_GTK_FE(cairo_region_xor_rectangle,        arginfo_cairo_region_xor_rectangle)  \

#else
#define PHP_CAIRO_REGION_T_FE_11000()
#endif


#define PHP_CAIRO_REGION_T_FE() \
    PHP_CAIRO_REGION_T_FE_11000() \


#define PHP_CAIRO_REGION_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_region_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_REGION_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_REGION_T_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_cairo_region_t_class_entry;


typedef struct _php_cairo_region_t php_cairo_region_t;
struct _php_cairo_region_t {
    cairo_region_t *ptr;

    zend_object std;
};

zend_class_entry*
php_cairo_region_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);



ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_region_t___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_region_t, __construct);

#if CAIRO_VERSION >= 11000
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_region_create, ZEND_RETURN_VALUE, 0, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_create);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_region_create_rectangle, ZEND_RETURN_VALUE, 1, cairo_region_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, rectangle, cairo_rectangle_int_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_create_rectangle);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_region_create_rectangles, ZEND_RETURN_VALUE, 1, cairo_region_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, rects, IS_ARRAY, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_create_rectangles);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_region_copy, ZEND_RETURN_VALUE, 1, cairo_region_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, original, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_copy);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_region_reference, ZEND_RETURN_VALUE, 1, cairo_region_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, region, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_reference);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_destroy, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, region, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_destroy);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_status, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, region, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_status);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_get_extents, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, region, cairo_region_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, extents, cairo_rectangle_int_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_get_extents);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_num_rectangles, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, region, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_num_rectangles);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_get_rectangle, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, region, cairo_region_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, nth, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, rectangle, cairo_rectangle_int_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_get_rectangle);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_is_empty, ZEND_RETURN_VALUE, 1, _IS_BOOL, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, region, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_is_empty);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_contains_point, ZEND_RETURN_VALUE, 3, _IS_BOOL, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, region, cairo_region_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_contains_point);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_contains_rectangle, ZEND_RETURN_VALUE, 2, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, region, cairo_region_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, rectangle, cairo_rectangle_int_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_contains_rectangle);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_equal, ZEND_RETURN_VALUE, 2, _IS_BOOL, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, a, cairo_region_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, b, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_equal);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_translate, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, region, cairo_region_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dx, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dy, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_translate);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_intersect, ZEND_RETURN_VALUE, 2, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, dst, cairo_region_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, other, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_intersect);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_intersect_rectangle, ZEND_RETURN_VALUE, 2, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, dst, cairo_region_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, rectangle, cairo_rectangle_int_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_intersect_rectangle);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_subtract, ZEND_RETURN_VALUE, 2, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, dst, cairo_region_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, other, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_subtract);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_subtract_rectangle, ZEND_RETURN_VALUE, 2, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, dst, cairo_region_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, rectangle, cairo_rectangle_int_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_subtract_rectangle);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_union, ZEND_RETURN_VALUE, 2, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, dst, cairo_region_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, other, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_union);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_union_rectangle, ZEND_RETURN_VALUE, 2, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, dst, cairo_region_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, rectangle, cairo_rectangle_int_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_union_rectangle);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_xor, ZEND_RETURN_VALUE, 2, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, dst, cairo_region_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, other, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_xor);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_region_xor_rectangle, ZEND_RETURN_VALUE, 2, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, dst, cairo_region_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, rectangle, cairo_rectangle_int_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_region_xor_rectangle);
#endif


#endif	/* PHP_CAIRO_REGION_T_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
