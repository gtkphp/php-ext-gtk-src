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
  | Author:                                                              |
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

#include "php_gtk.h"

#include "php_glib/glib.h"
#include "php_g/g-hash-table.h"

HashTable classes;



/* If you declare any globals in php_gtk.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(gtk)
*/

/* True global resources - no need for thread safety here */
static int le_gtk;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("gtk.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_gtk_globals, gtk_globals)
    STD_PHP_INI_ENTRY("gtk.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_gtk_globals, gtk_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_gtk_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_gtk_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "gtk", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_gtk_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_gtk_init_globals(zend_gtk_globals *gtk_globals)
{
	gtk_globals->global_value = 0;
	gtk_globals->global_string = NULL;
}
*/
/* }}} */


extern zend_object_handlers php_glib_object_handlers;


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(gtk)
{
    //zm_startup_gtk(int type, int module_number)

	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	zend_class_entry ce;
	zend_class_entry *g_hash_table_ce;
	
	zend_object_handlers *handlers= php_glib_object_get_handlers();

	zend_hash_init(&classes, 0, NULL, NULL, 1);

	g_hash_table_ce = php_g_hash_table_class_init(&ce);

	return SUCCESS;
}
/* }}} */



/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(gtk)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(gtk)
{
#if defined(COMPILE_DL_GTK) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(gtk)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(gtk)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "gtk support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/*----------------------------------------------------------------------+
 | Vendor\ExtName\g_str_hash                                         |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_str_hash, 0, 0, 0)
	ZEND_ARG_INFO(0, v)
ZEND_END_ARG_INFO()

PHP_FUNCTION(g_str_hash)
{
    zend_string *v;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(v);
    ZEND_PARSE_PARAMETERS_END();

    guint hash = g_str_hash(v->val);

    RETURN_LONG(hash);
}

/*----------------------------------------------------------------------+
 | Vendor\ExtName\g_str_equal                                           |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_str_equal, 0, 0, 0)
	ZEND_ARG_INFO(0, v1)
	ZEND_ARG_INFO(0, v2)
ZEND_END_ARG_INFO()
//gboolean g_str_equal (gconstpointer v1, gconstpointer v2);
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


/*----------------------------------------------------------------------+
 | Vendor\ExtName\g_hash_table_new                                      |
 +----------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_hash_table_new, 0, 0, 0)
	ZEND_ARG_INFO(0, hash_func)
	ZEND_ARG_INFO(0, key_equal_func)
ZEND_END_ARG_INFO()

PHP_FUNCTION(g_hash_table_new)
{
	zval *hash_func = NULL;
	zval *key_equal_func = NULL;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "|zz", &hash_func, &key_equal_func) == FAILURE) {
		return;
	}
	php_g_hash_table *intern = php_g_hash_table_new(hash_func, key_equal_func);
	
	RETURN_OBJ(&intern->parent_instance.std);
}

/*----------------------------------------------------------------------+
 | Vendor\ExtName\g_hash_table_add                                      |
 +----------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_hash_table_add, 0, 0, 2)
	ZEND_ARG_INFO(0, hash_table)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

PHP_FUNCTION(g_hash_table_add)
{
	zval *hash_table;
	zval *key;
#if 1
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(hash_table);
        Z_PARAM_ZVAL(key);
    ZEND_PARSE_PARAMETERS_END();
#else
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "oz", &hash_table, &key) == FAILURE) {
		return;
	}
#endif
	php_g_hash_table *obj = PHP_G_HASH_TABLE_FROM_STD(hash_table->value.obj);
	zend_bool ret = php_g_hash_table_add(obj, key);
	RETURN_BOOL(ret);
}

/*----------------------------------------------------------------------+
 | Vendor\ExtName\g_hash_table_insert                                   |
 +----------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_hash_table_insert, 0, 0, 3)
	ZEND_ARG_INFO(0, hash_table)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

PHP_FUNCTION(g_hash_table_insert)
{
	zval *hash_table;
	zval *key;
	zval *value;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ozz", &hash_table, &key, &value) == FAILURE) {
		return;
	}
	php_g_hash_table *obj = PHP_G_HASH_TABLE_FROM_STD(hash_table->value.obj);
	zend_bool ret = php_g_hash_table_insert(obj, key, value);
	RETURN_BOOL(ret);
}


/* {{{ gtk_functions[]
 *
 * Every user visible function must have an entry in gtk_functions[].
 */
const zend_function_entry gtk_functions[] = {
    PHP_FE(confirm_gtk_compiled,	NULL)		/* For testing, remove later. */
    PHP_FE(g_str_hash, arginfo_g_str_hash)
    PHP_FE(g_str_equal, arginfo_g_str_equal)
    PHP_FE(g_hash_table_new, arginfo_g_hash_table_new)
    PHP_FE(g_hash_table_add, arginfo_g_hash_table_add)
    PHP_FE(g_hash_table_insert, arginfo_g_hash_table_insert)
    PHP_FE_END	/* Must be the last line in gtk_functions[] */
};
/* }}} */

/* {{{ gtk_module_entry
 */
zend_module_entry gtk_module_entry = {
	STANDARD_MODULE_HEADER,
	"gtk",
	gtk_functions,
	PHP_MINIT(gtk),
	PHP_MSHUTDOWN(gtk),
	PHP_RINIT(gtk),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(gtk),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(gtk),
	PHP_GTK_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/*}}} */



#ifdef COMPILE_DL_GTK
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(gtk)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

