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

#ifndef PHP_G_LIST_H
#define PHP_G_LIST_H

#include "php_glib/glib.h"

#define PHP_G_LIST(ptr)                ((php_g_list*)(ptr))
#define PHP_G_LIST_FROM_STD(ptr) \
    (php_g_list*) (((void*)(ptr))-(sizeof(php_g_list) - sizeof(zend_object)))



typedef struct _php_g_list {
    GList *ptr;

    HashTable *prop_handler;
    zend_object std;
} php_g_list;

typedef int (*php_g_list_read_t)(php_g_list *obj, zval *retval);
typedef int (*php_g_list_write_t)(php_g_list *obj, zval *newval);

typedef struct _php_g_list_prop_handler {
    php_g_list_read_t read_func;
    php_g_list_write_t write_func;
} php_g_list_prop_handler;


php_g_list *php_g_list_append(php_g_list *list, zval *data);




PHP_GLIB_EXPORT extern zend_class_entry *php_g_list_class_entry;
extern HashTable php_g_list_prop_handlers;



/*----------------------------------------------------------------------+
 | g_list_append                                                        |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_append, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_append);


#define PHP_G_LIST_FE() \
    PHP_FE(g_list_append, arginfo_g_list_append)


zend_class_entry *php_g_list_class_init(zend_class_entry *ce);


#endif	/* PHP_G_LIST_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
