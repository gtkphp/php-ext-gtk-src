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
#include "php_cairo/path-data-type.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;



/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_path_data_type_t_class_init */
zend_class_entry*
php_cairo_path_data_type_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {

    zend_register_long_constant("CAIRO_PATH_MOVE_TO", sizeof("CAIRO_PATH_MOVE_TO")-1,
        CAIRO_PATH_MOVE_TO, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_PATH_LINE_TO", sizeof("CAIRO_PATH_LINE_TO")-1,
        CAIRO_PATH_LINE_TO, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_PATH_CURVE_TO", sizeof("CAIRO_PATH_CURVE_TO")-1,
        CAIRO_PATH_CURVE_TO, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_PATH_CLOSE_PATH", sizeof("CAIRO_PATH_CLOSE_PATH")-1,
        CAIRO_PATH_CLOSE_PATH, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);

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
