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

#include <glib.h>
#include "php_gtk.h"
#include "quark.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

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

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

/* {{{ proto GQuark g_quark_from_string(string string) */
PHP_FUNCTION(g_quark_from_string)
{
    zval *zstring = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zstring)
    ZEND_PARSE_PARAMETERS_END();

    zend_string *__string = Z_TYPE_P(zstring)==IS_STRING? zstring->value.str: NULL;
    zend_long __ret = (zend_long)g_quark_from_string(__string->val);

    if(__string && __string->val)
        RETURN_LONG(__ret);
}/* }}} */

/* {{{ proto string g_quark_to_string(GQuark quark) */
PHP_FUNCTION(g_quark_to_string)
{
    zval *zquark = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zquark)
    ZEND_PARSE_PARAMETERS_END();

    zend_long __quark = Z_TYPE_P(zquark)==IS_LONG? zquark->value.lval: 0;
    char *__ret = g_quark_to_string((GQuark)__quark);

    if(__ret)
        RETURN_STRING(__ret);
}/* }}} */

/* {{{ proto GQuark g_quark_try_string(string string) */
PHP_FUNCTION(g_quark_try_string)
{
    zval *zstring = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zstring)
    ZEND_PARSE_PARAMETERS_END();

    zend_string *__string = Z_TYPE_P(zstring)==IS_STRING? zstring->value.str: 0;
    GQuark __ret = g_quark_try_string(__string->val);

    RETURN_LONG(__ret);
}/* }}} */

/* {{{ proto string g_intern_string(string string) */
PHP_FUNCTION(g_intern_string)
{
    zval *zstring = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zstring)
    ZEND_PARSE_PARAMETERS_END();

    zend_string *__string = Z_TYPE_P(zstring)==IS_STRING? zstring->value.str: 0;
    char *__ret = g_intern_string(__string->val);

    RETURN_STRING(__ret);
}/* }}} */



#if 0
/* {{{ proto GError g_quark_new_literal(mixed domain, int code, string message) */
PHP_FUNCTION(g_quark_new_literal)
{
    zval *domain = NULL;
    zval *code = NULL;
    zval *message = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 3)
        Z_PARAM_ZVAL(domain)
        Z_PARAM_ZVAL(code)
        Z_PARAM_ZVAL(message)
    ZEND_PARSE_PARAMETERS_END();

    zend_long __domain = Z_TYPE_P(domain)==IS_LONG? domain->value.lval: 0;
    //php_glib_quark *__ret = php_glib_quark_new_literal(__list, data);


}/* }}} */

/* {{{ proto void g_quark_free(GError error) */
PHP_FUNCTION(g_quark_free)
{
    zval *error = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_ZVAL(error)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_quark *__error = ZVAL_IS_PHP_GLIB_ERROR(error)? ZVAL_GET_PHP_GLIB_ERROR(error): NULL;
    //php_glib_quark *__ret = php_glib_quark_free(__list, data);


}/* }}} */

/* {{{ proto GError g_quark_copy(GError error) */
PHP_FUNCTION(g_quark_copy)
{
    zval *error = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_ZVAL(error)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_quark *__error = ZVAL_IS_PHP_GLIB_ERROR(error)? ZVAL_GET_PHP_GLIB_ERROR(error): NULL;
    //php_glib_quark *__ret = php_glib_quark_copy(__list, data);


}/* }}} */

/* {{{ proto bool g_quark_matches(GError error, mixed domain, int code) */
PHP_FUNCTION(g_quark_matches)
{
    zval *error = NULL;
    zval *domain = NULL;
    zval *code = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 3)
        Z_PARAM_ZVAL(error)
        Z_PARAM_ZVAL(domain)
        Z_PARAM_ZVAL(code)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_quark *__error = ZVAL_IS_PHP_GLIB_ERROR(error)? ZVAL_GET_PHP_GLIB_ERROR(error): NULL;
    //php_glib_quark *__ret = php_glib_quark_matches(__list, data);

}/* }}} */

/* {{{ proto void g_set_error(GError err, mixed domain, int code, string format) */
PHP_FUNCTION(g_set_error)
{
    zval *err = NULL;
    zval *domain = NULL;
    zval *code = NULL;
    zval *format = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 4)
        Z_PARAM_ZVAL(err)
        Z_PARAM_ZVAL(domain)
        Z_PARAM_ZVAL(code)
        Z_PARAM_ZVAL(format)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_quark *__err = ZVAL_IS_PHP_GLIB_ERROR(err)? ZVAL_GET_PHP_GLIB_ERROR(err): NULL;
    //php_glib_quark *__ret = php_g_set_error(__list, data);

}/* }}} */

/* {{{ proto void g_set_error_literal(GError err, mixed domain, int code, string message) */
PHP_FUNCTION(g_set_error_literal)
{
    zval *err = NULL;
    zval *domain = NULL;
    zval *code = NULL;
    zval *message = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 4)
        Z_PARAM_ZVAL(err)
        Z_PARAM_ZVAL(domain)
        Z_PARAM_ZVAL(code)
        Z_PARAM_ZVAL(message)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_quark *__err = ZVAL_IS_PHP_GLIB_ERROR(err)? ZVAL_GET_PHP_GLIB_ERROR(err): NULL;
    //php_glib_quark *__ret = php_g_set_error_literal(__list, data);

}/* }}} */

/* {{{ proto void g_propagate_error(GError dest, GError src) */
PHP_FUNCTION(g_propagate_error)
{
    zval *zdest = NULL;
    zval *zsrc = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 2)
        Z_PARAM_ZVAL(zdest)
        Z_PARAM_ZVAL(zsrc)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_quark *__dest = ZVAL_IS_PHP_GLIB_ERROR(zdest)? ZVAL_GET_PHP_GLIB_ERROR(zdest): NULL;
    //php_glib_quark *__ret = php_g_propagate_error(__list, data);

}/* }}} */

/* {{{ proto void g_clear_error(GError err) */
PHP_FUNCTION(g_clear_error)
{
    zval *zerr = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_ZVAL(zerr)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_quark *__err = ZVAL_IS_PHP_GLIB_ERROR(zerr)? ZVAL_GET_PHP_GLIB_ERROR(zerr): NULL;
    //php_glib_quark *__ret = php_g_clear_error(__list, data);

}/* }}} */

/* {{{ proto void g_prefix_error(GError err, string format) */
PHP_FUNCTION(g_prefix_error)
{
    zval *zerr = NULL;
    zval *zformat = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 2)
        Z_PARAM_ZVAL(zerr)
        Z_PARAM_ZVAL(zformat)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_quark *__err = ZVAL_IS_PHP_GLIB_ERROR(zerr)? ZVAL_GET_PHP_GLIB_ERROR(zerr): NULL;
    //php_glib_quark *__ret = php_g_prefix_error(__err, format, ...);

}/* }}} */

/* {{{ proto void g_propagate_prefixed_error(GError dest, GError src, string format) */
PHP_FUNCTION(g_propagate_prefixed_error)
{
    zval *zdest = NULL;
    zval *zsrc = NULL;
    zval *zformat = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 3)
        Z_PARAM_ZVAL(zdest)
        Z_PARAM_ZVAL(zsrc)
        Z_PARAM_ZVAL(zformat)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_quark *__dest = ZVAL_IS_PHP_GLIB_ERROR(zdest)? ZVAL_GET_PHP_GLIB_ERROR(zdest): NULL;
    php_glib_quark *__src  = ZVAL_IS_PHP_GLIB_ERROR(zsrc)? ZVAL_GET_PHP_GLIB_ERROR(zsrc): NULL;
    zend_string    *__format = Z_TYPE_P(zformat)==IS_STRING? zformat->value.str: NULL;
    //php_glib_quark *__ret = php_g_propagate_prefixed_error(__dest, __src, __format);

}/* }}} */

#endif

