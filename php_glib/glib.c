
#include <php.h>
#include <php_ini.h>
#include <zend_interfaces.h>
#include <ext/standard/info.h>

#include "glib.h"

extern zend_module_entry gtk_module_entry;
extern HashTable classes;

zend_class_entry *php_glib_class_entry;
zend_object_handlers php_glib_object_handlers;

void php_glib_copy_prop_handler(zval *zv) /* {{{ */
{
	TRACE();
    php_glib_prop_handler *hnd = Z_PTR_P(zv);
    Z_PTR_P(zv) = malloc(sizeof(php_glib_prop_handler));
    memcpy(Z_PTR_P(zv), hnd, sizeof(php_glib_prop_handler));
}
/* }}} */

void php_glib_dtor_prop_handler(zval *zv) /* {{{ */
{
	TRACE();
    free(Z_PTR_P(zv));
}

// @see MACRO like in PHP 8.0
php_glib_object*
php_glib_from_zend(zend_object *obj) {
	TRACE();
    return (php_glib_object*)((char*)(obj) - XtOffsetOf(php_glib_object, std));
}

/* {{{ php_glib_create_object */
zend_object *php_glib_create_object(zend_class_entry *class_type)
{
	TRACE();
    php_glib_object *intern = php_glib_set_class(class_type, 1);
    intern->type = PHP_GLIB_NONE_TYPE;
    intern->std.handlers = &php_glib_object_handlers;
    return &intern->std;
}
/* }}} */

php_glib_object* php_glib_set_class(zend_class_entry *class_type, zend_bool hash_copy) /* {{{ */
{
	TRACE();
    php_glib_object *intern = ecalloc(1, sizeof(php_glib_object) + zend_object_properties_size(class_type));
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



/* {{{ dom_objects_free_storage */
void php_glib_free_storage(zend_object *object)
{
	TRACE();

    php_glib_object *intern = php_glib_from_zend(object);
#if defined(__GNUC__) && __GNUC__ >= 3
    int retcount __attribute__((unused)); /* keep compiler quiet */
#else
    int retcount;
#endif

    zend_object_std_dtor(&intern->std);
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

zval *php_glib_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
	TRACE();
    php_glib_object *obj = php_glib_from_zend(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    zval *retval = NULL;

    g_print("%s\n", "php_glib_get_property_ptr_ptr");
    if (!obj->prop_handler || !zend_hash_exists(obj->prop_handler, member_str)) {
        zend_object_handlers *std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->get_property_ptr_ptr(object, member, type, cache_slot);
    }

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ gtk_read_property */
zval *php_glib_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
	TRACE();
    php_glib_object *obj = php_glib_from_zend(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    php_glib_prop_handler *hnd = NULL;
    g_print("%s(%s)\n", "php_glib_read_property", member->value.str->val);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member_str);
    } else if (instanceof_function(obj->std.ce, php_glib_class_entry)) {
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
void php_glib_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
	TRACE();
    php_glib_object *obj = php_glib_from_zend(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    php_glib_prop_handler *hnd = NULL;

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
int php_glib_read_na(php_glib_object *obj, zval *retval)
{
	TRACE();
    zend_throw_error(NULL, "Cannot read property");
    return FAILURE;
}
/* }}} */

/* {{{ dom_write_na */
int php_glib_write_na(php_glib_object *obj, zval *newval)
{
	TRACE();
    zend_throw_error(NULL, "Cannot write property");
    return FAILURE;
}
/* }}} */

/* {{{ dom_register_prop_handler */
void php_glib_register_prop_handler(HashTable *prop_handler, char *name, size_t name_len, glib_read_t read_func, glib_write_t write_func)
{
	TRACE();
    php_glib_prop_handler hnd;

    hnd.read_func = read_func ? read_func : php_glib_read_na;
    hnd.write_func = write_func ? write_func : php_glib_write_na;
    zend_hash_str_add_mem(prop_handler, name, name_len, &hnd, sizeof(php_glib_prop_handler));
}
/* }}} */

static HashTable*
php_glib_get_debug_info_helper(zval *object, int *is_temp) /* {{{ */
{
	TRACE();

    php_glib_object *obj =  php_glib_from_zend(Z_OBJ_P(object));
    HashTable              *debug_info,
                           *prop_handlers = obj->prop_handler,
                           *std_props;
    zend_string            *string_key;
    php_glib_prop_handler  *entry;
    zend_string            *object_str;

    *is_temp = 1;

    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    if (!prop_handlers) {
        return debug_info;
    }

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

    return debug_info;
}
/* }}} */

HashTable*
php_glib_get_debug_info(zval *object, int *is_temp)
{
	TRACE();
    return php_glib_get_debug_info_helper(object, is_temp);
}


zend_object_handlers*
php_glib_object_get_handlers()
{
	TRACE();
	memcpy(&php_glib_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_glib_object_handlers.offset = XtOffsetOf(php_glib_object, std);
	php_glib_object_handlers.free_obj = php_glib_free_storage;
	php_glib_object_handlers.read_property = php_glib_read_property;
	php_glib_object_handlers.write_property = php_glib_write_property;
	php_glib_object_handlers.get_property_ptr_ptr = php_glib_get_property_ptr_ptr;
	php_glib_object_handlers.get_debug_info = php_glib_get_debug_info;

	return &php_glib_object_handlers;
}

