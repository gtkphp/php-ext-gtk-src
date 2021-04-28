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
#include "php_gtk.h"
#include "object.h"

#include "php_doc/tag.h";
#include "php_doc/comment.h";

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_gobject_object_class_entry;
//HashTable             php_gobject_object_prop_handlers;
zend_object_handlers  php_gobject_object_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry php_gobject_object_methods[] = {
    PHP_ME(g_object, __construct, arginfo_g_object___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/
static void  php_gobject_object_unset_property(zval *object, zval *member, void **cache_slot);
static void  php_gobject_object_write_property(zval *object, zval *member, zval *value, void **cache_slot);
static zval* php_gobject_object_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv);
static char* php_gobject_object_dump(php_gobject_object *list, int tab);

static void
php_gobject_object_unset_dimension(zval *object, zval *offset) {
    //php_gobject *list = ZVAL_GET_PHP_GOBJECT_OBJECT(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
        // @TODO
        //zend_hash_index_del(list->prop_handler, );
        // php_gobject
        break;
    case IS_STRING:
        php_gobject_object_unset_property(object, offset, &cache);
        break;
    default:
        break;
    }
}

static void
php_gobject_object_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_gobject_object_write_property(object, &member, value, &cache);
}

static zval*
php_gobject_object_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
        return NULL;
    }

    php_gobject_object *intern = ZVAL_GET_PHP_GOBJECT_OBJECT(object);
    php_gobject_object *list;
    void *cache=NULL;

    if (Z_TYPE_P(offset)==IS_LONG) {
        ZVAL_NULL(rv);
        return rv;
    } else if (Z_TYPE_P(offset)==IS_STRING) {
        return php_gobject_object_read_property(object, offset, type, &cache, rv);
    } else {
        // error
    }

    return rv;
} /* }}} end php_g_hash_table_read_dimension */

static int
php_gobject_object_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

/* updates *count to hold the number of elements present and returns SUCCESS.
 * Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_gobject_object_count_elements(zval *object, zend_long *count) {

    *count = 0;

    return SUCCESS;
}

static int
php_gobject_object_cast_object(zval *readobj, zval *retval, int type)
{
    g_print("php_gobject_object_cast_object\n");
    ZVAL_NULL(retval);

    return FAILURE;
}

static HashTable*
php_gobject_object_get_properties(zval *object){
    php_gobject_object  *self =  ZVAL_GET_PHP_GOBJECT_OBJECT(object);
    HashTable *props = self->properties;
    if (props==NULL) {
        ALLOC_HASHTABLE(self->properties);
        props = self->properties;
    } else {
        // TODO: rebuild the props( update)
        return props;// Else leaks : zend_hash_next_index_insert
    }

    /*
    zend_long length = php_gobject_object_length(self);

    zend_hash_init(props, length, NULL, ZVAL_PTR_DTOR, 1);

    zval data;

    php_gobject_object *it;
    for(it=php_gobject_object_first(self); it; it = it->next){
        ZVAL_COPY(&data, &it->data);
        zend_hash_next_index_insert(props, &data);
    }
    */

    return props;
}

static HashTable*
php_gobject_object_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_gobject_object  *obj =  ZVAL_GET_PHP_GOBJECT_OBJECT(object);
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

    /*
    zval prev; ZVAL_SET_PHP_GOBJECT_OBJECT(&prev, obj->prev);
    zend_hash_str_update(debug_info, "prev", sizeof("prev")-1, &prev);

    zval data; ZVAL_COPY(&data, &obj->data);
    zend_hash_str_update(debug_info, "data", sizeof("data")-1, &data);

    zval next; ZVAL_SET_PHP_GOBJECT_OBJECT(&next, obj->next);
    zend_hash_str_update(debug_info, "next", sizeof("next")-1, &next);
    */

    return debug_info;
}
/* }}} */

static void
php_gobject_object_unset_property(zval *object, zval *member, void **cache_slot) {
    php_gobject_object *obj = ZVAL_GET_PHP_GOBJECT_OBJECT(object);
    zend_string *member_str = zval_get_string(member);
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (zend_string_equals_literal(member->value.str, "next")
     || zend_string_equals_literal(member->value.str, "prev")
     || zend_string_equals_literal(member->value.str, "data") ) {
#if 0
        if (ZVAL_IS_PHP_GOBJECT_OBJECT(value)) {
            // do unset(object->next) and php_gobject_object_insert(object, value, 0);
        } else {
            zend_string *type = zend_zval_get_type(value);
            zend_error(E_USER_WARNING, "Cannot assign %s to property GObject::$next of type GObject", type->val);
        }
#else
        zend_error(E_USER_WARNING, "Readonly property GObject::$%s", member->value.str->val);
#endif
        return;
    }
    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}

/* {{{ php_gobject_object_write_property */
static void
php_gobject_object_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_gobject_object *obj = ZVAL_GET_PHP_GOBJECT_OBJECT(object);
    zend_string *member_str = zval_get_string(member);
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (zend_string_equals_literal(member->value.str, "next")
     || zend_string_equals_literal(member->value.str, "prev")
     || zend_string_equals_literal(member->value.str, "data") ) {
#if 0
        if (ZVAL_IS_PHP_GOBJECT_OBJECT(value)) {
            // do unset(object->next) and php_gobject_object_insert(object, value, 0);
        } else {
            zend_string *type = zend_zval_get_type(value);
            zend_error(E_USER_WARNING, "Cannot assign %s to property GObject::$next of type GObject", type->val);
        }
#else
        zend_error(E_USER_WARNING, "Readonly property GObject::$%s", member->value.str->val);
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
php_gobject_object_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_gobject_object *obj = ZVAL_GET_PHP_GOBJECT_OBJECT(object);
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    /*
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
    */

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    retval = std_hnd->read_property(object, member, type, cache_slot, rv);

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ php_gobject_object_free_object */
static void
php_gobject_object_free_object(zend_object *object)
{
    php_gobject_object *intern = ZOBJ_TO_PHP_GOBJECT_OBJECT(object);
    TRACE("php_gobject_object_free_object(\"%s\") / %d\n", intern->data.value.str->val, object->gc.refcount);

#if 0
    // TODO: connect destroy to set ->ptr to NULL
    if (intern->ptr) {
        g_clear_object(&intern->ptr);
    }
#endif

    if (intern->properties!=NULL) {
        zend_hash_destroy(intern->properties);
        efree(intern->properties);
        intern->properties=NULL;
    }

    zend_object_std_dtor(&intern->std);
    //efree(intern);
}
/* }}} php_gobject_object_free_object */

static void
php_gobject_object_dtor_object(zend_object *obj) {
    php_gobject_object *intern = ZOBJ_TO_PHP_GOBJECT_OBJECT(obj);
    TRACE("php_gobject_object_dtor_object(\"%s\") / %d\n", intern->data.value.str->val, obj->gc.refcount);

    /*
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
    */
}


/* {{{ php_gobject_object_create_object */
static zend_object*
php_gobject_object_create_object(zend_class_entry *class_type)
{
    php_gobject_object *intern = ecalloc(1, sizeof(php_gobject_object) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);


    intern->ptr = g_object_new(G_TYPE_OBJECT, NULL); //NULL;// new GObject ?
    intern->properties = NULL;

    intern->std.handlers = &php_gobject_object_handlers;

    TRACE("php_gobject_object_create_object(%p) / %d\n", &intern->std, intern->std.gc.refcount);
    return &intern->std;
}
/* }}} php_gobject_object_create_object */

/*
static void php_gobject_object_dtor_prop_handler(zval *zv)
{
    free(Z_PTR_P(zv));
}
*/

static zend_object_handlers*
php_gobject_object_get_handlers()
{
    memcpy(&php_gobject_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_gobject_object_handlers.offset = PHP_GOBJECT_OBJECT_OFFSET;
    //php_gobject_object_handlers.clone_obj;
    //php_gobject_object_handlers.compare;
    //php_gobject_object_handlers.compare_objects;
    //php_gobject_object_handlers.get_constructor;
    php_gobject_object_handlers.dtor_obj = php_gobject_object_dtor_object;
    php_gobject_object_handlers.free_obj = php_gobject_object_free_object;
    php_gobject_object_handlers.read_property = php_gobject_object_read_property;
    php_gobject_object_handlers.write_property = php_gobject_object_write_property;
    php_gobject_object_handlers.unset_property = php_gobject_object_unset_property;
    //php_gobject_object_handlers.get_property_ptr_ptr = php_gobject_object_get_property_ptr_ptr;

    php_gobject_object_handlers.get_debug_info = php_gobject_object_get_debug_info;
    php_gobject_object_handlers.get_properties = php_gobject_object_get_properties;//get_properties_for TODO php 8.0
    //php_gobject_object_handlers.set = php_gobject_object_set;
    php_gobject_object_handlers.cast_object = php_gobject_object_cast_object;

    php_gobject_object_handlers.count_elements = php_gobject_object_count_elements;
    php_gobject_object_handlers.has_dimension = php_gobject_object_has_dimension;
    php_gobject_object_handlers.read_dimension = php_gobject_object_read_dimension;
    php_gobject_object_handlers.unset_dimension = php_gobject_object_unset_dimension;
    php_gobject_object_handlers.write_dimension = php_gobject_object_write_dimension;


    return &php_gobject_object_handlers;
}



/*----------------------------------------------------------------------+
| PHP_MINIT                                                            |
+----------------------------------------------------------------------*/

/*{{{ php_gobject_object_class_init */
zend_class_entry*
php_gobject_object_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gobject_object_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "GObject", php_gobject_object_methods);
    php_gobject_object_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_gobject_object_class_entry->create_object = php_gobject_object_create_object;
    //ce->serialize;
    /*
    zend_hash_init(&php_gobject_object_prop_handlers, 0, NULL, php_gobject_object_dtor_prop_handler, 1);
    php_gobject_object_register_prop_handler(&php_gobject_object_prop_handlers, "prev", sizeof("prev")-1, php_gobject_object_read_prev, php_gobject_object_write_prev);
    php_gobject_object_register_prop_handler(&php_gobject_object_prop_handlers, "data", sizeof("data")-1, php_gobject_object_read_data, php_gobject_object_write_data);
    php_gobject_object_register_prop_handler(&php_gobject_object_prop_handlers, "next", sizeof("next")-1, php_gobject_object_read_next, php_gobject_object_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_gobject_object_prop_handlers);
    */

    return php_gobject_object_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/
zend_function*
php_gobject_get_user_method(zend_object *zobject, char *name) {

    php_doc_block *doc_comment;

    zend_object *zobj = zobject;//&widget->parent_instance.std;
    zend_class_entry *top = zobj->ce;
    zend_class_entry *base = php_gobject_object_class_entry;
    while (top) {
        zend_function *func;
        zend_string *key;
        ZEND_HASH_FOREACH_STR_KEY_PTR(&top->function_table, key, func) {
            if (func->type == ZEND_USER_FUNCTION) {
                //g_print("%s\n", func->op_array.doc_comment->val);
                //g_print("function %s - %s\n", key->val, func->common.function_name->val);
                char *str = func->op_array.doc_comment->val;
                doc_comment = php_doc_comment_create(str/*, &error*/);
                php_doc_tag *tag = php_doc_comment_get_tag_by_name(doc_comment, "override");
                if (tag && 0==g_strcmp0(tag->value, name)) {
                    php_doc_comment_free(doc_comment);
                    return func;
                }
                php_doc_comment_free(doc_comment);
            }
        } ZEND_HASH_FOREACH_END();

        break;
        top = top->parent;
        if (top==base)
            break;
    }

    return NULL;
}


/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
php_gobject_object*
php_gobject_object_new(GObject *object) {
    zend_object *zobject = php_gobject_object_create_object(php_gobject_object_class_entry);
    php_gobject_object *gobject = ZOBJ_TO_PHP_GOBJECT_OBJECT(zobject);
    gobject->ptr = object;

    return gobject;
}

php_gobject_object *
php_gobject_object_connect(php_gobject_object *list, zval *data) {

    return NULL;
}



/*----------------------------------------------------------------------+
| PHP_METHOD                                                           |
+----------------------------------------------------------------------*/

/* {{{ GObject::__construct() */
PHP_METHOD(g_object, __construct)
{
    /*
    zval *data=NULL;
    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();
    */

    zend_object *zobj = Z_OBJ_P(getThis());
    php_gobject_object *self = ZOBJ_TO_PHP_GOBJECT_OBJECT(zobj);

}
/* }}} */

/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/

/* {{{ proto GObject g_object_connect(GObject list, mixed data) */
PHP_FUNCTION(g_object_connect)
{
    int argc;
    char *detail;
    zval *object = NULL;
    size_t detail_len;
    zval *args = NULL;
    zval *zcallable;
    zval *zuser_data;

    ZEND_PARSE_PARAMETERS_START(4, -1)
        Z_PARAM_ZVAL(object);
        Z_PARAM_STRING(detail, detail_len);
        Z_PARAM_ZVAL(zcallable);
        Z_PARAM_ZVAL(zuser_data);
        Z_PARAM_VARIADIC('+', args, argc);
    ZEND_PARSE_PARAMETERS_END();

    int i;
    int num_event = (argc-1)/3;
    int arg_missing = (argc-1)%3;
    if (0 != arg_missing) {
        php_printf("Error. We just asume the correct group param\n");
        //num_event = (argc-1-arg_missing)/3;
    }

    php_gobject_object *gobject = ZVAL_GET_PHP_GOBJECT_OBJECT(object);

    ///@see: /home/dev/Projects/php-ubuntu/ext/gtkml/php_gobject/object.c

}/* }}} */

/* {{{ proto g_object_unref(GObject object) */
PHP_FUNCTION(g_object_unref)
{
    zval *zobject = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL_DEREF(zobject);
    ZEND_PARSE_PARAMETERS_END();

    php_gobject_object *object = ZVAL_GET_PHP_GOBJECT_OBJECT(zobject);
    GObject *gobject = object->ptr;

    //g_print("g_object_unref();    zval(%d){%d}\n", zobject->value.counted->gc.refcount, gobject->ref_count);
    if (gobject && gobject->ref_count==1) {
        object->ptr = NULL;
    }
    if (zobject->value.counted->gc.refcount<=2) {
        //ZVAL_NULL(zobject);
    }
    g_object_unref(gobject);


    //zend_object_release(&object->std);

}/* }}} */

/* {{{ proto g_object_unref(GObject object) */
PHP_FUNCTION(g_object_ref)
{
    zval *zobject = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zobject);
    ZEND_PARSE_PARAMETERS_END();

    php_gobject_object *gobject = ZVAL_GET_PHP_GOBJECT_OBJECT(zobject);

    //GC_REFCOUNT(&gobject->std)++;
    g_object_ref(gobject->ptr);

}/* }}} */

