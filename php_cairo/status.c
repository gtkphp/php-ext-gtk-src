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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <php_ini.h>
#include <zend_interfaces.h>
#include <ext/standard/info.h>

#include <cairo/cairo.h>
#include "php_gtk.h"

#include "status.h"

extern zend_module_entry gtk_module_entry;

/*----------------------------------------------------------------------+
| Internal                                                             |
+----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

/*{{{ php_cairo_t_class_init */
zend_class_entry*
php_cairo_status_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    zend_register_long_constant("CAIRO_STATUS_SUCCESS", sizeof("CAIRO_STATUS_SUCCESS")-1,
        CAIRO_STATUS_SUCCESS, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_NO_MEMORY", sizeof("CAIRO_STATUS_NO_MEMORY")-1,
        CAIRO_STATUS_NO_MEMORY, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);

    return NULL;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

/* {{{ proto cairo_t cairo_reference(cairo_t cr) */
PHP_FUNCTION(cairo_status_to_string)
{
    zend_long status;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(status)
    ZEND_PARSE_PARAMETERS_END();

    const char *msg = cairo_status_to_string(status);

    RETURN_STRING(msg);
}/* }}} */

/* {{{ proto void cairo_destroy(cairo_t cr) */
PHP_FUNCTION(cairo_debug_reset_static_data)
{
    cairo_debug_reset_static_data();
}/* }}} */

