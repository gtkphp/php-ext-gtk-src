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

#include <php.h>
#include <php_ini.h>
#include <zend_interfaces.h>
#include <ext/standard/info.h>

#include <glib-object.h>
#include "php_gobject/object.h"
#include "list.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_glib_list_class_entry;
//HashTable             php_glib_list_prop_handlers;
zend_object_handlers  php_glib_list_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
| Internal                                                             |
+----------------------------------------------------------------------*/

static const zend_function_entry php_glib_list_methods[] = {
    PHP_ME(g_list, __construct, arginfo_g_list___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/
static void  php_glib_list_unset_property(zval *object, zval *member, void **cache_slot);
static void  php_glib_list_write_property(zval *object, zval *member, zval *value, void **cache_slot);
static zval* php_glib_list_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv);
static char* php_glib_list_dump(php_glib_list *list, int tab);

static void
php_glib_list_unset_dimension(zval *object, zval *offset) {
    //php_glib_list *list = ZVAL_GET_PHP_GLIB_LIST(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
        // @TODO
        //zend_hash_index_del(list->prop_handler, );
        // php_glib_list
        break;
    case IS_STRING:
        php_glib_list_unset_property(object, offset, &cache);
        break;
    default:
        break;
    }
}

static void
php_glib_list_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_glib_list_write_property(object, &member, value, &cache);
}

static zval*
php_glib_list_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
        return NULL;
    }

    php_glib_list *intern = ZVAL_GET_PHP_GLIB_LIST(object);
    php_glib_list *list;
    void *cache=NULL;

    if (Z_TYPE_P(offset)==IS_LONG) {
        list = php_glib_list_nth(intern, offset->value.lval);
        if (list) {
            ZVAL_COPY(rv, &list->data);
        } else {
            ZVAL_NULL(rv);
            zend_error(E_USER_WARNING, "Undefined offset: %d", offset->value.lval);
        }
        return rv;
    } else if (Z_TYPE_P(offset)==IS_STRING) {
        return php_glib_list_read_property(object, offset, type, &cache, rv);
    } else {
        // error
    }

    return rv;
} /* }}} end php_g_hash_table_read_dimension */

static int
php_glib_list_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

/* updates *count to hold the number of elements present and returns SUCCESS.
 * Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_glib_list_count_elements(zval *object, zend_long *count) {

    *count = php_glib_list_length(ZVAL_GET_PHP_GLIB_LIST(object));

    return SUCCESS;
}

static int
php_glib_list_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}

static HashTable*
php_glib_list_get_properties(zval *object){
    php_glib_list  *self =  ZVAL_GET_PHP_GLIB_LIST(object);
    HashTable *props = self->properties;
    if (props==NULL) {
        ALLOC_HASHTABLE(self->properties);
        props = self->properties;
    } else {
        // TODO: rebuild the props( update)
        return props;// Else leaks : zend_hash_next_index_insert
    }

    zend_long length = php_glib_list_length(self);

    zend_hash_init(props, length, NULL, ZVAL_PTR_DTOR, 1);

    zval data;

    php_glib_list *it;
    for(it=php_glib_list_first(self); it; it = it->next){
        ZVAL_COPY(&data, &it->data);
        zend_hash_next_index_insert(props, &data);
    }

    return props;
}

static HashTable*
php_glib_list_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_glib_list  *obj =  ZVAL_GET_PHP_GLIB_LIST(object);
    HashTable   *debug_info,
                *std_props;
    zend_string *string_key = NULL;
    zval *value;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    ZEND_HASH_FOREACH_STR_KEY_VAL(obj->std.properties, string_key, value) {
        zend_hash_add(debug_info, string_key, value);
    } ZEND_HASH_FOREACH_END();


    zval prev; ZVAL_SET_PHP_GLIB_LIST(&prev, obj->prev);
    zend_hash_str_update(debug_info, "prev", sizeof("prev")-1, &prev);

    zval data; ZVAL_COPY(&data, &obj->data);
    zend_hash_str_update(debug_info, "data", sizeof("data")-1, &data);

    zval next; ZVAL_SET_PHP_GLIB_LIST(&next, obj->next);
    zend_hash_str_update(debug_info, "next", sizeof("next")-1, &next);

    return debug_info;
}
/* }}} */

static void
php_glib_list_unset_property(zval *object, zval *member, void **cache_slot) {
    php_glib_list *obj = ZVAL_GET_PHP_GLIB_LIST(object);
    zend_string *member_str = zval_get_string(member);
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (zend_string_equals_literal(member->value.str, "next")
     || zend_string_equals_literal(member->value.str, "prev")
     || zend_string_equals_literal(member->value.str, "data") ) {
#if 0
        if (ZVAL_IS_PHP_GLIB_LIST(value)) {
            // do unset(object->next) and php_glib_list_insert(object, value, 0);
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
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}

/* {{{ php_glib_list_write_property */
static void
php_glib_list_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_glib_list *obj = ZVAL_GET_PHP_GLIB_LIST(object);
    zend_string *member_str = zval_get_string(member);
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (zend_string_equals_literal(member->value.str, "next")
     || zend_string_equals_literal(member->value.str, "prev")
     || zend_string_equals_literal(member->value.str, "data") ) {
#if 0
        if (ZVAL_IS_PHP_GLIB_LIST(value)) {
            // do unset(object->next) and php_glib_list_insert(object, value, 0);
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

static zval zval_ret;
/* {{{ gtk_read_property */
static zval*
php_glib_list_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_glib_list *obj = ZVAL_GET_PHP_GLIB_LIST(object);
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (zend_string_equals_literal(member_str, "next")) {
        if (NULL==obj->next) {
            ZVAL_NULL(&zval_ret);
            return &zval_ret;
        }
        ZVAL_OBJ(&zval_ret, &obj->next->std);
        return &zval_ret;
    }
    if (zend_string_equals_literal(member_str, "prev")) {
        if (NULL==obj->prev) {
            ZVAL_NULL(&zval_ret);
            return &zval_ret;
        }
        ZVAL_OBJ(&zval_ret, &obj->prev->std);
        return &zval_ret;
    }
    if (zend_string_equals_literal(member_str, "data")) {
        ZVAL_COPY(&zval_ret, &obj->data);
        return &zval_ret;
    }

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    retval = std_hnd->read_property(object, member, type, cache_slot, rv);

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ php_glib_list_free_object */
static void
php_glib_list_free_object(zend_object *object)
{
    php_glib_list *intern = ZOBJ_TO_PHP_GLIB_LIST(object);
    if (ZVAL_IS_NULL(&intern->data))
        TRACE("php_glib_list_free_object(\"%s\") / %d\n", "NULL", object->gc.refcount);
    else
        TRACE("php_glib_list_free_object(\"%s\") / %d\n", intern->data.value.str->val, object->gc.refcount);

    if (intern->ptr) {
        g_list_free_1(intern->ptr);
        intern->ptr = NULL;
    }


    if (intern->properties!=NULL) {
        zend_hash_destroy(intern->properties);
        efree(intern->properties);
        intern->properties=NULL;
    }

    zend_object_std_dtor(&intern->std);
    //efree(intern);
}
/* }}} php_glib_list_free_object */

static void
php_glib_list_dtor_object(zend_object *obj) {
    php_glib_list *intern = ZOBJ_TO_PHP_GLIB_LIST(obj);
    if (ZVAL_IS_NULL(&intern->data)) {
        TRACE("php_glib_list_dtor_object(\"%s\") / %d\n", "NULL", obj->gc.refcount);
    } else if (IS_STRING==Z_TYPE(intern->data)) {
        TRACE("php_glib_list_dtor_object(\"%s\") / %d\n", intern->data.value.str->val, obj->gc.refcount);
    } else {
        TRACE("php_glib_list_dtor_object(\"%s\") / %d\n", "?", obj->gc.refcount);
    }
    g_print("php_glib_list_dtor_object\n");

    if (!ZVAL_IS_NULL(&intern->data)) {
        Z_TRY_DELREF_P(&intern->data);
        //zval_ptr_dtor(&intern->data);
        //g_print("zend_string: %p\n", intern->data.value.str);
        //g_print("            (%d)\n", intern->data.value.str->gc.refcount);
        //zend_string_release(intern->data.value.str);
        ZVAL_NULL(&intern->data);
    }

    if (intern->next) {
        zend_object_release(&intern->next->std);
        intern->next=NULL;
    }

    if (intern->prev!=NULL) {
        zend_object_release(&intern->prev->std);
        intern->prev=NULL;
    }
}
static void
php_glib_list__unset() {

}

/* {{{ php_glib_list_create_object */
static zend_object*
php_glib_list_create_object(zend_class_entry *class_type)
{
    php_glib_list *intern = ecalloc(1, sizeof(php_glib_list) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    g_print("php_glib_list_create_object\n");

    //php_glib_list_properties_init(intern);
    ZVAL_NULL(&intern->data);
    intern->next = NULL;
    intern->prev = NULL;

    intern->ptr = NULL;// new GList ?
    intern->properties = NULL;

    intern->std.handlers = &php_glib_list_handlers;

    TRACE("php_glib_list_create_object(%p) / %d\n", &intern->std, intern->std.gc.refcount);
    return &intern->std;
}
/* }}} php_glib_list_create_object */

/*
static void php_glib_list_dtor_prop_handler(zval *zv)
{
    free(Z_PTR_P(zv));
}
*/

static zend_object_handlers*
php_glib_list_get_handlers()
{
    memcpy(&php_glib_list_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_glib_list_handlers.offset = PHP_GLIB_LIST_OFFSET;
    //php_glib_list_handlers.clone_obj;
    //php_glib_list_handlers.compare;
    //php_glib_list_handlers.compare_objects;
    //php_glib_list_handlers.get_constructor;
    php_glib_list_handlers.dtor_obj = php_glib_list_dtor_object;
    php_glib_list_handlers.free_obj = php_glib_list_free_object;
    php_glib_list_handlers.read_property = php_glib_list_read_property;
    php_glib_list_handlers.write_property = php_glib_list_write_property;
    php_glib_list_handlers.unset_property = php_glib_list_unset_property;
    //php_glib_list_handlers.get_property_ptr_ptr = php_glib_list_get_property_ptr_ptr;

    php_glib_list_handlers.get_debug_info = php_glib_list_get_debug_info;
    php_glib_list_handlers.get_properties = php_glib_list_get_properties;//get_properties_for TODO php 8.0
    //php_glib_list_handlers.set = php_glib_list_set;
    php_glib_list_handlers.cast_object = php_glib_list_cast_object;

    php_glib_list_handlers.count_elements = php_glib_list_count_elements;
    php_glib_list_handlers.has_dimension = php_glib_list_has_dimension;
    php_glib_list_handlers.read_dimension = php_glib_list_read_dimension;
    php_glib_list_handlers.unset_dimension = php_glib_list_unset_dimension;
    php_glib_list_handlers.write_dimension = php_glib_list_write_dimension;


    return &php_glib_list_handlers;
}



/*----------------------------------------------------------------------+
| PHP_MINIT                                                            |
+----------------------------------------------------------------------*/

/*{{{ php_glib_list_class_init */
zend_class_entry*
php_glib_list_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_glib_list_get_handlers();
    //INIT_NS_CLASS_ENTRY((*ce), "Gnome\\G", "List", php_glib_list_methods);
    INIT_CLASS_ENTRY((*container_ce), "GList", php_glib_list_methods);
    php_glib_list_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_glib_list_class_entry->create_object = php_glib_list_create_object;
    //container_ce->__unset = php_glib_list__unset;
    //ce->serialize;
    /*
    zend_hash_init(&php_glib_list_prop_handlers, 0, NULL, php_glib_list_dtor_prop_handler, 1);
    php_glib_list_register_prop_handler(&php_glib_list_prop_handlers, "prev", sizeof("prev")-1, php_glib_list_read_prev, php_glib_list_write_prev);
    php_glib_list_register_prop_handler(&php_glib_list_prop_handlers, "data", sizeof("data")-1, php_glib_list_read_data, php_glib_list_write_data);
    php_glib_list_register_prop_handler(&php_glib_list_prop_handlers, "next", sizeof("next")-1, php_glib_list_read_next, php_glib_list_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_glib_list_prop_handlers);
    */

    return php_glib_list_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/
static php_glib_list*
php_glib_list_insert_sorted_real(php_glib_list *list, zval *data, zval *func, zval *user_data) {

    php_glib_list *tmp_list = list;
    php_glib_list *new_list;
    zend_object *tmp;
    zend_long cmp = 0;

    int result;
    int param_count = 3;
    zval retval;
    zval params[3];

    if (ZVAL_IS_NULL(func)) {
        return list;
    }

    if (!list)
      {
        tmp = php_glib_list_create_object(php_glib_list_class_entry);
        new_list = ZOBJ_TO_PHP_GLIB_LIST(tmp);
        ZVAL_COPY(&new_list->data, data);
        return new_list;
      }

    ZVAL_COPY(&params[0], data);
    ZVAL_COPY(&params[1], &tmp_list->data);
    ZVAL_COPY(&params[2], user_data);

    result = call_user_function(NULL, NULL, func, &retval, param_count, params);
    if (result==FAILURE) {
        php_printf("Unexpected 222 : php_g_hash_table_hash_func\n");
    } else if (Z_TYPE(retval)==IS_LONG) {
        cmp = retval.value.lval;
    } else {
        php_printf("Unexpected 223 : php_g_hash_table_hash_func\n");
    }

    while ((tmp_list->next) && (cmp > 0))
      {
        tmp_list = tmp_list->next;

        ZVAL_COPY(&params[0], data);
        ZVAL_COPY(&params[1], &tmp_list->data);
        ZVAL_COPY(&params[2], user_data);

        result = call_user_function(NULL, NULL, func, &retval, param_count, params);
        cmp = retval.value.lval;

      }

    tmp = php_glib_list_create_object(php_glib_list_class_entry);
    new_list = ZOBJ_TO_PHP_GLIB_LIST(tmp);
    ZVAL_COPY(&new_list->data, data);

    if ((!tmp_list->next) && (cmp > 0))
      {
        tmp_list->next = new_list;
        new_list->prev = tmp_list;
        GC_REFCOUNT(&tmp_list->std)++;
        return list;
      }
    if (tmp_list->prev)
      {
        //GC_REFCOUNT(&tmp_list->prev->std)++;
        tmp_list->prev->next = new_list;
        new_list->prev = tmp_list->prev;
      }
    new_list->next = tmp_list;
    tmp_list->prev = new_list;

    if (tmp_list == list) {
        GC_REFCOUNT(&tmp_list->std)++;
        return new_list;
    } else {
        GC_REFCOUNT(&new_list->std)++;
        return list;
    }
}


/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
php_glib_list *
php_glib_list_append(php_glib_list *list, zval *data) {
    php_glib_list *last = NULL;

    zend_object *new_std = php_glib_list_create_object(php_glib_list_class_entry);
    php_glib_list *new_list = ZOBJ_TO_PHP_GLIB_LIST(new_std);
    ZVAL_COPY(&new_list->data, data);

    if (list) {
        last = php_glib_list_last(list);
        last->next = new_list;
        new_list->prev = last;
        GC_REFCOUNT(&last->std)++;

        return list;
    }

    return new_list;
}

php_glib_list *
php_glib_list_prepend(php_glib_list *list, zval *data) {
    zend_object *new_std = php_glib_list_create_object(php_glib_list_class_entry);
    php_glib_list *new_list = ZOBJ_TO_PHP_GLIB_LIST(new_std);
    ZVAL_COPY(&new_list->data, data);

    if (list) {
        new_list->next = list;

        new_list->prev = list->prev;
        if (list->prev) {
            list->prev->next = new_list;
            GC_REFCOUNT(&new_list->std)++;
        } else {
            GC_REFCOUNT(&list->std)++;
        }
        list->prev = new_list;
    }

    return new_list;
}

php_glib_list *
php_glib_list_insert(php_glib_list *list, zval *data, zend_long position) {
    php_glib_list *tmp_list = NULL;
    php_glib_list *new_list = NULL;

    if (position < 0)
      return php_glib_list_append (list, data);
    else if (position == 0)
      return php_glib_list_prepend (list, data);

    tmp_list = php_glib_list_nth (list, position);
    if (!tmp_list)
      return php_glib_list_append (list, data);

    zend_object *new_std = php_glib_list_create_object(php_glib_list_class_entry);
    new_list = ZOBJ_TO_PHP_GLIB_LIST(new_std);
    ZVAL_COPY(&new_list->data, data);

    new_list->prev = tmp_list->prev;
    tmp_list->prev->next = new_list;
    new_list->next = tmp_list;
    tmp_list->prev = new_list;

    return list;
}

php_glib_list *
php_glib_list_insert_before(php_glib_list *list, php_glib_list *sibling, zval *data) {
    zend_object *new_list;
    if (!list) {
        new_list = php_glib_list_create_object(php_glib_list_class_entry);
        list = ZOBJ_TO_PHP_GLIB_LIST(new_list);
        ZVAL_COPY(&list->data, data);
        return list;
    } else if (sibling) {
      php_glib_list *node;

      new_list = php_glib_list_create_object(php_glib_list_class_entry);
      node = ZOBJ_TO_PHP_GLIB_LIST(new_list);
      ZVAL_COPY(&node->data, data);
      node->prev = sibling->prev;
      node->next = sibling;
      sibling->prev = node;
      if (node->prev) {
        node->prev->next = node;
        GC_REFCOUNT(&node->std)++;
        return list;
      } else {
        GC_REFCOUNT(&sibling->std)++;
        return node;
      }
    } else {
      php_glib_list *last;

      last = list;
      while (last->next)
        last = last->next;

      new_list = php_glib_list_create_object(php_glib_list_class_entry);
      last->next = ZOBJ_TO_PHP_GLIB_LIST(new_list);
      ZVAL_COPY(&last->next->data, data);
      last->next->prev = last;
      last->next->next = NULL;
      GC_REFCOUNT(&last->std)++;

      return list;
    }
}


php_glib_list *
php_glib_list_insert_sorted(php_glib_list *list, zval *data, zval *func) {
    zval user_data; ZVAL_NULL(&user_data);
    return php_glib_list_insert_sorted_real(list, data, func, &user_data);
}

php_glib_list *
php_glib_list_remove(php_glib_list *list, zval *data) {
    php_glib_list *tmp;
    php_glib_list *prev=NULL;
    php_glib_list *next=NULL;
    zend_long i=0;
    zend_long counter=0;

    tmp = list;
    while (tmp) {
      if (! zend_is_identical(&tmp->data, data))
        tmp = tmp->next;
      else {

          if (list == tmp)
            list = list->next;

          prev = tmp->prev;
          next = tmp->next;

          // 1) detach
          if (prev) {
              prev->next = next;
              if(next)
                  GC_REFCOUNT(&prev->std)++;
              counter++;// release(tmp); GC_REFCOUNT(&tmp->std)--;
          } else if (next) {
              GC_REFCOUNT(&next->std)++;
          }

          if (next) {
              next->prev = prev;
              if(prev)
                GC_REFCOUNT(&next->std)++;
              counter++;// release(tmp); GC_REFCOUNT(&tmp->std)--;
          }

          // 2) attach
          php_glib_list_dtor_object(&tmp->std);
          for(i=0; i<counter; i++) {
              zend_object_release(&tmp->std);
          }

        break;
      }
    }
    return list;
}

php_glib_list *
php_glib_list_remove_link_real(php_glib_list *list, php_glib_list *link) {
    php_glib_list *prev;
    php_glib_list *next;

    if (link) {
        prev = link->prev;
        next = link->next;

        if (link == list)
            list = list->next;

        zend_long counter=0;

        // 1) detach
        if (prev) {
            prev->next = next;
            if(next)
                GC_REFCOUNT(&prev->std)++;
            counter++;// release(tmp); GC_REFCOUNT(&tmp->std)--;
            GC_REFCOUNT(&list->std)++;
        } else if (next) {
            GC_REFCOUNT(&next->std)++;
            //counter++;
        }

        if (next) {
            next->prev = prev;
            if(prev)
              GC_REFCOUNT(&next->std)++;
            counter++;// release(tmp); GC_REFCOUNT(&tmp->std)--;
        }

        // 2) attach
        if (link->prev!=NULL) {
            zend_object_release(&link->prev->std);
            link->prev = NULL;
        }
        if (link->next) {
            zend_object_release(&link->next->std);
            link->next = NULL;
        }
        for(; counter>0; counter--) {
            zend_object_release(&link->std);
        }

    }

    return list;
}
php_glib_list *
php_glib_list_remove_link(php_glib_list *list, php_glib_list *llink) {
    return php_glib_list_remove_link_real(list, llink);
}

php_glib_list *
php_glib_list_delete_link(php_glib_list *list, php_glib_list *link_) {
    list = php_glib_list_remove_link_real(list, link_);
    php_glib_list_dtor_object(&link_->std);
    return list;
}

php_glib_list *
php_glib_list_remove_all(php_glib_list *list, zval *data) {
    php_glib_list *head = NULL;
    php_glib_list *tmp = list;
    zend_long i = 0;
    zend_long counter;

    if (NULL==list->prev) {
         head = list;
    }

    while (tmp) {
        if (! zend_is_identical(&tmp->data, data))
            tmp = tmp->next;
        else {
            php_glib_list *prev = tmp->prev;
            php_glib_list *next = tmp->next;
            counter = 0;

            // 1) detach
            if (prev) {
                prev->next = next;
                if(next)
                    GC_REFCOUNT(&prev->std)++;
                counter++;
            } else if(head==tmp) {
                if (next) {
                    list = next;
                    GC_REFCOUNT(&next->std)++;
                    ///counter++;
                } else {
                    //GC_REFCOUNT(&next->std)++;
                    //GC_REFCOUNT(&tmp->std)--;
                    counter++;
                    list = NULL;
                }
            } else {
                if (next) {
                    list = next;
                    GC_REFCOUNT(&next->std)++;
                } else {
                    g_print("Case ??\n");
                }
                //counter++;
            }// else list = NULL;

            if (next) {
                next->prev = prev;
                if(prev)
                  GC_REFCOUNT(&next->std)++;
                counter++;
            }

            // 2) attach
            /**/
            char *str = php_glib_list_dump(list, 1);
            g_print("    %s\n", str);
            g_free(str);
            /**/
            php_glib_list_dtor_object(&tmp->std);
            /**/
            char *str2 = php_glib_list_dump(tmp, 2);
            g_print("        %s\n", str2);
            g_free(str2);
            g_print("%d / %d\n", tmp->std.gc.refcount, counter);
            /**/
            for(i=0; i<counter; i++) {
                zend_object_release(&tmp->std);
            }
            //g_print("remaind: %d\n", tmp->std.gc.refcount);
            tmp = next;
        }
    }
    return list;
}
#if 0
GList *tmp = list;

while (tmp)
  {
    if (tmp->data != data)
  tmp = tmp->next;
    else
  {
    GList *next = tmp->next;

    if (tmp->prev)
      tmp->prev->next = next;
    else
      list = next;
    if (next)
      next->prev = tmp->prev;

    _g_list_free1 (tmp);
    tmp = next;
  }
  }
return list;
#endif
void
php_glib_list_free(php_glib_list *list) {
    // TODO: implementation
}

void
php_glib_list_free_full(php_glib_list *list, zval *free_func) {
    // TODO: implementation
}

php_glib_list *
php_glib_list_alloc() {
    // TODO: implementation
    return NULL;
}

void
php_glib_list_free_1(php_glib_list *list) {
    // TODO: implementation
}

zend_long
php_glib_list_length(php_glib_list *list) {
    zend_long length = 0;

    while(list) {
        length++;
        list = list->next;
    }

    return length;
}

php_glib_list *
php_glib_list_copy(php_glib_list *list) {
    // TODO: implementation
    return NULL;
}

php_glib_list *
php_glib_list_copy_deep(php_glib_list *list, zval *func, zval *user_data) {
    // TODO: implementation
    return NULL;
}

php_glib_list *
php_glib_list_reverse(php_glib_list *list) {
    // TODO: implementation
    return NULL;
}

php_glib_list *
php_glib_list_sort(php_glib_list *list, zval *compare_func) {
    // TODO: implementation
    return NULL;
}

php_glib_list *
php_glib_list_insert_sorted_with_data(php_glib_list *list, zval *data, zval *func, zval *user_data) {
    return php_glib_list_insert_sorted_real (list, data, func, user_data);
}

php_glib_list *
php_glib_list_sort_with_data(php_glib_list *list, zval *compare_func, zval *user_data) {
    // TODO: implementation
    return NULL;
}

php_glib_list *
php_glib_list_concat(php_glib_list *list1, php_glib_list *list2) {
    // TODO: implementation
    return NULL;
}

void
php_glib_list_foreach(php_glib_list *list, zval *func, zval *user_data) {
    // TODO: implementation
}

php_glib_list *
php_glib_list_first(php_glib_list *list) {
    if (list) {
        while(list->prev) {
            list = list->prev;
        }
    }

    return list;
}

php_glib_list *
php_glib_list_last(php_glib_list *list) {
    php_glib_list *last;

    if (list==NULL) {
        return NULL;
    }

    while(list) {
        last = list;
        list = list->next;
    }

    return last;
}

php_glib_list *
php_glib_list_nth(php_glib_list *list, zend_long n) {
    while ((n-- > 0) && list)
        list = list->next;

    return list;
}

zval *
php_glib_list_nth_data(php_glib_list *list, zend_long n) {
    // TODO: implementation
    return NULL;
}

php_glib_list *
php_glib_list_nth_prev(php_glib_list *list, zend_long n) {
    // TODO: implementation
    return NULL;
}

php_glib_list *
php_glib_list_find(php_glib_list *list, zval *data) {
    // TODO: implementation
    return NULL;
}

php_glib_list *
php_glib_list_find_custom(php_glib_list *list, zval *data, zval *func) {
    // TODO: implementation
    return NULL;
}

zend_long
php_glib_list_position(php_glib_list *list, php_glib_list *llink) {
    // TODO: implementation
    return 0;
}

zend_long
php_glib_list_index(php_glib_list *list, zval *data) {
    // TODO: implementation
    return 0;
}

php_glib_list*
php_glib_list_new(GList *list) {
    zend_object *zlist;
    php_glib_list *plist = NULL;
    php_glib_list *prev = NULL;
    php_glib_list *head = NULL;

    GList *it;
    for(it=list; it; it=it->next) {
        zlist = php_glib_list_create_object(php_glib_list_class_entry);
        plist = ZOBJ_TO_PHP_GLIB_LIST(zlist);
        plist->ptr = it;

        if (prev) {
            prev->next = plist;
            GC_REFCOUNT(zlist)++;
        }
        plist->prev = prev;
        GC_REFCOUNT(zlist)++;
        // {{{wrapper data
        if (G_IS_OBJECT(it->data)) {
            GObject *object = (GObject *)it->data;
            zend_object *z_object = g_object_get_data(object, "zend_object");
            GC_REFCOUNT(z_object)++;
            ZVAL_OBJ(&plist->data, z_object);
            // On aimerai conserver l'id (GtkButton)#1( pas de create_object, svp
            // il faut GtkWidget->data[zend] = zend_object*
            // mais on garde ->data pour le user, donc on va créer un array specifique.
            // Donc :
            // Pour chaque new GtkWidget, pop stack
            // Set<Pair<GObject*, zend_object*>>
            /*
            const char *name = g_type_name_from_instance((GTypeInstance*)it->data);
            zend_string *class_name = zend_string_init(name, strlen(name), 0);
            zend_class_entry *ce = zend_lookup_class(class_name);
            zend_object *zobject = ce->create_object(ce);
            ZOBJ_TO_PHP_GOBJECT_OBJECT(zobject)->ptr = it->data;
            ZVAL_OBJ(&plist->data, zobject);
            zend_string_release(class_name);
            */
        }
        // wrapper data}}}
        prev = plist;
        if (it==list) {
            head = plist;
        }
    }

    //g_print("ref: %d\n", head->std.gc.refcount);
    return head;
}



/*----------------------------------------------------------------------+
| PHP_METHOD                                                           |
+----------------------------------------------------------------------*/

/* {{{ GList::__construct() */
PHP_METHOD(g_list, __construct)
{
    zval *data=NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    zend_object *zobj = Z_OBJ_P(getThis());
    php_glib_list *self = ZOBJ_TO_PHP_GLIB_LIST(zobj);

    if (data!=NULL) {
        ZVAL_COPY(&self->data, data);
    }
}
/* }}} */

/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/

/* {{{ proto GList g_list_append(GList list, mixed data) */
PHP_FUNCTION(g_list_append)
{
    zval *list = NULL;
    zval *data = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_append(__list, data);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_prepend(GList list, mixed data) */
PHP_FUNCTION(g_list_prepend)
{
    zval *list = NULL;
    zval *data = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_prepend(__list, data);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_insert(GList list, mixed data, int position) */
PHP_FUNCTION(g_list_insert)
{
    zval *list = NULL;
    zval *data = NULL;
    zval *position = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(data)
        Z_PARAM_ZVAL(position)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_insert(__list, data, position->value.lval);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_insert_before(GList list, GList sibling, mixed data) */
PHP_FUNCTION(g_list_insert_before)
{
    zval *list = NULL;
    zval *sibling = NULL;
    zval *data = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(sibling)
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list    = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__sibling = ZVAL_IS_PHP_GLIB_LIST(sibling)? ZVAL_GET_PHP_GLIB_LIST(sibling): NULL;
    php_glib_list *__ret     = php_glib_list_insert_before(__list, __sibling, data);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_insert_sorted(GList list, mixed data, mixed func) */
PHP_FUNCTION(g_list_insert_sorted)
{
    zval *list = NULL;
    zval *data = NULL;
    zval *func = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(data)
        Z_PARAM_ZVAL(func)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_insert_sorted(__list, data, func);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_remove(GList list, mixed data) */
PHP_FUNCTION(g_list_remove)
{
    zval *list = NULL;
    zval *data = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_remove(__list, data);

    if (NULL==__ret) {
        RETURN_NULL();
    }

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_remove_link(GList list, GList llink) */
PHP_FUNCTION(g_list_remove_link)
{
    zval *list = NULL;
    zval *llink = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(llink)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list  = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__llink = ZVAL_IS_PHP_GLIB_LIST(llink)? ZVAL_GET_PHP_GLIB_LIST(llink): NULL;
    php_glib_list *__ret = php_glib_list_remove_link(__list, __llink);

    if (__ret) {
        RETURN_OBJ(&__ret->std);
    } else {
        RETURN_NULL();
    }
}/* }}} */

/* {{{ proto GList g_list_delete_link(GList list, GList link_) */
PHP_FUNCTION(g_list_delete_link)
{
    zval *list = NULL;
    zval *link_ = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(link_)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list  = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__link_ = ZVAL_IS_PHP_GLIB_LIST(link_)? ZVAL_GET_PHP_GLIB_LIST(link_): NULL;
    php_glib_list *__ret   = php_glib_list_delete_link(__list, __link_);

    if (__ret) {
        RETURN_OBJ(&__ret->std);
    } else {
        RETURN_NULL();
    }
}/* }}} */

/* {{{ proto GList g_list_remove_all(GList list, mixed data) */
PHP_FUNCTION(g_list_remove_all)
{
    zval *list = NULL;
    zval *data = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_remove_all(__list, data);

    if (__ret) {
        //GC_REFCOUNT(&__ret->std)++;
        RETURN_OBJ(&__ret->std);
    } else {
        RETURN_NULL();
    }
}/* }}} */

/* {{{ proto void g_list_free(GList list) */
PHP_FUNCTION(g_list_free)
{
    zval *list = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(list)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list_free(__list);

    RETURN_NULL();
}/* }}} */

/* {{{ proto void g_list_free_full(GList list, callback free_func) */
PHP_FUNCTION(g_list_free_full)
{
    zval *list = NULL;
    zval *free_func = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(free_func)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list_free_full(__list, free_func);

    RETURN_NULL();
}/* }}} */

/* {{{ proto GList g_list_alloc() */
PHP_FUNCTION(g_list_alloc)
{
    php_glib_list *__ret = php_glib_list_alloc();

    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void g_list_free_1(GList list) */
PHP_FUNCTION(g_list_free_1)
{
    zval *list = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(list)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list_free_1(__list);

    RETURN_NULL();
}/* }}} */

/* {{{ proto int g_list_length(GList list) */
PHP_FUNCTION(g_list_length)
{
    zval *list = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(list)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    zend_long __ret = php_glib_list_length(__list);

    RETURN_LONG(__ret);
}/* }}} */

/* {{{ proto GList g_list_copy(GList list) */
PHP_FUNCTION(g_list_copy)
{
    zval *list = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(list)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_copy(__list);

    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_copy_deep(GList list, mixed func, mixed user_data) */
PHP_FUNCTION(g_list_copy_deep)
{
    zval *list = NULL;
    zval *func = NULL;
    zval *user_data = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(func)
        Z_PARAM_ZVAL(user_data)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_copy_deep(__list, func, user_data);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_reverse(GList list) */
PHP_FUNCTION(g_list_reverse)
{
    zval *list = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(list)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_reverse(__list);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_sort(GList list, mixed compare_func) */
PHP_FUNCTION(g_list_sort)
{
    zval *list = NULL;
    zval *compare_func = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(compare_func)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_sort(__list, compare_func);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_insert_sorted_with_data(GList list, mixed data, mixed func, mixed user_data) */
PHP_FUNCTION(g_list_insert_sorted_with_data)
{
    zval *list = NULL;
    zval *data = NULL;
    zval *func = NULL;
    zval *user_data = NULL;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(data)
        Z_PARAM_ZVAL(func)
        Z_PARAM_ZVAL(user_data)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_insert_sorted_with_data(__list, data, func, user_data);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_sort_with_data(GList list, mixed compare_func, mixed user_data) */
PHP_FUNCTION(g_list_sort_with_data)
{
    zval *list = NULL;
    zval *compare_func = NULL;
    zval *user_data = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(compare_func)
        Z_PARAM_ZVAL(user_data)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_sort_with_data(__list, compare_func, user_data);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_concat(GList list1, GList list2) */
PHP_FUNCTION(g_list_concat)
{
    zval *list1 = NULL;
    zval *list2 = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list1)
        Z_PARAM_ZVAL(list2)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list1 = ZVAL_IS_PHP_GLIB_LIST(list1)? ZVAL_GET_PHP_GLIB_LIST(list1): NULL;
    php_glib_list *__list2 = ZVAL_IS_PHP_GLIB_LIST(list2)? ZVAL_GET_PHP_GLIB_LIST(list2): NULL;
    php_glib_list *__ret = php_glib_list_concat(__list1, __list2);

    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void g_list_foreach(GList list, mixed func, mixed user_data) */
PHP_FUNCTION(g_list_foreach)
{
    zval *list = NULL;
    zval *func = NULL;
    zval *user_data = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(func)
        Z_PARAM_ZVAL(user_data)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list_foreach(__list, func, user_data);

    RETURN_NULL();
}/* }}} */

/* {{{ proto GList g_list_first(GList list) */
PHP_FUNCTION(g_list_first)
{
    zval *list = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(list)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_first(__list);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_last(GList list) */
PHP_FUNCTION(g_list_last)
{
    zval *list = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(list)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_last(__list);

    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_nth(GList list, int n) */
PHP_FUNCTION(g_list_nth)
{
    zval *list = NULL;
    zval *n = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(n)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    zend_long   __n    = Z_TYPE_P(n)==IS_LONG? n->value.lval: 0;
    php_glib_list *__ret = php_glib_list_nth(__list, __n);

    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto mixed g_list_nth_data(GList list, int n) */
PHP_FUNCTION(g_list_nth_data)
{
    zval *list = NULL;
    zval *n = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(n)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    zend_long   __n    = Z_TYPE_P(n)==IS_LONG? n->value.lval: 0;
    zval       *__ret  = php_glib_list_nth_data(__list, __n);

    RETURN_ZVAL(__ret, 0, 0);
}/* }}} */

/* {{{ proto GList g_list_nth_prev(GList list, int n) */
PHP_FUNCTION(g_list_nth_prev)
{
    zval *list = NULL;
    zval *n = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(n)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    zend_long   __n    = Z_TYPE_P(n)==IS_LONG? n->value.lval: 0;
    zval       *__ret  = php_glib_list_nth_prev(__list, __n);

    RETURN_ZVAL(__ret, 0, 0);
}/* }}} */

/* {{{ proto GList g_list_find(GList list, mixed data) */
PHP_FUNCTION(g_list_find)
{
    zval *list = NULL;
    zval *data = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_find(__list, data);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto GList g_list_find_custom(GList list, mixed data, mixed func) */
PHP_FUNCTION(g_list_find_custom)
{
    zval *list = NULL;
    zval *data = NULL;
    zval *func = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(data)
        Z_PARAM_ZVAL(func)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_find_custom(__list, data, func);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto int g_list_position(GList list, GList llink) */
PHP_FUNCTION(g_list_position)
{
    zval *list = NULL;
    zval *llink = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(llink)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list  = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__llist = ZVAL_IS_PHP_GLIB_LIST(llink)? ZVAL_GET_PHP_GLIB_LIST(llink): NULL;
    zend_long   __ret   = php_glib_list_position(__list, __llist);

    RETURN_LONG(__ret);
}/* }}} */

/* {{{ proto int g_list_index(GList list, mixed data) */
PHP_FUNCTION(g_list_index)
{
    zval *list = NULL;
    zval *data = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(list)
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_list *__list = ZVAL_IS_PHP_GLIB_LIST(list)? ZVAL_GET_PHP_GLIB_LIST(list): NULL;
    php_glib_list *__ret = php_glib_list_index(__list, data);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */


static char *php_glib_list_dump_zval(zval *data, int tab);
static GList *recursions = NULL;// of php_glib_list
static char *php_glib_list_dump_zobj(zend_object *z_object, int tab){
    char *str;
    char *tmp_prev;
    char *tmp_data;
    char *tmp_next;
    php_gobject_object *ptr = NULL;


    ptr = z_object==NULL ? NULL : ((char*)z_object) - z_object->handlers->offset;

    char *t = g_strdup_printf("%*.s", tab*4, "");
    GList *is_recursion = g_list_find(recursions, (gconstpointer)z_object);

    if (z_object==NULL) {
        str = g_strdup_printf("NULL");
    } else if (NULL!=is_recursion) {
        //str = g_strdup_printf("*RECURSION*");
        str = g_strdup_printf("\e[1;34m%s\e[0;m\e[2;31m#%d\e[0;m{*RECURSION*}", z_object->ce->name->val, z_object->handle);
    } else if (z_object->ce==php_glib_list_class_entry) {
        php_glib_list *list = ptr;
        recursions = g_list_append(recursions, z_object);
        zend_object *prev = list->prev ? &list->prev->std : NULL;
        zend_object *next = list->next ? &list->next->std : NULL;

        tmp_prev = php_glib_list_dump_zobj(prev, tab+1);
        tmp_data = php_glib_list_dump_zval(&list->data, tab+1);
        tmp_next = php_glib_list_dump_zobj(next, tab+1);

        str = g_strdup_printf("\e[1;34m%s\e[0;m\e[1;31m#%d\e[0;m(\e[2;35m%d\e[0;m)%p{\n"
                "%s    prev: %s,\n"
                "%s    data: %s,\n"
                "%s    next: %s\n"
                "%s}",
                list->std.ce->name->val,
                list->std.handle,
                list->std.gc.refcount, list,//&list->std,
                t, tmp_prev,
                t, tmp_data,
                t, tmp_next,
                t);
        g_free(tmp_prev);
        g_free(tmp_data);
        g_free(tmp_next);
    } else if (G_IS_OBJECT(ptr->ptr)) {
        str = g_strdup_printf("\e[2;34m%s\e[0;m(\e[2;35m%d\e[0;m)\e[2;31m#%d\e[0;m{ %s}",
                              g_type_name_from_instance((GTypeInstance*)ptr->ptr),
                              z_object->gc.refcount,
                              z_object->handle,
                              "...");
    } else {// for next, prev
        str = g_strdup_printf("\e[2;34m%s\e[0;m(\e[2;35m%d\e[0;m)\e[2;31m#%d\e[0;m{ %s}",
                              z_object->ce->name->val,
                              z_object->gc.refcount,
                              z_object->handle,
                              "..."
                              );
    }
    g_free(t);


    return str;
}

#include "php_gtk/button.h"
static char*
php_glib_list_dump_zval(zval *data, int tab) {
    char *str = NULL;
    char *tmp = NULL;
    char *t = g_strdup_printf("%*.s", tab*4, "");
    if (ZVAL_IS_NULL(data)) {
        str = g_strdup_printf("\e[2;34m%s\e[0;m{ %s}", "zval", "NULL");
    } else if (Z_TYPE_P(data)==IS_STRING) {
        str = g_strdup_printf("\e[2;34m%s\e[0;m{ \e[1;31m\"%s\"\e[0;m}", "zval", data->value.str->val);
    } else if (Z_TYPE_P(data)==IS_LONG) {
        str = g_strdup_printf("\e[2;34m%s\e[0;m{ %ld}", "zval", data->value.lval);
    } else if (Z_TYPE_P(data)==IS_OBJECT) {
        tmp = php_glib_list_dump_zobj(data->value.obj, tab+1);
        str = g_strdup_printf("\e[2;34m%s\e[0;m(\e[2;35m%d\e[0;m){ %s\n%s}",
                              "zval",
                              data->value.counted->gc.refcount,
                              tmp,
                              t);
        g_free(tmp);
    } else {
        str = g_strdup_printf("\e[2;34m%s\e[0;m{ %s}", "zval", "Unknow");
    }
    g_free(t);
    return str;
}
static char *php_glib_list_dump(php_glib_list *list, int tab){

    char *str = php_glib_list_dump_zobj(&list->std, tab);
    g_list_free(recursions);
    recursions=NULL;
    return str;
}


/* {{{ proto string php_glib_list_dump(GList list)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(g_list_dump)
{
    zval *list = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "z", &list) == FAILURE) {
        return;
    }

    char *str = php_glib_list_dump_zval(list, 0);
    g_print("%s\n", str);
    g_free(str);
    g_list_free(recursions);
    recursions=NULL;

    RETURN_NULL();
}
/* }}} */
