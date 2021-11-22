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

#ifndef PHP_CAIRO_RASTER_SOURCE_H
#define PHP_CAIRO_RASTER_SOURCE_H


#if CAIRO_VERSION >= 11200
#define PHP_CAIRO_RASTER_SOURCE_FE_11200()  \
    PHP_GTK_FE(cairo_pattern_create_raster_source,        arginfo_cairo_pattern_create_raster_source)  \
    PHP_GTK_FE(cairo_raster_source_pattern_set_callback_data,        arginfo_cairo_raster_source_pattern_set_callback_data)  \
    PHP_GTK_FE(cairo_raster_source_pattern_get_callback_data,        arginfo_cairo_raster_source_pattern_get_callback_data)  \
    PHP_GTK_FE(cairo_raster_source_pattern_set_acquire,        arginfo_cairo_raster_source_pattern_set_acquire)  \
    PHP_GTK_FE(cairo_raster_source_pattern_get_acquire,        arginfo_cairo_raster_source_pattern_get_acquire)  \
    PHP_GTK_FE(cairo_raster_source_pattern_set_snapshot,        arginfo_cairo_raster_source_pattern_set_snapshot)  \
    PHP_GTK_FE(cairo_raster_source_pattern_get_snapshot,        arginfo_cairo_raster_source_pattern_get_snapshot)  \
    PHP_GTK_FE(cairo_raster_source_pattern_set_copy,        arginfo_cairo_raster_source_pattern_set_copy)  \
    PHP_GTK_FE(cairo_raster_source_pattern_get_copy,        arginfo_cairo_raster_source_pattern_get_copy)  \
    PHP_GTK_FE(cairo_raster_source_pattern_set_finish,        arginfo_cairo_raster_source_pattern_set_finish)  \
    PHP_GTK_FE(cairo_raster_source_pattern_get_finish,        arginfo_cairo_raster_source_pattern_get_finish)  \

#else
#define PHP_CAIRO_RASTER_SOURCE_FE_11200()
#endif


#define PHP_CAIRO_RASTER_SOURCE_FE() \
    PHP_CAIRO_RASTER_SOURCE_FE_11200() \


#define PHP_CAIRO_RASTER_SOURCE_MINIT_FUNCTION(container_ce, parent_ce)

#define PHP_CAIRO_RASTER_SOURCE_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_RASTER_SOURCE_RSHUTDOWN_FUNCTION() {\
}





ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_raster_source___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_raster_source, __construct);

#if CAIRO_VERSION >= 11200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_cairo_pattern_create_raster_source, ZEND_RETURN_VALUE, 4, cairo_pattern_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, user_data)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, content, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, height, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_pattern_create_raster_source);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_raster_source_pattern_set_callback_data, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_raster_source_pattern_set_callback_data);
ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_raster_source_pattern_get_callback_data, 0, ZEND_RETURN_VALUE, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_raster_source_pattern_get_callback_data);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_raster_source_pattern_set_acquire, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_CALLABLE_INFO(ZEND_SEND_BY_VAL, acquire, 0)
    ZEND_ARG_CALLABLE_INFO(ZEND_SEND_BY_VAL, release, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_raster_source_pattern_set_acquire);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_raster_source_pattern_get_acquire, ZEND_RETURN_VALUE, 3, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_REF, acquire)
    ZEND_ARG_INFO(ZEND_SEND_BY_REF, release)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_raster_source_pattern_get_acquire);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_raster_source_pattern_set_snapshot, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, snapshot)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_raster_source_pattern_set_snapshot);
ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_raster_source_pattern_get_snapshot, 0, ZEND_RETURN_VALUE, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_raster_source_pattern_get_snapshot);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_raster_source_pattern_set_copy, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_CALLABLE_INFO(ZEND_SEND_BY_VAL, copy, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_raster_source_pattern_set_copy);
ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_raster_source_pattern_get_copy, 0, ZEND_RETURN_VALUE, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_raster_source_pattern_get_copy);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_cairo_raster_source_pattern_set_finish, ZEND_RETURN_VALUE, 2, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
    ZEND_ARG_CALLABLE_INFO(ZEND_SEND_BY_VAL, finish, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_raster_source_pattern_set_finish);
ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_raster_source_pattern_get_finish, 0, ZEND_RETURN_VALUE, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pattern, cairo_pattern_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_raster_source_pattern_get_finish);
#endif


#endif	/* PHP_CAIRO_RASTER_SOURCE_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
