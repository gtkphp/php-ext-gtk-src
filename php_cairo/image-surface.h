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

#ifndef PHP_CAIRO_IMAGE_SURFACE_T_H
#define PHP_CAIRO_IMAGE_SURFACE_T_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "surface.h"

#define IS_IMPLEMENTED 0

#define PHP_CAIRO_IMAGE_SURFACE_T(ptr)           ((php_cairo_image_surface_t*)(ptr))
#define PHP_CAIRO_IMAGE_SURFACE_T_CLASS          php_cairo_image_surface_t_class_entry
#define PHP_CAIRO_IMAGE_SURFACE_T_OFFSET         (sizeof(php_cairo_image_surface_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_IMAGE_SURFACE_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_surface_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_IMAGE_SURFACE_T(std)   PHP_CAIRO_IMAGE_SURFACE_T( ((void*)(std))-PHP_CAIRO_IMAGE_SURFACE_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_IMAGE_SURFACE_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_IMAGE_SURFACE_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_IMAGE_SURFACE_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_IMAGE_SURFACE_T((val)->value.obj))

#define ZVAL_SET_PHP_CAIRO_IMAGE_SURFACE_T(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

#if IS_IMPLEMENTED

#define PHP_CAIRO_IMAGE_SURFACE_T_FE() \
    PHP_FE(cairo_format_stride_for_width,       arginfo_cairo_format_stride_for_width) \
    PHP_FE(cairo_image_surface_create,          arginfo_cairo_image_surface_create) \
    PHP_FE(cairo_image_surface_create_for_data, arginfo_cairo_image_surface_create_for_data) \
    PHP_FE(cairo_image_surface_get_data,        arginfo_cairo_image_surface_get_data) \
    PHP_FE(cairo_image_surface_get_format,      arginfo_cairo_image_surface_get_format) \
    PHP_FE(cairo_image_surface_get_width,       arginfo_cairo_image_surface_get_width) \
    PHP_FE(cairo_image_surface_get_height,      arginfo_cairo_image_surface_get_height) \
    PHP_FE(cairo_image_surface_get_stride,      arginfo_cairo_image_surface_get_stride) \

#else

#define PHP_CAIRO_IMAGE_SURFACE_T_FE() \
    PHP_FE(cairo_image_surface_create,          arginfo_cairo_image_surface_create) \
    PHP_FE(cairo_image_surface_get_format,      arginfo_cairo_image_surface_get_format) \
    PHP_FE(cairo_image_surface_get_width,       arginfo_cairo_image_surface_get_width) \
    PHP_FE(cairo_image_surface_get_height,      arginfo_cairo_image_surface_get_height) \
    PHP_FE(cairo_image_surface_get_stride,      arginfo_cairo_image_surface_get_stride) \

#endif

#define PHP_CAIRO_IMAGE_SURFACE_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_image_surface_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_IMAGE_SURFACE_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_IMAGE_SURFACE_T_RSHUTDOWN_FUNCTION() {\
}

typedef php_cairo_surface_t php_cairo_image_surface_t;

zend_class_entry *php_cairo_image_surface_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);


#if IS_IMPLEMENTED
ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_format_stride_for_width, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, format)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, width)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_format_stride_for_width);
#endif

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_image_surface_create, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, format)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, width)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, height)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_create);

#if IS_IMPLEMENTED
ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_image_surface_create_for_data, 0, ZEND_SEND_BY_VAL, 5)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, data)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, format)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, width)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, height)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, stride)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_create_for_data);


ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_image_surface_get_data, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_get_data);
#endif

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_image_surface_get_format, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_get_format);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_image_surface_get_width, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_get_width);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_image_surface_get_height, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_get_height);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_image_surface_get_stride, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, surface)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_image_surface_get_stride);



#endif	/* PHP_CAIRO_IMAGE_SURFACE_T_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
