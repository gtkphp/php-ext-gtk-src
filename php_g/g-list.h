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


#define PHP_G_LIST(ptr)           ((php_g_list*)(ptr))
#define PHP_G_LIST_CLASS          php_g_list_class_entry
#define PHP_G_LIST_OFFSET         (sizeof(php_g_list) - sizeof(zend_object))

#define ZOBJ_IS_PHP_G_LIST(obj)   ((obj)!=NULL && obj->ce == php_g_list_class_entry)
#define ZOBJ_TO_PHP_G_LIST(std)   PHP_G_LIST( ((void*)(std))-PHP_G_LIST_OFFSET )

#define ZVAL_IS_PHP_G_LIST(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_G_LIST((val)->value.obj))
#define ZVAL_GET_PHP_G_LIST(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_G_LIST((val)->value.obj))
#define ZVAL_SET_PHP_G_LIST(z, o) do {              \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);						\
            Z_OBJ_P(__z) = &(o)->std;    			\
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;		\
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

#define PHP_G_LIST_FE() \
    PHP_FE(g_list_dump,    arginfo_g_list_dump)     \
    PHP_FE(g_list_append,  arginfo_g_list_append)   \
    PHP_FE(g_list_prepend, arginfo_g_list_prepend)  \
    PHP_FE(g_list_insert,  arginfo_g_list_insert)   \
    PHP_FE(g_list_first,   arginfo_g_list_first)

#define PHP_G_LIST_MINIT_FUNCTION(parent_ce) \
    php_g_list_class_init(parent_ce)

#define PHP_G_LIST_MSHUTDOWN_FUNCTION() { \
    zend_hash_destroy(&php_g_list_prop_handlers); \
}

#define PHP_G_LIST_RSHUTDOWN_FUNCTION() {\
}

PHP_GLIB_EXPORT extern zend_class_entry *php_g_list_class_entry;
extern HashTable php_g_list_prop_handlers;
extern HashTable php_g_hash_table_prop_handlers;

typedef struct _php_g_list php_g_list;

struct _php_g_list {
    GList *ptr;

    zval prev;// php_g_list *prev = NULL;
    zval data;
    zval next;
    /*
    php_g_list *prev;// php_g_list *prev = NULL;
    zval data;
    php_g_list *next;
    */

    HashTable *properties;// TODO remove and use the std->property_handlers. Howto to hack "prev", "data", "next"( see function _register_)
    HashTable *array_properties;
    zend_object std;
};



/*----------------------------------------------------------------------+
 | Zend-user API                                                        |
 | see https://github.com/GNOME/glib/blob/master/glib/glist.c           |
 +----------------------------------------------------------------------*/
php_g_list *php_g_list_append(php_g_list *list, zval *data);
php_g_list *php_g_list_prepend(php_g_list *list, zval *data);
php_g_list *php_g_list_insert(php_g_list *list, zval *data, zval *position);

php_g_list *php_g_list_first(php_g_list *list);
php_g_list *php_g_list_last(php_g_list *node);
php_g_list *php_g_list_nth(php_g_list *list, zend_long index);

zend_class_entry *php_g_list_class_init(zend_class_entry *ce);

//private php_g_list *php_g_list_dump(php_g_list *list);

zend_long   php_g_list_length(php_g_list *list);


/*----------------------------------------------------------------------+
 | Php-user API                                                         |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | g_list_dump                                                          |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_dump, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_dump);

/*----------------------------------------------------------------------+
 | g_list_append                                                        |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_append, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_append);

/*----------------------------------------------------------------------+
 | g_list_prepend                                                       |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_prepend, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_prepend);

/*----------------------------------------------------------------------+
 | g_list_insert                                                        |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_insert, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, position)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_insert);

/*----------------------------------------------------------------------+
 | g_list_first                                                        |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list_first, 0, 0, 0)
    ZEND_ARG_INFO(0, list)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_list_first);

/*----------------------------------------------------------------------+
 | GList::__construct                                                   |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list___construct, 0, 0, 0)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
PHP_METHOD(G_List, __construct);

/*----------------------------------------------------------------------+
 | GList::__set_state                                                   |
 +----------------------------------------------------------------------*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list___set_state, 0, 0, 0)
    ZEND_ARG_INFO(0, properties)
ZEND_END_ARG_INFO()
PHP_METHOD(G_List, __set_state);


#endif	/* PHP_G_LIST_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
