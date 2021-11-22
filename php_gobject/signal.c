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
#include "php_gtk.h"
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
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "GSignal", php_gobject_signal_methods);
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

    zend_register_long_constant("G_SIGNAL_RUN_FIRST",    sizeof("G_SIGNAL_RUN_FIRST")-1,    G_SIGNAL_RUN_FIRST,    CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("G_SIGNAL_RUN_LAST",     sizeof("G_SIGNAL_RUN_LAST")-1,     G_SIGNAL_RUN_LAST,     CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("G_SIGNAL_RUN_CLEANUP",  sizeof("G_SIGNAL_RUN_CLEANUP")-1,  G_SIGNAL_RUN_CLEANUP,  CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("G_SIGNAL_NO_RECURSE",   sizeof("G_SIGNAL_NO_RECURSE")-1,   G_SIGNAL_NO_RECURSE,   CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("G_SIGNAL_DETAILED",     sizeof("G_SIGNAL_DETAILED")-1,     G_SIGNAL_DETAILED,     CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("G_SIGNAL_ACTION",       sizeof("G_SIGNAL_ACTION")-1,       G_SIGNAL_ACTION,       CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("G_SIGNAL_NO_HOOKS",     sizeof("G_SIGNAL_NO_HOOKS")-1,     G_SIGNAL_NO_HOOKS,     CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("G_SIGNAL_MUST_COLLECT", sizeof("G_SIGNAL_MUST_COLLECT")-1, G_SIGNAL_MUST_COLLECT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("G_SIGNAL_DEPRECATED",   sizeof("G_SIGNAL_DEPRECATED")-1,   G_SIGNAL_DEPRECATED,   CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);

    return php_gobject_signal_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/

typedef struct _CallbackHandler {
    zval handler;// user callback
    zval context;// object instance
    GSignalQuery query;
    zval data;// user data
    char *property_name;//FIX BUG ???

    int connect_flags;
    zval *params;// zval params[];

} CallbackHandler;

static zval*
my_wrapper(gpointer val) {

    return NULL;
}
#include "paramspecs.h"
static int
my_callback(gpointer user_data, ...) {
    zend_object *pspec=NULL;
    CallbackHandler *data = (CallbackHandler*)user_data;
    int num_params = data->query.n_params;
    int result;
    zval retval;
    php_printf("my_callback(%d: ...)\n", num_params);

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
        ZVAL_COPY(&data->params[0], &data->context);
        for (int i=0; i<num_params; i++) {
            switch (G_TYPE_FUNDAMENTAL(data->query.param_types[i])) {
            case G_TYPE_OBJECT: {
                    GObject *obj = va_arg(ap, GObject*);
                    php_printf("GObject{%s}\n", g_type_name_from_instance(obj));
                    zend_object* z_object = g_object_get_data(obj, "zend_object");
                    ///GC_REFCOUNT(z_object)++;
                    ZVAL_OBJ(&data->params[i+1], z_object);
                }
                break;
            case G_TYPE_INT: {
                    gpointer ptr = va_arg(ap, gpointer);
                    php_printf("Int{%d}\n", GPOINTER_TO_INT(ptr));
                    ZVAL_LONG(&data->params[i+1], ptr);
                }
                break;
            case G_TYPE_PARAM: {
                    GParamSpec *ptr = va_arg(ap, GParamSpec*);
                    php_printf("GParamSpec{%s}\n", ptr->name);
                    if (NULL==ptr && data->property_name) {
                        //php_printf("from g_signal_emit|g_signal_emit_by_name: %p\n", ptr);
                        php_gobject_object *obj = ZVAL_GET_PHP_GOBJECT_OBJECT(&data->context);
                        ptr = g_object_class_find_property(G_OBJECT_GET_CLASS(obj->ptr), data->property_name);
                    }
                    pspec = php_gobject_param_spec_new(ptr);
                    //php_gobject_param_spec *spec = ZOBJ_TO_PHP_GOBJECT_PARAM_SPEC(pspec);
                    ZVAL_OBJ(&data->params[i+1], pspec);

                    //ZVAL_OBJ(param_spec);
                    //ZVAL_NULL(&data->params[i+1]);
                }
                break;
            default:
                php_printf("Unexpected(%s)\n", g_type_name(G_TYPE_FUNDAMENTAL(data->query.param_types[i])));
                break;
            }
        }
        // GParamSpec *ptr = va_arg(ap, gpointer);
        ZVAL_COPY_VALUE(&data->params[num_params+1], &data->data);

        break;
    }

    va_end(ap);

    result = call_user_function(NULL, NULL, &data->handler, &retval, num_params+2, data->params);
    if (result == FAILURE) {
        g_print("call_user_function FAILURE\n");
    }
    //zval_ptr_dtor(&data->params[0]);
    zend_object_release(Z_OBJ(data->params[0]));


    if (pspec) zend_object_release(pspec);
    //for (int i=0; i<data->query.n_params; i++) {
        //TODO: switch IS_OBJECT
        ///zend_object *obj = data->params[i+1].value.obj;
        ///zend_object_release(obj);
    //}

    if (Z_TYPE(retval)==IS_LONG) { return retval.value.lval;}
    return 0;
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
    //zend_object_release(user_data->context.value.obj);
    //zval_ptr_dtor(&user_data->context);
    //php_printf("=>%d\n", user_data->context.value.obj->gc.refcount);
    //zval_ptr_dtor(&user_data->data);
    if (user_data->property_name)
        g_free(user_data->property_name);
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
    php_printf("php_gobject_signal_connect\n");

    char *signal_name = g_strdup(detailed_signal->val);// notify::detail
    char *ptr = strstr(signal_name, "::");
    if (ptr>signal_name) {
        signal_name[ptr-signal_name] = '\0';
    }

    guint id = g_signal_lookup(signal_name, G_TYPE_FROM_INSTANCE(gobject));
    //guint id = g_signal_lookup(detailed_signal->val, G_TYPE_FROM_INSTANCE(gobject));
    if (id) {
        CallbackHandler *my_data = g_new(CallbackHandler, 1);
        g_signal_query(id, &my_data->query);
        ZVAL_COPY(&my_data->handler, handler);
        ZVAL_COPY_VALUE(&my_data->context, instance);
        //ZVAL_COPY(&my_data->context, instance);
        //ZVAL_OBJ(&my_data->context, Z_OBJ_P(instance));
        ZVAL_COPY(&my_data->data, data);
        my_data->connect_flags = 0;
        my_data->params = g_new(zval, my_data->query.n_params+2);
        if (ptr>signal_name)
            my_data->property_name = g_strdup(ptr+2);
        else
            my_data->property_name = NULL;

        //g_signal_connect_data((gpointer)gobject, detailed_signal->val, my_callback, &my_data, NULL, (GConnectFlags) G_CONNECT_SWAPPED);
        GClosure *closure = g_cclosure_new_swap (G_CALLBACK (my_callback), my_data, destroy_data);
        g_signal_connect_closure((gpointer)gobject, detailed_signal->val, closure, TRUE);
    } else {
        printf("2] Error signal '%s' not found from %s\n", signal_name, detailed_signal->val);
    }
    g_free(signal_name);

    return id;
}

static void
my_destroy(gpointer	 data,
           GClosure	*closure)
{
    CallbackHandler *my_data = data;
    //Z_TRY_DELREF(my_data->context);
    ///php_printf("my_destroy(%d)\n", my_data->context.value.obj->gc.refcount);
    //zval_ptr_dtor(&my_data->context);
    //zend_object_release(my_data->context.value.obj);
    if (my_data->property_name)
        g_free(my_data->property_name);

    g_free(my_data->params);
    g_free(my_data);
}

zend_long
php_gobject_signal_connect_data(zval *instance,
                                zend_string *detailed_signal,
                                zval *handler,// Callback
                                zval *data, // Callback
                                zval *destroy_data,//GClosureNotify
                                zend_long connect_flags) {
#if 1
    php_gobject_object *ginstance = ZVAL_IS_PHP_GOBJECT_OBJECT(instance) ? ZVAL_GET_PHP_GOBJECT_OBJECT(instance) : NULL;
    GObject *gobject = G_OBJECT(ginstance->ptr);

    char *signal_name = g_strdup(detailed_signal->val);// notify::detail
    char *ptr = strstr(signal_name, "::");
    if (ptr>signal_name) {
        signal_name[ptr-signal_name] = '\0';
    }

    guint id = g_signal_lookup(signal_name, G_TYPE_FROM_INSTANCE(gobject));
    if (id) {
        CallbackHandler *my_data = g_new(CallbackHandler, 1);
        g_signal_query(id, &my_data->query);
        ZVAL_COPY(&my_data->handler, handler);
        ZVAL_COPY_VALUE(&my_data->context, instance);
        ZVAL_COPY(&my_data->data, data);
        my_data->connect_flags = 0;
        my_data->params = g_new(zval, my_data->query.n_params+2);// silent g_new0
        if (ptr>signal_name)
            my_data->property_name = g_strdup(ptr+2);
        else
            my_data->property_name = NULL;

        //g_signal_connect_data((gpointer)gobject, detailed_signal->val, my_callback, &my_data, NULL, (GConnectFlags) G_CONNECT_SWAPPED);
        GClosure *closure = g_cclosure_new_swap (G_CALLBACK (my_callback), my_data, my_destroy);// call user_function destroy_data->value.str.val
        g_signal_connect_closure((gpointer)gobject, detailed_signal->val, closure, TRUE);
    } else {
        printf("Error signal '%s' not found from %s\n", signal_name, detailed_signal->val);
    }
    g_free(signal_name);

    return id;

#else

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

/* {{{ proto ulong g_signal_new(string signal_name, ...) */
PHP_FUNCTION(g_signal_new)
{

#if 1
    zend_string *signal_name = NULL;
    zval *itype = NULL;
    zend_long signal_flags = 0;
    zval *class_offset = NULL;
    zval *accumulator = NULL;
    zval *accu_data = NULL;
    zend_long return_type = 0;
    zend_long n_params = 0;
    zval *args = NULL;
    int argc;

    ZEND_PARSE_PARAMETERS_START(8, -1)
        Z_PARAM_STR(signal_name)
        Z_PARAM_ZVAL(itype)//string|int => "MyObject::class"|1
        Z_PARAM_LONG(signal_flags)
        Z_PARAM_ZVAL(class_offset)
        Z_PARAM_ZVAL(accumulator)
        Z_PARAM_ZVAL(accu_data)
        Z_PARAM_LONG(return_type)
        Z_PARAM_LONG(n_params)
        Z_PARAM_VARIADIC('*', args, argc)
    ZEND_PARSE_PARAMETERS_END();


    zend_long ret = 0;//php_gobject_signal_new(zinstance, detailed_signal, zhandler, zdata);

    RETURN_LONG(ret);

#endif
}/* }}} */

/* {{{ proto g_signal_emit( ...) */
PHP_FUNCTION(g_signal_emit)
{
    zend_object *instance;
    zend_long    signal_id;
    zend_string *detail;
    zval *args = NULL;
    int argc;

    ZEND_PARSE_PARAMETERS_START(4, -1)
        Z_PARAM_OBJ(instance)
        Z_PARAM_LONG(signal_id)
        Z_PARAM_STR(detail)
        Z_PARAM_VARIADIC('+', args, argc)
    ZEND_PARSE_PARAMETERS_END();
    //ZVAL_REF(ret, args[argc])
    //php_printf("??? %s\n", instance->ce->name->val);
    //php_printf("=> %s\n", g_type_name_from_instance(ZOBJ_TO_PHP_GOBJECT_OBJECT(instance)->ptr));

    GValue *instance_and_params = calloc(argc+1, sizeof(GValue));//array  null-terminated
    g_value_init(&instance_and_params[0], G_TYPE_OBJECT);
    g_value_set_object(&instance_and_params[0], ZOBJ_TO_PHP_GOBJECT_OBJECT(instance)->ptr);
    for (int i = 0; i<argc; i++) {
        g_value_init(&instance_and_params[i+1], G_TYPE_INT);
        g_value_set_int(&instance_and_params[i+1], args[i].value.lval);
    }

    GQuark quark_detail = g_quark_from_static_string(detail->val);//"changed"
    GValue ret_value = G_VALUE_INIT;
    g_value_init(&ret_value, G_TYPE_INT);
    g_signal_emitv(instance_and_params, signal_id, quark_detail, &ret_value);
    //g_signal_emitv(&instance_and_params, signal_id, quark_detail, &ret_value);
    //g_signal_emit(instance_and_params, signal_id, quark_detail, ..., return_value);

    free(instance_and_params);
    //put ret_value in ZVAL_REF(ret)


    RETURN_LONG(g_value_get_int(&ret_value));
}

/* {{{ proto g_signal_emit( ...) */
PHP_FUNCTION(g_signal_emit_by_name)
{
    GSignalQuery query;
    int signal_id;
    uint32_t num_args = ZEND_NUM_ARGS();
    gboolean use_ret = FALSE;
    guint n_params;

    zend_object *instance;
    zval *signal_return = NULL;
    zend_string *signal_detail;
    zval *args = NULL;
    int argc = num_args-2;

    ZEND_PARSE_PARAMETERS_START(2, -1)
        Z_PARAM_OBJ(instance)
        Z_PARAM_STR(signal_detail)

        signal_id = g_signal_lookup(signal_detail->val, G_TYPE_FROM_INSTANCE(ZOBJ_TO_PHP_GOBJECT_OBJECT(instance)->ptr));
        g_signal_query(signal_id, &query);

        n_params = query.n_params + 1;
        if (query.return_type==G_TYPE_NONE) {
            if (argc==(query.n_params+1)) {
                use_ret = TRUE;
            } else if (argc==(query.n_params)) {
            // check if return value is omited
            } else {
                // Count args error
            }
        } else {//G_TYPE_NONE != query.return_type && G_TYPE_INVALID != query.return_type
            if (argc==(query.n_params+1)) {
                use_ret = TRUE;
            } else {
                // Count arg error
            }
        }

        Z_PARAM_OPTIONAL
        if (use_ret) {
            Z_PARAM_VARIADIC_EX('*', args, argc, 1)
            Z_PARAM_ZVAL_EX2(signal_return, 0, ZEND_SEND_BY_REF, 1)
        } else {
            Z_PARAM_VARIADIC('*', args, argc)
        }
    ZEND_PARSE_PARAMETERS_END();
    //    Z_PARAM_OPTIONAL
    //    Z_PARAM_ZVAL_EX2(signal_return, 0, ZEND_SEND_BY_REF, 0)

    //if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|sl", &value, &valuelen, &ignores, &ignoreslen, &flags) != SUCCESS) {RETURN_THROWS();}




    GValue *instance_and_params = ecalloc(n_params, sizeof(GValue));
    g_value_init(&instance_and_params[0], G_TYPE_OBJECT);
    g_value_set_object(&instance_and_params[0], ZOBJ_TO_PHP_GOBJECT_OBJECT(instance)->ptr);
    for (int i=0; i<query.n_params; i++) {
        GType gtype = query.param_types[i];
        zval *arg = &args[i];
        zend_uchar ztype = Z_TYPE_P(arg);
        if (IS_REFERENCE==ztype) {
            arg = &Z_REF_P(arg)->val;
            ztype = Z_TYPE_P(arg);
        }
        switch (ztype) {
        case IS_CONSTANT_AST:
        case IS_RESOURCE:
        case IS_OBJECT:
        case IS_STRING:
        case IS_REFERENCE:
            zend_error(E_WARNING, "Not implemented");
            break;
        case IS_DOUBLE:
            g_value_init(&instance_and_params[i+1], gtype);
            if (gtype==G_TYPE_DOUBLE) {g_value_set_double(&instance_and_params[i+1], Z_DVAL_P(arg)); break;}
            if (gtype==G_TYPE_FLOAT) {g_value_set_float(&instance_and_params[i+1], Z_DVAL_P(arg)); break;}
            // Error type
            break;
        case IS_LONG:
            g_value_init(&instance_and_params[i+1], gtype);
            if (gtype==G_TYPE_INT) {g_value_set_int(&instance_and_params[i+1], Z_LVAL_P(arg)); break;}
            if (gtype==G_TYPE_UINT) {g_value_set_uint(&instance_and_params[i+1], Z_LVAL_P(arg)); break;}
            if (gtype==G_TYPE_LONG) {g_value_set_long(&instance_and_params[i+1], Z_LVAL_P(arg)); break;}
            if (gtype==G_TYPE_ULONG) {g_value_set_ulong(&instance_and_params[i+1], Z_LVAL_P(arg)); break;}
            if (gtype==G_TYPE_INT64) {g_value_set_int64(&instance_and_params[i+1], Z_LVAL_P(arg)); break;}
            if (gtype==G_TYPE_UINT64) {g_value_set_uint64(&instance_and_params[i+1], Z_LVAL_P(arg)); break;}
            // Error type
            break;
        case IS_TRUE:
            g_value_init(&instance_and_params[i+1], gtype);
            if (gtype==G_TYPE_BOOLEAN) {g_value_set_boolean(&instance_and_params[i+1], TRUE); break;}
            // Error type param
            break;
        case IS_FALSE:
            g_value_init(&instance_and_params[i+1], gtype);
            if (gtype==G_TYPE_BOOLEAN) {g_value_set_boolean(&instance_and_params[i+1], FALSE); break;}
            // Error type param
            break;
        case IS_NULL:
        case IS_UNDEF:
        default:
            zend_error(E_WARNING, "Not implemented");
            break;
        }
    }


    if (use_ret) {
        GQuark quark_detail = g_quark_from_static_string(signal_detail->val);//"changed"
        GValue ret_value = G_VALUE_INIT;
        if(query.return_type!=G_TYPE_NONE && query.return_type!=G_TYPE_INVALID) g_value_init(&ret_value, query.return_type);
        g_signal_emitv(instance_and_params, signal_id, quark_detail, &ret_value);

        // TODO check if $ret is a REF
        if (ret_value.g_type==G_TYPE_INT) {
            ZVAL_SET_LONG(signal_return, g_value_get_int(&ret_value));
            //php_printf("return = %d\n", g_value_get_int(&ret_value));
        } else if (ret_value.g_type==G_TYPE_NONE) {
            //silent
        } else if (ret_value.g_type==G_TYPE_INVALID) {
            //silent
        } else {
            zend_error(E_WARNING, "Unimplemented case : return of GValue{%s}", g_type_name(ret_value.g_type));
        }
    } else {
        GQuark quark_detail = g_quark_from_static_string(signal_detail->val);//"changed"
        GValue ret_value = G_VALUE_INIT;
        //g_value_init(&ret_value, query.return_type);
        g_signal_emitv(instance_and_params, signal_id, quark_detail, &ret_value);

    }

    free(instance_and_params);

    /*
    g_print("::%s\n", g_signal_name(signal_id));
    g_print("  %s %s(%d: ", g_type_name(query.return_type), query.signal_name, query.n_params);

    int x;
    char glue[]="  ";
    glue[0]='\0';
    for (x=0; x<query.n_params; x++) {
        g_print("%s%s", glue, g_type_name(query.param_types[x]));
        glue[0]=',';
    }
    g_print(")\n");
    */

    //my_data.num_args = 3;//query.n_params;


#if 0
    GType *inst_params = calloc(argc-1, sizeof(GType));
    for (int i = 0; i<(argc-1); i++) {
        inst_params = args[i].value.lval;
    }

    GValue *instance_and_params = calloc(2, sizeof(GValue));//array  null-terminated
    g_value_init(&instance_and_params[0], G_TYPE_OBJECT);
    g_value_set_object(&instance_and_params[0], ZOBJ_TO_PHP_GOBJECT_OBJECT(instance)->ptr);
    g_value_init(&instance_and_params[1], G_TYPE_POINTER);
    g_value_set_pointer(&instance_and_params[1], inst_params);

    GQuark quark_detail = g_quark_from_static_string(signal_detail->val);//"changed"
    GValue ret_value = G_VALUE_INIT;
    g_value_init(&ret_value, (GType)args[argc-1].value.lval);
    int signal_id = g_signal_lookup(signal_detail->val, G_TYPE_FROM_INSTANCE(ZOBJ_TO_PHP_GOBJECT_OBJECT(instance)->ptr));
    g_signal_emitv(instance_and_params, signal_id, quark_detail, &ret_value);
    //g_signal_emitv(&instance_and_params, signal_id, quark_detail, &ret_value);
    //g_signal_emit(instance_and_params, signal_id, quark_detail, ..., return_value);

    free(inst_params);
    free(instance_and_params);
    //put ret_value in ZVAL_REF(ret)


    RETURN_LONG(g_value_get_int(&ret_value));
#endif
}
