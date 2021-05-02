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

#ifndef PHP_CAIRO_STATUS_T_H
#define PHP_CAIRO_STATUS_T_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#define PHP_CAIRO_STATUS_T_FE() \
    PHP_GTK_FE(cairo_status_to_string,         arginfo_cairo_status_to_string) \
    PHP_GTK_FE(cairo_debug_reset_static_data,  arginfo_cairo_debug_reset_static_data) \


#define PHP_CAIRO_STATUS_T_MINIT_FUNCTION(container_ce, parent_ce) \
    php_cairo_status_t_class_init(container_ce, parent_ce)

#define PHP_CAIRO_STATUS_T_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_STATUS_T_RSHUTDOWN_FUNCTION() {\
}


zend_class_entry *php_cairo_status_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_status_to_string, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, status)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_status_to_string);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_debug_reset_static_data, 0, ZEND_SEND_BY_VAL, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(cairo_debug_reset_static_data);



#endif	/* PHP_CAIRO_STATUS_T_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
