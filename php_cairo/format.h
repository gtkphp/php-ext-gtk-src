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

#ifndef PHP_CAIRO_FORMAT_T_H
#define PHP_CAIRO_FORMAT_T_H

#if CAIRO_HAS_IMAGE_SURFACE

#if CAIRO_VERSION >= 10600
#define PHP_CAIRO_FORMAT_T_FE_10600() \
    PHP_GTK_FE(cairo_format_stride_for_width,       arginfo_cairo_format_stride_for_width)
#else
#define PHP_CAIRO_FORMAT_T_FE_10600()
#endif

#define PHP_CAIRO_FORMAT_T_FE() \
    PHP_CAIRO_FORMAT_T_FE_10600()

#define PHP_CAIRO_FORMAT_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_format_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_FORMAT_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_FORMAT_T_RSHUTDOWN_FUNCTION() {\
}

zend_class_entry*
php_cairo_format_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);


#if CAIRO_VERSION >= 10600
ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_format_stride_for_width, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, format)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_format_stride_for_width);
#endif

#else

#define PHP_CAIRO_FORMAT_T_FE()
#define PHP_CAIRO_FORMAT_T_MINIT_FUNCTION(container_ce, parent_ce)
#define PHP_CAIRO_FORMAT_T_MSHUTDOWN_FUNCTION()
#define PHP_CAIRO_FORMAT_T_RSHUTDOWN_FUNCTION()

#endif /* CAIRO_HAS_IMAGE_SURFACE */

#endif	/* PHP_CAIRO_FORMAT_T_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
