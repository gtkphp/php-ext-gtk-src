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

#include "error.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_glib_error_class_entry;
zend_object_handlers  php_glib_error_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
| Internal                                                             |
+----------------------------------------------------------------------*/

static const zend_function_entry php_glib_error_methods[] = {
    PHP_ME(g_error, __construct, arginfo_g_error___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

static int
php_glib_error_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}

static HashTable*
php_glib_error_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_glib_error  *intern =  ZVAL_GET_PHP_GLIB_ERROR(object);
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

    zval zdomain;
    zval zcode;
    zval zmessage;
    if (intern->ptr) {
        ZVAL_STRING(&zdomain, g_quark_to_string(intern->ptr->domain));
        ZVAL_LONG(&zcode, intern->ptr->code);
        ZVAL_STRING(&zmessage, intern->ptr->message);
    } else {
        ZVAL_NULL(&zdomain);
        ZVAL_NULL(&zcode);
        ZVAL_NULL(&zmessage);
    }
    zend_hash_str_update(debug_info, "domain", sizeof("domain")-1, &zdomain);
    zend_hash_str_update(debug_info, "code", sizeof("code")-1, &zcode);
    zend_hash_str_update(debug_info, "message", sizeof("message")-1, &zmessage);

    return debug_info;
}
/* }}} */

static void
php_glib_error_unset_property(zval *object, zval *member, void **cache_slot) {
    php_glib_error *obj = ZVAL_GET_PHP_GLIB_ERROR(object);
    zend_string *member_str = zval_get_string(member);


    if (zend_string_equals_literal(member->value.str, "domain")
     || zend_string_equals_literal(member->value.str, "code")
     || zend_string_equals_literal(member->value.str, "message") ) {
#if 0
        if (ZVAL_IS_PHP_GLIB_ERROR(value)) {
            // do unset(object->child) and php_glib_error_insert(object, value, 0);
        } else {
            zend_string *type = zend_zval_get_type(value);
            zend_error(E_USER_WARNING, "Cannot assign %s to property Node::$next of type Node", type->val);
        }
#else
        zend_error(E_USER_WARNING, "Readonly property Node::$%s", member->value.str->val);
#endif
        return;
    }
    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}

/* {{{ php_glib_error_write_property */
static void
php_glib_error_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_glib_error *obj = ZVAL_GET_PHP_GLIB_ERROR(object);
    zend_string *member_str = zval_get_string(member);

    if (zend_string_equals_literal(member->value.str, "domain")
     || zend_string_equals_literal(member->value.str, "code")
     || zend_string_equals_literal(member->value.str, "message") ) {
#if 0
        if (ZVAL_IS_PHP_GLIB_ERROR(value)) {
            // do unset(object->child) and php_glib_error_insert(object, value, 0);
        } else {
            zend_string *type = zend_zval_get_type(value);
            zend_error(E_USER_WARNING, "Cannot assign %s to property Node::$next of type Node", type->val);
        }
#else
        zend_error(E_USER_WARNING, "Readonly property GError::$%s", member->value.str->val);
#endif
        return;
    }
    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->write_property(object, member, value, cache_slot);

    zend_string_release(member_str);
}
/* }}} */

/* {{{ gtk_read_property */
static zval*
php_glib_error_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_glib_error *obj = ZVAL_GET_PHP_GLIB_ERROR(object);
    zend_string *member_str = zval_get_string(member);
    zval *retval;

    if (zend_string_equals_literal(member->value.str, "domain")) {
        ZVAL_STRING(rv, g_quark_to_string(obj->ptr->domain));
        return rv;
    }
    if (zend_string_equals_literal(member->value.str, "code")) {
        ZVAL_LONG(rv, obj->ptr->code);
        return rv;
    }
    if (zend_string_equals_literal(member->value.str, "message")) {
        ZVAL_STRING(rv, obj->ptr->message);
        return rv;
    }

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    retval = std_hnd->read_property(object, member, type, cache_slot, rv);

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ php_glib_error_free_object */
static void
php_glib_error_free_object(zend_object *object)
{
    php_glib_error *intern = ZOBJ_TO_PHP_GLIB_ERROR(object);

    zend_object_std_dtor(&intern->std);
    //efree(intern);
}
/* }}} php_glib_error_free_object */

static void
php_glib_error_dtor_object(zend_object *obj) {
    php_glib_error *intern = ZOBJ_TO_PHP_GLIB_ERROR(obj);

    if (intern->ptr) {
        g_error_free(intern->ptr);
        intern->ptr = NULL;
    }


}

/* {{{ php_glib_error_create_object */
static zend_object*
php_glib_error_create_object(zend_class_entry *class_type)
{
    php_glib_error *intern = ecalloc(1, sizeof(php_glib_error) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    //php_glib_error_properties_init(intern);

    intern->ptr = NULL;

    intern->std.handlers = &php_glib_error_handlers;

    return &intern->std;
}
/* }}} php_glib_error_create_object */



static zend_object_handlers*
php_glib_error_get_handlers()
{
    memcpy(&php_glib_error_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_glib_error_handlers.offset = PHP_GLIB_ERROR_OFFSET;
    //php_glib_error_handlers.clone_obj;
    //php_glib_error_handlers.compare;
    //php_glib_error_handlers.compare_objects;
    //php_glib_error_handlers.get_constructor;
    php_glib_error_handlers.dtor_obj = php_glib_error_dtor_object;
    php_glib_error_handlers.free_obj = php_glib_error_free_object;
    php_glib_error_handlers.read_property = php_glib_error_read_property;
    php_glib_error_handlers.write_property = php_glib_error_write_property;
    php_glib_error_handlers.unset_property = php_glib_error_unset_property;
    //php_glib_error_handlers.get_property_ptr_ptr = php_glib_error_get_property_ptr_ptr;

    php_glib_error_handlers.get_debug_info = php_glib_error_get_debug_info;
    //php_glib_error_handlers.get_properties = php_glib_error_get_properties;//get_properties_for TODO php 8.0
    //php_glib_error_handlers.set = php_glib_error_set;
    php_glib_error_handlers.cast_object = php_glib_error_cast_object;

    /*
    php_glib_error_handlers.count_elements = php_glib_error_count_elements;
    php_glib_error_handlers.has_dimension = php_glib_error_has_dimension;
    php_glib_error_handlers.read_dimension = php_glib_error_read_dimension;
    php_glib_error_handlers.unset_dimension = php_glib_error_unset_dimension;
    php_glib_error_handlers.write_dimension = php_glib_error_write_dimension;
    */


    return &php_glib_error_handlers;
}



/*----------------------------------------------------------------------+
| PHP_MINIT                                                            |
+----------------------------------------------------------------------*/

/*{{{ php_glib_error_class_init */
zend_class_entry*
php_glib_error_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_glib_error_get_handlers();
    //INIT_NS_CLASS_ENTRY((*ce), "Gnome\\G", "List", php_glib_error_methods);
    INIT_CLASS_ENTRY((*container_ce), "GError", php_glib_error_methods);
    //ce->serialize;
    php_glib_error_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_glib_error_class_entry->create_object = php_glib_error_create_object;
    /*
    zend_hash_init(&php_glib_error_prop_handlers, 0, NULL, php_glib_error_dtor_prop_handler, 1);
    php_glib_error_register_prop_handler(&php_glib_error_prop_handlers, "prev", sizeof("prev")-1, php_glib_error_read_prev, php_glib_error_write_prev);
    php_glib_error_register_prop_handler(&php_glib_error_prop_handlers, "data", sizeof("data")-1, php_glib_error_read_data, php_glib_error_write_data);
    php_glib_error_register_prop_handler(&php_glib_error_prop_handlers, "next", sizeof("next")-1, php_glib_error_read_next, php_glib_error_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_glib_error_prop_handlers);
    */

    return php_glib_error_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/
static gpointer void_val = NULL;
static gpointer *zval_extract_ptr(zval *val) {
    if (NULL==val) {
        return void_val;
    }
    switch (Z_TYPE_P(val)) {
        case IS_NULL:
        case IS_FALSE:
        case IS_TRUE:
        case IS_LONG:
            return val->value.lval;
        case IS_RESOURCE:
        case IS_DOUBLE:
            return &val->value.dval;
        case IS_STRING:
            return &val->value.str->val;
        case IS_ARRAY:
        case IS_OBJECT:
            return val->value.obj;
        default:
            return 0;
    }
    return void_val;
}


/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
php_glib_error*
php_glib_error_create(GError *error) {
    zend_object *obj = php_glib_error_create_object(php_glib_error_class_entry);
    php_glib_error *intern = ZOBJ_TO_PHP_GLIB_ERROR(obj);
    intern->ptr = error;

    return intern;
}

php_glib_error *
php_glib_error_new(zend_long domain, zend_long code, zend_string *format, zval *args, int argc) {
    zend_object *obj = php_glib_error_create_object(php_glib_error_class_entry);
    php_glib_error *intern = ZOBJ_TO_PHP_GLIB_ERROR(obj);
    switch (argc) {
    case 2:
        intern->ptr = g_error_new((GQuark)domain, (gint)code, format->val,
                                  zval_extract_ptr(&args[0]), NULL);
        break;
    case 3:
        intern->ptr = g_error_new((GQuark)domain, (gint)code, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  NULL);
        break;
    case 4:
        intern->ptr = g_error_new((GQuark)domain, (gint)code, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  NULL);
        break;
    case 5:
        intern->ptr = g_error_new((GQuark)domain, (gint)code, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  NULL);
        break;
    case 6:
        intern->ptr = g_error_new((GQuark)domain, (gint)code, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  NULL);
        break;
    case 7:
        intern->ptr = g_error_new((GQuark)domain, (gint)code, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  zval_extract_ptr(&args[5]),
                                  NULL);
        break;
    case 8:
        intern->ptr = g_error_new((GQuark)domain, (gint)code, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  zval_extract_ptr(&args[5]),
                                  zval_extract_ptr(&args[6]),
                                  NULL);
        break;
    case 9:
        intern->ptr = g_error_new((GQuark)domain, (gint)code, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  zval_extract_ptr(&args[5]),
                                  zval_extract_ptr(&args[6]),
                                  zval_extract_ptr(&args[7]),
                                  NULL);
        break;
    case 1:
    default:
        intern->ptr = g_error_new((GQuark)domain, (gint)code, format->val, NULL);
    }
    return intern;
}

php_glib_error *
php_glib_error_new_literal(zend_long domain, zend_long code, zend_string *message) {
    zend_object *obj = php_glib_error_create_object(php_glib_error_class_entry);
    php_glib_error *intern = ZOBJ_TO_PHP_GLIB_ERROR(obj);
    intern->ptr = g_error_new((GQuark)domain, (gint)code, message->val);
    return intern;
}

void
php_glib_error_free(php_glib_error *error) {
    int ref = GC_REFCOUNT(&error->std);
    while(ref-->0) {
        zend_object_release(&error->std);
    }
}

php_glib_error *
php_glib_error_copy(php_glib_error *error) {
    zend_object *obj = php_glib_error_create_object(php_glib_error_class_entry);
    php_glib_error *intern = ZOBJ_TO_PHP_GLIB_ERROR(obj);
    intern->ptr = g_error_copy(error->ptr);
    return intern;
}

zend_bool
php_glib_error_matches(php_glib_error *error, zend_long domain, zend_long code) {
    gboolean ret = g_error_matches(error->ptr, domain, code);
    return ret;
}

//TODO: use g_strdup_printf ?
void
php_glib_set_error(php_glib_error **err, zend_long domain, zend_long code, zend_string *format, zval *args, int argc) {
    zend_object *obj;
    php_glib_error *intern = *err;
    GError *error = intern ? intern->ptr : NULL;
    if (NULL!=intern) {
        zend_error(E_USER_WARNING, "GError set over the top of a previous GError#%d", intern->std.handle);
    }
    switch (argc) {
    case 2:
        g_set_error(&error, domain, code, format->val,
                    zval_extract_ptr(&args[0]),
                    NULL);
        break;
    case 3:
        g_set_error(&error, domain, code, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  NULL);
        break;
    case 4:
        g_set_error(&error, domain, code, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  NULL);
        break;
    case 5:
        g_set_error(&error, domain, code, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  NULL);
        break;
    case 6:
        g_set_error(&error, domain, code, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  NULL);
        break;
    case 7:
        g_set_error(&error, domain, code, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  zval_extract_ptr(&args[5]),
                                  NULL);
        break;
    case 8:
        g_set_error(&error, domain, code, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  zval_extract_ptr(&args[5]),
                                  zval_extract_ptr(&args[6]),
                                  NULL);
        break;
    case 9:
        g_set_error(&error, domain, code, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  zval_extract_ptr(&args[5]),
                                  zval_extract_ptr(&args[6]),
                                  zval_extract_ptr(&args[7]),
                                  NULL);
        break;
    case 1:
    default:
        g_set_error(&error, domain, code, format->val, NULL);
    }
    if (NULL==intern) {
        obj = php_glib_error_create_object(php_glib_error_class_entry);
        intern = ZOBJ_TO_PHP_GLIB_ERROR(obj);
        intern->ptr = error;
        *err = intern;
    }
}

void
php_glib_set_error_literal(php_glib_error **err, zval *domain, zend_long code, zend_string *message) {
    zend_object *obj = php_glib_error_create_object(php_glib_error_class_entry);
    php_glib_error *intern = ZOBJ_TO_PHP_GLIB_ERROR(obj);
    GError *error = NULL;
    g_set_error_literal(&error, domain, code, message->val);

    intern->ptr = error;
    *err = intern;
}

void
php_glib_propagate_error(php_glib_error **dest, php_glib_error *src) {
    zend_object *obj = php_glib_error_create_object(php_glib_error_class_entry);
    php_glib_error *intern = ZOBJ_TO_PHP_GLIB_ERROR(obj);
    GError *error = NULL;
    GError *error_src = src->ptr;

    g_propagate_error(&error, error_src);
    src->ptr = NULL;

    intern->ptr = error;
    *dest = intern;
}

void
php_glib_clear_error(php_glib_error *err) {
    // TODO: implementation
}

void
php_glib_prefix_error(php_glib_error **err, zend_string *format, zval *args, int argc) {
    if(NULL==*err) {
        return;
    }
    GError *error = (*err)->ptr;
    switch (argc) {
    case 2:
        g_prefix_error(&error, format->val,
                    zval_extract_ptr(&args[0]),
                    NULL);
        break;
    case 3:
        g_prefix_error(&error, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  NULL);
        break;
    case 4:
        g_prefix_error(&error, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  NULL);
        break;
    case 5:
        g_prefix_error(&error, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  NULL);
        break;
    case 6:
        g_prefix_error(&error, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  NULL);
        break;
    case 7:
        g_prefix_error(&error, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  zval_extract_ptr(&args[5]),
                                  NULL);
        break;
    case 8:
        g_prefix_error(&error, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  zval_extract_ptr(&args[5]),
                                  zval_extract_ptr(&args[6]),
                                  NULL);
        break;
    case 9:
        g_prefix_error(&error, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  zval_extract_ptr(&args[5]),
                                  zval_extract_ptr(&args[6]),
                                  zval_extract_ptr(&args[7]),
                                  NULL);
        break;
    case 1:
    default:
        g_prefix_error(&error, format->val, NULL);
    }

}

void
php_glib_propagate_prefixed_error(php_glib_error **dest, php_glib_error *src, zend_string *format, zval *args, int argc) {
    zend_object *obj;
    php_glib_error *intern = *dest;

    GError *error = intern ? intern->ptr : NULL;
    GError *error_src = src->ptr;

    switch (argc) {
    case 2:
        g_propagate_prefixed_error(&error, error_src, format->val,
                                   zval_extract_ptr(&args[0]),
                                   NULL);
        break;
    case 3:
        g_propagate_prefixed_error(&error, error_src, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  NULL);
        break;
    case 4:
        g_propagate_prefixed_error(&error, error_src, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  NULL);
        break;
    case 5:
        g_propagate_prefixed_error(&error, error_src, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  NULL);
        break;
    case 6:
        g_propagate_prefixed_error(&error, error_src, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  NULL);
        break;
    case 7:
        g_propagate_prefixed_error(&error, error_src, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  zval_extract_ptr(&args[5]),
                                  NULL);
        break;
    case 8:
        g_propagate_prefixed_error(&error, error_src, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  zval_extract_ptr(&args[5]),
                                  zval_extract_ptr(&args[6]),
                                  NULL);
        break;
    case 9:
        g_propagate_prefixed_error(&error, error_src, format->val,
                                  zval_extract_ptr(&args[0]),
                                  zval_extract_ptr(&args[1]),
                                  zval_extract_ptr(&args[2]),
                                  zval_extract_ptr(&args[3]),
                                  zval_extract_ptr(&args[4]),
                                  zval_extract_ptr(&args[5]),
                                  zval_extract_ptr(&args[6]),
                                  zval_extract_ptr(&args[7]),
                                  NULL);
        break;
    case 1:
    default:
        g_propagate_prefixed_error(&error, error_src, format->val, NULL);
    }
    if (NULL==intern) {
        obj = php_glib_error_create_object(php_glib_error_class_entry);
        intern = ZOBJ_TO_PHP_GLIB_ERROR(obj);
        intern->ptr = error;
        *dest = intern;
    }
    src->ptr = NULL;

}




/*----------------------------------------------------------------------+
| PHP_METHOD                                                           |
+----------------------------------------------------------------------*/

/* {{{ GError::__construct() */
PHP_METHOD(g_error, __construct)
{
    zval *data=NULL;

    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();

    zend_object *zobj = Z_OBJ_P(getThis());
    php_glib_error *self = ZOBJ_TO_PHP_GLIB_ERROR(zobj);

    self->ptr = NULL;//g_error_new(g_quark_from_string("DOMAIN"), 40, "Message", NULL);

    // TODO g_error_new

}
/* }}} */

/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/

/* {{{ proto GError g_error_new(mixed domain, int code, string format) */
PHP_FUNCTION(g_error_new)
{
    zval *zdomain = NULL;
    zval *zcode = NULL;
    zval *zformat = NULL;
    int argc;
    zval *args = NULL;


    ZEND_PARSE_PARAMETERS_START(3, -1)
        Z_PARAM_ZVAL(zdomain)
        Z_PARAM_ZVAL(zcode)
        Z_PARAM_ZVAL(zformat)
        Z_PARAM_VARIADIC('+', args, argc);
    ZEND_PARSE_PARAMETERS_END();

    zend_long __domain = Z_TYPE_P(zdomain)==IS_LONG? zdomain->value.lval: 0;
    zend_long __code = Z_TYPE_P(zcode)==IS_LONG? zcode->value.lval: 0;
    zend_string *__format = Z_TYPE_P(zformat)==IS_STRING? zformat->value.str: 0;

    php_glib_error *__ret = php_glib_error_new(__domain, __code, __format, args, argc);

    RETURN_OBJ(&__ret->std);
}/* }}} */


/* {{{ proto GError g_error_new_literal(mixed domain, int code, string message) */
PHP_FUNCTION(g_error_new_literal)
{
    zval *zdomain = NULL;
    zval *zcode = NULL;
    zval *zmessage = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 13)
        Z_PARAM_ZVAL(zdomain)
        Z_PARAM_ZVAL(zcode)
        Z_PARAM_ZVAL(zmessage)
    ZEND_PARSE_PARAMETERS_END();

    zend_long __domain = Z_TYPE_P(zdomain)==IS_LONG? zdomain->value.lval: 0;
    zend_long __code = Z_TYPE_P(zcode)==IS_LONG? zcode->value.lval: 0;
    zend_string *__message = Z_TYPE_P(zmessage)==IS_STRING? zmessage->value.str: 0;

    php_glib_error *intern = php_glib_error_new_literal(__domain, __code, __message);

    RETURN_OBJ(&intern->std);
}/* }}} */

/* {{{ proto void g_error_free(GError error) */
PHP_FUNCTION(g_error_free)
{
    zval *zerror = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL_DEREF(zerror)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_error *__error = ZVAL_IS_PHP_GLIB_ERROR(zerror)? ZVAL_GET_PHP_GLIB_ERROR(zerror): NULL;
    php_glib_error_free(__error);

    ZVAL_NULL(zerror);

}/* }}} */

/* {{{ proto GError g_error_copy(GError error) */
PHP_FUNCTION(g_error_copy)
{
    zval *zerror = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zerror)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_error *__error = ZVAL_IS_PHP_GLIB_ERROR(zerror)? ZVAL_GET_PHP_GLIB_ERROR(zerror): NULL;
    php_glib_error *__ret = php_glib_error_copy(__error);

    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto bool g_error_matches(GError error, mixed domain, int code) */
PHP_FUNCTION(g_error_matches)
{
    zval *zerror = NULL;
    zval *zdomain = NULL;
    zval *zcode = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zerror)
        Z_PARAM_ZVAL(zdomain)
        Z_PARAM_ZVAL(zcode)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_error *__error = ZVAL_IS_PHP_GLIB_ERROR(zerror)? ZVAL_GET_PHP_GLIB_ERROR(zerror): NULL;
    zend_long *__domain = Z_TYPE_P(zdomain)==IS_LONG? zdomain->value.lval: NULL;
    zend_long *__code = Z_TYPE_P(zcode)==IS_LONG? zcode->value.lval: NULL;
    zend_bool __ret = php_glib_error_matches(__error, __domain, __code);

    if (__ret) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}/* }}} */

/* {{{ proto void g_set_error(GError err, mixed domain, int code, string format) */
PHP_FUNCTION(g_set_error)
{
    zval *zerror = NULL;
    zval *zdomain = NULL;
    zval *zcode = NULL;
    zval *zformat = NULL;
    int argc;
    zval *args = NULL;

    ZEND_PARSE_PARAMETERS_START(4, 14)
        Z_PARAM_ZVAL_DEREF(zerror)
        Z_PARAM_ZVAL(zdomain)
        Z_PARAM_ZVAL(zcode)
        Z_PARAM_ZVAL(zformat)
        Z_PARAM_VARIADIC('+', args, argc);
    ZEND_PARSE_PARAMETERS_END();

    php_glib_error *__error = ZVAL_IS_PHP_GLIB_ERROR(zerror)? ZVAL_GET_PHP_GLIB_ERROR(zerror): NULL;
    zend_long __domain = Z_TYPE_P(zdomain)==IS_LONG? zdomain->value.lval: 0;
    zend_long __code = Z_TYPE_P(zcode)==IS_LONG? zcode->value.lval: 0;
    zend_string *__format = Z_TYPE_P(zformat)==IS_STRING? zformat->value.str: NULL;

    php_glib_set_error(&__error, __domain, __code, __format, args, argc);

    ZVAL_OBJ(zerror, &__error->std);
}/* }}} */

/* {{{ proto void g_set_error_literal(GError err, mixed domain, int code, string message) */
PHP_FUNCTION(g_set_error_literal)
{
    zval *zerror = NULL;
    zval *zdomain = NULL;
    zval *zcode = NULL;
    zval *zmessage = NULL;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL_DEREF(zerror)
        Z_PARAM_ZVAL(zdomain)
        Z_PARAM_ZVAL(zcode)
        Z_PARAM_ZVAL(zmessage)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_error *__error = NULL;
    zend_long __domain = Z_TYPE_P(zdomain)==IS_LONG? zdomain->value.lval: 0;
    zend_long __code = Z_TYPE_P(zcode)==IS_LONG? zcode->value.lval: 0;
    zend_string *__message = Z_TYPE_P(zmessage)==IS_STRING? zmessage->value.str: NULL;

    php_glib_set_error_literal(&__error, __domain, __code, __message);

    ZVAL_OBJ(zerror, &__error->std);
}/* }}} */

/* {{{ proto void g_propagate_error(GError dest, GError src) */
PHP_FUNCTION(g_propagate_error)
{
    zval *zdest = NULL;
    zval *zsrc = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL_DEREF(zdest)
        Z_PARAM_ZVAL(zsrc)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_error *__dest = NULL;
    php_glib_error *__src = ZVAL_IS_PHP_GLIB_ERROR(zsrc)? ZVAL_GET_PHP_GLIB_ERROR(zsrc): NULL;

    php_glib_propagate_error(&__dest, __src);

    ZVAL_OBJ(zdest, &__dest->std);
}/* }}} */

/* {{{ proto void g_clear_error(GError err) */
PHP_FUNCTION(g_clear_error)
{
    zval *zerror = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL_DEREF(zerror)
    ZEND_PARSE_PARAMETERS_END();

    php_glib_error *__error = ZVAL_IS_PHP_GLIB_ERROR(zerror)? ZVAL_GET_PHP_GLIB_ERROR(zerror): NULL;

    g_clear_error(&__error->ptr);
    __error->ptr = NULL;
    zend_object_release(&__error->std);
    ZVAL_NULL(zerror);

}/* }}} */

/* {{{ proto void g_prefix_error(GError err, string format) */
PHP_FUNCTION(g_prefix_error)
{
    zval *zerr = NULL;
    zval *zformat = NULL;
    int argc;
    zval *args = NULL;

    ZEND_PARSE_PARAMETERS_START(3, -1)
        Z_PARAM_ZVAL_DEREF(zerr)
        Z_PARAM_ZVAL(zformat)
        Z_PARAM_VARIADIC('+', args, argc);
    ZEND_PARSE_PARAMETERS_END();

    php_glib_error *__err = ZVAL_IS_PHP_GLIB_ERROR(zerr)? ZVAL_GET_PHP_GLIB_ERROR(zerr): NULL;
    zend_string *__format = Z_TYPE_P(zformat)==IS_STRING? zformat->value.str: NULL;
    php_glib_prefix_error(&__err, __format, args, argc);


}/* }}} */

/* {{{ proto void g_propagate_prefixed_error(GError dest, GError src, string format) */
PHP_FUNCTION(g_propagate_prefixed_error)
{
    zval *zdest = NULL;
    zval *zsrc = NULL;
    zval *zformat = NULL;
    int argc;
    zval *args = NULL;

    ZEND_PARSE_PARAMETERS_START(4, 14)
        Z_PARAM_ZVAL_DEREF(zdest)
        Z_PARAM_ZVAL(zsrc)
        Z_PARAM_ZVAL(zformat)
        Z_PARAM_VARIADIC('+', args, argc);
    ZEND_PARSE_PARAMETERS_END();

    php_glib_error *__dest = ZVAL_IS_PHP_GLIB_ERROR(zdest)? ZVAL_GET_PHP_GLIB_ERROR(zdest): NULL;
    php_glib_error *__src  = ZVAL_IS_PHP_GLIB_ERROR(zsrc)? ZVAL_GET_PHP_GLIB_ERROR(zsrc): NULL;
    zend_string    *__format = Z_TYPE_P(zformat)==IS_STRING? zformat->value.str: NULL;
    php_glib_propagate_prefixed_error(&__dest, __src, __format, args, argc);

    ZVAL_OBJ(zdest, &__dest->std);

}/* }}} */

