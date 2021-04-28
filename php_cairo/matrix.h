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

#ifndef PHP_CAIRO_MATRIX_H
#define PHP_CAIRO_MATRIX_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif



#define PHP_CAIRO_MATRIX(ptr)           ((php_cairo_matrix*)(ptr))
#define PHP_CAIRO_MATRIX_CLASS          php_cairo_matrix_class_entry
#define PHP_CAIRO_MATRIX_OFFSET         (sizeof(php_cairo_matrix) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_MATRIX(obj)   ((obj)!=NULL && obj->ce == php_cairo_matrix_class_entry)
#define ZOBJ_TO_PHP_CAIRO_MATRIX(std)   PHP_CAIRO_MATRIX( ((void*)(std))-PHP_CAIRO_MATRIX_OFFSET )

#define ZVAL_IS_PHP_CAIRO_MATRIX(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_MATRIX((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_MATRIX(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_MATRIX((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_MATRIX(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)


#define PHP_CAIRO_MATRIX_FE() \
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


#define PHP_CAIRO_MATRIX_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_matrix_class_init(container_ce, parent_ce)

#define PHP_CAIRO_MATRIX_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_MATRIX_RSHUTDOWN_FUNCTION() {\
}

typedef struct _php_cairo_matrix php_cairo_matrix;
struct _php_cairo_matrix {
    cairo_matrix_t *ptr;

    zend_object std;
};

void php_cairo_matrix_init(php_cairo_matrix *matrix, double xx, double yx, double xy, double yy, double x0, double y0);
void php_cairo_matrix_init_identity(php_cairo_matrix *matrix);
void php_cairo_matrix_init_translate(php_cairo_matrix *matrix, double tx, double ty);
void php_cairo_matrix_init_scale(php_cairo_matrix *matrix, double sx, double sy);
void php_cairo_matrix_init_rotate(php_cairo_matrix *matrix, double radians);
void php_cairo_matrixranslate(php_cairo_matrix *matrix, double tx, double ty);
void php_cairo_matrix_scale(php_cairo_matrix *matrix, double sx, double sy);
void php_cairo_matrix_rotate(php_cairo_matrix *matrix, double radians);
php_cairo_matrix *php_cairo_matrix_invert(php_cairo_matrix *matrix);
void php_cairo_matrix_multiply(php_cairo_matrix *result, php_cairo_matrix *a, php_cairo_matrix *b);
void php_cairo_matrixransform_distance(php_cairo_matrix *matrix, double dx, double dy);
void php_cairo_matrixransform_point(php_cairo_matrix *matrix, double x, double y);

zend_class_entry *php_cairo_matrix_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_matrix, __construct);


ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_init, 0, 0, 7)
    ZEND_ARG_OBJ_INFO(0, matrix, cairo_matrix_t, 0)
    ZEND_ARG_TYPE_INFO(0, xx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, yx, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, xy, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, yy, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, x0, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, y0, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_init);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_init_identity, 0, 0, 1)
    ZEND_ARG_INFO(0, matrix)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_init_identity);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_init_translate, 0, 0, 3)
    ZEND_ARG_INFO(0, matrix)
    ZEND_ARG_INFO(0, tx)
    ZEND_ARG_INFO(0, ty)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_init_translate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_init_scale, 0, 0, 3)
    ZEND_ARG_INFO(0, matrix)
    ZEND_ARG_INFO(0, sx)
    ZEND_ARG_INFO(0, sy)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_init_scale);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_init_rotate, 0, 0, 2)
    ZEND_ARG_INFO(0, matrix)
    ZEND_ARG_INFO(0, radians)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_init_rotate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_translate, 0, 0, 3)
    ZEND_ARG_INFO(0, matrix)
    ZEND_ARG_INFO(0, tx)
    ZEND_ARG_INFO(0, ty)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_translate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_scale, 0, 0, 3)
    ZEND_ARG_INFO(0, matrix)
    ZEND_ARG_INFO(0, sx)
    ZEND_ARG_INFO(0, sy)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_scale);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_rotate, 0, 0, 2)
    ZEND_ARG_INFO(0, matrix)
    ZEND_ARG_INFO(0, radians)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_rotate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_invert, 0, 0, 1)
    ZEND_ARG_INFO(0, matrix)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_invert);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_multiply, 0, 0, 3)
    ZEND_ARG_INFO(0, result)
    ZEND_ARG_INFO(0, a)
    ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_multiply);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_transform_distance, 0, 0, 3)
    ZEND_ARG_INFO(0, matrix)
    ZEND_ARG_INFO(0, dx)
    ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_transform_distance);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_matrix_transform_point, 0, 0, 3)
    ZEND_ARG_INFO(0, matrix)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_matrix_transform_point);


#endif	/* PHP_CAIRO_MATRIX_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
