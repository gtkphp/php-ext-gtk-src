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

#ifndef PHP_GLIB_LIST_H
#define PHP_GLIB_LIST_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#define PHP_GLIB_LIST(ptr)           ((php_glib_list*)(ptr))
#define PHP_GLIB_LIST_CLASS          php_glib_list_class_entry
#define PHP_GLIB_LIST_OFFSET         (sizeof(php_glib_list) - sizeof(zend_object))

#define ZOBJ_IS_PHP_GLIB_LIST(obj)   ((obj)!=NULL && obj->ce == php_glib_list_class_entry)
#define ZOBJ_TO_PHP_GLIB_LIST(std)   PHP_GLIB_LIST( ((void*)(std))-PHP_GLIB_LIST_OFFSET )

#define ZVAL_IS_PHP_GLIB_LIST(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GLIB_LIST((val)->value.obj))
#define ZVAL_GET_PHP_GLIB_LIST(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GLIB_LIST((val)->value.obj))

#define ZVAL_SET_PHP_GLIB_LIST(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

#define PHP_GLIB_LIST_FE() \
    PHP_GTK_FE(g_list_append,                  arginfo_g_list_append) \
    PHP_GTK_FE(g_list_prepend,                 arginfo_g_list_prepend) \
    PHP_GTK_FE(g_list_insert,                  arginfo_g_list_insert) \
    PHP_GTK_FE(g_list_insert_before,           arginfo_g_list_insert_before) \
    PHP_GTK_FE(g_list_insert_sorted,           arginfo_g_list_insert_sorted) \
    PHP_GTK_FE(g_list_remove,                  arginfo_g_list_remove) \
    PHP_GTK_FE(g_list_remove_link,             arginfo_g_list_remove_link) \
    PHP_GTK_FE(g_list_delete_link,             arginfo_g_list_delete_link) \
    PHP_GTK_FE(g_list_remove_all,              arginfo_g_list_remove_all) \
    PHP_GTK_FE(g_list_free,                    arginfo_g_list_free) \
    PHP_GTK_FE(g_list_free_full,               arginfo_g_list_free_full) \
    PHP_GTK_FE(g_list_alloc,                   arginfo_g_list_alloc) \
    PHP_GTK_FE(g_list_free_1,                  arginfo_g_list_free_1) \
    PHP_GTK_FE(g_list_length,                  arginfo_g_list_length) \
    PHP_GTK_FE(g_list_copy,                    arginfo_g_list_copy) \
    PHP_GTK_FE(g_list_copy_deep,               arginfo_g_list_copy_deep) \
    PHP_GTK_FE(g_list_reverse,                 arginfo_g_list_reverse) \
    PHP_GTK_FE(g_list_sort,                    arginfo_g_list_sort) \
    PHP_GTK_FE(g_list_insert_sorted_with_data, arginfo_g_list_insert_sorted_with_data) \
    PHP_GTK_FE(g_list_sort_with_data,          arginfo_g_list_sort_with_data) \
    PHP_GTK_FE(g_list_concat,                  arginfo_g_list_concat) \
    PHP_GTK_FE(g_list_foreach,                 arginfo_g_list_foreach) \
    PHP_GTK_FE(g_list_first,                   arginfo_g_list_first) \
    PHP_GTK_FE(g_list_last,                    arginfo_g_list_last) \
    PHP_GTK_FE(g_list_nth,                     arginfo_g_list_nth) \
    PHP_GTK_FE(g_list_nth_data,                arginfo_g_list_nth_data) \
    PHP_GTK_FE(g_list_nth_prev,                arginfo_g_list_nth_prev) \
    PHP_GTK_FE(g_list_find,                    arginfo_g_list_find) \
    PHP_GTK_FE(g_list_find_custom,             arginfo_g_list_find_custom) \
    PHP_GTK_FE(g_list_position,                arginfo_g_list_position) \
    PHP_GTK_FE(g_list_index,                   arginfo_g_list_index) \
    PHP_GTK_FE(g_list_dump,                    arginfo_g_list_dump) \


extern zend_class_entry *php_glib_list_class_entry;

#define PHP_GLIB_LIST_MINIT_FUNCTION(container_ce, parent_ce) \
    php_glib_list_class_init(container_ce, parent_ce)

#define PHP_GLIB_LIST_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GLIB_LIST_RSHUTDOWN_FUNCTION() {\
}

typedef struct _php_glib_list php_glib_list;
struct _php_glib_list {
    GList *ptr;
    zval data;
    php_glib_list *next;
    php_glib_list *prev;

    HashTable *properties;

    zend_object std;
};

php_glib_list *php_glib_list_append(php_glib_list *list, zval *data);
php_glib_list *php_glib_list_prepend(php_glib_list *list, zval *data);
php_glib_list *php_glib_list_insert(php_glib_list *list, zval *data, zend_long position);
php_glib_list *php_glib_list_insert_before(php_glib_list *list, php_glib_list *sibling, zval *data);
php_glib_list *php_glib_list_insert_sorted(php_glib_list *list, zval *data, zval *func);
php_glib_list *php_glib_list_remove(php_glib_list *list, zval *data);
php_glib_list *php_glib_list_remove_link(php_glib_list *list, php_glib_list *llink);
php_glib_list *php_glib_list_delete_link(php_glib_list *list, php_glib_list *link_);
php_glib_list *php_glib_list_remove_all(php_glib_list *list, zval *data);
void php_glib_list_free(php_glib_list *list);
void php_glib_list_free_full(php_glib_list *list, zval *free_func);
php_glib_list *php_glib_list_alloc();
void php_glib_list_free_1(php_glib_list *list);
zend_long php_glib_list_length(php_glib_list *list);
php_glib_list *php_glib_list_copy(php_glib_list *list);
php_glib_list *php_glib_list_copy_deep(php_glib_list *list, zval *func, zval *user_data);
php_glib_list *php_glib_list_reverse(php_glib_list *list);
php_glib_list *php_glib_list_sort(php_glib_list *list, zval *compare_func);
php_glib_list *php_glib_list_insert_sorted_with_data(php_glib_list *list, zval *data, zval *func, zval *user_data);
php_glib_list *php_glib_list_sort_with_data(php_glib_list *list, zval *compare_func, zval *user_data);
php_glib_list *php_glib_list_concat(php_glib_list *list1, php_glib_list *list2);
void php_glib_list_foreach(php_glib_list *list, zval *func, zval *user_data);
php_glib_list *php_glib_list_first(php_glib_list *list);
php_glib_list *php_glib_list_last(php_glib_list *list);
php_glib_list *php_glib_list_nth(php_glib_list *list, zend_long n);
zval *php_glib_list_nth_data(php_glib_list *list, zend_long n);
php_glib_list *php_glib_list_nth_prev(php_glib_list *list, zend_long n);
php_glib_list *php_glib_list_find(php_glib_list *list, zval *data);
php_glib_list *php_glib_list_find_custom(php_glib_list *list, zval *data, zval *func);
zend_long php_glib_list_position(php_glib_list *list, php_glib_list *llink);
zend_long php_glib_list_index(php_glib_list *list, zval *data);

php_glib_list* php_glib_list_new(GList *list);
zend_class_entry *php_glib_list_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list___construct, 0, 0, 0)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_METHOD(g_list, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_append, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_append);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_prepend, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_prepend);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_insert, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, position)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_insert);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_insert_before, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, sibling)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_insert_before);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_insert_sorted, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, func)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_insert_sorted);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_remove, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_remove);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_remove_link, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, llink)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_remove_link);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_delete_link, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, link_)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_delete_link);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_remove_all, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_remove_all);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_free, 0, 0, 1)
    ZEND_ARG_INFO(1, list)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_free);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_free_full, 0, 0, 2)
    ZEND_ARG_INFO(1, list)
    ZEND_ARG_INFO(0, free_func)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_free_full);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_alloc, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_alloc);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_free_1, 0, 0, 1)
    ZEND_ARG_INFO(1, list)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_free_1);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_length, 0, 0, 1)
    ZEND_ARG_INFO(0, list)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_length);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_copy, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_copy);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_copy_deep, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, func)
    ZEND_ARG_INFO(0, user_data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_copy_deep);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_reverse, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_reverse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_sort, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, compare_func)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_sort);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_insert_sorted_with_data, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, func)
    ZEND_ARG_INFO(0, user_data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_insert_sorted_with_data);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_sort_with_data, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, compare_func)
    ZEND_ARG_INFO(0, user_data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_sort_with_data);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_concat, 0, 0, 0)
    ZEND_ARG_INFO(0, list1)
    ZEND_ARG_INFO(0, list2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_concat);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_foreach, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, func)
    ZEND_ARG_INFO(0, user_data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_foreach);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_first, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_first);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_last, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_last);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_nth, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, n)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_nth);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_nth_data, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, n)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_nth_data);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_nth_prev, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, n)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_nth_prev);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_find, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_find);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_find_custom, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, func)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_find_custom);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_position, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, llink)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_position);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_index, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_index);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_dump, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_dump);

#endif	/* PHP_GLIB_LIST_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
