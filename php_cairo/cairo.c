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

#include <cairo/cairo.h>
#include "php_gtk.h"
#include "surface.h"

#include "cairo.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;
//extern zend_class_entry     *php_cairo_surface_t_class_entry;


zend_class_entry     *php_cairo_t_class_entry;
zend_object_handlers  php_cairo_t_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
| Internal                                                             |
+----------------------------------------------------------------------*/

static const zend_function_entry php_cairo_t_methods[] = {
    PHP_ME(cairo_t, __construct, arginfo_cairo_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/


/* {{{ php_cairo_t_create_object */
static zend_object*
php_cairo_t_create_object(zend_class_entry *class_type)
{
    php_cairo_t *intern = ecalloc(1, sizeof(php_cairo_t) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_cairo_t_handlers;

    TRACE("php_cairo_t_create_object(%p) / %d\n", &intern->std, intern->std.gc.refcount);
    return &intern->std;
}
/* }}} php_cairo_t_create_object */


static void
php_cairo_t_dtor_object(zend_object *obj) {
    php_cairo_t *intern = ZOBJ_TO_PHP_CAIRO_T(obj);
    TRACE("php_cairo_t_dtor_object(\e[1;31m\"%s\"\e[0;m) / %d\n", intern->data.value.str->val, obj->gc.refcount);

}

/* {{{ php_cairo_t_free_object */
static void
php_cairo_t_free_object(zend_object *object)
{
    php_cairo_t *intern = ZOBJ_TO_PHP_CAIRO_T(object);
    TRACE("php_cairo_t_free_object(\e[1;31m\"%s\"\e[0;m) / %d\n", intern->data.value.str->val, object->gc.refcount);

    if (intern->ptr) {
        printf("php_cairo_t_free_object() / %d\n", cairo_get_reference_count(intern->ptr));
        cairo_destroy(intern->ptr);
    }

    zend_object_std_dtor(&intern->std);
    //efree(intern);
}
/* }}} php_cairo_t_free_object */


/* {{{ gtk_read_property */
static zval*
php_cairo_t_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_cairo_t *obj = ZVAL_GET_PHP_CAIRO_T(object);
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    retval = std_hnd->read_property(object, member, type, cache_slot, rv);

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ php_cairo_t_write_property */
static void
php_cairo_t_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_cairo_t *obj = ZVAL_GET_PHP_CAIRO_T(object);
    zend_string *member_str = zval_get_string(member);
    php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (zend_string_equals_literal(member->value.str, "child")
     || zend_string_equals_literal(member->value.str, "parent") ) {
#if 1
        zend_error(E_USER_WARNING, "Readonly property Node::$%s", member->value.str->val);
#else
        if (ZVAL_IS_PHP_SAMPLE_NODE(value)) {
            // do unset(object->child) and php_cairo_t_insert(object, value, 0);
        } else {
            zend_string *type = zend_zval_get_type(value);
            zend_error(E_USER_WARNING, "Cannot assign %s to property Node::$child of type Node", type->val);
        }
#endif
        return;
    }
    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->write_property(object, member, value, cache_slot);

    zend_string_release(member_str);
}
/* }}} */

static void
php_cairo_t_unset_property(zval *object, zval *member, void **cache_slot) {
    php_cairo_t *obj = ZVAL_GET_PHP_CAIRO_T(object);
    zend_string *member_str = zval_get_string(member);
    php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}

static HashTable*
php_cairo_t_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_cairo_t  *obj =  ZVAL_GET_PHP_CAIRO_T(object);
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


static HashTable*
php_cairo_t_get_properties(zval *object){
    php_cairo_t  *self =  ZVAL_GET_PHP_CAIRO_T(object);

    return NULL;
}


static int
php_cairo_t_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}


/* updates *count to hold the number of elements present and returns SUCCESS.
* Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_cairo_t_count_elements(zval *object, zend_long *count) {

    *count = 0;//php_cairo_t_length(ZVAL_GET_PHP_CAIRO_T(object));

    return SUCCESS;
}

static int
php_cairo_t_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

static zval*
php_cairo_t_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    return NULL;
} /* }}} end php_g_hash_table_read_dimension */


static void
php_cairo_t_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_cairo_t_write_property(object, &member, value, &cache);
}

static void
php_cairo_t_unset_dimension(zval *object, zval *offset) {
    //php_g_list *list = ZVAL_GET_PHP_G_LIST(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
    // @TODO
    //zend_hash_index_del(list->prop_handler, );
    // php_g_list
    break;
    case IS_STRING:
        php_cairo_t_unset_property(object, offset, &cache);
    break;
    default:
    break;
    }
}

static zend_object_handlers*
php_cairo_t_get_handlers()
{
    memcpy(&php_cairo_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_t_handlers.offset = PHP_CAIRO_T_OFFSET;
    //php_cairo_t_handlers.clone_obj;
    //php_cairo_t_handlers.compare;
    //php_cairo_t_handlers.compare_objects;
    //php_cairo_t_handlers.get_constructor;
    php_cairo_t_handlers.dtor_obj = php_cairo_t_dtor_object;
    php_cairo_t_handlers.free_obj = php_cairo_t_free_object;
    php_cairo_t_handlers.read_property = php_cairo_t_read_property;
    php_cairo_t_handlers.write_property = php_cairo_t_write_property;
    php_cairo_t_handlers.unset_property = php_cairo_t_unset_property;
    //php_cairo_t_handlers.get_property_ptr_ptr = php_cairo_t_get_property_ptr_ptr;

    php_cairo_t_handlers.get_debug_info = php_cairo_t_get_debug_info;
    php_cairo_t_handlers.get_properties = php_cairo_t_get_properties;//get_properties_for TODO php 8.0
    //php_cairo_t_handlers.set = php_cairo_t_set;
    php_cairo_t_handlers.cast_object = php_cairo_t_cast_object;

    php_cairo_t_handlers.count_elements = php_cairo_t_count_elements;
    php_cairo_t_handlers.has_dimension = php_cairo_t_has_dimension;
    php_cairo_t_handlers.read_dimension = php_cairo_t_read_dimension;
    php_cairo_t_handlers.unset_dimension = php_cairo_t_unset_dimension;
    php_cairo_t_handlers.write_dimension = php_cairo_t_write_dimension;


    return &php_cairo_t_handlers;
}



/*----------------------------------------------------------------------+
| PHP_MINIT                                                            |
+----------------------------------------------------------------------*/

/*{{{ php_cairo_t_class_init */
zend_class_entry*
php_cairo_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_t", php_cairo_t_methods);
    php_cairo_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_t_class_entry->create_object = php_cairo_t_create_object;
    //ce->serialize;
    /*
    zend_hash_init(&php_cairo_t_prop_handlers, 0, NULL, php_cairo_t_dtor_prop_handler, 1);
    php_cairo_t_register_prop_handler(&php_cairo_t_prop_handlers, "prev", sizeof("prev")-1, php_cairo_t_read_prev, php_cairo_t_write_prev);
    php_cairo_t_register_prop_handler(&php_cairo_t_prop_handlers, "data", sizeof("data")-1, php_cairo_t_read_data, php_cairo_t_write_data);
    php_cairo_t_register_prop_handler(&php_cairo_t_prop_handlers, "next", sizeof("next")-1, php_cairo_t_read_next, php_cairo_t_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_cairo_t_prop_handlers);
    */

    return php_cairo_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/
php_cairo_t *
php_cairo_new() {
    zend_object *zobj = php_cairo_t_create_object(php_cairo_t_class_entry);
    return ZOBJ_TO_PHP_CAIRO_T(zobj);
}

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/

php_cairo_t *
php_cairo_create(zval *target) {
    // TODO: implementation
}

php_cairo_t *
php_cairo_reference(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_destroy(php_cairo_t *cr) {
    // TODO: implementation
}

zval *
php_cairo_status(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_save(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_restore(php_cairo_t *cr) {
    // TODO: implementation
}

zval *
php_cairo_get_target(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_push_group(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_push_group_with_content(php_cairo_t *cr, zval *content) {
    // TODO: implementation
}

zval *
php_cairo_pop_group(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_pop_group_to_source(php_cairo_t *cr) {
    // TODO: implementation
}

zval *
php_cairo_get_group_target(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_set_source_rgb(php_cairo_t *cr, zval *red, zval *green, zval *blue) {
    // TODO: implementation
}

void
php_cairo_set_source_rgba(php_cairo_t *cr, zval *red, zval *green, zval *blue, zval *alpha) {
    // TODO: implementation
}

void
php_cairo_set_source(php_cairo_t *cr, zval *source) {
    // TODO: implementation
}

void
php_cairo_set_source_surface(php_cairo_t *cr, zval *surface, zval *x, zval *y) {
    // TODO: implementation
}

zval *
php_cairo_get_source(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_set_antialias(php_cairo_t *cr, zval *antialias) {
    // TODO: implementation
}

zval *
php_cairo_get_antialias(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_set_dash(php_cairo_t *cr, zval *dashes, zend_long num_dashes, zval *offset) {
    // TODO: implementation
}

zend_long
php_cairo_get_dash_count(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_get_dash(php_cairo_t *cr, zval *dashes, zval *offset) {
    // TODO: implementation
}

void
php_cairo_set_fill_rule(php_cairo_t *cr, zval *fill_rule) {
    // TODO: implementation
}

zval *
php_cairo_get_fill_rule(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_set_line_cap(php_cairo_t *cr, zval *line_cap) {
    // TODO: implementation
}

zval *
php_cairo_get_line_cap(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_set_line_join(php_cairo_t *cr, zval *line_join) {
    // TODO: implementation
}

zval *
php_cairo_get_line_join(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_set_line_width(php_cairo_t *cr, zval *width) {
    // TODO: implementation
}

zval *
php_cairo_get_line_width(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_set_miter_limit(php_cairo_t *cr, zval *limit) {
    // TODO: implementation
}

zval *
php_cairo_get_miter_limit(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_set_operator(php_cairo_t *cr, zval *op) {
    // TODO: implementation
}

zval *
php_cairo_get_operator(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_set_tolerance(php_cairo_t *cr, zval *tolerance) {
    // TODO: implementation
}

zval *
php_cairo_get_tolerance(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_clip(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_clip_preserve(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_clip_extents(php_cairo_t *cr, zval *x1, zval *y1, zval *x2, zval *y2) {
    // TODO: implementation
}

zval *
php_cairo_in_clip(php_cairo_t *cr, zval *x, zval *y) {
    // TODO: implementation
}

void
php_cairo_reset_clip(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_rectangle_list_destroy(zval *rectangle_list) {
    // TODO: implementation
}

zval *
php_cairo_copy_clip_rectangle_list(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_fill(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_fill_preserve(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_fill_extents(php_cairo_t *cr, zval *x1, zval *y1, zval *x2, zval *y2) {
    // TODO: implementation
}

zval *
php_cairo_in_fill(php_cairo_t *cr, zval *x, zval *y) {
    // TODO: implementation
}

void
php_cairo_mask(php_cairo_t *cr, zval *pattern) {
    // TODO: implementation
}

void
php_cairo_mask_surface(php_cairo_t *cr, zval *surface, zval *surface_x, zval *surface_y) {
    // TODO: implementation
}

void
php_cairo_paint(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_paint_with_alpha(php_cairo_t *cr, zval *alpha) {
    // TODO: implementation
}

void
php_cairo_stroke(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_stroke_preserve(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_stroke_extents(php_cairo_t *cr, zval *x1, zval *y1, zval *x2, zval *y2) {
    // TODO: implementation
}

zval *
php_cairo_in_stroke(php_cairo_t *cr, zval *x, zval *y) {
    // TODO: implementation
}

void
php_cairo_copy_page(php_cairo_t *cr) {
    // TODO: implementation
}

void
php_cairo_show_page(php_cairo_t *cr) {
    // TODO: implementation
}

zval *
php_cairo_get_reference_count(php_cairo_t *cr) {
    // TODO: implementation
}

zval *
php_cairo_set_user_data(php_cairo_t *cr, zval *key, void *user_data, zval *destroy) {
    // TODO: implementation
}

void
php_cairo_get_user_data(php_cairo_t *cr, zval *key) {
    // TODO: implementation
}




/*----------------------------------------------------------------------+
| PHP_METHOD                                                           |
+----------------------------------------------------------------------*/

/* {{{ cairo_t::__construct() */
PHP_METHOD(cairo_t, __construct)
{
    zval *data=NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();

    zend_object *zobj = Z_OBJ_P(getThis());
    php_cairo_t *self = ZOBJ_TO_PHP_CAIRO_T(zobj);

}
/* }}} */

/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/

/* {{{ proto cairo_t cairo_create(mixed target) */
PHP_FUNCTION(cairo_create)
{

    zval *ztarget;

    ZEND_PARSE_PARAMETERS_START(1, 1);
        Z_PARAM_OBJECT_OF_CLASS_EX(ztarget, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_target = ZVAL_IS_PHP_CAIRO_SURFACE_T(ztarget)? ZVAL_GET_PHP_CAIRO_SURFACE_T(ztarget): NULL;
    cairo_surface_t *target = php_target==NULL ? NULL : php_target->ptr;

    cairo_t *ret = cairo_create(target);
    cairo_status_t status = cairo_status (ret);
    if (CAIRO_STATUS_SUCCESS==status) {
        zend_object *z_ret = php_cairo_t_create_object(php_cairo_t_class_entry);
        php_cairo_t *php_ret = ZOBJ_TO_PHP_CAIRO_T(z_ret);
        php_ret->ptr = ret;
        RETURN_OBJ(z_ret);
    } else {
        const char *msg = cairo_status_to_string (status);
        zend_error(E_USER_ERROR, "%s", msg);
        RETURN_NULL();
    }

}/* }}} */


/* {{{ proto cairo_t cairo_reference(cairo_t cr) */
PHP_FUNCTION(cairo_reference)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr = php_cr==NULL ? NULL : php_cr->ptr;
    if (NULL==cr) {
        g_print("Internal Error: cairo_reference\n");
        return;
    }

    cairo_t *ret = cairo_reference(cr);
    cairo_status_t status = cairo_status (ret);
    if (CAIRO_STATUS_SUCCESS==status) {
        zend_object *z_ret = php_cairo_t_create_object(php_cairo_t_class_entry);
        php_cairo_t *php_ret = ZOBJ_TO_PHP_CAIRO_T(z_ret);
        php_ret->ptr = ret;
        RETURN_OBJ(z_ret);
    } else {
        const char *msg = cairo_status_to_string (status);
        zend_error(E_USER_ERROR, "%s", msg);
        RETURN_NULL();
    }


}/* }}} */

/* {{{ proto void cairo_destroy(cairo_t cr) */
PHP_FUNCTION(cairo_destroy)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr = php_cr==NULL ? NULL : php_cr->ptr;
    if (NULL==cr) {
        g_print("Internal Error: cairo_destroy\n");
        return;
    }

    cairo_destroy(cr);
    php_cr->ptr = NULL;

}/* }}} */

/* {{{ proto mixed cairo_status(cairo_t cr) */
PHP_FUNCTION(cairo_status)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr = php_cr==NULL ? NULL : php_cr->ptr;
    if (NULL==cr) {
        g_print("Internal Error: cairo_status\n");
        return;
    }

    cairo_status_t ret = cairo_status(cr);
    RETURN_LONG(ret);

}/* }}} */

/* {{{ proto void cairo_save(cairo_t cr) */
PHP_FUNCTION(cairo_save)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr = php_cr==NULL ? NULL : php_cr->ptr;
    if (NULL==cr) {
        g_print("Internal Error: cairo_save\n");
        return;
    }

    cairo_save(cr);

}/* }}} */

/* {{{ proto void cairo_restore(cairo_t cr) */
PHP_FUNCTION(cairo_restore)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_restore(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_get_target(cairo_t cr) */
PHP_FUNCTION(cairo_get_target)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_get_target(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_push_group(cairo_t cr) */
PHP_FUNCTION(cairo_push_group)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_push_group(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_push_group_with_content(cairo_t cr, mixed content) */
PHP_FUNCTION(cairo_push_group_with_content)
{
    zval *zcr = NULL;
    zval *zcontent = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zcontent)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__content = zcontent;
    php_cairo_t *__ret = php_cairo_push_group_with_content(, __cr, __content);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_pop_group(cairo_t cr) */
PHP_FUNCTION(cairo_pop_group)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_pop_group(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_pop_group_to_source(cairo_t cr) */
PHP_FUNCTION(cairo_pop_group_to_source)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_pop_group_to_source(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_get_group_target(cairo_t cr) */
PHP_FUNCTION(cairo_get_group_target)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_get_group_target(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_set_source_rgb(cairo_t cr, mixed red, mixed green, mixed blue) */
PHP_FUNCTION(cairo_set_source_rgb)
{
    zval *zcr = NULL;
    zval *zred = NULL;
    zval *zgreen = NULL;
    zval *zblue = NULL;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zred)
        Z_PARAM_ZVAL(zgreen)
        Z_PARAM_ZVAL(zblue)
    ZEND_PARSE_PARAMETERS_END();


    php_cairo_t *__cr = ZVAL_IS_PHP_CAIRO_T(zcr) ? ZVAL_GET_PHP_CAIRO_T(zcr) : NULL;
    double __red = Z_TYPE_P(zred)==IS_DOUBLE ? zred->value.dval : 0.0;
    double __green = Z_TYPE_P(zgreen)==IS_DOUBLE ? zgreen->value.dval : 0.0;
    double __blue = Z_TYPE_P(zblue)==IS_DOUBLE ? zblue->value.dval : 0.0;
    cairo_set_source_rgb(__cr->ptr, __red, __green, __blue);

}/* }}} */

/* {{{ proto void cairo_set_source_rgba(cairo_t cr, mixed red, mixed green, mixed blue, mixed alpha) */
PHP_FUNCTION(cairo_set_source_rgba)
{
    zval *zcr = NULL;
    zval *zred = NULL;
    zval *zgreen = NULL;
    zval *zblue = NULL;
    zval *zalpha = NULL;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zred)
        Z_PARAM_ZVAL(zgreen)
        Z_PARAM_ZVAL(zblue)
        Z_PARAM_ZVAL(zalpha)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__red = zred;
    zval * *__green = zgreen;
    zval * *__blue = zblue;
    zval * *__alpha = zalpha;
    php_cairo_t *__ret = php_cairo_set_source_rgba(, __cr, __red, __green, __blue, __alpha);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_set_source(cairo_t cr, mixed source) */
PHP_FUNCTION(cairo_set_source)
{
    zval *zcr = NULL;
    zval *zsource = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zsource)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__source = zsource;
    php_cairo_t *__ret = php_cairo_set_source(, __cr, __source);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_set_source_surface(cairo_t cr, mixed surface, mixed x, mixed y) */
PHP_FUNCTION(cairo_set_source_surface)
{
    zval *zcr = NULL;
    zval *zsurface = NULL;
    zval *zx = NULL;
    zval *zy = NULL;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zx)
        Z_PARAM_ZVAL(zy)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__surface = zsurface;
    zval * *__x = zx;
    zval * *__y = zy;
    php_cairo_t *__ret = php_cairo_set_source_surface(, __cr, __surface, __x, __y);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_get_source(cairo_t cr) */
PHP_FUNCTION(cairo_get_source)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_get_source(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_set_antialias(cairo_t cr, mixed antialias) */
PHP_FUNCTION(cairo_set_antialias)
{
    zval *zcr = NULL;
    zval *zantialias = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zantialias)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__antialias = zantialias;
    php_cairo_t *__ret = php_cairo_set_antialias(, __cr, __antialias);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_get_antialias(cairo_t cr) */
PHP_FUNCTION(cairo_get_antialias)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_get_antialias(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_set_dash(cairo_t cr, mixed dashes, int num_dashes, mixed offset) */
PHP_FUNCTION(cairo_set_dash)
{
    zval *zcr = NULL;
    zval *zdashes = NULL;
    zval *znum_dashes = NULL;
    zval *zoffset = NULL;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zdashes)
        Z_PARAM_ZVAL(znum_dashes)
        Z_PARAM_ZVAL(zoffset)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__dashes = zdashes;
    zend_long  *__num_dashes = znum_dashes;
    zval * *__offset = zoffset;
    php_cairo_t *__ret = php_cairo_set_dash(, __cr, __dashes, __num_dashes, __offset);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto int cairo_get_dash_count(cairo_t cr) */
PHP_FUNCTION(cairo_get_dash_count)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_get_dash_count(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_get_dash(cairo_t cr, mixed dashes, mixed offset) */
PHP_FUNCTION(cairo_get_dash)
{
    zval *zcr = NULL;
    zval *zdashes = NULL;
    zval *zoffset = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zdashes)
        Z_PARAM_ZVAL(zoffset)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__dashes = zdashes;
    zval * *__offset = zoffset;
    php_cairo_t *__ret = php_cairo_get_dash(, __cr, __dashes, __offset);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_set_fill_rule(cairo_t cr, mixed fill_rule) */
PHP_FUNCTION(cairo_set_fill_rule)
{
    zval *zcr = NULL;
    zval *zfill_rule = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zfill_rule)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__fill_rule = zfill_rule;
    php_cairo_t *__ret = php_cairo_set_fill_rule(, __cr, __fill_rule);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_get_fill_rule(cairo_t cr) */
PHP_FUNCTION(cairo_get_fill_rule)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_get_fill_rule(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_set_line_cap(cairo_t cr, mixed line_cap) */
PHP_FUNCTION(cairo_set_line_cap)
{
    zval *zcr = NULL;
    zval *zline_cap = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zline_cap)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__line_cap = zline_cap;
    php_cairo_t *__ret = php_cairo_set_line_cap(, __cr, __line_cap);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_get_line_cap(cairo_t cr) */
PHP_FUNCTION(cairo_get_line_cap)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_get_line_cap(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_set_line_join(cairo_t cr, mixed line_join) */
PHP_FUNCTION(cairo_set_line_join)
{
    zval *zcr = NULL;
    zval *zline_join = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zline_join)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__line_join = zline_join;
    php_cairo_t *__ret = php_cairo_set_line_join(, __cr, __line_join);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_get_line_join(cairo_t cr) */
PHP_FUNCTION(cairo_get_line_join)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_get_line_join(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_set_line_width(cairo_t cr, mixed width) */
PHP_FUNCTION(cairo_set_line_width)
{
    zval *zcr = NULL;
    zval *zwidth = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zwidth)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *__cr = ZVAL_IS_PHP_CAIRO_T(zcr) ? ZVAL_GET_PHP_CAIRO_T(zcr) : NULL;
    cairo_set_line_width(__cr->ptr, zwidth->value.dval);

}/* }}} */

/* {{{ proto mixed cairo_get_line_width(cairo_t cr) */
PHP_FUNCTION(cairo_get_line_width)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_get_line_width(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_set_miter_limit(cairo_t cr, mixed limit) */
PHP_FUNCTION(cairo_set_miter_limit)
{
    zval *zcr = NULL;
    zval *zlimit = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zlimit)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__limit = zlimit;
    php_cairo_t *__ret = php_cairo_set_miter_limit(, __cr, __limit);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_get_miter_limit(cairo_t cr) */
PHP_FUNCTION(cairo_get_miter_limit)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_get_miter_limit(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_set_operator(cairo_t cr, mixed op) */
PHP_FUNCTION(cairo_set_operator)
{
    zval *zcr = NULL;
    zval *zop = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zop)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__op = zop;
    php_cairo_t *__ret = php_cairo_set_operator(, __cr, __op);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_get_operator(cairo_t cr) */
PHP_FUNCTION(cairo_get_operator)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_get_operator(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_set_tolerance(cairo_t cr, mixed tolerance) */
PHP_FUNCTION(cairo_set_tolerance)
{
    zval *zcr = NULL;
    zval *ztolerance = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(ztolerance)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__tolerance = ztolerance;
    php_cairo_t *__ret = php_cairo_set_tolerance(, __cr, __tolerance);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_get_tolerance(cairo_t cr) */
PHP_FUNCTION(cairo_get_tolerance)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_get_tolerance(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_clip(cairo_t cr) */
PHP_FUNCTION(cairo_clip)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_clip(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_clip_preserve(cairo_t cr) */
PHP_FUNCTION(cairo_clip_preserve)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_clip_preserve(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_clip_extents(cairo_t cr, mixed x1, mixed y1, mixed x2, mixed y2) */
PHP_FUNCTION(cairo_clip_extents)
{
    zval *zcr = NULL;
    zval *zx1 = NULL;
    zval *zy1 = NULL;
    zval *zx2 = NULL;
    zval *zy2 = NULL;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zx1)
        Z_PARAM_ZVAL(zy1)
        Z_PARAM_ZVAL(zx2)
        Z_PARAM_ZVAL(zy2)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__x1 = zx1;
    zval * *__y1 = zy1;
    zval * *__x2 = zx2;
    zval * *__y2 = zy2;
    php_cairo_t *__ret = php_cairo_clip_extents(, __cr, __x1, __y1, __x2, __y2);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_in_clip(cairo_t cr, mixed x, mixed y) */
PHP_FUNCTION(cairo_in_clip)
{
    zval *zcr = NULL;
    zval *zx = NULL;
    zval *zy = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zx)
        Z_PARAM_ZVAL(zy)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__x = zx;
    zval * *__y = zy;
    php_cairo_t *__ret = php_cairo_in_clip(, __cr, __x, __y);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_reset_clip(cairo_t cr) */
PHP_FUNCTION(cairo_reset_clip)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_reset_clip(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_rectangle_list_destroy(mixed rectangle_list) */
PHP_FUNCTION(cairo_rectangle_list_destroy)
{
    zval *zrectangle_list = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zrectangle_list)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    zval * *__rectangle_list = zrectangle_list;
    php_cairo_t *__ret = php_cairo_rectangle_list_destroy(, __rectangle_list);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_copy_clip_rectangle_list(cairo_t cr) */
PHP_FUNCTION(cairo_copy_clip_rectangle_list)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_copy_clip_rectangle_list(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_fill(cairo_t cr) */
PHP_FUNCTION(cairo_fill)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *__cr = ZVAL_IS_PHP_CAIRO_T(zcr) ? ZVAL_GET_PHP_CAIRO_T(zcr) : NULL;
    cairo_fill(__cr->ptr);

}/* }}} */

/* {{{ proto void cairo_fill_preserve(cairo_t cr) */
PHP_FUNCTION(cairo_fill_preserve)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_fill_preserve(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_fill_extents(cairo_t cr, mixed x1, mixed y1, mixed x2, mixed y2) */
PHP_FUNCTION(cairo_fill_extents)
{
    zval *zcr = NULL;
    zval *zx1 = NULL;
    zval *zy1 = NULL;
    zval *zx2 = NULL;
    zval *zy2 = NULL;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zx1)
        Z_PARAM_ZVAL(zy1)
        Z_PARAM_ZVAL(zx2)
        Z_PARAM_ZVAL(zy2)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__x1 = zx1;
    zval * *__y1 = zy1;
    zval * *__x2 = zx2;
    zval * *__y2 = zy2;
    php_cairo_t *__ret = php_cairo_fill_extents(, __cr, __x1, __y1, __x2, __y2);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_in_fill(cairo_t cr, mixed x, mixed y) */
PHP_FUNCTION(cairo_in_fill)
{
    zval *zcr = NULL;
    zval *zx = NULL;
    zval *zy = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zx)
        Z_PARAM_ZVAL(zy)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__x = zx;
    zval * *__y = zy;
    php_cairo_t *__ret = php_cairo_in_fill(, __cr, __x, __y);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_mask(cairo_t cr, mixed pattern) */
PHP_FUNCTION(cairo_mask)
{
    zval *zcr = NULL;
    zval *zpattern = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zpattern)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__pattern = zpattern;
    php_cairo_t *__ret = php_cairo_mask(, __cr, __pattern);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_mask_surface(cairo_t cr, mixed surface, mixed surface_x, mixed surface_y) */
PHP_FUNCTION(cairo_mask_surface)
{
    zval *zcr = NULL;
    zval *zsurface = NULL;
    zval *zsurface_x = NULL;
    zval *zsurface_y = NULL;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zsurface_x)
        Z_PARAM_ZVAL(zsurface_y)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__surface = zsurface;
    zval * *__surface_x = zsurface_x;
    zval * *__surface_y = zsurface_y;
    php_cairo_t *__ret = php_cairo_mask_surface(, __cr, __surface, __surface_x, __surface_y);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_paint(cairo_t cr) */
PHP_FUNCTION(cairo_paint)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_paint(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_paint_with_alpha(cairo_t cr, mixed alpha) */
PHP_FUNCTION(cairo_paint_with_alpha)
{
    zval *zcr = NULL;
    zval *zalpha = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zalpha)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__alpha = zalpha;
    php_cairo_t *__ret = php_cairo_paint_with_alpha(, __cr, __alpha);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_stroke(cairo_t cr) */
PHP_FUNCTION(cairo_stroke)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *__cr = ZVAL_IS_PHP_CAIRO_T(zcr) ? ZVAL_GET_PHP_CAIRO_T(zcr) : NULL;
    cairo_stroke(__cr->ptr);

}/* }}} */

/* {{{ proto void cairo_stroke_preserve(cairo_t cr) */
PHP_FUNCTION(cairo_stroke_preserve)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_stroke_preserve(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_stroke_extents(cairo_t cr, mixed x1, mixed y1, mixed x2, mixed y2) */
PHP_FUNCTION(cairo_stroke_extents)
{
    zval *zcr = NULL;
    zval *zx1 = NULL;
    zval *zy1 = NULL;
    zval *zx2 = NULL;
    zval *zy2 = NULL;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zx1)
        Z_PARAM_ZVAL(zy1)
        Z_PARAM_ZVAL(zx2)
        Z_PARAM_ZVAL(zy2)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__x1 = zx1;
    zval * *__y1 = zy1;
    zval * *__x2 = zx2;
    zval * *__y2 = zy2;
    php_cairo_t *__ret = php_cairo_stroke_extents(, __cr, __x1, __y1, __x2, __y2);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_in_stroke(cairo_t cr, mixed x, mixed y) */
PHP_FUNCTION(cairo_in_stroke)
{
    zval *zcr = NULL;
    zval *zx = NULL;
    zval *zy = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zx)
        Z_PARAM_ZVAL(zy)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__x = zx;
    zval * *__y = zy;
    php_cairo_t *__ret = php_cairo_in_stroke(, __cr, __x, __y);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_copy_page(cairo_t cr) */
PHP_FUNCTION(cairo_copy_page)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_copy_page(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_show_page(cairo_t cr) */
PHP_FUNCTION(cairo_show_page)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zcr)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    php_cairo_t *__ret = php_cairo_show_page(, __cr);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto mixed cairo_get_reference_count(cairo_t cr) */
PHP_FUNCTION(cairo_get_reference_count)
{
    zval *zcr = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_t *cr = php_cr==NULL ? NULL : php_cr->ptr;

    unsigned int ref = cairo_get_reference_count(cr);

    RETURN_LONG(ref);

}/* }}} */

/* {{{ proto mixed cairo_set_user_data(cairo_t cr, mixed key, void user_data, mixed destroy) */
PHP_FUNCTION(cairo_set_user_data)
{
    zval *zcr = NULL;
    zval *zkey = NULL;
    zval *zuser_data = NULL;
    zval *zdestroy = NULL;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zkey)
        Z_PARAM_ZVAL(zuser_data)
        Z_PARAM_ZVAL(zdestroy)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__key = zkey;
    void  *__user_data = zuser_data;
    zval * *__destroy = zdestroy;
    php_cairo_t *__ret = php_cairo_set_user_data(, __cr, __key, __user_data, __destroy);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */

/* {{{ proto void cairo_get_user_data(cairo_t cr, mixed key) */
PHP_FUNCTION(cairo_get_user_data)
{
    zval *zcr = NULL;
    zval *zkey = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zcr)
        Z_PARAM_ZVAL(zkey)
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t * *__cr = zcr;
    zval * *__key = zkey;
    php_cairo_t *__ret = php_cairo_get_user_data(, __cr, __key);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
#endif
}/* }}} */
