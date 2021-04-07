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

#ifndef PHP_GTK_MAIN_H
#define PHP_GTK_MAIN_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gtk/gtk.h>


#define PHP_GTK_MAIN_FE() \
    PHP_FE(gtk_init,      arginfo_gtk_init) \
    PHP_FE(gtk_main,      arginfo_gtk_main) \
    PHP_FE(gtk_main_quit, arginfo_gtk_main_quit)

#define PHP_GTK_MAIN_MINIT_FUNCTION(container_ce, parent_ce)

#define PHP_GTK_MAIN_MSHUTDOWN_FUNCTION()

#define PHP_GTK_MAIN_RSHUTDOWN_FUNCTION()



void php_gtk_init(int *argc, char **argv[]);
void php_gtk_main();
void php_gtk_main_quit();



ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_init, 0, 0, 0)
    ZEND_ARG_INFO(0, argc)
    ZEND_ARG_INFO(0, argv)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_init);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_main, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_main);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_main_quit, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_main_quit);


#endif	/* PHP_GTK_MAIN_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
