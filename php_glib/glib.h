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

#ifndef PHP_GLIB_H
#define PHP_GLIB_H

#include <glib.h>

#ifdef PHP_WIN32
#	ifdef GLIB_EXPORTS
#		define PHP_GLIB_EXPORT __declspec(dllexport)
#	elif !defined(DOM_LOCAL_DEFINES) /* Allow to counteract LNK4049 warning. */
#		define PHP_GLIB_EXPORT __declspec(dllimport)
#	else
#		define PHP_GLIB_EXPORT
#	endif /* GLIB_EXPORTS */
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_GLIB_EXPORT __attribute__ ((visibility("default")))
#elif defined(PHPAPI)
#   define PHP_GLIB_EXPORT PHPAPI
#else
#   define PHP_GLIB_EXPORT
#endif

#define TRACE() 
//#define TRACE() g_print("%s\n", __FUNCTION__)


extern zend_object_handlers php_glib_handlers;

typedef enum _PhpGlibType {
    PHP_GLIB_NONE_TYPE = 0x00,
    /* ------ */
    PHP_GLIB_G_HASH_TABLE_TYPE,
    PHP_GLIB_G_LIST_TYPE,
    PHP_GLIB_G_OBJECT_TYPE,
    PHP_GLIB_GDK_EVENT_TYPE,
    PHP_GLIB_GTK_OBJECT_TYPE,// UnownedType...
    /* ------ */
    PHP_GLIB_LAST_TYPE,
} PhpGlibType;


typedef struct _php_glib_object {
    void *ptr;
    PhpGlibType type;

    HashTable *prop_handler;//TODO remove
    zend_object std;
} php_glib_object;

/**
struct php_g_object {
    php_glib_object
}
struct php_gtk_widget {
    php_g_object parent_instance;
    // parent;
    // previousSibling;
    // nextSibling;
    // children;
    php_g_object
}
*/

#define PHP_GLIB_OBJECT_FROM_STD(ptr) \
    (php_glib_object*) (((void*)(ptr))-(sizeof(php_glib_object) - sizeof(zend_object)))

#define PHP_GLIB_OBJECT(ptr)  ((php_glib_object*)(ptr))

typedef int (*glib_read_t)(php_glib_object *obj, zval *retval);
typedef int (*glib_write_t)(php_glib_object *obj, zval *newval);

typedef struct _php_glib_prop_handler {
    glib_read_t read_func;
    glib_write_t write_func;
} php_glib_prop_handler;


zend_object     *php_glib_create_object(zend_class_entry *class_type);
php_glib_object *php_glib_from_zend(zend_object *obj);

void             php_glib_copy_prop_handler(zval *zv);
void             php_glib_dtor_prop_handler(zval *zv);

zend_object_handlers *php_glib_get_obj_handlers(void);
php_glib_object      *php_glib_set_class(zend_class_entry *class_type, zend_bool hash_copy);
void                  php_glib_free_storage(zend_object *object);
zval *php_glib_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot);
void  php_glib_register_prop_handler(HashTable *prop_handler, char *name, size_t name_len, glib_read_t read_func, glib_write_t write_func);
zval *php_glib_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv);
void  php_glib_write_property(zval *object, zval *member, zval *value, void **cache_slot);
int   php_glib_read_na(php_glib_object *obj, zval *retval);
int   php_glib_write_na(php_glib_object *obj, zval *newval);

HashTable *php_glib_get_debug_info(zval *object, int *is_temp);

zend_class_entry *php_glib_class_init(zend_class_entry *ce);
PHP_GLIB_EXPORT zend_object_handlers *php_glib_object_get_handlers();

#endif	/* PHP_GLIB_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
