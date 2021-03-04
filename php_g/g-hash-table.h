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
  | Author: Sergio de Vasconcelos                                        |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_G_HASH_TABLE_H
#define PHP_G_HASH_TABLE_H


#define PHP_G_HASH_TABLE(ptr)                ((php_g_hash_table*)(ptr))
#define PHP_G_HASH_TABLE_FROM_STD(ptr) \
    (php_g_hash_table*) (((void*)(ptr))-(sizeof(php_g_hash_table) - sizeof(zend_object)))

typedef struct _php_g_hash_table {
    zval *hash_func;
    zval *key_equal_func;
    HashTable *prop_handler;
    php_glib_object parent_instance;
} php_g_hash_table;

typedef int (*php_g_hash_table_read_t)(php_g_hash_table *obj, zval *retval);
typedef int (*php_g_hash_table_write_t)(php_g_hash_table *obj, zval *newval);

typedef struct _php_g_hash_table_prop_handler {
    php_g_hash_table_read_t read_func;
    php_g_hash_table_write_t write_func;
} php_g_hash_table_prop_handler;


php_g_hash_table *php_g_hash_table_new(zval *hash, zval *equal);
zend_bool         php_g_hash_table_add(php_g_hash_table *hash_table, zval *key);
zend_bool         php_g_hash_table_insert(php_g_hash_table *hash_table, zval *key, zval *value);


void  php_g_hash_table_free(php_g_hash_table *hash_table);

zend_class_entry *php_g_hash_table_class_init(zend_class_entry *ce);

/*----------------------------------------------------------------------+
 | g_hash_table_insert                                                  |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_hash_table_insert, 0, 0, 3)
    ZEND_ARG_INFO(0, hash_table)
    ZEND_ARG_INFO(0, key)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_hash_table_insert);

/*----------------------------------------------------------------------+
 | g_hash_table_add                                                     |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_hash_table_add, 0, 0, 0)
    ZEND_ARG_INFO(0, hash_table)
    ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_hash_table_add);


/*----------------------------------------------------------------------+
 | Vendor\ExtName\g_hash_table_new                                      |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_hash_table_new, 0, 0, 0)
    ZEND_ARG_INFO(0, hash_func)
    ZEND_ARG_INFO(0, key_equal_func)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_hash_table_new);


/*----------------------------------------------------------------------+
 | Vendor\ExtName\g_str_hash                                         |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_str_hash, 0, 0, 0)
    ZEND_ARG_INFO(0, v)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_str_hash);

/*----------------------------------------------------------------------+
 | Vendor\ExtName\g_str_equal                                           |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_str_equal, 0, 0, 0)
    ZEND_ARG_INFO(0, v1)
    ZEND_ARG_INFO(0, v2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_str_equal);



#endif	/* PHP_G_HASH_TABLE_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */