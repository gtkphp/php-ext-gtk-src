/*
+----------------------------------------------------------------------+
| PHP Version 8                                                        |
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

#ifndef PHP_G_LIST_H
#define PHP_G_LIST_H


#define PHP_G_LIST(ptr)           ((php_g_list*)(ptr))
#define PHP_G_LIST_CLASS          php_g_list_class_entry
#define PHP_G_LIST_OFFSET         (sizeof(php_g_list) - sizeof(zend_object))

#define ZOBJ_IS_PHP_G_LIST(obj)   ((obj)!=NULL && obj->ce == php_g_list_class_entry)
#define ZOBJ_TO_PHP_G_LIST(std)   PHP_G_LIST( ((void*)(std))-PHP_G_LIST_OFFSET )

#define ZVAL_IS_PHP_G_LIST(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_G_LIST((val)->value.obj))
#define ZVAL_GET_PHP_G_LIST(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_G_LIST((val)->value.obj))

#define ZVAL_SET_PHP_G_LIST(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)


#define PHP_G_LIST_COPY(src, dest) \


#define PHP_G_LIST_SET(dest, src) \



#define DECL_PHP_G_LIST(name) \
    g_list __##name; \
    g_list *name = &__##name; \
    PHP_G_LIST_COPY(php_##name, name);




#define PHP_G_LIST_FE() \
    PHP_GTK_FE(g_list_append,        arginfo_g_list_append)  \
    PHP_GTK_FE(g_list_prepend,       arginfo_g_list_prepend)  \
    PHP_GTK_FE(g_list_insert,        arginfo_g_list_insert)  \
    PHP_GTK_FE(g_list_insert_before, arginfo_g_list_insert_before)  \
    PHP_GTK_FE(g_list_remove,        arginfo_g_list_remove)  \
    PHP_GTK_FE(g_list_remove_link,   arginfo_g_list_remove_link)  \
    PHP_GTK_FE(g_list_delete_link,   arginfo_g_list_delete_link)  \
    PHP_GTK_FE(g_list_remove_all,    arginfo_g_list_remove_all)  \
    PHP_GTK_FE(g_list_free,          arginfo_g_list_free)  \
    PHP_GTK_FE(g_list_length,        arginfo_g_list_length)  \
    PHP_GTK_FE(g_list_first,         arginfo_g_list_first)  \
    PHP_GTK_FE(g_list_last,          arginfo_g_list_last)  \
    PHP_GTK_FE(g_list_nth,           arginfo_g_list_nth)  \



#define PHP_G_LIST_MINIT_FUNCTION(container_ce, parent_ce) \
    php_g_list_class_init(container_ce, parent_ce)

#define PHP_G_LIST_MSHUTDOWN_FUNCTION() { \
}

#define PHP_G_LIST_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_g_list_class_entry;

typedef struct _php_g_list php_g_list;
struct _php_g_list {
    zval data;// of zval *
    zval next;// of php_g_list *
    zval prev;// of php_g_list *

    zend_object std;
};

zend_class_entry*
php_g_list_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);

php_g_list *php_g_list_new(GList *list);
GList      *php_g_list_export(php_g_list *list);

php_g_list *php_g_list_append(php_g_list *php_list, zval *zdata);
php_g_list *php_g_list_prepend(php_g_list *php_list, zval *zdata);
php_g_list *php_g_list_insert(php_g_list *php_list, zval *zdata, int position);
php_g_list *php_g_list_insert_befor(php_g_list *php_list, php_g_list *php_sibling, zval *zdata);
php_g_list *php_g_list_remove (php_g_list *list, zval *data);
php_g_list *php_g_list_remove_link(php_g_list *list, php_g_list *llink);
php_g_list *php_g_list_delete_link(php_g_list *list, php_g_list *llink);
php_g_list *php_g_list_remove_all(php_g_list *list, zval *data);
void        php_g_list_free(php_g_list *list);
zend_long   php_g_list_length(php_g_list *list);
php_g_list *php_g_list_first(php_g_list *list);
php_g_list *php_g_list_last(php_g_list *list);
php_g_list *php_g_list_nth(php_g_list *php_list, zend_long n);


ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list___construct, 0, 0, 0)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_METHOD(g_list, __construct);

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_list_append, ZEND_RETURN_VALUE, 2, GList, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, list, GList, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_append);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_list_prepend, ZEND_RETURN_VALUE, 2, GList, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, list, GList, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_prepend);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_list_insert, ZEND_RETURN_VALUE, 3, GList, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, list, GList, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, data)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, position, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_insert);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_list_insert_before, ZEND_RETURN_VALUE, 3, GList, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, list, GList, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, sibling, GList, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_insert_before);
//PHP_FUNCTION(g_list_insert_sorted);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_list_remove, ZEND_RETURN_VALUE, 2, GList, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, list, GList, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_remove);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_list_remove_link, ZEND_RETURN_VALUE, 2, GList, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, list, GList, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, llink, GList, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_remove_link);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_list_delete_link, ZEND_RETURN_VALUE, 2, GList, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, list, GList, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, link_, GList, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_delete_link);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_list_remove_all, ZEND_RETURN_VALUE, 2, GList, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, list, GList, 0)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_remove_all);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_g_list_free, ZEND_RETURN_VALUE, 1, IS_VOID, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_REF, list, GList, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_free);
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_g_list_length, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, list, GList, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_length);

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_list_first, ZEND_RETURN_VALUE, 1, GList, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, list, GList, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_first);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_list_last, ZEND_RETURN_VALUE, 1, GList, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, list, GList, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_last);
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_g_list_nth, ZEND_RETURN_VALUE, 2, GList, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, list, GList, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, n, guint, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_nth);

#endif	/* PHP_G_LIST_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
