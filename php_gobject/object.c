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
#include "object-extends.h"
#include "signal.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_gobject_object_class_entry;
//HashTable             php_gobject_object_prop_handlers;
zend_object_handlers  php_gobject_object_handlers;

//extern zend_object *php_gobject_hack_dirty_bad_smel;
static zend_object *php_gobject_hack_dirty_bad_smel=0;
void push_zend(zend_object *zob){
    php_gobject_hack_dirty_bad_smel = zob;
}
zend_object *pop_zend(){
    return php_gobject_hack_dirty_bad_smel;
}

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
static zval *php_gobject_object_write_property(zend_object *zobj, zend_string *member, zval *value, void **cache_slot);
static zval *php_gobject_object_read_property(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv);

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
    //php_gobject_object_write_property(object, &member, value, &cache);
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
php_gobject_object_cast_object(zend_object *readobj, zval *retval, int type)
{
    g_print("Error: php_gobject_object_cast_object(%d, %d)\n", type, IS_STRING);
    ZVAL_NULL(retval);

    return FAILURE;
}

static HashTable*
php_gobject_object_get_properties(zval *object){
    php_gobject_object  *self =  ZVAL_GET_PHP_GOBJECT_OBJECT(object);
    if (self==NULL) {
        return NULL;
    }
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
php_gobject_object_get_debug_info(zend_object *object, int *is_temp) /* {{{ */
{
    php_gobject_object  *obj =  ZOBJ_TO_PHP_GOBJECT_OBJECT(object);
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
static zval*
php_gobject_object_write_property(zend_object *zobj, zend_string *member, zval *value, void **cache_slot)
{
    php_gobject_object *obj = ZOBJ_TO_PHP_GOBJECT_OBJECT(zobj);
    TRACE("%s(%s)\n", __FUNCTION__, member->val);

    // static GtkObject

    // check installed properties
    GObjectClass *obj_class = G_OBJECT_GET_CLASS(obj->ptr);
    GParamSpec *spec = g_object_class_find_property(obj_class, member->val);
    if (spec) {
        GValue gvalue = G_VALUE_INIT;
        g_value_init(&gvalue, G_TYPE_INT);
        g_value_set_int(&gvalue, Z_LVAL_P(value));
        zend_object_handlers *std_hnd = zend_get_std_object_handlers();
        zval *ptr = std_hnd->write_property(zobj, member, value, cache_slot);
        g_object_set_property(obj->ptr, member->val, &gvalue);
        return ptr;
    }

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    return std_hnd->write_property(zobj, member, value, cache_slot);
}
/* }}} */

static zval zval_ret;
/* {{{ gtk_read_property */
static zval*
php_gobject_object_read_property(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv)
{
    php_gobject_object *obj = ZOBJ_TO_PHP_GOBJECT_OBJECT(object);
    zval *retval;
    TRACE("%s(%s)\n", __FUNCTION__, member->val);

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

    return retval;
}
/* }}} */

/* {{{ php_gobject_object_free_object */
static void
php_gobject_object_free_object(zend_object *object)
{
    php_gobject_object *intern = ZOBJ_TO_PHP_GOBJECT_OBJECT(object);
    TRACE("php_gobject_object_free_object(\"%s\") / %d\n", intern->data.value.str->val, object->gc.refcount);
    //php_printf("php_gobject_object_free_object %p(%p) - %d\n", intern->ptr, intern, object->gc.refcount);

#if 1
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
    //php_printf("php_gobject_object_dtor_object- %d\n", obj->gc.refcount);

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
    php_gobject_object *intern = zend_object_alloc(sizeof(php_gobject_object), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = &php_gobject_object_handlers;
    intern->properties = NULL;
    intern->ptr = NULL;

    intern->ptr = php_gobject_object_extends(intern);// after handlers

    return &intern->std;
}
/* }}} php_gobject_object_create_object */


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

/*{{{ php_gobject_object_class_minit */
zend_class_entry*
php_gobject_object_class_minit(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
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

#if 0
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
#endif

    return NULL;
}


/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
php_gobject_object*
php_gobject_object_new(GObject *object) {
    //printf("\t\t php_gobject_object_new\n");
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

typedef enum _ConnectSignal {            // flag = AFTER|SWAPPE|OBJECT
    CONNECT_SIGNAL,                      // 0x00
    CONNECT_OBJECT_SIGNAL,               // 0x01
    CONNECT_SIGNAL_AFTER,                // 0x02 = 0x00 | 0x02
    CONNECT_OBJECT_SIGNAL_AFTER,         // 0x03 = 0x00 | 0x02 | 0x01

    CONNECT_SWAPPED_SIGNAL,              // 0x04
    CONNECT_SWAPPED_OBJECT_SIGNAL,       // 0x05
    CONNECT_SWAPPED_SIGNAL_AFTER,        // 0x06 = 0x04 | 0x02
    CONNECT_SWAPPED_OBJECT_SIGNAL_AFTER, // 0x07 = 0x04 | 0x02 | 0x01
    CONNECT_UNKNOW,
} ConnectSignal;
#define CONNECT_OBJECT_MASK 0x01
#define CONNECT_AFTER_MASK 0x02
#define CONNECT_SWAPPED_MASK 0x04

typedef struct _SignalEntry {
    char *modifier;
    ConnectSignal signal;
} SignalEntry;

static SignalEntry php_gobject_object_signals[] = {
    //{"notify",                      CONNECT_SIGNAL},
    {"signal",                      CONNECT_SIGNAL},
    {"object-signal",               CONNECT_OBJECT_SIGNAL},
    {"swapped-signal",              CONNECT_SWAPPED_SIGNAL},
    {"swapped-object-signal",       CONNECT_SWAPPED_OBJECT_SIGNAL},
    {"signal-after",                CONNECT_SIGNAL_AFTER},
    {"object-signal-after",         CONNECT_OBJECT_SIGNAL_AFTER},
    {"swapped-signal-after",        CONNECT_SWAPPED_SIGNAL_AFTER},
    {"swapped-object-signal-after", CONNECT_SWAPPED_OBJECT_SIGNAL_AFTER},
    {NULL}
};


static ConnectSignal php_gobject_object_connect_signal_lookup(char *modifier, size_t modifier_len) {
    SignalEntry *entry;
    int i;

    if (NULL==*modifier) {
        return CONNECT_SIGNAL;
    }

    for(i = 0; NULL!=php_gobject_object_signals[i].modifier; i++) {
        entry = &php_gobject_object_signals[i];
        if (0==strncmp(entry->modifier, modifier, modifier_len)) {
            return entry->signal;
        }
    }
    g_print("Error: ConnectSignal not found for detail: '%s'\n", modifier);

    return CONNECT_UNKNOW;
}
static char *normalize_signal_detail(char *signal_detail, char **modifier, char **signal, char **detail) {
    if (NULL==signal_detail || NULL==signal_detail[0]) {
        *modifier=NULL;
        *signal=NULL;
        *detail=NULL;
        g_print("Error string null or empty\n");
        return 0;
    }
    char *ret = g_strdup(signal_detail);

    char *pos[] = {ret, 0, 0};
    char *ptr;
    char *str=ret;
    for(int i=1; i<3; i++) {
        ptr = strstr(str, "::");
        if (NULL==ptr) break;
        str = pos[i] = ptr+2;
        ptr[0] = '\0';
    }
    char *modifier_len = pos[1]>pos[0] ? pos[1]-pos[0]-2 : 0;

    if ( modifier_len && CONNECT_UNKNOW==php_gobject_object_connect_signal_lookup(pos[0], modifier_len)) {
        *modifier = 0;
        *signal = pos[0];
        *detail = pos[2];
    } else {
        *modifier = pos[0];
        *signal = pos[1];
        *detail = pos[2];
    }


    //for (pos=*modifier ; *pos; pos++) if('_'==*pos) *pos = '-'; else *pos = tolower(*pos);
    //for (pos=*detail ; *pos; pos++) if('_'==*pos) *pos = '-'; else  *pos = tolower(*pos);

    return ret;
}

/* {{{ proto GObject g_object_connect(GObject list, mixed data) */
PHP_FUNCTION(g_object_connect)
{
    int argc;
    char *signal_detail;
    size_t signal_detail_len;
    zval *zobject = NULL;
    zval *args = NULL;
    zval *zcallable;
    zval *zuser_data;

    ZEND_PARSE_PARAMETERS_START(4, -1)
        Z_PARAM_ZVAL(zobject);
        Z_PARAM_STRING(signal_detail, signal_detail_len);
        Z_PARAM_ZVAL(zcallable);
        Z_PARAM_ZVAL(zuser_data);
        Z_PARAM_VARIADIC('+', args, argc);
    ZEND_PARSE_PARAMETERS_END();

    int i;
    int num_event = (argc-1)/3;
    int arg_missing = (argc-1)%3;// check: call with multiple args
    if (0 != arg_missing) {
        php_printf("Error. We just asume the correct group param\n");
        //num_event = (argc-1-arg_missing)/3;
    }

    php_gobject_object *gobject = ZVAL_GET_PHP_GOBJECT_OBJECT(zobject);

    char *modifier=NULL;
    char *signal=NULL;
    char *detail=NULL;

    ConnectSignal flags;


    char *tmp = normalize_signal_detail(signal_detail, &modifier, &signal, &detail);
    flags = php_gobject_object_connect_signal_lookup(modifier, strlen(modifier));
    if(flags&CONNECT_OBJECT_MASK) {
        /*
        zval *zdestroy_data = NULL;
        zend_string *detailed_signal = zend_string_init(signal, strlen(signal), 0);
        zend_long connect_flags = flags>>1;
        zend_long ret = php_g_signal_connect_object(zobject, detailed_signal, zcallable, zuser_data, zdestroy_data, connect_flags);
        zend_string_release(detailed_signal);
        */
    } else {
        //g_print("%s = [%s,%s,%s]\n", signal_detail, modifier, signal, detail);
        zval *zdestroy_data = NULL;
        zend_string *detailed_signal = zend_string_init(signal, strlen(signal), 0);
        zend_long connect_flags = flags>>1;
        zend_long handle = php_gobject_signal_connect_data(zobject, detailed_signal, zcallable, zuser_data, zdestroy_data, connect_flags);
        zend_string_release(detailed_signal);
    }
    g_free(tmp);

    for(i=0; i<num_event; i++) {
        zval *zval_detail = &args[i*3];
        signal_detail = zval_detail->value.str->val;
        signal_detail_len = zval_detail->value.str->len;
        assert(zval_get_type(zval_detail)==IS_STRING);

        ZVAL_COPY(zcallable, &args[i*3+1]);
        ZVAL_COPY(zuser_data, &args[i*3+2]);// free it in

        char *tmp = normalize_signal_detail(signal_detail, &modifier, &signal, &detail);
        flags = php_gobject_object_connect_signal_lookup(modifier, strlen(modifier));

        if(flags&CONNECT_OBJECT_MASK) {
            /*
            zval *zdestroy_data = NULL;
            zend_string *detailed_signal = zend_string_init(signal, strlen(signal), 0);
            zend_long connect_flags = flags>>1;
            zend_long ret = php_g_signal_connect_object(zobject, detailed_signal, zcallable, zuser_data, zdestroy_data, connect_flags);
            zend_string_release(detailed_signal);
            */
        } else {
            zval *zdestroy_data = NULL;
            //zend_string *detailed_signal = zend_string_init(signal, strlen(signal), 0);
            zend_string *detailed_signal = zend_string_init(signal, strlen(signal), 0);
            zend_long connect_flags = flags>>1;
            //g_print("%s = [%s,%s]\n", signal, modifier, detail);
            zend_long ret = php_gobject_signal_connect_data(zobject, detailed_signal, zcallable, zuser_data, zdestroy_data, connect_flags);
            zend_string_release(detailed_signal);
        }
        g_free(tmp);

    }


}/* }}} */

/* {{{ proto g_object_unref(GObject object) */
PHP_FUNCTION(g_object_unref)
{
    zval *zobject = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL_EX2(zobject, 0, 1, 0);
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
    //g_object_ref(gobject->ptr);

    //guint signal_id = 1;// php_gobject_object_ext_signals[0];
    ///gpointer user_data= GINT_TO_POINTER(0x08);
    //g_signal_emit (G_OBJECT(gobject->ptr), signal_id, 0, user_data);

    //int ret;
    //g_signal_emit_by_name(G_OBJECT(gobject->ptr), "notify::zoom", user_data, &ret);
    //g_signal_emit_by_name(G_OBJECT(gobject->ptr), "changed", user_data, &ret);
    int ret;
    g_signal_emit_by_name(G_OBJECT(gobject->ptr), "changed", 14, &ret);

    //printf("g_signal_emit_by_name() ret=%d\n", ret);

}/* }}} */

#include "value.h"
/* {{{ proto g_object_unref(GObject object) */
PHP_FUNCTION(g_object_set_property)
{
    zend_object *object = NULL;
    zend_string *property_name = NULL;
    zend_object *value = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJ(object);
        Z_PARAM_STR(property_name);
        Z_PARAM_OBJ(value);
    ZEND_PARSE_PARAMETERS_END();

    php_gobject_object *zobject = ZOBJ_TO_PHP_GOBJECT_OBJECT(object);
    php_gobject_value *zvalue = ZOBJ_TO_PHP_GOBJECT_VALUE(value);

    g_object_set_property(G_OBJECT(zobject->ptr), property_name->val, &zvalue->gvalue);

}/* }}} */
