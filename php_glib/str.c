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
  | Author: Gnome\Glib                                                   |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif



// #ifdef HAVE_GTK

#include <php.h>
#include <php_ini.h>
#include <zend_interfaces.h>
#include <ext/standard/info.h>

#include <glib.h>
#include "php_gtk.h"

#include "str.h"

PHP_FUNCTION(g_str_equal)
{
    zend_string *v1;
    zend_string *v2;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(v1);
        Z_PARAM_STR(v2);
    ZEND_PARSE_PARAMETERS_END();
    gboolean equal = g_str_equal(v1->val, v2->val);

    //RETURN_BOOL(equal);
    RETURN_BOOL(equal);

}
PHP_FUNCTION(g_str_hash)
{
    zend_string *v;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(v);
    ZEND_PARSE_PARAMETERS_END();

    guint hash = g_str_hash(v->val);

    RETURN_LONG(hash);
}

// #endif
