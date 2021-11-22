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

#include "php_gtk.h"
#include "php_cairo/operator.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;



/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_operator_t_class_init */
zend_class_entry*
php_cairo_operator_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {

    zend_register_long_constant("CAIRO_OPERATOR_CLEAR", sizeof("CAIRO_OPERATOR_CLEAR")-1,
        CAIRO_OPERATOR_CLEAR, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_SOURCE", sizeof("CAIRO_OPERATOR_SOURCE")-1,
        CAIRO_OPERATOR_SOURCE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_OVER", sizeof("CAIRO_OPERATOR_OVER")-1,
        CAIRO_OPERATOR_OVER, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_IN", sizeof("CAIRO_OPERATOR_IN")-1,
        CAIRO_OPERATOR_IN, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_OUT", sizeof("CAIRO_OPERATOR_OUT")-1,
        CAIRO_OPERATOR_OUT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_ATOP", sizeof("CAIRO_OPERATOR_ATOP")-1,
        CAIRO_OPERATOR_ATOP, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_DEST", sizeof("CAIRO_OPERATOR_DEST")-1,
        CAIRO_OPERATOR_DEST, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_DEST_OVER", sizeof("CAIRO_OPERATOR_DEST_OVER")-1,
        CAIRO_OPERATOR_DEST_OVER, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_DEST_IN", sizeof("CAIRO_OPERATOR_DEST_IN")-1,
        CAIRO_OPERATOR_DEST_IN, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_DEST_OUT", sizeof("CAIRO_OPERATOR_DEST_OUT")-1,
        CAIRO_OPERATOR_DEST_OUT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_DEST_ATOP", sizeof("CAIRO_OPERATOR_DEST_ATOP")-1,
        CAIRO_OPERATOR_DEST_ATOP, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_XOR", sizeof("CAIRO_OPERATOR_XOR")-1,
        CAIRO_OPERATOR_XOR, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_ADD", sizeof("CAIRO_OPERATOR_ADD")-1,
        CAIRO_OPERATOR_ADD, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_SATURATE", sizeof("CAIRO_OPERATOR_SATURATE")-1,
        CAIRO_OPERATOR_SATURATE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
#if CAIRO_VERSION >= 11000
    zend_register_long_constant("CAIRO_OPERATOR_MULTIPLY", sizeof("CAIRO_OPERATOR_MULTIPLY")-1,
        CAIRO_OPERATOR_MULTIPLY, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_SCREEN", sizeof("CAIRO_OPERATOR_SCREEN")-1,
        CAIRO_OPERATOR_SCREEN, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_OVERLAY", sizeof("CAIRO_OPERATOR_OVERLAY")-1,
        CAIRO_OPERATOR_OVERLAY, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_DARKEN", sizeof("CAIRO_OPERATOR_DARKEN")-1,
        CAIRO_OPERATOR_DARKEN, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_LIGHTEN", sizeof("CAIRO_OPERATOR_LIGHTEN")-1,
        CAIRO_OPERATOR_LIGHTEN, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_COLOR_DODGE", sizeof("CAIRO_OPERATOR_COLOR_DODGE")-1,
        CAIRO_OPERATOR_COLOR_DODGE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_COLOR_BURN", sizeof("CAIRO_OPERATOR_COLOR_BURN")-1,
        CAIRO_OPERATOR_COLOR_BURN, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_HARD_LIGHT", sizeof("CAIRO_OPERATOR_HARD_LIGHT")-1,
        CAIRO_OPERATOR_HARD_LIGHT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_SOFT_LIGHT", sizeof("CAIRO_OPERATOR_SOFT_LIGHT")-1,
        CAIRO_OPERATOR_SOFT_LIGHT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_DIFFERENCE", sizeof("CAIRO_OPERATOR_DIFFERENCE")-1,
        CAIRO_OPERATOR_DIFFERENCE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_EXCLUSION", sizeof("CAIRO_OPERATOR_EXCLUSION")-1,
        CAIRO_OPERATOR_EXCLUSION, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_HSL_HUE", sizeof("CAIRO_OPERATOR_HSL_HUE")-1,
        CAIRO_OPERATOR_HSL_HUE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_HSL_SATURATION", sizeof("CAIRO_OPERATOR_HSL_SATURATION")-1,
        CAIRO_OPERATOR_HSL_SATURATION, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_HSL_COLOR", sizeof("CAIRO_OPERATOR_HSL_COLOR")-1,
        CAIRO_OPERATOR_HSL_COLOR, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_OPERATOR_HSL_LUMINOSITY", sizeof("CAIRO_OPERATOR_HSL_LUMINOSITY")-1,
        CAIRO_OPERATOR_HSL_LUMINOSITY, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
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


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
