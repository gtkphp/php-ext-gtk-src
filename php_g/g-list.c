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

typedef int (*php_g_list_read_t)(php_g_list *obj, zval *retval);
typedef int (*php_g_list_write_t)(php_g_list *obj, zval *newval);

typedef struct _php_g_list_prop_handler {
    php_g_list_read_t read_func;
    php_g_list_write_t write_func;
} php_g_list_prop_handler;

static int          php_g_list_write_na(php_g_list *obj, zval *newval);
static int          php_g_list_read_na(php_g_list *obj, zval *retval);

static void         php_g_list_free_storage(zend_object *object);
static void         php_g_list_dtor_obj(zend_object *obj);
static zend_object *php_g_list_create_object(zend_class_entry *class_type);
static HashTable   *php_g_list_get_debug_info(zval *object, int *is_temp);
static void         php_g_list_write_property(zval *object, zval *member, zval *value, void **cache_slot);
static zval        *php_g_list_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv);
static zval        *php_g_list_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot);
static void         php_g_list_dtor_prop_handler(zval *zv);

static void php_g_list_dtor_prop_handler(zval *zv) /* {{{ */
{
    TRACE();
    free(Z_PTR_P(zv));
}

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

    php_g_list  *obj =  ZVAL_GET_PHP_G_LIST(object);
    HashTable   *debug_info,
                *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    zval prev; ZVAL_COPY(&prev, &obj->prev);
    zend_hash_str_update(debug_info, "prev", 4, &prev);

    zval data; ZVAL_COPY(&data, &obj->data);
    zend_hash_str_update(debug_info, "data", 4, &data);

    zval next; ZVAL_COPY(&next, &obj->next);
    zend_hash_str_update(debug_info, "next", 4, &next);

    return debug_info;
}
/* }}} */

static HashTable*
php_g_list_get_debug_info(zval *object, int *is_temp)
{
    TRACE();
    return php_g_list_get_debug_info_helper(object, is_temp);
}

static int
php_g_list_has_dimension(zval *object, zval *member, int check_empty) {
    TRACE();
    g_print("php_g_list_has_dimension not implemented\n");
    return FAILURE;
    return SUCCESS;
}

static int
php_g_list_cast_object(zval *readobj, zval *retval, int type)
{
    g_print("Type: %d/%d\n", type, IS_ARRAY);
    return FAILURE;//SUCCESS;
}

static void
php_g_list_properties_init(php_g_list *intern)
{
    ZVAL_NULL(&intern->prev);
    ZVAL_NULL(&intern->data);
    ZVAL_NULL(&intern->next);
}

static php_g_list*
php_g_list_set_class(zend_class_entry *class_type,
                           zend_bool hash_copy) /* {{{ */
{
    TRACE();
    php_g_list *intern = ecalloc(1, sizeof(php_g_list) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);

    if (hash_copy) {
        object_properties_init(&intern->std, class_type);
    }
    php_g_list_properties_init(intern);

    intern->ptr = g_list_alloc();

    return intern;
}
/* }}} */

/* {{{ php_glib_create_object */
static zend_object *php_g_list_create_object(zend_class_entry *class_type)
{
    TRACE();
    php_g_list *intern = php_g_list_set_class(class_type, 1);
    intern->std.handlers = &php_g_list_handlers;
    return &intern->std;
}
/* }}} */

static void
php_g_list_element_unref(gpointer data) {
    //GList *list = (GList*) data;

    //g_free(list->data->value);
}


/* {{{ php_hashcontext_dtor */
static void php_g_list_dtor_obj(zend_object *obj) {
    TRACE();
    php_g_list *intern = ZOBJ_GET_PHP_G_LIST(obj);

    Z_TRY_DELREF(intern->prev);
    Z_TRY_DELREF(intern->data);
    Z_TRY_DELREF(intern->next);

}
/* }}} */

/* {{{ dom_objects_free_storage */
static void
php_g_list_free_storage(zend_object *object)
{
    TRACE();

    php_g_list *intern = ZOBJ_GET_PHP_G_LIST(object);
    //g_print("                  GList(%p)\n",  intern->ptr);
    //g_print("php_g_list_free_storage(%p) (Ref: %d)\n", &intern->std, intern->std.gc.refcount);
#if defined(__GNUC__) && __GNUC__ >= 3
    int retcount __attribute__((unused)); /* keep compiler quiet */
#else
    int retcount;
#endif

    zend_object_std_dtor(&intern->std);
    g_list_free_full(intern->ptr, php_g_list_element_unref);
    intern->ptr = NULL;
    efree(intern);
}
/* }}} */

/*----------------------------------------------------------------------+
 | Property handlers ################################################## |
 +----------------------------------------------------------------------*/

static zval *php_g_list_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    TRACE();
    php_g_list *obj = ZOBJ_GET_PHP_G_LIST(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    zval *retval = NULL;

    if (!obj->prop_handler || !zend_hash_exists(obj->prop_handler, member_str)) {
        zend_object_handlers *std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->get_property_ptr_ptr(object, member, type, cache_slot);
    }

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ gtk_read_property */
static zval *php_g_list_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    TRACE();
    php_g_list *obj = ZOBJ_GET_PHP_G_LIST(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    php_g_list_prop_handler *hnd = NULL;
    //g_print("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member_str);
    } else if (instanceof_function(obj->std.ce, php_g_list_class_entry)) {
        php_error(E_WARNING, "Couldn't fetch %s. GList no longer exists", ZSTR_VAL(obj->std.ce->name));
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
static void php_g_list_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    TRACE();
    php_g_list *obj = ZOBJ_GET_PHP_G_LIST(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    php_g_list_prop_handler *hnd = NULL;
    //g_print("%s(%s)\n", __FUNCTION__, member->value.str->val);

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
static int php_g_list_read_na(php_g_list *obj, zval *retval)
{
    TRACE();
    zend_throw_error(NULL, "Cannot read property");
    return FAILURE;
}
/* }}} */

/* {{{ dom_write_na */
static int php_g_list_write_na(php_g_list *obj, zval *newval)
{
    TRACE();
    zend_throw_error(NULL, "Cannot write property");
    return FAILURE;
}
/* }}} */

/* {{{ dom_register_prop_handler */
static void php_g_list_register_prop_handler(HashTable *prop_handler, char *name, size_t name_len, php_g_list_read_t read_func, php_g_list_write_t write_func)
{
    php_g_list_prop_handler hnd;

    hnd.read_func = read_func ? read_func : php_g_list_read_na;
    hnd.write_func = write_func ? write_func : php_g_list_write_na;
    zend_hash_str_add_mem(prop_handler, name, name_len, &hnd, sizeof(php_g_list_prop_handler));

}
/* }}} */

static int php_g_list_read_prev(php_g_list *obj, zval *retval) {
    ZVAL_COPY(retval, &obj->prev);
    return SUCCESS;
}
static int php_g_list_write_prev(php_g_list *obj, zval *newval) {
    if (Z_TYPE_P(newval)==IS_OBJECT && ZVAL_IS_PHP_G_LIST(newval)) {
        ZVAL_OBJ(&obj->prev, newval->value.obj);
        return SUCCESS;
    }
    if (ZVAL_IS_NULL(newval)) {
        ZVAL_NULL(&obj->prev);
        return SUCCESS;
    }
    zend_throw_error(NULL, "Invalid argument supplied for GList->prev");

    return FAILURE;
}

static int php_g_list_read_data(php_g_list *obj, zval *retval) {
    ZVAL_COPY(retval, &obj->data);
    return SUCCESS;
}
static int php_g_list_write_data(php_g_list *obj, zval *newval) {
    ZVAL_COPY(&obj->data, newval);
    return SUCCESS;
}

static int php_g_list_read_next(php_g_list *obj, zval *retval) {
    ZVAL_COPY(retval, &obj->next);
    return SUCCESS;
}
static int php_g_list_write_next(php_g_list *obj, zval *newval) {
    if (ZVAL_IS_NULL(newval)) {
        ZVAL_NULL(&obj->next);
        //FIX unref old obj->next
        return SUCCESS;
    }
    if (ZVAL_IS_PHP_G_LIST(newval)) {
        //FIX unref old obj->next
        ZVAL_OBJ(&obj->next, newval->value.obj);
        return SUCCESS;
    }
    zend_throw_error(NULL, "Invalid argument supplied for GList::$next");

    return FAILURE;
}

/*----------------------------------------------------------------------+
 | Implementation                                                       |
 +----------------------------------------------------------------------*/

static php_g_list*
php_g_list_last(php_g_list *node) {
    php_g_list *last = node;
    php_g_list *list = node;
    while(list){
        last = list;
        if (ZVAL_IS_PHP_G_LIST(&list->next)) {
            list = ZVAL_GET_PHP_G_LIST(&list->next);
        } else {
            list = NULL;
        }
    }

    return last;
}

static php_g_list*
php_g_list_first(php_g_list *node) {
    php_g_list *first = node;
    php_g_list *prev = node;
    while(prev){
        //g_print("Loop\n");
        first = prev;
        if (ZVAL_IS_PHP_G_LIST(&prev->prev)) {// maybe is preferable check if ZVAL_IS_NULL
            prev = ZVAL_GET_PHP_G_LIST(&prev->prev);
        } else {
            prev = NULL;
        }
    }

    return first;
}

php_g_list*
php_g_list_append(php_g_list *list, zval *data) {

    php_g_list *php_last_node = NULL;
    php_g_list *php_first_node = NULL;

    if (list!=NULL) {
        php_last_node = php_g_list_last(list);
        php_first_node = php_g_list_first(list);
    }

    zend_object *std_new_node = php_g_list_create_object(php_g_list_class_entry);// Ref: 1
    php_g_list *php_new_node = ZOBJ_GET_PHP_G_LIST(std_new_node);
    ZVAL_COPY(&php_new_node->data, data);
    //Z_TRY_ADDREF(php_new_node->data);

    if(php_last_node) {// has previous
        ZVAL_OBJ(&php_last_node->next, &php_new_node->std);
        Z_TRY_ADDREF(php_last_node->next);
        ZVAL_OBJ(&php_new_node->prev, &php_last_node->std);
        Z_TRY_ADDREF(php_last_node->prev);
    }

    return php_first_node != NULL ? php_first_node : php_new_node;
}

php_g_list*
php_g_list_prepend(php_g_list *list, zval *data) {
    php_g_list *php_first_node = NULL;

    if (list!=NULL) {
        php_first_node = php_g_list_first(list);
    }

    zend_object *std_new_node = php_g_list_create_object(php_g_list_class_entry);// Ref: 1
    php_g_list *php_new_node = ZOBJ_GET_PHP_G_LIST(std_new_node);
    ZVAL_COPY(&php_new_node->data, data);
    //Z_TRY_ADDREF(php_new_node->data);

    if(php_first_node) {// has previous
        ZVAL_OBJ(&php_first_node->prev, &php_new_node->std);
        Z_TRY_ADDREF(php_first_node->prev);
        ZVAL_OBJ(&php_new_node->next, &php_first_node->std);
        Z_TRY_ADDREF(php_new_node->next);
    }

    return php_new_node;
}



/*----------------------------------------------------------------------+
 | g_list_append                                                        |
 +----------------------------------------------------------------------*/


/* {{{ */
PHP_FUNCTION(g_list_append)
{
    zval *list;
    zval *data;
    zval ret;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();


    php_g_list *__list = ZVAL_IS_PHP_G_LIST(list)? ZVAL_GET_PHP_G_LIST(list): NULL;
    php_g_list *__ret = php_g_list_append(__list, data);

    ZVAL_OBJ(&ret, &__ret->std);
    RETURN_ZVAL(&ret, 1, 0);
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
    zval ret;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list);
        Z_PARAM_ZVAL(data);
    ZEND_PARSE_PARAMETERS_END();

    php_g_list *__list = ZVAL_IS_PHP_G_LIST(list)? ZVAL_GET_PHP_G_LIST(list): NULL;
    php_g_list *__ret = php_g_list_prepend(__list, data);

    ZVAL_OBJ(&ret, &__ret->std);
    RETURN_ZVAL(&ret, 1, 0);
}
/* }}} */


/*----------------------------------------------------------------------+
 | Vendor\ExtName\GList::__construct                                    |
 +----------------------------------------------------------------------*/

/* {{{ GList::__construct() */
PHP_METHOD(G_List, __construct)
{
    TRACE();
    zval *data=NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    zend_object *zobj = Z_OBJ_P(getThis());
    php_g_list *self = ZOBJ_GET_PHP_G_LIST(zobj);

    if (data!=NULL) {
        ZVAL_COPY(&self->data, data);
        //Z_TRY_ADDREF(self->data);
    }

}
/* }}} GHashTable::__construct() */

static const zend_function_entry php_g_list_methods[] = {
    PHP_ME(G_List, __construct, arginfo_g_list___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};


/*----------------------------------------------------------------------+
 | Register                                                             |
 +----------------------------------------------------------------------*/

static zend_object_handlers*
php_g_list_get_handlers()
{
    TRACE();
    memcpy(&php_g_list_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_g_list_handlers.offset = XtOffsetOf(php_g_list, std);
    //php_g_list_handlers.clone_obj;
    php_g_list_handlers.cast_object = php_g_list_cast_object;
    //php_g_list_handlers.compare;
    //php_g_list_handlers.compare_objects;
    //php_g_list_handlers.get_constructor;
    php_g_list_handlers.dtor_obj = php_g_list_dtor_obj;
    php_g_list_handlers.free_obj = php_g_list_free_storage;
    php_g_list_handlers.read_property = php_g_list_read_property;
    php_g_list_handlers.write_property = php_g_list_write_property;
    php_g_list_handlers.get_property_ptr_ptr = php_g_list_get_property_ptr_ptr;
    php_g_list_handlers.get_debug_info = php_g_list_get_debug_info;


    php_g_list_handlers.has_dimension = php_g_list_has_dimension;
/*
php_g_list_handlers.read_dimension;
php_g_list_handlers.unset_dimension;
php_g_list_handlers.write_dimension;
*/
    return &php_g_list_handlers;
}

/*{{{ php_g_list_class_init */
zend_class_entry*
php_g_list_class_init(zend_class_entry *ce) {
    php_g_list_get_handlers();
    //INIT_NS_CLASS_ENTRY((*ce), "Gnome\\G", "GList", php_g_list_methods);
    INIT_CLASS_ENTRY((*ce), "GList", php_g_list_methods);
    ce->create_object = php_g_list_create_object;
    //ce->serialize;
    php_g_list_class_entry = zend_register_internal_class_ex(ce, NULL);
    zend_hash_init(&php_g_list_prop_handlers, 0, NULL, php_g_list_dtor_prop_handler, 1);
    php_g_list_register_prop_handler(&php_g_list_prop_handlers, "prev", sizeof("prev")-1, php_g_list_read_prev, php_g_list_write_prev);
    php_g_list_register_prop_handler(&php_g_list_prop_handlers, "data", sizeof("data")-1, php_g_list_read_data, php_g_list_write_data);
    php_g_list_register_prop_handler(&php_g_list_prop_handlers, "next", sizeof("next")-1, php_g_list_read_next, php_g_list_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_g_list_prop_handlers);

    return php_g_list_class_entry;
}/*}}} */

