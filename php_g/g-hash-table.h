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




/*if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oz", &hash_table, php_g_hash_table_class_entry, &key) == FAILURE) {*/

gboolean g_hash_table_add (GHashTable *hash_table, gpointer key);

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

#endif	/* PHP_G_HASH_TABLE_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
