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

#ifndef PHP_GLIB_QUARK_H
#define PHP_GLIB_QUARK_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib.h>

#define PHP_GLIB_QUARK_FE() \
    PHP_FE(g_quark_from_string,                arginfo_g_quark_from_string) \
    PHP_FALIAS(g_quark_from_static_string,     g_quark_from_string, arginfo_g_quark_from_string) \
    PHP_FE(g_quark_to_string,                  arginfo_g_quark_to_string) \
    PHP_FE(g_quark_try_string,                 arginfo_g_quark_try_string) \
    PHP_FE(g_intern_string,                    arginfo_g_intern_string) \
    PHP_FALIAS(g_intern_static_string,         g_intern_string, arginfo_g_intern_string) \



#define PHP_GLIB_QUARK_MINIT_FUNCTION(container_ce, parent_ce)

#define PHP_GLIB_QUARK_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GLIB_QUARK_RSHUTDOWN_FUNCTION() {\
}

zend_long php_glib_quark_from_string(zend_string *string);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_quark_from_string, 0, 0, 1)
    ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_quark_from_string);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_quark_to_string, 0, 0, 1)
    ZEND_ARG_INFO(0, quark)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_quark_to_string);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_quark_try_string, 0, 0, 1)
    ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_quark_try_string);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_intern_string, 0, 0, 1)
    ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_intern_string);


#endif	/* PHP_GLIB_QUARK_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
