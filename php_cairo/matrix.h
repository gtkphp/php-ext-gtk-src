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

#ifndef PHP_CAIRO_MATRIX_T_H
#define PHP_CAIRO_MATRIX_T_H


#define PHP_CAIRO_MATRIX_T(ptr)           ((php_cairo_matrix_t*)(ptr))
#define PHP_CAIRO_MATRIX_T_CLASS          php_cairo_matrix_t_class_entry
#define PHP_CAIRO_MATRIX_T_OFFSET         (sizeof(php_cairo_matrix_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_MATRIX_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_matrix_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_MATRIX_T(std)   PHP_CAIRO_MATRIX_T( ((void*)(std))-PHP_CAIRO_MATRIX_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_MATRIX_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_MATRIX_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_MATRIX_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_MATRIX_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_MATRIX_T(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)


//(dest)->xx = zval_get_double(&src->xx);
#define PHP_CAIRO_MATRIX_T_COPY(src, dest) \
    (dest)->xx = zval_get_double(&src->xx); \
    (dest)->yx = zval_get_double(&src->yx); \
    (dest)->xy = zval_get_double(&src->xy); \
    (dest)->yy = zval_get_double(&src->yy); \
    (dest)->x0 = zval_get_double(&src->x0); \
    (dest)->y0 = zval_get_double(&src->y0);

#define PHP_CAIRO_MATRIX_T_SET(dest, src) \
    ZVAL_SET_DOUBLE(&(dest)->xx, (src)->xx) \
    ZVAL_SET_DOUBLE(&(dest)->yx, (src)->yx) \
    ZVAL_SET_DOUBLE(&(dest)->xy, (src)->xy) \
    ZVAL_SET_DOUBLE(&(dest)->yy, (src)->yy) \
    ZVAL_SET_DOUBLE(&(dest)->x0, (src)->x0) \
    ZVAL_SET_DOUBLE(&(dest)->y0, (src)->y0)



#define PHP_CAIRO_MATRIX_T_PTR(intern)       php_cairo_matrix_t_get_ptr(intern)

#define DECL_PHP_CAIRO_MATRIX_T(name) \
    cairo_matrix_t __##name; \
    cairo_matrix_t *name = &__##name; \
    PHP_CAIRO_MATRIX_T_COPY(php_##name, name);




#define PHP_CAIRO_MATRIX_T_FE() \
    PHP_GTK_FE(cairo_matrix_init,               arginfo_cairo_matrix_init) \
    PHP_GTK_FE(cairo_matrix_init_identity,      arginfo_cairo_matrix_init_identity) \
    PHP_GTK_FE(cairo_matrix_init_translate,     arginfo_cairo_matrix_init_translate) \
    PHP_GTK_FE(cairo_matrix_init_scale,         arginfo_cairo_matrix_init_scale) \
    PHP_GTK_FE(cairo_matrix_init_rotate,        arginfo_cairo_matrix_init_rotate) \
    PHP_GTK_FE(cairo_matrix_translate,          arginfo_cairo_matrix_translate) \
    PHP_GTK_FE(cairo_matrix_scale,              arginfo_cairo_matrix_scale) \
    PHP_GTK_FE(cairo_matrix_rotate,             arginfo_cairo_matrix_rotate) \
    PHP_GTK_FE(cairo_matrix_invert,             arginfo_cairo_matrix_invert) \
    PHP_GTK_FE(cairo_matrix_multiply,           arginfo_cairo_matrix_multiply) \
    PHP_GTK_FE(cairo_matrix_transform_distance, arginfo_cairo_matrix_transform_distance) \
    PHP_GTK_FE(cairo_matrix_transform_point,    arginfo_cairo_matrix_transform_point) \

#define PHP_CAIRO_MATRIX_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_matrix_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_MATRIX_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_MATRIX_T_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_cairo_matrix_t_class_entry;


typedef struct _php_cairo_matrix_t php_cairo_matrix_t;
struct _php_cairo_matrix_t {
    zval xx;// of double
    zval yx;// of double
    zval xy;// of double
    zval yy;// of double
    zval x0;// of double
    zval y0;// of double

    zend_object std;
};

zend_class_entry*
php_cairo_matrix_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);

php_cairo_matrix_t *
php_cairo_matrix_t_new();

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_t___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_matrix_t, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_init, 0, ZEND_SEND_BY_VAL, 7)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, xx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, yx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, xy, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, yy, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x0, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y0, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_init);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_init_identity, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_init_identity);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_init_translate, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, tx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, ty, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_init_translate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_init_scale, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, sx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, sy, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_init_scale);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_init_rotate, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, radians, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_init_rotate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_translate, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, tx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, ty, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_translate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_scale, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, sx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, sy, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_scale);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_rotate, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, radians, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_rotate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_invert, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_invert);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_multiply, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, result, cairo_matrix_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, a, cairo_matrix_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, b, cairo_matrix_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_multiply);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_transform_distance, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, dx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, dy, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_transform_distance);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_transform_point, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, matrix, cairo_matrix_t, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, x, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_transform_point);


#endif	/* PHP_CAIRO_MATRIX_T_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
