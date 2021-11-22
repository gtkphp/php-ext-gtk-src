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
#include "php_cairo/device-type.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;



/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_device_type_t_class_init */
zend_class_entry*
php_cairo_device_type_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {

    zend_register_long_constant("CAIRO_DEVICE_TYPE_DRM", sizeof("CAIRO_DEVICE_TYPE_DRM")-1,
        CAIRO_DEVICE_TYPE_DRM, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_DEVICE_TYPE_GL", sizeof("CAIRO_DEVICE_TYPE_GL")-1,
        CAIRO_DEVICE_TYPE_GL, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_DEVICE_TYPE_SCRIPT", sizeof("CAIRO_DEVICE_TYPE_SCRIPT")-1,
        CAIRO_DEVICE_TYPE_SCRIPT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_DEVICE_TYPE_XCB", sizeof("CAIRO_DEVICE_TYPE_XCB")-1,
        CAIRO_DEVICE_TYPE_XCB, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_DEVICE_TYPE_XLIB", sizeof("CAIRO_DEVICE_TYPE_XLIB")-1,
        CAIRO_DEVICE_TYPE_XLIB, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_DEVICE_TYPE_XML", sizeof("CAIRO_DEVICE_TYPE_XML")-1,
        CAIRO_DEVICE_TYPE_XML, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_DEVICE_TYPE_COGL", sizeof("CAIRO_DEVICE_TYPE_COGL")-1,
        CAIRO_DEVICE_TYPE_COGL, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_DEVICE_TYPE_WIN32", sizeof("CAIRO_DEVICE_TYPE_WIN32")-1,
        CAIRO_DEVICE_TYPE_WIN32, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_DEVICE_TYPE_INVALID", sizeof("CAIRO_DEVICE_TYPE_INVALID")-1,
        CAIRO_DEVICE_TYPE_INVALID, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);

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
