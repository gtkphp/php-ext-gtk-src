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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib.h>

#include <php.h>
#include <php_ini.h>
#include <zend_interfaces.h>
#include <ext/standard/info.h>

#include "g-list.h"



extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry    *php_g_list_class_entry;
HashTable            php_g_list_prop_handlers;
zend_object_handlers php_g_list_handlers;

/*----------------------------------------------------------------------+
 | zend_object_handlers                                                 |
 +----------------------------------------------------------------------*/

static void php_g_list_dtor_prop_handler(zval *zv) /* {{{ */
{
    TRACE();
    free(Z_PTR_P(zv));
}

/* {{{ dom_objects_free_storage */
void php_g_list_free_storage(zend_object *object)
{
    TRACE();

    php_g_list *intern = PHP_G_LIST_FROM_STD(object);
#if defined(__GNUC__) && __GNUC__ >= 3
    int retcount __attribute__((unused)); /* keep compiler quiet */
#else
    int retcount;
#endif

    zend_object_std_dtor(&intern->std);// maybe use PHP_STD_FROM_G_HASH_TABLE()
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

zval *php_g_list_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    TRACE();
    php_g_list *obj = PHP_G_LIST_FROM_STD(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    zval *retval = NULL;

    g_print("%s\n", "php_g_list_get_property_ptr_ptr");
    if (!obj->prop_handler || !zend_hash_exists(obj->prop_handler, member_str)) {
        zend_object_handlers *std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->get_property_ptr_ptr(object, member, type, cache_slot);
    }

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ gtk_read_property */
zval *php_g_list_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    TRACE();
    php_g_list *obj = PHP_G_LIST_FROM_STD(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    php_g_list_prop_handler *hnd = NULL;
    g_print("%s(%s)\n", "php_glib_read_property", member->value.str->val);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member_str);
    } else if (instanceof_function(obj->std.ce, php_g_list_class_entry)) {
        php_error(E_WARNING, "Couldn't fetch %s. Widget no longer exists", ZSTR_VAL(obj->std.ce->name));
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
void php_g_list_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    TRACE();
    php_g_list *obj = PHP_G_LIST_FROM_STD(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    php_g_list_prop_handler *hnd = NULL;

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
int php_g_list_read_na(php_g_list *obj, zval *retval)
{
    TRACE();
    zend_throw_error(NULL, "Cannot read property");
    return FAILURE;
}
/* }}} */

/* {{{ dom_write_na */
int php_g_list_write_na(php_g_list *obj, zval *newval)
{
    TRACE();
    zend_throw_error(NULL, "Cannot write property");
    return FAILURE;
}
/* }}} */

static char *php_g_list_tostring_object(zval *obj, char *salt) {
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
php_g_list_get_debug_info_helper(zval *object, int *is_temp) /* {{{ */
{
    TRACE();

    php_g_list *obj =  PHP_G_LIST_FROM_STD(Z_OBJ_P(object));
    HashTable              *debug_info,
                           *prop_handlers = obj->prop_handler,
                           *std_props;
    zend_string            *string_key;
    php_g_list_prop_handler  *entry;
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
#if 0
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
        char *name = php_g_list_tostring_object(key, NULL);
        ZVAL_STRING(&k, name);
        g_free(name);
    } else {
        g_print("Unexpected 21 : php_g_list_get_debug_info_helper\n");
    }
    if (Z_TYPE_P(value)==IS_STRING) {
        ZVAL_COPY(&val, value);
    } else if (Z_TYPE_P(value)==IS_OBJECT ) {
        ZVAL_COPY(&val, value);
    } else {
        g_print("Unexpected 21 : php_g_list_get_debug_info_helper\n");
    }

    //g_print("%s=>%s\n", (char *)k->value.str->val, (char *)val.value.str->val);
    zend_hash_add(debug_info, k.value.str, &val);

  }
#endif
    return debug_info;
}
/* }}} */

HashTable*
php_g_list_get_debug_info(zval *object, int *is_temp)
{
    TRACE();
    return php_g_list_get_debug_info_helper(object, is_temp);
}

static zend_object_handlers*
php_g_list_get_handlers()
{
    TRACE();
    memcpy(&php_g_list_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_g_list_handlers.offset = XtOffsetOf(php_g_list, std);
    php_g_list_handlers.free_obj = php_g_list_free_storage;
    php_g_list_handlers.read_property = php_g_list_read_property;
    php_g_list_handlers.write_property = php_g_list_write_property;
    php_g_list_handlers.get_property_ptr_ptr = php_g_list_get_property_ptr_ptr;
    php_g_list_handlers.get_debug_info = php_g_list_get_debug_info;

/*
php_g_list_handlers.has_dimension;
php_g_list_handlers.read_dimension;
php_g_list_handlers.unset_dimension;
php_g_list_handlers.write_dimension;
*/
    return &php_g_list_handlers;
}


static php_g_list*
php_g_list_set_class(zend_class_entry *class_type,
                           zend_bool hash_copy) /* {{{ */
{
    TRACE();
    php_g_list *intern = ecalloc(1, sizeof(php_g_list) + zend_object_properties_size(class_type));
    zend_class_entry *base_class = class_type;
    while ((   base_class->type != ZEND_INTERNAL_CLASS
            || base_class->info.internal.module->module_number != gtk_module_entry.module_number
           )
           && base_class->parent != NULL) {
        base_class = base_class->parent;
    }

    intern->prop_handler = zend_hash_find_ptr(&classes, base_class->name);

    zend_object_std_init(&intern->std, class_type);

    if (hash_copy) {
        object_properties_init(&intern->std, class_type);
    }

    return intern;
}
/* }}} */

/* {{{ php_glib_create_object */
zend_object *php_g_list_create_object(zend_class_entry *class_type)
{
    TRACE();
    php_g_list *intern = php_g_list_set_class(class_type, 1);
    intern->std.handlers = &php_g_list_handlers;
    return &intern->std;
}
/* }}} */

/*----------------------------------------------------------------------+
 | Implementation                                                       |
 +----------------------------------------------------------------------*/
php_g_list*
php_g_list_append(php_g_list *list, zval *data) {
    // gpointer
    // TODO...
    return NULL;
}



/*----------------------------------------------------------------------+
 | g_list_append                                                        |
 +----------------------------------------------------------------------*/

/* {{{ */
PHP_FUNCTION(g_list_append)
{
    zval *list;
    zval *data;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list);
        Z_PARAM_ZVAL(data);
    ZEND_PARSE_PARAMETERS_END();

    php_g_list *__self = PHP_G_LIST_FROM_STD(list->value.obj);
    php_g_list *__ret = php_g_list_append(__self, data);
    RETURN_OBJECT(&__ret->std);
}
/* }}} */


/*----------------------------------------------------------------------+
 | g_list_prepend                                                       |
 +----------------------------------------------------------------------*/

/* {{{ */
PHP_FUNCTION(g_list_prepend)
{
    zval *list;
    zval *data;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list);
        Z_PARAM_ZVAL(data);
    ZEND_PARSE_PARAMETERS_END();

    php_g_list *__self = PHP_G_LIST_FROM_STD(list->value.obj);
    php_g_list *__ret = php_g_list_prepend(__self, data);
    RETURN_OBJECT(&__ret->std);
}
/* }}} */



/*----------------------------------------------------------------------+
 | Vendor\ExtName\GList::__construct                                    |
 +----------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_list___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

/* {{{ GHashTable::__construct() */
PHP_METHOD(G_List, __construct)
{
    TRACE();
}
/* }}} GHashTable::__construct() */

static const zend_function_entry php_g_list_methods[] = {
    PHP_ME(G_List, __construct, arginfo_g_list___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};


/*{{{ php_g_list_class_init */
zend_class_entry*
php_g_list_class_init(zend_class_entry *ce) {
    php_g_list_get_handlers();
    //INIT_NS_CLASS_ENTRY((*ce), "Gnome\\G", "GList", php_g_list_methods);
    INIT_CLASS_ENTRY((*ce), "GList", php_g_list_methods);
    ce->create_object = php_g_list_create_object;
    php_g_list_class_entry = zend_register_internal_class_ex(ce, NULL);
    zend_hash_init(&php_g_list_prop_handlers, 0, NULL, php_glib_dtor_prop_handler, 1);
    zend_hash_add_ptr(&classes, ce->name, &php_g_list_prop_handlers);

    return php_g_list_class_entry;
}/*}}} */

