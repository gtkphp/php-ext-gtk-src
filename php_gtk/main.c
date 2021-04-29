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

#include <gtk/gtk.h>
#include "php_gtk.h"

#include "main.h"


/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
| PHP_MINIT                                                            |
+----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/


/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
void
php_gtk_init(int *argc, char **argv[]) {

}

void
php_gtk_main() {

}

void
php_gtk_main_quit() {

}

/*----------------------------------------------------------------------+
| PHP_METHOD                                                           |
+----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/

/* {{{ proto void gtk_init(...) */
PHP_FUNCTION(gtk_init)
{
    zval *zargc = NULL;
    zval *zargv = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 2)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(zargc)
        Z_PARAM_ZVAL(zargv)
    ZEND_PARSE_PARAMETERS_END();

    if(NULL!=zargc && !ZVAL_IS_NULL(zargc) && Z_TYPE_P(zargc)==IS_LONG
    && NULL!=zargv && !ZVAL_IS_NULL(zargv) && Z_TYPE_P(zargv)==IS_ARRAY ) {
        if (zargc->value.lval>0) {
            // TODO
        }
    }

    char **argv = (char **)g_new(char**, 1);
    argv[0] = g_strdup("");
    int    argc = 0;
    gtk_init(&argc, &argv);
    g_free(argv[0]);
    g_free(argv);


}/* }}} */

/* {{{ proto void gtk_main() */
PHP_FUNCTION(gtk_main)
{
    gtk_main();

}/* }}} */

/* {{{ proto void gtk_main_quit() */
PHP_FUNCTION(gtk_main_quit)
{
    gtk_main_quit();

}/* }}} */
