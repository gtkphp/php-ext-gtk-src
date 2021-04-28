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

#include <glib.h>
#include "php_gtk.h"
/*#include <glib-object.h>
#include <gtk/gtk.h>
#include <gmodule.h>
#include <gdk/gdk.h>
#include <ctype.h>*/

#include "hash-table.h"


extern HashTable classes;
extern zend_class_entry *php_glib_class_entry;
//extern zend_object_handlers php_glib_handlers;
extern zend_module_entry gtk_module_entry;

zend_class_entry *php_glib_hash_table_class_entry;
//HashTable php_glib_hash_table_prop_handlers;
zend_object_handlers php_glib_hash_table_handlers;

#define TRACE()

/*----------------------------------------------------------------------+
 | Zend Internals                                                       |
 +----------------------------------------------------------------------*/

/**
 * GHashTable's functions calls callbacks that need to know which instance it's
 */
static php_glib_hash_table *current_hash_table = NULL;

static void php_glib_hash_table_dtor_prop_handler(zval *zv) /* {{{ */
{
    TRACE();
    free(Z_PTR_P(zv));
}

/* {{{ dom_objects_free_storage */
void php_glib_hash_table_free_storage(zend_object *object)
{
    TRACE();

    php_glib_hash_table *intern = ZOBJ_TO_PHP_GLIB_HASH_TABLE(object);

    current_hash_table = intern;
    g_hash_table_unref((GHashTable*)intern->ptr);
    current_hash_table = NULL;

    zend_object_std_dtor(&intern->std);// maybe use PHP_STD_FROM_G_HASH_TABLE()
    //efree(intern);
}
/* }}} */


/* {{{ gtk_read_property */
zval *php_glib_hash_table_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    TRACE();
    php_glib_hash_table *intern = ZVAL_GET_PHP_GLIB_HASH_TABLE(object);
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    //TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    /*
    if (zend_string_equals_literal(member_str, "next")) {
        if (NULL==intern->next) {
            ZVAL_NULL(&zval_ret);
            return &zval_ret;
        }
        ZVAL_OBJ(&zval_ret, &intern->next->std);
        return &zval_ret;
    }
    if (zend_string_equals_literal(member_str, "prev")) {
        if (NULL==intern->prev) {
            ZVAL_NULL(&zval_ret);
            return &zval_ret;
        }
        ZVAL_OBJ(&zval_ret, &intern->prev->std);
        return &zval_ret;
    }
    if (zend_string_equals_literal(member_str, "data")) {
        ZVAL_COPY(&zval_ret, &intern->data);
        return &zval_ret;
    }
    */

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    retval = std_hnd->read_property(object, member, type, cache_slot, rv);

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ gtk_write_property */
void php_glib_hash_table_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    TRACE();
    php_glib_hash_table *intern = ZVAL_GET_PHP_GLIB_HASH_TABLE(object);
    zend_string *member_str = zval_get_string(member);

    if (zend_string_equals_literal(member->value.str, "next")
     || zend_string_equals_literal(member->value.str, "prev")
     || zend_string_equals_literal(member->value.str, "data") ) {
#if 0
        if (ZVAL_IS_php_glib_hash_table(value)) {
            // do unset(object->next) and php_glib_hash_table_insert(object, value, 0);
        } else {
            zend_string *type = zend_zval_get_type(value);
            zend_error(E_USER_WARNING, "Cannot assign %s to property GList::$next of type GList", type->val);
        }
#else
        zend_error(E_USER_WARNING, "Readonly property GList::$%s", member->value.str->val);
#endif
        return;
    }
    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->write_property(object, member, value, cache_slot);

    zend_string_release(member_str);
}
/* }}} */



/* {{{ dom_read_na */
int php_glib_hash_table_read_na(php_glib_hash_table *obj, zval *retval)
{
    TRACE();
    zend_throw_error(NULL, "Cannot read property");
    return FAILURE;
}
/* }}} */

/* {{{ dom_write_na */
int php_glib_hash_table_write_na(php_glib_hash_table *obj, zval *newval)
{
    TRACE();
    zend_throw_error(NULL, "Cannot write property");
    return FAILURE;
}
/* }}} */

static char *php_glib_hash_table_tostring_object(zval *obj, char *salt) {
    TRACE();
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
php_glib_hash_table_get_debug_info_helper(zval *object, int *is_temp) /* {{{ */
{
    TRACE();

    php_glib_hash_table *intern =  ZVAL_GET_PHP_GLIB_HASH_TABLE(object);
    HashTable   *debug_info,
                *std_props;
    zend_string *string_key = NULL;
    zval *value;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    ZEND_HASH_FOREACH_STR_KEY_VAL(intern->std.properties, string_key, value) {
        zend_hash_add(debug_info, string_key, value);
    } ZEND_HASH_FOREACH_END();

    //g_print("-zend_object %p\n", Z_OBJCE_P(object));
    //g_print("-intern_object %p\n", obj);

GHashTableIter iter;
zval *key;
zval val;
zend_string *str_key;

g_hash_table_iter_init (&iter, intern->ptr);
while (g_hash_table_iter_next (&iter, (gpointer)&key, (gpointer)&value))
  {
    zval k;
    //g_print("g_hash_table_iter(%p, %p)\n", key, value);
    //str_key = zend_string_init((char*)key, strlen((char*)key), 0);
    if (Z_TYPE_P(key)==IS_STRING) {
        //k = (zval *)key;
        ZVAL_COPY(&k, key);
    } else if (Z_TYPE_P(key)==IS_OBJECT ) {
        char *name = php_glib_hash_table_tostring_object(key, NULL);
        ZVAL_STRING(&k, name);
        g_free(name);
    } else {
        g_print("Unexpected 21 : php_glib_hash_table_get_debug_info_helper\n");
    }

    //g_print("%s=>%s\n", (char *)k->value.str->val, (char *)val.value.str->val);
    zend_hash_add(debug_info, k.value.str, value);
    Z_TRY_DELREF(k);
    Z_TRY_ADDREF_P(value);

  }
    return debug_info;
}
/* }}} */

HashTable*
php_glib_hash_table_get_debug_info(zval *object, int *is_temp)
{
    TRACE();
    return php_glib_hash_table_get_debug_info_helper(object, is_temp);
}


static int
php_glib_hash_table_has_dimension(zval *object, zval *member, int check_empty)
{
    TRACE();
    zend_long offset = zval_get_long(member);
    zval rv;

    if (offset < 0) {
        return 0;
    } else {
        //zval *length = zend_read_property(Z_OBJCE_P(object), object, "length", sizeof("length") - 1, 0, &rv);

        //return length && offset < Z_LVAL_P(length);
        php_glib_hash_table *intern = ZVAL_GET_PHP_GLIB_HASH_TABLE(object);
        GHashTable *hash_table = intern->ptr;
        guint size = g_hash_table_size(hash_table);
        return size>0;
    }
} /* }}} end php_glib_hash_table_has_dimension */


static zval*
php_glib_hash_table_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    TRACE();
    zval offset_copy;
    if (!offset) {
        return NULL;
    }


    //ZVAL_LONG(&offset_copy, zval_get_long(offset));
    php_glib_hash_table *intern = ZVAL_GET_PHP_GLIB_HASH_TABLE(object);
    GHashTable *hash_table = intern->ptr;
    zval *value = NULL;
    if (hash_table!=NULL) {
        current_hash_table = intern;
        value = g_hash_table_lookup(hash_table, (gconstpointer)offset);
        current_hash_table = NULL;
    }

    return value;
} /* }}} end php_glib_hash_table_read_dimension */


static zend_object_handlers*
php_glib_hash_table_get_handlers()
{
    TRACE();
    memcpy(&php_glib_hash_table_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_glib_hash_table_handlers.offset = PHP_GLIB_HASH_TABLE_OFFSET;
    php_glib_hash_table_handlers.free_obj = php_glib_hash_table_free_storage;
    php_glib_hash_table_handlers.read_property = php_glib_hash_table_read_property;
    php_glib_hash_table_handlers.write_property = php_glib_hash_table_write_property;
    //php_glib_hash_table_handlers.get_property_ptr_ptr = php_glib_hash_table_get_property_ptr_ptr;
    php_glib_hash_table_handlers.get_debug_info = php_glib_hash_table_get_debug_info;

    php_glib_hash_table_handlers.has_dimension = php_glib_hash_table_has_dimension;
    php_glib_hash_table_handlers.read_dimension = php_glib_hash_table_read_dimension;

/*
    php_glib_hash_table_handlers.unset_dimension;
    php_glib_hash_table_handlers.write_dimension;
    php_glib_hash_table_handlers.count_elements;
*/
    return &php_glib_hash_table_handlers;
}

/*----------------------------------------------------------------------+
 | Internals                                                            |
 +----------------------------------------------------------------------*/

/* {{{ php_glib_create_object */
zend_object *php_glib_hash_table_create_object(zend_class_entry *class_type)
{
    TRACE();
    php_glib_hash_table *intern = ecalloc(1, sizeof(php_glib_hash_table) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    //g_print("php_glib_hash_table_create_object\n");

    //php_glib_hash_table_properties_init(intern);
    ZVAL_NULL(&intern->hash_func);
    ZVAL_NULL(&intern->key_equal_func);

    intern->ptr = NULL;// new GList ?
    intern->properties = NULL;

    intern->std.handlers = &php_glib_hash_table_handlers;

    //TRACE("php_glib_hash_table_create_object(%p) / %d\n", &intern->std, intern->std.gc.refcount);
    return &intern->std;

}
/* }}} */


static guint
php_glib_hash_table_hash_func(gconstpointer v) {
    TRACE();
    zval *hash_func = &current_hash_table->hash_func;
    zval *val = (zval *)v;
    if (ZVAL_IS_NULL(hash_func)) {
        if (Z_TYPE_P(val)==IS_STRING) {
            guint hash = g_str_hash(val->value.str->val);
            return hash;
        } else if (Z_TYPE_P(val)==IS_OBJECT ) {
            char *name = php_glib_hash_table_tostring_object(val, NULL);
            guint hash = g_str_hash(name);
            g_free(name);
            return hash;
        } else {
            g_print("Unexpected 21 : php_glib_hash_table_hash_func\n");
        }
    } else {
        int result;
        int param_count = 1;
        zval retval;
        zval params[1];
        if (Z_TYPE_P(val)==IS_STRING) {
            ZVAL_COPY(&params[0], val);
        } else if (Z_TYPE_P(val)==IS_OBJECT) {
            char *name = php_glib_hash_table_tostring_object(val, NULL);
            ZVAL_STRING(&params[0], name);
            g_free(name);
        }
        //g_print("!!!%p\n", hash_func);
        //g_print("%d\n", Z_TYPE_P(hash_func));
        result = call_user_function(NULL, NULL, hash_func, &retval, param_count, params);
        if (result==FAILURE) {
            g_print("Unexpected 22 : php_glib_hash_table_hash_func\n");
        } else if (Z_TYPE(retval)==IS_LONG) {
            return retval.value.lval;
        } else {
            g_print("Unexpected 23 : php_glib_hash_table_hash_func\n");
        }
    }
    g_print("Unexpected 22 : php_glib_hash_table_hash_func\n");
    // zend call function
    return 0;
}

static gboolean
php_glib_hash_table_key_equal_func(gconstpointer v1, gconstpointer v2) {
    TRACE();
    zval *key_equal_func = &current_hash_table->key_equal_func;
    zval *val1 = (zval *)v1;
    zval *val2 = (zval *)v2;
    if (ZVAL_IS_NULL(key_equal_func)) {
        if (Z_TYPE_P(val1)==IS_STRING && Z_TYPE_P(val2)==IS_STRING) {
            return g_str_equal(val1->value.str->val, val2->value.str->val);
        } else if (Z_TYPE_P(val1)==IS_OBJECT && Z_TYPE_P(val2)==IS_OBJECT) {
            char *name1 = php_glib_hash_table_tostring_object(val1, NULL);
            char *name2 = php_glib_hash_table_tostring_object(val2, NULL);
            gboolean equal = g_str_equal(name1, name2);
            g_free(name1);
            g_free(name2);
            return equal;
        } else {
            g_print("Unexpected 12 : php_glib_hash_table_key_equal_func\n");
        }
    } else {
        int result;
        int param_count = 2;
        zval retval;
        zval params[2];
        if (Z_TYPE_P(val1)==IS_STRING) {
            ZVAL_COPY_VALUE(&params[0], val1);
        } else if (Z_TYPE_P(val1)==IS_OBJECT) {
            char *name = php_glib_hash_table_tostring_object(val1, NULL);
            ZVAL_STRING(&params[0], name);
            g_free(name);
        }
        if (Z_TYPE_P(val2)==IS_STRING) {
            ZVAL_COPY_VALUE(&params[1], val2);
        } else if (Z_TYPE_P(val2)==IS_OBJECT) {
            char *name = php_glib_hash_table_tostring_object(val2, NULL);
            ZVAL_STRING(&params[1], name);
            g_free(name);
        }
        result = call_user_function(NULL, NULL, key_equal_func, &retval, param_count, params);
        // check result== FAILURE
        if (result==FAILURE) {
            g_print("Unexpected 14 : php_glib_hash_table_key_equal_func\n");
        } else if (Z_TYPE(retval)==IS_TRUE) {
            return TRUE;
        } else if (Z_TYPE(retval)==IS_FALSE) {
            return FALSE;
        } else {
            g_print("Unexpected 13 : php_glib_hash_table_key_equal_func\n");
        }
    }
    // zend call function
    return TRUE;
}

static zval *php_glib_hash_table_key_destroy = NULL;
static void
php_glib_hash_table_key_destroy_func(gpointer data)
{
    TRACE();
    zval *val = (zval*)data;
    /*
    g_print("php_glib_hash_table_key_destroy_func\n");
    g_print("    %p\n", data);
    g_print("          IS_OBJECT ? %d\n", Z_TYPE_P(val)==IS_OBJECT);
    g_print("          %s\n", val->value.obj->ce->name->val);
    g_print("          %p\n", val->value.obj);
    g_print("          ? %d\n", Z_TYPE_FLAGS(*val) & IS_TYPE_REFCOUNTED);
    g_print("          refcount:%d\n", val->value.obj->gc.refcount);
    */


    php_glib_hash_table_key_destroy = data;
    Z_TRY_DELREF_P(val);
    efree(val);
}

static void
php_glib_hash_table_value_destroy_func(gpointer data)
{
    TRACE();
    //g_print("php_glib_hash_table_value_destroy_func\n");
    //g_print("    %p\n", data);
    //zval *val = (zval*)data;
    //Z_TRY_DELREF(*val);
    // add ref in php_glib_hash_table_add
    if (php_glib_hash_table_key_destroy==data) {
        //g_print("    value as key\n");
    }
    //Z_TRY_DELREF_P(val);

    php_glib_hash_table_key_destroy = NULL;
}

php_glib_hash_table*
php_glib_hash_table_new(zval *hash_func, zval *key_equal_func)
{
    TRACE();
    zend_object *object = php_glib_hash_table_create_object(php_glib_hash_table_class_entry);
    php_glib_hash_table *hash_table = ZOBJ_TO_PHP_GLIB_HASH_TABLE(object);


    /*obj->ptr = g_hash_table_new(php_glib_hash_table_hash_func,
                                php_glib_hash_table_key_equal_func);*/
    hash_table->ptr = g_hash_table_new_full(php_glib_hash_table_hash_func,
                                            php_glib_hash_table_key_equal_func,
                                            php_glib_hash_table_key_destroy_func,
                                            php_glib_hash_table_value_destroy_func);

    if (hash_func && ! ZVAL_IS_NULL(hash_func)) {
        ZVAL_COPY(&hash_table->hash_func, hash_func);
    } else {
        //hash_table->hash_func = NULL;
    }
    if (key_equal_func && ! ZVAL_IS_NULL(key_equal_func)) {
        ZVAL_COPY(&hash_table->key_equal_func, key_equal_func);
    } else {
        //hash_table->key_equal_func = NULL;
    }

    return hash_table;
}

zend_bool
php_glib_hash_table_add(php_glib_hash_table *hash_table, zval *key)
{
    TRACE();
    GHashTable *hash = hash_table->ptr;

    zval *k = emalloc(sizeof(zval));
    ZVAL_COPY(k, key);

    current_hash_table = hash_table;
    gboolean retval = g_hash_table_add(hash, k);
    current_hash_table = NULL;

    return (zend_bool)retval;
}

zend_bool
php_glib_hash_table_insert(php_glib_hash_table *hash_table, zval *key, zval *value)
{
    TRACE();
    GHashTable *hash = hash_table->ptr;

    zval *k = emalloc(sizeof(zval));
    ZVAL_COPY(k, key);
    zval *v = emalloc(sizeof(zval));
    ZVAL_COPY(v, value);

    current_hash_table = hash_table;
    zend_bool retval = g_hash_table_insert(hash, k, v);
    current_hash_table = NULL;

    return retval;
}




/*----------------------------------------------------------------------+
 | Vendor\ExtName\g_str_equal                                           |
 +----------------------------------------------------------------------*/
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
 | Vendor\ExtName\g_str_hash                                         |
 +----------------------------------------------------------------------*/
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
 | Vendor\ExtName\g_hash_table_insert                                   |
 +----------------------------------------------------------------------*/
PHP_FUNCTION(g_hash_table_insert)
{
    zval *hash_table;
    zval *key;
    zval *value;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ozz", &hash_table, &key, &value) == FAILURE) {
        return;
    }
    php_glib_hash_table *obj = ZVAL_GET_PHP_GLIB_HASH_TABLE(hash_table);
    zend_bool ret = php_glib_hash_table_insert(obj, key, value);
    RETURN_BOOL(ret);
}

/*----------------------------------------------------------------------+
 | Vendor\ExtName\g_hash_table_add                                      |
 +----------------------------------------------------------------------*/
/* {{{ */
PHP_FUNCTION(g_hash_table_add)
{
    zval *hash_table;
    zval *key;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(hash_table);
        Z_PARAM_ZVAL(key);
    ZEND_PARSE_PARAMETERS_END();

    php_glib_hash_table *__self = ZVAL_GET_PHP_GLIB_HASH_TABLE(hash_table);
    zend_bool __ret = php_glib_hash_table_add(__self, key);

    //Z_TRY_DELREF(*hash_table);
    //Z_TRY_DELREF(*key);
    RETURN_BOOL(__ret);
}
/* }}} */

/*----------------------------------------------------------------------+
 | Vendor\ExtName\g_hash_table_new                                      |
 +----------------------------------------------------------------------*/
PHP_FUNCTION(g_hash_table_new)
{
    zval *hash_func = NULL;
    zval *key_equal_func = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|zz", &hash_func, &key_equal_func) == FAILURE) {
        return;
    }
    php_glib_hash_table *intern = php_glib_hash_table_new(hash_func, key_equal_func);

    RETURN_OBJ(&intern->std);
}

/*----------------------------------------------------------------------+
 | Vendor\ExtName\GHashTable::__construct                               |
 +----------------------------------------------------------------------*/

/* {{{ GHashTable::__construct() */
PHP_METHOD(g_hash_table, __construct)
{
    TRACE();
}
/* }}} GHashTable::__construct() */

static const zend_function_entry php_glib_hash_table_methods[] = {
    PHP_ME(g_hash_table, __construct, arginfo_g_hash_table___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};




/*{{{ juste pour var_dump(zval) ou zval est un php_glib_hash_table->php_glib_object */
zend_class_entry*
php_glib_hash_table_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
   php_glib_hash_table_get_handlers();
   PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "GHashTable", php_glib_hash_table_methods);
   php_glib_hash_table_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
   php_glib_hash_table_class_entry->create_object = php_glib_hash_table_create_object;
   /*
   zend_hash_init(&php_glib_hash_table_prop_handlers, 0, NULL, php_glib_hash_table_dtor_prop_handler, 1);
   zend_hash_add_ptr(&classes, container_ce->name, &php_glib_hash_table_prop_handlers);
   */

   return php_glib_hash_table_class_entry;
}/*}}} */



// #endif
