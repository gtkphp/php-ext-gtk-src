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

#include <php.h>
#include <php_ini.h>
#include <zend_interfaces.h>
#include <ext/standard/info.h>

#include <cairo/cairo.h>

#if CAIRO_HAS_IMAGE_SURFACE

#include "php_gtk.h"
#include "php_cairo/format.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;



/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_format_t_class_init */
zend_class_entry*
php_cairo_format_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {

    zend_register_long_constant("CAIRO_FORMAT_INVALID", sizeof("CAIRO_FORMAT_INVALID")-1,
        CAIRO_FORMAT_INVALID, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_FORMAT_ARGB32", sizeof("CAIRO_FORMAT_ARGB32")-1,
        CAIRO_FORMAT_ARGB32, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_FORMAT_RGB24", sizeof("CAIRO_FORMAT_RGB24")-1,
        CAIRO_FORMAT_RGB24, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_FORMAT_A8", sizeof("CAIRO_FORMAT_A8")-1,
        CAIRO_FORMAT_A8, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_FORMAT_A1", sizeof("CAIRO_FORMAT_A1")-1,
        CAIRO_FORMAT_A1, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
#if CAIRO_VERSION >= 10200
    zend_register_long_constant("CAIRO_FORMAT_RGB16_565", sizeof("CAIRO_FORMAT_RGB16_565")-1,
        CAIRO_FORMAT_RGB16_565, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
#endif
#if CAIRO_VERSION >= 11200
    zend_register_long_constant("CAIRO_FORMAT_RGB30", sizeof("CAIRO_FORMAT_RGB30")-1,
        CAIRO_FORMAT_RGB30, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
#endif

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

#if CAIRO_VERSION >= 10600
/* {{{ proto int cairo_format_stride_for_width(int format, int width)
   This function provides a stride value that will respect all alignment... */
PHP_FUNCTION(cairo_format_stride_for_width)
{
    zend_long zformat;
    zend_long width;

    ZEND_PARSE_PARAMETERS_START(2, 2);
        Z_PARAM_LONG(zformat);
        Z_PARAM_LONG(width);
    ZEND_PARSE_PARAMETERS_END();

    cairo_format_t format = zformat;

    int ret = cairo_format_stride_for_width(format, width);

    RETURN_LONG(ret);
}/* }}} */
#endif

#endif /* CAIRO_HAS_IMAGE_SURFACE */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
