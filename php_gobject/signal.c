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

#include <gtk/gtk.h>
#include "signal.h"
#include "object.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_gobject_signal_class_entry;
//HashTable             php_gobject_signal_prop_handlers;
zend_object_handlers  php_gobject_signal_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
| Internal                                                             |
+----------------------------------------------------------------------*/

static const zend_function_entry php_gobject_signal_methods[] = {
    PHP_ME(g_signal, __construct, arginfo_g_signal___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/
static void  php_gobject_signal_unset_property(zval *object, zval *member, void **cache_slot);
static void  php_gobject_signal_write_property(zval *object, zval *member, zval *value, void **cache_slot);
static zval* php_gobject_signal_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv);

static void
php_gobject_signal_unset_dimension(zval *object, zval *offset) {
    //php_gobject_signal *list = ZVAL_GET_PHP_GOBJECT_SIGNAL(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
        // @TODO
        //zend_hash_index_del(list->prop_handler, );
        // php_gobject_signal
        break;
    case IS_STRING:
        php_gobject_signal_unset_property(object, offset, &cache);
        break;
    default:
        break;
    }
}

static void
php_gobject_signal_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_gobject_signal_write_property(object, &member, value, &cache);
}

static zval*
php_gobject_signal_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
        return NULL;
    }

    php_gobject_signal *intern = ZVAL_GET_PHP_GOBJECT_SIGNAL(object);
    php_gobject_signal *list;
    void *cache=NULL;

    if (Z_TYPE_P(offset)==IS_LONG) {
        ZVAL_NULL(rv);
        return rv;
    } else if (Z_TYPE_P(offset)==IS_STRING) {
        return php_gobject_signal_read_property(object, offset, type, &cache, rv);
    } else {
        // error
    }

    return rv;
} /* }}} end php_g_hash_table_read_dimension */

static int
php_gobject_signal_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

/* updates *count to hold the number of elements present and returns SUCCESS.
 * Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_gobject_signal_count_elements(zval *object, zend_long *count) {

    *count = 0;

    return SUCCESS;
}

static int
php_gobject_signal_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}

static HashTable*
php_gobject_signal_get_properties(zval *object){
    php_gobject_signal  *self =  ZVAL_GET_PHP_GOBJECT_SIGNAL(object);
    HashTable *props = self->properties;
    if (props==NULL) {
        ALLOC_HASHTABLE(self->properties);
        props = self->properties;
    } else {
        // TODO: rebuild the props( update)
        return props;// Else leaks : zend_hash_next_index_insert
    }

    return props;
}

static HashTable*
php_gobject_signal_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_gobject_signal  *obj =  ZVAL_GET_PHP_GOBJECT_SIGNAL(object);
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


    return debug_info;
}
/* }}} */

static void
php_gobject_signal_unset_property(zval *object, zval *member, void **cache_slot) {
    php_gobject_signal *obj = ZVAL_GET_PHP_GOBJECT_SIGNAL(object);
    zend_string *member_str = zval_get_string(member);
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}

/* {{{ php_gobject_signal_write_property */
static void
php_gobject_signal_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_gobject_signal *obj = ZVAL_GET_PHP_GOBJECT_SIGNAL(object);
    zend_string *member_str = zval_get_string(member);
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->write_property(object, member, value, cache_slot);

    zend_string_release(member_str);
}
/* }}} */

static zval zval_ret;
/* {{{ gtk_read_property */
static zval*
php_gobject_signal_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_gobject_signal *obj = ZVAL_GET_PHP_GOBJECT_SIGNAL(object);
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    retval = std_hnd->read_property(object, member, type, cache_slot, rv);

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ php_gobject_signal_free_object */
static void
php_gobject_signal_free_object(zend_object *object)
{
    php_gobject_signal *intern = ZOBJ_TO_PHP_GOBJECT_SIGNAL(object);
    TRACE("php_gobject_signal_free_object(\"%s\") / %d\n", intern->data.value.str->val, object->gc.refcount);

    if (intern->properties!=NULL) {
        zend_hash_destroy(intern->properties);
        efree(intern->properties);
        intern->properties=NULL;
    }

    zend_object_std_dtor(&intern->std);
    //efree(intern);
}
/* }}} php_gobject_signal_free_object */

static void
php_gobject_signal_dtor_object(zend_object *obj) {
    php_gobject_signal *intern = ZOBJ_TO_PHP_GOBJECT_SIGNAL(obj);
    TRACE("php_gobject_signal_dtor_object(\"%s\") / %d\n", intern->data.value.str->val, obj->gc.refcount);

}

/* {{{ php_gobject_signal_create_object */
static zend_object*
php_gobject_signal_create_object(zend_class_entry *class_type)
{
    php_gobject_signal *intern = ecalloc(1, sizeof(php_gobject_signal) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);


    intern->properties = NULL;

    intern->std.handlers = &php_gobject_signal_handlers;

    TRACE("php_gobject_signal_create_object(%p) / %d\n", &intern->std, intern->std.gc.refcount);
    return &intern->std;
}
/* }}} php_gobject_signal_create_object */

/*
static void php_gobject_signal_dtor_prop_handler(zval *zv)
{
    free(Z_PTR_P(zv));
}
*/

static zend_object_handlers*
php_gobject_signal_get_handlers()
{
    memcpy(&php_gobject_signal_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_gobject_signal_handlers.offset = PHP_GOBJECT_SIGNAL_OFFSET;
    //php_gobject_signal_handlers.clone_obj;
    //php_gobject_signal_handlers.compare;
    //php_gobject_signal_handlers.compare_objects;
    //php_gobject_signal_handlers.get_constructor;
    php_gobject_signal_handlers.dtor_obj = php_gobject_signal_dtor_object;
    php_gobject_signal_handlers.free_obj = php_gobject_signal_free_object;
    php_gobject_signal_handlers.read_property = php_gobject_signal_read_property;
    php_gobject_signal_handlers.write_property = php_gobject_signal_write_property;
    php_gobject_signal_handlers.unset_property = php_gobject_signal_unset_property;
    //php_gobject_signal_handlers.get_property_ptr_ptr = php_gobject_signal_get_property_ptr_ptr;

    php_gobject_signal_handlers.get_debug_info = php_gobject_signal_get_debug_info;
    php_gobject_signal_handlers.get_properties = php_gobject_signal_get_properties;//get_properties_for TODO php 8.0
    //php_gobject_signal_handlers.set = php_gobject_signal_set;
    php_gobject_signal_handlers.cast_object = php_gobject_signal_cast_object;

    php_gobject_signal_handlers.count_elements = php_gobject_signal_count_elements;
    php_gobject_signal_handlers.has_dimension = php_gobject_signal_has_dimension;
    php_gobject_signal_handlers.read_dimension = php_gobject_signal_read_dimension;
    php_gobject_signal_handlers.unset_dimension = php_gobject_signal_unset_dimension;
    php_gobject_signal_handlers.write_dimension = php_gobject_signal_write_dimension;


    return &php_gobject_signal_handlers;
}



/*----------------------------------------------------------------------+
| PHP_MINIT                                                            |
+----------------------------------------------------------------------*/

/*{{{ php_gobject_signal_class_init */
zend_class_entry*
php_gobject_signal_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gobject_signal_get_handlers();
    //INIT_NS_CLASS_ENTRY((*ce), "Gnome\\G", "List", php_gobject_signal_methods);
    INIT_CLASS_ENTRY((*container_ce), "GSignal", php_gobject_signal_methods);
    container_ce->create_object = php_gobject_signal_create_object;
    //ce->serialize;
    php_gobject_signal_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    /*
    zend_hash_init(&php_gobject_signal_prop_handlers, 0, NULL, php_gobject_signal_dtor_prop_handler, 1);
    php_gobject_signal_register_prop_handler(&php_gobject_signal_prop_handlers, "prev", sizeof("prev")-1, php_gobject_signal_read_prev, php_gobject_signal_write_prev);
    php_gobject_signal_register_prop_handler(&php_gobject_signal_prop_handlers, "data", sizeof("data")-1, php_gobject_signal_read_data, php_gobject_signal_write_data);
    php_gobject_signal_register_prop_handler(&php_gobject_signal_prop_handlers, "next", sizeof("next")-1, php_gobject_signal_read_next, php_gobject_signal_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_gobject_signal_prop_handlers);
    */

    return php_gobject_signal_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/

zend_long
php_gobject_signal_connect_data(zval *instance,
                                zend_string *detailed_signal,
                                zval *handler,// Callback
                                zval *data, // Callback
                                zval *destroy_data,//GClosureNotify
                                zend_long connect_flags) {
#if 0
    g_print("connect: %s\n", detailed_signal->val);


    php_gobject_object *ginstance = ZVAL_IS_PHP_GOBJECT_OBJECT(instance) ? ZVAL_GET_PHP_GOBJECT_OBJECT(instance) : NULL;
    GObject *gobject = G_OBJECT(ginstance->ptr);

    char *event = detailed_signal->val;
    GSignalQuery query;

    guint id = g_signal_lookup(event, G_TYPE_FROM_INSTANCE(gobject));
    g_print("%s::%s\n", ginstance->std.ce->name->val, g_signal_name(id));
    g_signal_query(id, &query);
    g_print("  %s %s(", g_type_name(query.return_type), query.signal_name, query.n_params);

    int x;
    char glue[]="  ";
    glue[0]='\0';
    for (x=0; x<query.n_params; x++) {
        g_print("%s%s", glue, g_type_name(query.param_types[x]));
        glue[0]=',';
    }
    g_print(")\n");

    my_data.num_args = 3;//query.n_params;

    //g_signal_connect_data((gpointer)gobject, detailed_signal->val, my_callback, &my_data, NULL, (GConnectFlags) G_CONNECT_SWAPPED);
    GClosure *closure = g_cclosure_new (G_CALLBACK (my_callback), &my_data, destroy_data);
    g_signal_connect_closure((gpointer)gobject, detailed_signal->val, closure, TRUE);
#endif
    return 0;
}


typedef struct _CallbackHandler {
    zval handler;// user callback
    zval context;// object instance
    GSignalQuery query;
    zval data;// user data

    int connect_flags;
    zval *params;

} CallbackHandler;

static zval*
my_wrapper(gpointer val) {

    return NULL;
}

static void
my_callback(gpointer user_data, ...) {
    CallbackHandler *data = (CallbackHandler*)user_data;
    int num_params = data->query.n_params;
    int result;
    zval retval;

    //G_TYPE_FUNDAMENTAL()
    va_list ap;
    va_start(ap, user_data);

    //TODO: if (0==data->connect_flags) ZVAL_COPY(...);
    // else if (1==data->connect_flags) ZVAL_COPY(...);
    // ...
    switch(data->connect_flags) {
    case 1:// G_CONNECT_AFTER
    break;
    case 2:// G_CONNECT_SWAPPED
    break;
    case 3:// G_CONNECT_AFTER | G_CONNECT_SWAPPED
    break;
    case 0:
    default:
        ZVAL_COPY_VALUE(&data->params[0], &data->context);
        for (int i=0; i<num_params; i++) {
            switch (G_TYPE_FUNDAMENTAL(data->query.param_types[i])) {
            case G_TYPE_OBJECT: {
                GObject *obj = va_arg(ap, GObject*);
                const char *name = g_type_name_from_instance((GTypeInstance*)obj);
                zend_string *class_name = zend_string_init(name, strlen(name), 0);
                zend_class_entry *ce = zend_lookup_class(class_name);
                zend_object *zobject = ce->create_object(ce);
                ZOBJ_TO_PHP_GOBJECT_OBJECT(zobject)->ptr = obj;
                ZVAL_OBJ(&data->params[i+1], zobject);
                zend_string_release(class_name);
            }
            break;
            }
        }
        ZVAL_COPY_VALUE(&data->params[num_params+1], &data->data);

        break;
    }

    va_end(ap);


#if 0
    g_print("%s::%s\n", ginstance->std.ce->name->val, g_signal_name(id));
    g_print("  %s %s(", g_type_name(my_data->query.return_type), my_data->query.signal_name, my_data->query.n_params);
    g_print("%s", g_type_name(my_data->query.itype));

    int x;
    char glue[]=", ";
    //glue[0]='\0';
    for (x=0; x<my_data->query.n_params; x++) {
        g_print("%s%s", glue, g_type_name(my_data->query.param_types[x]));
        glue[0]=',';
    }
    g_print(", %s", "gpointer user_data");
    g_print(")\n");
#endif

    result = call_user_function(NULL, NULL, &data->handler, &retval, num_params+2, data->params);
    if (result == FAILURE) {
        g_print("call_user_function FAILURE\n");
    }

    for (int i=0; i<data->query.n_params; i++) {
        //TODO: switch IS_OBJECT
        zend_object *obj = data->params[i+1].value.obj;
        zend_object_release(obj);
    }

}

//static void
//proxy_user_data_free(ProxyUserData *user_data, GClosure	*closure) {
//    ProxyUserData*data = (ProxyUserData*)user_data;
//    Z_TRY_DELREF(data->callable);
//    g_free(user_data);
//}
static void
destroy_data(gpointer	 data,
             GClosure	*closure) {
    CallbackHandler *user_data = (CallbackHandler*)data;
    Z_TRY_DELREF(user_data->context);
    Z_TRY_DELREF(user_data->data);
    g_free(user_data->params);
    g_free(user_data);
}

zend_long
php_gobject_signal_connect(zval *instance,
                           zend_string *detailed_signal,
                           zval *handler,
                           zval *data)
{
    php_gobject_object *ginstance = ZVAL_IS_PHP_GOBJECT_OBJECT(instance) ? ZVAL_GET_PHP_GOBJECT_OBJECT(instance) : NULL;
    GObject *gobject = G_OBJECT(ginstance->ptr);


    guint id = g_signal_lookup(detailed_signal->val, G_TYPE_FROM_INSTANCE(gobject));
    CallbackHandler *my_data = g_new(CallbackHandler, 1);
    g_signal_query(id, &my_data->query);
    ZVAL_COPY(&my_data->handler, handler);
    ZVAL_COPY(&my_data->context, instance);
    ZVAL_COPY(&my_data->data, data);
    my_data->connect_flags = 0;
    my_data->params = g_new(zval, my_data->query.n_params+2);

    //g_signal_connect_data((gpointer)gobject, detailed_signal->val, my_callback, &my_data, NULL, (GConnectFlags) G_CONNECT_SWAPPED);
    GClosure *closure = g_cclosure_new_swap (G_CALLBACK (my_callback), my_data, destroy_data);
    g_signal_connect_closure((gpointer)gobject, detailed_signal->val, closure, TRUE);

    return 0;

}

/*----------------------------------------------------------------------+
| PHP_METHOD                                                           |
+----------------------------------------------------------------------*/

/* {{{ GSignal::__construct() */
PHP_METHOD(g_signal, __construct)
{
    zval *data=NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    zend_object *zobj = Z_OBJ_P(getThis());
    php_gobject_signal *self = ZOBJ_TO_PHP_GOBJECT_SIGNAL(zobj);

}
/* }}} */

/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/

/* {{{ proto ulong g_signal_connect_data(...) */
PHP_FUNCTION(g_signal_connect_data)
{
    zval *zinstance = NULL;
    zval *zdetailed_signal = NULL;
    zval *zhandler = NULL;
    zval *zdata = NULL;
    zval *zdestroy_data = NULL;
    zval *zconnect_flags = NULL;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(zinstance)
        Z_PARAM_ZVAL(zdetailed_signal)
        Z_PARAM_ZVAL(zhandler)
        Z_PARAM_ZVAL(zdata)
        Z_PARAM_ZVAL(zdestroy_data)
        Z_PARAM_ZVAL(zconnect_flags)
    ZEND_PARSE_PARAMETERS_END();

    zend_string *detailed_signal = zdetailed_signal->value.str;
    zend_long connect_flags = zconnect_flags->value.lval;
    zend_long ret = php_gobject_signal_connect_data(zinstance, detailed_signal, zhandler, zdata, zdestroy_data, connect_flags);

    RETURN_LONG(ret);
}/* }}} */

/* {{{ proto ulong g_signal_connect_data(...) */
PHP_FUNCTION(g_signal_connect)
{
    zval *zinstance = NULL;
    zval *zdetailed_signal = NULL;
    zval *zhandler = NULL;
    zval *zdata = NULL;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(zinstance)
        Z_PARAM_ZVAL(zdetailed_signal)
        Z_PARAM_ZVAL(zhandler)
        Z_PARAM_ZVAL(zdata)
    ZEND_PARSE_PARAMETERS_END();

    zend_string *detailed_signal = zdetailed_signal->value.str;
    zend_long ret = php_gobject_signal_connect(zinstance, detailed_signal, zhandler, zdata);

    RETURN_LONG(ret);
}/* }}} */
