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

#include "php_glib/glib.h"
#include "g-hash-table.h"

#include <glib-object.h>
#include <gdk/gdk.h>
#include <ctype.h>


extern HashTable classes;
extern zend_class_entry *php_glib_class_entry;
//extern zend_object_handlers php_glib_handlers;
extern zend_module_entry gtk_module_entry;

zend_class_entry *php_g_hash_table_class_entry;
HashTable php_g_hash_table_prop_handlers;
zend_object_handlers php_g_hash_table_handlers;


/*----------------------------------------------------------------------+
 | Zend Internals                                                       |
 +----------------------------------------------------------------------*/

static void php_g_hash_table_dtor_prop_handler(zval *zv) /* {{{ */
{
	TRACE();
    free(Z_PTR_P(zv));
}

/* {{{ dom_objects_free_storage */
void php_g_hash_table_free_storage(zend_object *object)
{
	TRACE();

    php_g_hash_table *intern = PHP_G_HASH_TABLE_FROM_STD(object);
    php_glib_object *parent = PHP_GLIB_OBJECT(&intern->parent_instance);
#if defined(__GNUC__) && __GNUC__ >= 3
    int retcount __attribute__((unused)); /* keep compiler quiet */
#else
    int retcount;
#endif

    zend_object_std_dtor(&parent->std);// maybe use PHP_STD_FROM_G_HASH_TABLE()
    efree(intern);
// FIXME
#if 0
    if (intern->ptr != NULL ) {

        /*
        if (((xmlNodePtr) ((php_libxml_node_ptr *)intern->ptr)->node)->type != XML_DOCUMENT_NODE && ((xmlNodePtr) ((php_libxml_node_ptr *)intern->ptr)->node)->type != XML_HTML_DOCUMENT_NODE) {
            php_libxml_node_decrement_resource((php_libxml_node_object *) intern);
        } else {
            php_libxml_decrement_node_ptr((php_libxml_node_object *) intern);
            retcount = php_libxml_decrement_doc_ref((php_libxml_node_object *)intern);
        }
        */
        intern->ptr = NULL;
    }
#endif
}
/* }}} */

zval *php_g_hash_table_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
	TRACE();
    php_g_hash_table *obj = PHP_G_HASH_TABLE_FROM_STD(Z_OBJ_P(object));
    php_glib_object *parent = &obj->parent_instance;
    zend_string *member_str = zval_get_string(member);
    zval *retval = NULL;

    g_print("%s\n", "php_g_hash_table_get_property_ptr_ptr");
    if (!obj->prop_handler || !zend_hash_exists(obj->prop_handler, member_str)) {
        zend_object_handlers *std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->get_property_ptr_ptr(object, member, type, cache_slot);
    }

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ gtk_read_property */
zval *php_g_hash_table_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
	TRACE();
    php_g_hash_table *obj = PHP_G_HASH_TABLE_FROM_STD(Z_OBJ_P(object));
    php_glib_object *parent = &obj->parent_instance;
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    php_g_hash_table_prop_handler *hnd = NULL;
    g_print("%s(%s)\n", "php_glib_read_property", member->value.str->val);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member_str);
    } else if (instanceof_function(parent->std.ce, php_g_hash_table_class_entry)) {
        php_error(E_WARNING, "Couldn't fetch %s. Widget no longer exists", ZSTR_VAL(parent->std.ce->name));
    }

    if (hnd) {
        int ret = hnd->read_func(obj, rv);
        if (ret == SUCCESS) {
            retval = rv;
        } else {
            retval = &EG(uninitialized_zval);
        }
    } else {
        zend_object_handlers *std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->read_property(object, member, type, cache_slot, rv);
    }

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ gtk_write_property */
void php_g_hash_table_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
	TRACE();
    php_g_hash_table *obj = PHP_G_HASH_TABLE_FROM_STD(Z_OBJ_P(object));
    php_glib_object *parent = &obj->parent_instance;
    zend_string *member_str = zval_get_string(member);
    php_g_hash_table_prop_handler *hnd = NULL;

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member_str);
    }
    if (hnd) {
        hnd->write_func(obj, value);
    } else {
        zend_object_handlers *std_hnd = zend_get_std_object_handlers();
        std_hnd->write_property(object, member, value, cache_slot);
    }

    zend_string_release(member_str);
}
/* }}} */



/* {{{ dom_read_na */
int php_g_hash_table_read_na(php_g_hash_table *obj, zval *retval)
{
	TRACE();
    zend_throw_error(NULL, "Cannot read property");
    return FAILURE;
}
/* }}} */

/* {{{ dom_write_na */
int php_g_hash_table_write_na(php_g_hash_table *obj, zval *newval)
{
	TRACE();
    zend_throw_error(NULL, "Cannot write property");
    return FAILURE;
}
/* }}} */

static char *php_g_hash_table_tostring_object(zval *obj, char *salt) {
	char *name = obj->value.obj->ce->name->val;
	guint id = Z_OBJ_HANDLE_P(obj);
	gchar default_format[]="object(%s)#%d";
	gchar *format=default_format;
	if (salt!=NULL) {
		format = salt;
	}
	gchar *key = g_strdup_printf (format, name, id);
	return key;
}



static HashTable*
php_g_hash_table_get_debug_info_helper(zval *object, int *is_temp) /* {{{ */
{
	TRACE();

    php_g_hash_table *obj =  PHP_G_HASH_TABLE_FROM_STD(Z_OBJ_P(object));
    php_glib_object *parent = &obj->parent_instance;
    HashTable              *debug_info,
                           *prop_handlers = obj->prop_handler,
                           *std_props;
    zend_string            *string_key;
    php_g_hash_table_prop_handler  *entry;
    zend_string            *object_str;

    *is_temp = 1;

    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    if (!prop_handlers) {
        return debug_info;
    }

    /*
    object_str = zend_string_init("(object value omitted)", sizeof("(object value omitted)")-1, 0);

    ZEND_HASH_FOREACH_STR_KEY_PTR(prop_handlers, string_key, entry) {
        zval value;

        if (entry->read_func(obj, &value) == FAILURE || !string_key) {
            continue;
        }

        if (Z_TYPE(value) == IS_OBJECT) {
            zval_dtor(&value);
            ZVAL_NEW_STR(&value, object_str);
            zend_string_addref(object_str);
        }

        zend_hash_add(debug_info, string_key, &value);
    } ZEND_HASH_FOREACH_END();

    zend_string_release(object_str);
    */
GHashTableIter iter;
zval *key, *value;
zval val;
zend_string *str_key;

g_hash_table_iter_init (&iter, parent->ptr);
while (g_hash_table_iter_next (&iter, (gpointer)&key, (gpointer)&value))
  {
    zval k;
    //g_print("g_hash_table_iter(%p, %p)\n", key, value);
    //str_key = zend_string_init((char*)key, strlen((char*)key), 0);
	if (Z_TYPE_P(key)==IS_STRING) {
		//k = (zval *)key;
		ZVAL_COPY(&k, key);
	} else if (Z_TYPE_P(key)==IS_OBJECT ) {
		char *name = php_g_hash_table_tostring_object(key, NULL);
		ZVAL_STRING(&k, name);
		g_free(name);
	} else {
		g_print("Unexpected 21 : php_g_hash_table_get_debug_info_helper\n");
	}
	if (Z_TYPE_P(value)==IS_STRING) {
		ZVAL_COPY(&val, value);
	} else if (Z_TYPE_P(value)==IS_OBJECT ) {
		ZVAL_COPY(&val, value);
	} else {
		g_print("Unexpected 21 : php_g_hash_table_get_debug_info_helper\n");
	}

    //g_print("%s=>%s\n", (char *)k->value.str->val, (char *)val.value.str->val);
    zend_hash_add(debug_info, k.value.str, &val);

  }
    return debug_info;
}
/* }}} */

HashTable*
php_g_hash_table_get_debug_info(zval *object, int *is_temp)
{
	TRACE();
    return php_g_hash_table_get_debug_info_helper(object, is_temp);
}

static zend_object_handlers*
php_g_hash_table_get_handlers()
{
	TRACE();
	memcpy(&php_g_hash_table_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_g_hash_table_handlers.offset = XtOffsetOf(php_g_hash_table, parent_instance.std);
	php_g_hash_table_handlers.free_obj = php_g_hash_table_free_storage;
	php_g_hash_table_handlers.read_property = php_g_hash_table_read_property;
	php_g_hash_table_handlers.write_property = php_g_hash_table_write_property;
	php_g_hash_table_handlers.get_property_ptr_ptr = php_g_hash_table_get_property_ptr_ptr;
	php_g_hash_table_handlers.get_debug_info = php_g_hash_table_get_debug_info;

/*
php_g_hash_table_handlers.has_dimension;
php_g_hash_table_handlers.read_dimension;
php_g_hash_table_handlers.unset_dimension;
php_g_hash_table_handlers.write_dimension;
*/
	return &php_g_hash_table_handlers;
}

/*----------------------------------------------------------------------+
 | Internals                                                            |
 +----------------------------------------------------------------------*/


//extern gtk_module_entry ?
//extern classes
static php_g_hash_table*
php_g_hash_table_set_class(zend_class_entry *class_type,
                           zend_bool hash_copy) /* {{{ */
{
	TRACE();
    php_g_hash_table *intern = ecalloc(1, sizeof(php_g_hash_table) + zend_object_properties_size(class_type));
    php_glib_object *parent = PHP_GLIB_OBJECT(&intern->parent_instance);
    zend_class_entry *base_class = class_type;
    while ((   base_class->type != ZEND_INTERNAL_CLASS
            || base_class->info.internal.module->module_number != gtk_module_entry.module_number
           )
           && base_class->parent != NULL) {
        base_class = base_class->parent;
    }

    intern->prop_handler = zend_hash_find_ptr(&classes, base_class->name);

    zend_object_std_init(&parent->std, class_type);

    if (hash_copy) {
        object_properties_init(&parent->std, class_type);
    }

    return intern;
}
/* }}} */

/* {{{ php_glib_create_object */
zend_object *php_g_hash_table_create_object(zend_class_entry *class_type)
{
	TRACE();
    php_g_hash_table *intern = php_g_hash_table_set_class(class_type, 1);
    php_glib_object  *parent = PHP_GLIB_OBJECT(&intern->parent_instance);
    parent->type = PHP_GLIB_G_HASH_TABLE_TYPE;
    parent->std.handlers = &php_g_hash_table_handlers;//-------------------------------------
    return &parent->std;
}
/* }}} */

static php_g_hash_table *current_hash_table = NULL;

static guint
php_g_hash_table_hash_func(gconstpointer v) {
	//g_print("php_g_hash_table_hash_func(TODO v IS_OBJECT etc.)\n");
	zval *hash_func = current_hash_table->hash_func;
	zval *val = (zval *)v;
	if (NULL==hash_func) {
		if (Z_TYPE_P(val)==IS_STRING) {
			guint hash = g_str_hash(val->value.str->val);
			return hash;
		} else if (Z_TYPE_P(val)==IS_OBJECT ) {
			char *name = php_g_hash_table_tostring_object(val, NULL);
			guint hash = g_str_hash(name);
			g_free(name);
			return hash;
		} else {
			g_print("Unexpected 21 : php_g_hash_table_hash_func\n");
		}
	} else {
		int result;
		int param_count = 1;
		zval retval;
		zval params[1];
		if (Z_TYPE_P(val)==IS_STRING) {
			ZVAL_COPY(&params[0], val);
		} else if (Z_TYPE_P(val)==IS_OBJECT) {
			char *name = php_g_hash_table_tostring_object(val, NULL);
			ZVAL_STRING(&params[0], name);
			g_free(name);
		}
		result = call_user_function(NULL, NULL, hash_func, &retval, param_count, params);
		if (result==FAILURE) {
			g_print("Unexpected 22 : php_g_hash_table_hash_func\n");
		} else if (Z_TYPE(retval)==IS_LONG) {
			return retval.value.lval;
		} else {
			g_print("Unexpected 23 : php_g_hash_table_hash_func\n");
		}
	}
	g_print("Unexpected 22 : php_g_hash_table_hash_func\n");
	// zend call function
	return 0;
}

static gboolean
php_g_hash_table_key_equal_func(gconstpointer v1, gconstpointer v2) {
	//g_print("php_g_hash_table_key_equal_func(TODO: v1|v2 IS_OBJECT)\n");
	zval *key_equal_func = current_hash_table->key_equal_func;
	zval *val1 = (zval *)v1;
	zval *val2 = (zval *)v2;
	if (NULL==key_equal_func) {
		if (Z_TYPE_P(val1)==IS_STRING && Z_TYPE_P(val2)==IS_STRING) {
			return g_str_equal(val1->value.str->val, val2->value.str->val);
		} else if (Z_TYPE_P(val1)==IS_OBJECT && Z_TYPE_P(val2)==IS_OBJECT) {
			char *name1 = php_g_hash_table_tostring_object(val1, "0123456789%s%d");
			char *name2 = php_g_hash_table_tostring_object(val2, "0123456789%s%d");
			gboolean equal = g_str_equal(name1, name2);
			g_free(name1);
			g_free(name2);
			return equal;
		} else {
			g_print("Unexpected 12 : php_g_hash_table_key_equal_func\n");
		}
	} else {
		int result;
		int param_count = 2;
		zval retval;
		zval params[2];
		if (Z_TYPE_P(val1)==IS_STRING) {
			ZVAL_COPY_VALUE(&params[0], val1);
		} else if (Z_TYPE_P(val1)==IS_OBJECT) {
			char *name = php_g_hash_table_tostring_object(val1, NULL);
			ZVAL_STRING(&params[0], name);
			g_free(name);
		}
		if (Z_TYPE_P(val2)==IS_STRING) {
			ZVAL_COPY_VALUE(&params[1], val2);
		} else if (Z_TYPE_P(val2)==IS_OBJECT) {
			char *name = php_g_hash_table_tostring_object(val2, NULL);
			ZVAL_STRING(&params[1], name);
			g_free(name);
		}
		result = call_user_function(NULL, NULL, key_equal_func, &retval, param_count, params);
		// check result== FAILURE
		if (result==FAILURE) {
			g_print("Unexpected 14 : php_g_hash_table_key_equal_func\n");
		} else if (Z_TYPE(retval)==IS_TRUE) {
			return TRUE;
		} else if (Z_TYPE(retval)==IS_FALSE) {
			return FALSE;
		} else {
			g_print("Unexpected 13 : php_g_hash_table_key_equal_func\n");
		}
	}
	// zend call function
	return TRUE;
}

php_g_hash_table*
php_g_hash_table_new(zval *hash_func, zval *key_equal_func)
{
	TRACE();
    zend_object *object = php_g_hash_table_create_object(php_g_hash_table_class_entry);
    php_g_hash_table *hash_table = PHP_G_HASH_TABLE_FROM_STD(object);
    php_glib_object *obj = PHP_GLIB_OBJECT(&hash_table->parent_instance);


    obj->ptr = g_hash_table_new(php_g_hash_table_hash_func,
                                php_g_hash_table_key_equal_func);
	if (hash_func && ! ZVAL_IS_NULL(hash_func)) {
		hash_table->hash_func = emalloc(sizeof(zval));
		ZVAL_COPY(hash_table->hash_func, hash_func);
	} else {
		hash_table->hash_func = NULL;
	}
	if (key_equal_func && ! ZVAL_IS_NULL(key_equal_func)) {
		hash_table->key_equal_func = emalloc(sizeof(zval));
		ZVAL_COPY(hash_table->key_equal_func, key_equal_func);
	} else {
		hash_table->key_equal_func = NULL;
	}

    return PHP_G_HASH_TABLE_FROM_STD(object);
}

zend_bool
php_g_hash_table_add(php_g_hash_table *hash_table, zval *key)
{
	TRACE();
    current_hash_table = hash_table;
    php_glib_object *obj = &hash_table->parent_instance;
    GHashTable *hash = obj->ptr;

    zval *k = emalloc(sizeof(zval));
    ZVAL_COPY(k, key);
    zend_bool retval = g_hash_table_add(hash, k);

    current_hash_table = NULL;
    return retval;
}


zend_bool
php_g_hash_table_insert(php_g_hash_table *hash_table, zval *key, zval *value)
{
	TRACE();
    current_hash_table = hash_table;
    php_glib_object *obj = &hash_table->parent_instance;
    GHashTable *hash = obj->ptr;

    zval *k = emalloc(sizeof(zval));
    ZVAL_COPY(k, key);
    zval *v = emalloc(sizeof(zval));
    ZVAL_COPY(v, value);
    zend_bool retval = g_hash_table_insert(hash, k, v);

    current_hash_table = NULL;
    return retval;
}





/*----------------------------------------------------------------------+
 | Vendor\ExtName\GHashTable::__construct                               |
 +----------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_hash_table___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

/* {{{ GHashTable::__construct() */
PHP_METHOD(G_Hash_Table, __construct)
{
	TRACE();
}
/* }}} GHashTable::__construct() */

static const zend_function_entry php_g_hash_table_methods[] = {
    PHP_ME(G_Hash_Table, __construct, arginfo_g_hash_table___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};




/*{{{ juste pour var_dump(zval) ou zval est un php_g_hash_table->php_glib_object */
zend_class_entry*
php_g_hash_table_class_init(zend_class_entry *ce) {
	TRACE();
   php_g_hash_table_get_handlers();
   //INIT_NS_CLASS_ENTRY((*ce), "Vendor\\ExtName", "GHashTable", php_g_hash_table_methods);
   INIT_CLASS_ENTRY((*ce), "GHashTable", php_g_hash_table_methods);
   ce->create_object = php_g_hash_table_create_object;
   php_g_hash_table_class_entry = zend_register_internal_class_ex(ce, NULL);
   zend_hash_init(&php_g_hash_table_prop_handlers, 0, NULL, php_g_hash_table_dtor_prop_handler, 1);
   zend_hash_add_ptr(&classes, ce->name, &php_g_hash_table_prop_handlers);

   return php_g_hash_table_class_entry;
}/*}}} */



// #endif
