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


zend_class_entry     *php_g_list_class_entry;
HashTable             php_g_list_prop_handlers;
zend_object_handlers  php_g_list_handlers;

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

static zend_object *php_g_list_create_object(zend_class_entry *class_type);
static void         php_g_list_dtor_obj(zend_object *obj);
static void         php_g_list_free_storage(zend_object *object);
static HashTable   *php_g_list_get_debug_info(zval *object, int *is_temp);
static void         php_g_list_write_property(zval *object, zval *member, zval *value, void **cache_slot);
static zval        *php_g_list_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv);
static void         php_g_list_unset_property(zval *object, zval *member, void **cache_slot);
static zval        *php_g_list_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot);
static void         php_g_list_dtor_prop_handler(zval *zv);
static void         php_g_list_unset_dimension(zval *object, zval *offset);


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
static HashTable*
php_g_list_get_properties(zval *object){
    php_g_list *self = ZVAL_GET_PHP_G_LIST(object);
    HashTable *props = self->array_properties;
    if (props==NULL) {
        ALLOC_HASHTABLE(self->array_properties);
        props = self->array_properties;
    } else {
        // TODO: rebuild the props( update)
        return props;// Else leaks : zend_hash_next_index_insert
    }

    zend_long length = php_g_list_length(self);

    zend_hash_init(props, length, NULL, ZVAL_PTR_DTOR, 1);

    zval data;

    php_g_list *it;
    for(it=php_g_list_first(self); it; it = ZVAL_GET_PHP_G_LIST(&it->next)){
        ZVAL_COPY(&data, &it->data);
        zend_hash_next_index_insert(props, &data);
    }

    return props;
}

/* updates *count to hold the number of elements present and returns SUCCESS.
 * Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_g_list_count_elements(zval *object, zend_long *count) {
    g_print("%s\n", __FUNCTION__);

    *count = php_g_list_length(ZVAL_GET_PHP_G_LIST(object));

    return SUCCESS;
}

static int
php_g_list_has_dimension(zval *object, zval *member, int check_empty) {
    TRACE();
    g_print("php_g_list_has_dimension not implemented\n");
    //return FAILURE;
    return SUCCESS;
}


static zval*
php_g_list_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    TRACE();
    if (!offset) {
        return NULL;
    }

    php_g_list *intern = ZVAL_GET_PHP_G_LIST(object);
    php_g_list *list;
    void *cache=NULL;

    if (Z_TYPE_P(offset)==IS_LONG) {
        list = php_g_list_nth(intern, offset->value.lval);
        if (list) {
            ZVAL_COPY(rv, &list->data);
        } else {
            ZVAL_NULL(rv);
        }
        return rv;
    } else if (Z_TYPE_P(offset)==IS_STRING) {
        return php_g_list_read_property(object, offset, type, &cache, rv);
    } else {
        // error
    }

    return rv;
} /* }}} end php_g_hash_table_read_dimension */

static void
php_g_list_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_g_list_write_property(object, &member, value, &cache);
}

static void
php_g_list_unset_dimension(zval *object, zval *offset) {
    php_g_list *list = ZVAL_GET_PHP_G_LIST(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
        //zend_hash_index_del(list->prop_handler, );
        // php_g_list
        break;
    case IS_STRING:
        php_g_list_unset_property(object, offset, &cache);
        break;
    default:
        break;
    }
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
    intern->properties = &php_g_list_prop_handlers;
    intern->array_properties = NULL;
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
    php_g_list *intern = ZOBJ_TO_PHP_G_LIST(obj);
    //g_print("php_g_list_dtor_obj(%p) (Ref: %d)\n", &intern->std, intern->std.gc.refcount);

    if(!ZVAL_IS_NULL(&intern->prev))
        zend_object_release(intern->prev.value.obj);
    if(!ZVAL_IS_NULL(&intern->next))
        zend_object_release(intern->next.value.obj);
    //if(!ZVAL_IS_NULL(&intern->data))
    Z_TRY_DELREF(intern->data);

}
/* }}} */

/* {{{ dom_objects_free_storage */
static void
php_g_list_free_storage(zend_object *object)
{
    TRACE();

    php_g_list *intern = ZOBJ_TO_PHP_G_LIST(object);
    //g_print("                  GList(%p)\n",  intern->ptr);
    //g_print("php_g_list_free_storage(%p) (Ref: %d)\n", &intern->std, intern->std.gc.refcount);

    g_list_free_full(intern->ptr, php_g_list_element_unref);
    intern->ptr = NULL;
    if (intern->array_properties!=NULL) {
        zend_hash_destroy(intern->array_properties);
        efree(intern->array_properties);
        intern->array_properties=NULL;
    }

    zend_object_std_dtor(&intern->std);
    //efree(intern);
}
/* }}} */

/*----------------------------------------------------------------------+
 | Property handlers ################################################## |
 +----------------------------------------------------------------------*/

static zval *php_g_list_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    TRACE();
    php_g_list *obj = ZOBJ_TO_PHP_G_LIST(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    zval *retval = NULL;
    g_print("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (!obj->properties || !zend_hash_exists(obj->properties, member_str)) {
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
    php_g_list *obj = ZOBJ_TO_PHP_G_LIST(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    php_g_list_prop_handler *hnd = NULL;
    g_print("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (obj->properties != NULL) {
        hnd = zend_hash_find_ptr(obj->properties, member_str);
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
    php_g_list *obj = ZOBJ_TO_PHP_G_LIST(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    php_g_list_prop_handler *hnd = NULL;
    g_print("%s(%s)\n", __FUNCTION__, member->value.str->val);

    /*if (strcmp("Foo", member->value.str->val)==0 ) {
        g_print("Hello World\n");
    }*/


    if (obj->properties != NULL) {
        hnd = zend_hash_find_ptr(obj->properties, member_str);
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

static void
php_g_list_unset_property(zval *object, zval *member, void **cache_slot) {
    TRACE();
    php_g_list *obj = ZVAL_GET_PHP_G_LIST(object);
    zend_string *member_str = zval_get_string(member);
    php_g_list_prop_handler *hnd = NULL;

    if (obj->properties != NULL) {
        hnd = zend_hash_find_ptr(obj->properties, member_str);
    }
    if (hnd) {
        zend_error(E_NOTICE, "Forbidden to delete GList::$%s", member_str->val);
    } else {
        zend_object_handlers *std_hnd = zend_get_std_object_handlers();
        std_hnd->unset_property(object, member, cache_slot);
    }

    zend_string_release(member_str);
}

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
        ZVAL_COPY(&obj->prev, newval);
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
        ZVAL_COPY(&obj->next, newval);
        return SUCCESS;
    }
    zend_throw_error(NULL, "Invalid argument supplied for GList::$next");

    return FAILURE;
}

/*----------------------------------------------------------------------+
 | Implementation                                                       |
 +----------------------------------------------------------------------*/

php_g_list*
php_g_list_append(php_g_list *list, zval *data) {

    php_g_list *php_last_node = NULL;


    zend_object *std_new_node = php_g_list_create_object(php_g_list_class_entry);// Ref: 1
    php_g_list *php_new_node = ZOBJ_TO_PHP_G_LIST(std_new_node);
    ZVAL_COPY(&php_new_node->data, data);
    //Z_TRY_ADDREF(php_new_node->data);
    //php_new_node->std.gc.refcount++;

    if (list==NULL) {
        return php_new_node;
    }

    php_last_node = php_g_list_last(list);

    GC_REFCOUNT(&php_last_node->std)++;
    ZVAL_OBJ(&php_last_node->next, &php_new_node->std);
    ZVAL_OBJ(&php_new_node->prev, &php_last_node->std);
    //Z_TRY_ADDREF(php_last_node->prev);

    GC_REFCOUNT(&list->std)++;
    return list;
}

php_g_list*
php_g_list_prepend(php_g_list *list, zval *data) {

    zend_object *std_new_node = php_g_list_create_object(php_g_list_class_entry);
    php_g_list *php_new_node = ZOBJ_TO_PHP_G_LIST(std_new_node);
    ZVAL_COPY(&php_new_node->data, data);
    //Z_TRY_ADDREF(php_new_node->data); transfer full


    if(!list) {
        return php_new_node;
    }

    if (ZVAL_IS_NULL(&list->prev)) {// head of list
        ZVAL_OBJ(&list->prev, &php_new_node->std);// #1
        //Z_TRY_ADDREF(list->prev);//                  #2
        ZVAL_OBJ(&php_new_node->next, &list->std);// #3
        //Z_TRY_ADDREF(php_new_node->next);
        GC_REFCOUNT(&list->std)++;
    } else {
        php_g_list *prev = ZVAL_GET_PHP_G_LIST(&list->prev);
        ZVAL_OBJ(&prev->next, &php_new_node->std);
        ZVAL_OBJ(&php_new_node->prev, &prev->std);

        ZVAL_OBJ(&list->prev, &php_new_node->std);// #1
        Z_TRY_ADDREF(list->prev);//                  #2
        ZVAL_OBJ(&php_new_node->next, &list->std);// #3
    }

    GC_REFCOUNT(std_new_node)++;
    return php_new_node;
}

php_g_list*
php_g_list_insert(php_g_list *list, zval *data, zval *position) {

    // get list at, and append
    php_g_list *new_list;
    php_g_list *tmp_list;
    php_g_list *prev_list;
    zend_long pos = position->value.lval;

    if (pos < 0)
      return php_g_list_append (list, data);
    else if (pos == 0)
      return php_g_list_prepend (list, data);

    tmp_list = php_g_list_nth (list, pos);
    if (!tmp_list)
      return php_g_list_append (list, data);

    zend_object *std_new_node = php_g_list_create_object(php_g_list_class_entry);
    new_list = ZOBJ_TO_PHP_G_LIST(std_new_node);
    ZVAL_COPY(&new_list->data, data);

    prev_list = ZVAL_GET_PHP_G_LIST(&tmp_list->prev);
    ZVAL_COPY(&new_list->prev, &tmp_list->prev);
    ZVAL_OBJ(&prev_list->next, &new_list);
    ZVAL_OBJ(&new_list->next, &tmp_list);
    ZVAL_COPY(&tmp_list->prev, &new_list);

    GC_REFCOUNT(&list->std)++;
    return list;
}

php_g_list*
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

php_g_list*
php_g_list_first(php_g_list *list) {
    php_g_list *first = list;
    php_g_list *prev = list;
    while(prev){
        first = prev;
        if (ZVAL_IS_PHP_G_LIST(&prev->prev)) {// maybe is preferable check if ZVAL_IS_NULL
            prev = ZVAL_GET_PHP_G_LIST(&prev->prev);
        } else {
            prev = NULL;
        }
    }

    GC_REFCOUNT(&first->std)++;
    return first;
}

php_g_list*
php_g_list_nth(php_g_list *list, zend_long index) {
    php_g_list *first = php_g_list_first(list);

    zend_long i;
    php_g_list *node = first;
    for(i=0; node && i<index; i++){
        if (ZVAL_IS_NULL(&node->next)) {
            zend_error(E_NOTICE, "Undefined offset: " ZEND_LONG_FMT, index);
            node = NULL;
        } else {
            node = ZVAL_GET_PHP_G_LIST(&node->next);
        }
    }

    return node;
}

zend_long
php_g_list_length(php_g_list *list) {
    zend_long length = 0;

    php_g_list *it;
    for(it=php_g_list_first(list); it; it = ZVAL_GET_PHP_G_LIST(&it->next)){
        length++;
    }

    return length;
}


/*----------------------------------------------------------------------+
 | g_list_append                                                        |
 +----------------------------------------------------------------------*/


/* {{{ */
PHP_FUNCTION(g_list_append)
{
    zval *list = NULL;
    zval *data = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    php_g_list *__list = ZVAL_IS_PHP_G_LIST(list)? ZVAL_GET_PHP_G_LIST(list): NULL;
    php_g_list *__ret = php_g_list_append(__list, data);

    RETURN_OBJ(&__ret->std);
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

    php_g_list *__list = ZVAL_IS_PHP_G_LIST(list)? ZVAL_GET_PHP_G_LIST(list): NULL;
    php_g_list *__ret = php_g_list_prepend(__list, data);

    RETURN_OBJ(&__ret->std);
}
/* }}} */

/*----------------------------------------------------------------------+
 | g_list_insert                                                        |
 +----------------------------------------------------------------------*/

/* {{{ proto string g_list_insert(GList list, mixed data, int position)
   Inserts a new element into the list at the given position */
PHP_FUNCTION(g_list_insert)
{
    zval *list;
    zval *data;
    zval *position;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(list);
        Z_PARAM_ZVAL(data);
        Z_PARAM_ZVAL(position);
    ZEND_PARSE_PARAMETERS_END();

    php_g_list *__list = ZVAL_IS_PHP_G_LIST(list)? ZVAL_GET_PHP_G_LIST(list): NULL;
    php_g_list *__ret = php_g_list_insert(__list, data, position);

    RETURN_OBJ(&__ret->std);
}
/* }}} */

/*----------------------------------------------------------------------+
 | g_list_first                                                         |
 +----------------------------------------------------------------------*/
/* {{{ proto g_list_insert(GList list):GList */
PHP_FUNCTION(g_list_first)
{
    zval *list;
    zval ret;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(list);
    ZEND_PARSE_PARAMETERS_END();

    php_g_list *__list = ZVAL_IS_PHP_G_LIST(list)? ZVAL_GET_PHP_G_LIST(list): NULL;
    php_g_list *__ret = php_g_list_first(__list);

    RETURN_OBJ(&__ret->std);
}
/* }}} */


static char*
php_g_list_dump_zval(zval *data) {
    char *str = NULL;
    if (ZVAL_IS_NULL(data)) {
        str = g_strdup_printf("NULL");
    } else if (Z_TYPE_P(data)==IS_STRING) {
        str = g_strdup_printf("\e[1;31m\"%s\"\e[0;m", data->value.str->val);
    } else if (Z_TYPE_P(data)==IS_LONG) {
        str = g_strdup_printf("%ld", data->value.lval);
    } else if (Z_TYPE_P(data)==IS_OBJECT) {
        str = g_strdup_printf("\e[2;34m%s\e[0;m\e[2;31m#%d\e[0;m(\e[2;35m%d\e[0;m){}",
                data->value.obj->ce->name->val,
                Z_OBJ_HANDLE_P(data),
                data->value.obj->gc.refcount);
    } else {
        str = g_strdup_printf("%ld", data->value.lval);
    }
    return str;
}
static char* php_g_list_dump(zval *list, int tab){
    char *str;
    char *tmp_prev;
    char *tmp_data;
    char *tmp_next;

    php_g_list *__list = ZVAL_GET_PHP_G_LIST(list);
    char *t = g_strdup_printf("%*.s", tab*4, "");

    if (ZVAL_IS_NULL(list)) {
        str = g_strdup_printf("NULL");
    } else {
        tmp_prev = php_g_list_dump_zval(&__list->prev);
        tmp_data = php_g_list_dump_zval(&__list->data);
        tmp_next = php_g_list_dump(&__list->next, tab+1);

        str = g_strdup_printf("\e[2;34mzval\e[0;m(\e[2;35m%d\e[0;m){ value: \e[1;34m%s\e[0;m\e[1;31m#%d\e[0;m(\e[2;35m%d\e[0;m)%p{\n"
                "%s    prev: %s,\n"
                "%s    data: %s,\n"
                "%s    next: %s\n"
                "%s}}",
                list->value.counted->gc.refcount,
                list->value.obj->ce->name->val,
                Z_OBJ_HANDLE_P(list),
                list->value.obj->gc.refcount, list->value.obj,
                t, tmp_prev,
                t, tmp_data,
                t, tmp_next,
                t);
        g_free(tmp_prev);
        g_free(tmp_data);
        g_free(tmp_next);
    }
    g_free(t);


    return str;
}

/* {{{ proto string php_g_list_dump(GList list)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(g_list_dump)
{
    zval *list = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "z", &list) == FAILURE) {
        return;
    }

    //php_g_list_first();
    char *str = php_g_list_dump(list, 0);
    g_print("%s\n", str);
    g_free(str);

    RETURN_NULL();
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
    php_g_list *self = ZOBJ_TO_PHP_G_LIST(zobj);

    if (data!=NULL) {
        ZVAL_COPY(&self->data, data);
        //Z_TRY_ADDREF(self->data);
    }

}
/* }}} GList::__construct() */

/*----------------------------------------------------------------------+
 | Vendor\ExtName\GList::___set_state                                   |
 +----------------------------------------------------------------------*/
/* {{{ GList::___set_state(array $properties) : object */
PHP_METHOD(G_List, __set_state)
{
    TRACE();
    zval ret;
    zval *properties=NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(properties)
    ZEND_PARSE_PARAMETERS_END();

    php_g_list *self = ZVAL_GET_PHP_G_LIST(getThis());

    if (properties!=NULL && Z_TYPE_P(properties)==IS_ARRAY) {
        g_print("Not implemented!\n");
        g_print("How to __set_state GList::$data ?\n");
    }

    RETURN_NULL();
}
/* }}} GList::___set_state() */


static const zend_function_entry php_g_list_methods[] = {
    PHP_ME(G_List, __construct, arginfo_g_list___construct, ZEND_ACC_PUBLIC)
    PHP_ME(G_List, __set_state, arginfo_g_list___set_state, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
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
    php_g_list_handlers.offset = PHP_G_LIST_OFFSET;
    //php_g_list_handlers.clone_obj;
    //php_g_list_handlers.compare;
    //php_g_list_handlers.compare_objects;
    //php_g_list_handlers.get_constructor;
    php_g_list_handlers.dtor_obj = php_g_list_dtor_obj;
    php_g_list_handlers.free_obj = php_g_list_free_storage;
    php_g_list_handlers.read_property = php_g_list_read_property;
    php_g_list_handlers.write_property = php_g_list_write_property;
    php_g_list_handlers.unset_property = php_g_list_unset_property;
    php_g_list_handlers.get_property_ptr_ptr = php_g_list_get_property_ptr_ptr;

    php_g_list_handlers.get_debug_info = php_g_list_get_debug_info;
    php_g_list_handlers.get_properties = php_g_list_get_properties;//get_properties_for TODO php 8.0
    //php_g_list_handlers.set = php_g_list_set;
    php_g_list_handlers.cast_object = php_g_list_cast_object;

    php_g_list_handlers.count_elements = php_g_list_count_elements;
    php_g_list_handlers.has_dimension = php_g_list_has_dimension;
    php_g_list_handlers.read_dimension = php_g_list_read_dimension;
    php_g_list_handlers.unset_dimension = php_g_list_unset_dimension;
    php_g_list_handlers.write_dimension = php_g_list_write_dimension;


    return &php_g_list_handlers;
}



/*{{{ php_g_list_class_init */
zend_class_entry*
php_g_list_class_init(zend_class_entry *ce) {
    php_g_list_get_handlers();
    //INIT_NS_CLASS_ENTRY((*ce), "Gnome\\G", "GList", php_g_list_methods);
    //INIT_NS_CLASS_ENTRY((*ce), "", "GList", php_g_list_methods);
    INIT_CLASS_ENTRY((*ce), "GList", php_g_list_methods);
    ce->create_object = php_g_list_create_object;
    //ce->serialize;
    php_g_list_class_entry = zend_register_internal_class_ex(ce, NULL);
    //zend_declare_property_null(&php_g_list_class_entry, "scheme", sizeof("scheme")-1, ZEND_ACC_PUBLIC TSRMLS_CC);

    zend_hash_init(&php_g_list_prop_handlers, 0, NULL, php_g_list_dtor_prop_handler, 1);
    php_g_list_register_prop_handler(&php_g_list_prop_handlers, "prev", sizeof("prev")-1, php_g_list_read_prev, php_g_list_write_prev);
    php_g_list_register_prop_handler(&php_g_list_prop_handlers, "data", sizeof("data")-1, php_g_list_read_data, php_g_list_write_data);
    php_g_list_register_prop_handler(&php_g_list_prop_handlers, "next", sizeof("next")-1, php_g_list_read_next, php_g_list_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_g_list_prop_handlers);

    return php_g_list_class_entry;
}/*}}} */

