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

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_surface_t_class_entry;
zend_object_handlers  php_cairo_surface_t_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
| Internal                                                             |
+----------------------------------------------------------------------*/

static const zend_function_entry php_cairo_surface_t_methods[] = {
    PHP_ME(cairo_surface_t, __construct, arginfo_cairo_surface_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/


/* {{{ php_cairo_surface_t_create_object */
zend_object*
php_cairo_surface_t_create_object(zend_class_entry *class_type)
{
    php_cairo_surface_t *intern = ecalloc(1, sizeof(php_cairo_surface_t) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_cairo_surface_t_handlers;

    TRACE("php_cairo_surface_t_create_object(%p) / %d\n", &intern->std, intern->std.gc.refcount);
    return &intern->std;
}
/* }}} php_cairo_surface_t_create_object */


static void
php_cairo_surface_t_dtor_object(zend_object *obj) {
    php_cairo_surface_t *intern = ZOBJ_TO_PHP_CAIRO_SURFACE_T(obj);

}

/* {{{ php_cairo_surface_t_free_object */
static void
php_cairo_surface_t_free_object(zend_object *object)
{
    php_cairo_surface_t *intern = ZOBJ_TO_PHP_CAIRO_SURFACE_T(object);
    //printf("php_cairo_surface_t_free_object() / %d\n", object->gc.refcount);

    if (intern->ptr) {
        printf("php_cairo_surface_t_free_object() / %d\n", cairo_surface_get_reference_count(intern->ptr));
        cairo_surface_destroy(intern->ptr);
        intern->ptr = NULL;
    }

    zend_object_std_dtor(&intern->std);
    //efree(intern);
}
/* }}} php_cairo_surface_t_free_object */


/* {{{ gtk_read_property */
static zval*
php_cairo_surface_t_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_cairo_surface_t *obj = ZOBJ_TO_PHP_CAIRO_SURFACE_T(object);
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    retval = std_hnd->read_property(object, member, type, cache_slot, rv);

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ php_cairo_surface_t_write_property */
static void
php_cairo_surface_t_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_cairo_surface_t *obj = ZOBJ_TO_PHP_CAIRO_SURFACE_T(object);
    zend_string *member_str = zval_get_string(member);
    php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (zend_string_equals_literal(member->value.str, "child")
     || zend_string_equals_literal(member->value.str, "parent") ) {
#if 1
        zend_error(E_USER_WARNING, "Readonly property Node::$%s", member->value.str->val);
#else
        if (ZVAL_IS_PHP_SAMPLE_NODE(value)) {
            // do unset(object->child) and php_cairo_surface_t_insert(object, value, 0);
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
php_cairo_surface_t_unset_property(zval *object, zval *member, void **cache_slot) {
    php_cairo_surface_t *obj = ZOBJ_TO_PHP_CAIRO_SURFACE_T(object);
    zend_string *member_str = zval_get_string(member);
    php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}

static HashTable*
php_cairo_surface_t_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_cairo_surface_t  *obj =  ZVAL_GET_PHP_CAIRO_SURFACE_T(object);
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
php_cairo_surface_t_get_properties(zval *object){
    php_cairo_surface_t  *self =  ZVAL_GET_PHP_CAIRO_SURFACE_T(object);

    return NULL;
}


static int
php_cairo_surface_t_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}


/* updates *count to hold the number of elements present and returns SUCCESS.
* Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_cairo_surface_t_count_elements(zval *object, zend_long *count) {

    *count = 0;

    return SUCCESS;
}

static int
php_cairo_surface_t_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

static zval*
php_cairo_surface_t_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
    return NULL;
    }

    php_cairo_surface_t *intern = ZVAL_GET_PHP_CAIRO_SURFACE_T(object);


    return rv;
} /* }}} end php_g_hash_table_read_dimension */


static void
php_cairo_surface_t_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_cairo_surface_t_write_property(object, &member, value, &cache);
}

static void
php_cairo_surface_t_unset_dimension(zval *object, zval *offset) {
    //php_g_list *list = ZVAL_GET_PHP_G_LIST(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
    // @TODO
    //zend_hash_index_del(list->prop_handler, );
    // php_g_list
    break;
    case IS_STRING:
        php_cairo_surface_t_unset_property(object, offset, &cache);
    break;
    default:
    break;
    }
}

static zend_object_handlers*
php_cairo_surface_t_get_handlers()
{
    memcpy(&php_cairo_surface_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_surface_t_handlers.offset = PHP_CAIRO_SURFACE_T_OFFSET;
    //php_cairo_surface_t_handlers.clone_obj;
    //php_cairo_surface_t_handlers.compare;
    //php_cairo_surface_t_handlers.compare_objects;
    //php_cairo_surface_t_handlers.get_constructor;
    php_cairo_surface_t_handlers.dtor_obj = php_cairo_surface_t_dtor_object;
    php_cairo_surface_t_handlers.free_obj = php_cairo_surface_t_free_object;
    php_cairo_surface_t_handlers.read_property = php_cairo_surface_t_read_property;
    php_cairo_surface_t_handlers.write_property = php_cairo_surface_t_write_property;
    php_cairo_surface_t_handlers.unset_property = php_cairo_surface_t_unset_property;
    //php_cairo_surface_t_handlers.get_property_ptr_ptr = php_cairo_surface_t_get_property_ptr_ptr;

    php_cairo_surface_t_handlers.get_debug_info = php_cairo_surface_t_get_debug_info;
    php_cairo_surface_t_handlers.get_properties = php_cairo_surface_t_get_properties;//get_properties_for TODO php 8.0
    //php_cairo_surface_t_handlers.set = php_cairo_surface_t_set;
    php_cairo_surface_t_handlers.cast_object = php_cairo_surface_t_cast_object;

    php_cairo_surface_t_handlers.count_elements = php_cairo_surface_t_count_elements;
    php_cairo_surface_t_handlers.has_dimension = php_cairo_surface_t_has_dimension;
    php_cairo_surface_t_handlers.read_dimension = php_cairo_surface_t_read_dimension;
    php_cairo_surface_t_handlers.unset_dimension = php_cairo_surface_t_unset_dimension;
    php_cairo_surface_t_handlers.write_dimension = php_cairo_surface_t_write_dimension;


    return &php_cairo_surface_t_handlers;
}



/*----------------------------------------------------------------------+
| PHP_MINIT                                                            |
+----------------------------------------------------------------------*/

/*{{{ php_cairo_surface_t_class_init */
zend_class_entry*
php_cairo_surface_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_surface_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_surface_t", php_cairo_surface_t_methods);
    php_cairo_surface_t_class_entry = zend_register_internal_class_ex(container_ce, NULL);
    php_cairo_surface_t_class_entry->create_object = php_cairo_surface_t_create_object;
    //ce->serialize;
    /*
    zend_hash_init(&php_cairo_surface_t_prop_handlers, 0, NULL, php_cairo_surface_t_dtor_prop_handler, 1);
    php_cairo_surface_t_register_prop_handler(&php_cairo_surface_t_prop_handlers, "prev", sizeof("prev")-1, php_cairo_surface_t_read_prev, php_cairo_surface_t_write_prev);
    php_cairo_surface_t_register_prop_handler(&php_cairo_surface_t_prop_handlers, "data", sizeof("data")-1, php_cairo_surface_t_read_data, php_cairo_surface_t_write_data);
    php_cairo_surface_t_register_prop_handler(&php_cairo_surface_t_prop_handlers, "next", sizeof("next")-1, php_cairo_surface_t_read_next, php_cairo_surface_t_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_cairo_surface_t_prop_handlers);
    */

    int module_number = gtk_module_entry.module_number;
    zend_register_long_constant("CAIRO_FORMAT_INVALID", sizeof("CAIRO_FORMAT_INVALID")-1,
                                CAIRO_FORMAT_INVALID, CONST_CS | CONST_PERSISTENT, module_number);
    zend_register_long_constant("CAIRO_FORMAT_ARGB32", sizeof("CAIRO_FORMAT_ARGB32")-1,
                                CAIRO_FORMAT_ARGB32, CONST_CS | CONST_PERSISTENT, module_number);
    zend_register_long_constant("CAIRO_FORMAT_RGB24", sizeof("CAIRO_FORMAT_RGB24")-1,
                                CAIRO_FORMAT_RGB24, CONST_CS | CONST_PERSISTENT, module_number);
    zend_register_long_constant("CAIRO_FORMAT_A8", sizeof("CAIRO_FORMAT_A8")-1,
                                CAIRO_FORMAT_A8, CONST_CS | CONST_PERSISTENT, module_number);
    zend_register_long_constant("CAIRO_FORMAT_A1", sizeof("CAIRO_FORMAT_A1")-1,
                                CAIRO_FORMAT_A1, CONST_CS | CONST_PERSISTENT, module_number);
    zend_register_long_constant("CAIRO_FORMAT_RGB16_565", sizeof("CAIRO_FORMAT_RGB16_565")-1,
                                CAIRO_FORMAT_RGB16_565, CONST_CS | CONST_PERSISTENT, module_number);
    zend_register_long_constant("CAIRO_FORMAT_RGB30", sizeof("CAIRO_FORMAT_RGB30")-1,
                                CAIRO_FORMAT_RGB30, CONST_CS | CONST_PERSISTENT, module_number);

    return php_cairo_surface_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
#if IS_IMPLEMENTED
php_cairo_surface_t *
php_cairo_surface_create_similar(php_cairo_surface_t *other, zval *content, zend_long width, zend_long height) {
    // TODO: implementation
}

php_cairo_surface_t *
php_cairo_surface_create_similar_image(php_cairo_surface_t *other, zval *format, zend_long width, zend_long height) {
    // TODO: implementation
}

php_cairo_surface_t *
php_cairo_surface_create_for_rectangle(php_cairo_surface_t *target, zval *x, zval *y, zval *width, zval *height) {
    // TODO: implementation
}

php_cairo_surface_t *
php_cairo_surface_reference(php_cairo_surface_t *surface) {
    // TODO: implementation
}

void
php_cairo_surface_destroy(php_cairo_surface_t *surface) {
    // TODO: implementation
}

zval *
php_cairo_surface_status(php_cairo_surface_t *surface) {
    // TODO: implementation
}

void
php_cairo_surface_finish(php_cairo_surface_t *surface) {
    // TODO: implementation
}

void
php_cairo_surface_flush(php_cairo_surface_t *surface) {
    // TODO: implementation
}

zval *
php_cairo_surface_get_device(php_cairo_surface_t *surface) {
    // TODO: implementation
}

void
php_cairo_surface_get_font_options(php_cairo_surface_t *surface, zval *options) {
    // TODO: implementation
}

zval *
php_cairo_surface_get_content(php_cairo_surface_t *surface) {
    // TODO: implementation
}

void
php_cairo_surface_mark_dirty(php_cairo_surface_t *surface) {
    // TODO: implementation
}

void
php_cairo_surface_mark_dirty_rectangle(php_cairo_surface_t *surface, zend_long x, zend_long y, zend_long width, zend_long height) {
    // TODO: implementation
}

void
php_cairo_surface_set_device_offset(php_cairo_surface_t *surface, zval *x_offset, zval *y_offset) {
    // TODO: implementation
}

void
php_cairo_surface_get_device_offset(php_cairo_surface_t *surface, zval *x_offset, zval *y_offset) {
    // TODO: implementation
}

void
php_cairo_surface_get_device_scale(php_cairo_surface_t *surface, zval *x_scale, zval *y_scale) {
    // TODO: implementation
}

void
php_cairo_surface_set_device_scale(php_cairo_surface_t *surface, zval *x_scale, zval *y_scale) {
    // TODO: implementation
}

void
php_cairo_surface_set_fallback_resolution(php_cairo_surface_t *surface, zval *x_pixels_per_inch, zval *y_pixels_per_inch) {
    // TODO: implementation
}

void
php_cairo_surface_get_fallback_resolution(php_cairo_surface_t *surface, zval *x_pixels_per_inch, zval *y_pixels_per_inch) {
    // TODO: implementation
}

zval *
php_cairo_surface_get_type(php_cairo_surface_t *surface) {
    // TODO: implementation
}

zval *
php_cairo_surface_get_reference_count(php_cairo_surface_t *surface) {
    // TODO: implementation
}

zval *
php_cairo_surface_set_user_data(php_cairo_surface_t *surface, zval *key, void user_data, zval *destroy) {
    // TODO: implementation
}

void
php_cairo_surface_get_user_data(php_cairo_surface_t *surface, zval *key) {
    // TODO: implementation
}

void
php_cairo_surface_copy_page(php_cairo_surface_t *surface) {
    // TODO: implementation
}

void
php_cairo_surface_show_page(php_cairo_surface_t *surface) {
    // TODO: implementation
}

zval *
php_cairo_surface_has_show_text_glyphs(php_cairo_surface_t *surface) {
    // TODO: implementation
}

zval *
php_cairo_surface_set_mime_data(php_cairo_surface_t *surface, zval *mime_type, zval *data, zval *length, zval *destroy, void closure) {
    // TODO: implementation
}

void
php_cairo_surface_get_mime_data(php_cairo_surface_t *surface, zval *mime_type, zval *data, zval *length) {
    // TODO: implementation
}

zval *
php_cairo_surface_supports_mime_type(php_cairo_surface_t *surface, zval *mime_type) {
    // TODO: implementation
}

php_cairo_surface_t *
php_cairo_surface_map_to_image(php_cairo_surface_t *surface, zval *extents) {
    // TODO: implementation
}

void
php_cairo_surface_unmap_image(php_cairo_surface_t *surface, php_cairo_surface_t *image) {
    // TODO: implementation
}
#endif




/*----------------------------------------------------------------------+
| PHP_METHOD                                                           |
+----------------------------------------------------------------------*/

/* {{{ cairo_surface_t::__construct() */
PHP_METHOD(cairo_surface_t, __construct)
{
    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();

    zend_object *zobj = Z_OBJ_P(getThis());
    php_cairo_surface_t *self = ZOBJ_TO_PHP_CAIRO_SURFACE_T(zobj);

}
/* }}} */


/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/
#if IS_IMPLEMENTED

/* {{{ proto cairo_surface_t cairo_surface_create_similar(cairo_surface_t other, mixed content, int width, int height) */
PHP_FUNCTION(cairo_surface_create_similar)
{
    zval *zother = NULL;
    zval *zcontent = NULL;
    zval *zwidth = NULL;
    zval *zheight = NULL;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(zother)
        Z_PARAM_ZVAL(zcontent)
        Z_PARAM_ZVAL(zwidth)
        Z_PARAM_ZVAL(zheight)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__other = zother;
    zval * *__content = zcontent;
    zend_long  *__width = zwidth;
    zend_long  *__height = zheight;
    php_cairo_surface_t *__ret = php_cairo_surface_create_similar(, __other, __content, __width, __height);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto cairo_surface_t cairo_surface_create_similar_image(cairo_surface_t other, mixed format, int width, int height) */
PHP_FUNCTION(cairo_surface_create_similar_image)
{
    zval *zother = NULL;
    zval *zformat = NULL;
    zval *zwidth = NULL;
    zval *zheight = NULL;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(zother)
        Z_PARAM_ZVAL(zformat)
        Z_PARAM_ZVAL(zwidth)
        Z_PARAM_ZVAL(zheight)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__other = zother;
    zval * *__format = zformat;
    zend_long  *__width = zwidth;
    zend_long  *__height = zheight;
    php_cairo_surface_t *__ret = php_cairo_surface_create_similar_image(, __other, __format, __width, __height);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto cairo_surface_t cairo_surface_create_for_rectangle(cairo_surface_t target, mixed x, mixed y, mixed width, mixed height) */
PHP_FUNCTION(cairo_surface_create_for_rectangle)
{
    zval *ztarget = NULL;
    zval *zx = NULL;
    zval *zy = NULL;
    zval *zwidth = NULL;
    zval *zheight = NULL;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(ztarget)
        Z_PARAM_ZVAL(zx)
        Z_PARAM_ZVAL(zy)
        Z_PARAM_ZVAL(zwidth)
        Z_PARAM_ZVAL(zheight)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__target = ztarget;
    zval * *__x = zx;
    zval * *__y = zy;
    zval * *__width = zwidth;
    zval * *__height = zheight;
    php_cairo_surface_t *__ret = php_cairo_surface_create_for_rectangle(, __target, __x, __y, __width, __height);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto cairo_surface_t cairo_surface_reference(cairo_surface_t surface) */
PHP_FUNCTION(cairo_surface_reference)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    php_cairo_surface_t *__ret = php_cairo_surface_reference(, __surface);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */
#endif

/* {{{ proto void cairo_surface_destroy(cairo_surface_t surface) */
PHP_FUNCTION(cairo_surface_destroy)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    cairo_surface_t *surface = php_surface==NULL ? NULL : php_surface->ptr;

    cairo_surface_destroy(surface);
    php_surface->ptr = NULL;

}/* }}} */

#if 0
/* {{{ proto mixed cairo_surface_status(cairo_surface_t surface) */
PHP_FUNCTION(cairo_surface_status)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    php_cairo_surface_t *__ret = php_cairo_surface_status(, __surface);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_finish(cairo_surface_t surface) */
PHP_FUNCTION(cairo_surface_finish)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    php_cairo_surface_t *__ret = php_cairo_surface_finish(, __surface);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_flush(cairo_surface_t surface) */
PHP_FUNCTION(cairo_surface_flush)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    php_cairo_surface_t *__ret = php_cairo_surface_flush(, __surface);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto mixed cairo_surface_get_device(cairo_surface_t surface) */
PHP_FUNCTION(cairo_surface_get_device)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    php_cairo_surface_t *__ret = php_cairo_surface_get_device(, __surface);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_get_font_options(cairo_surface_t surface, mixed options) */
PHP_FUNCTION(cairo_surface_get_font_options)
{
    zval *zsurface = NULL;
    zval *zoptions = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zoptions)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    zval * *__options = zoptions;
    php_cairo_surface_t *__ret = php_cairo_surface_get_font_options(, __surface, __options);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto mixed cairo_surface_get_content(cairo_surface_t surface) */
PHP_FUNCTION(cairo_surface_get_content)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    php_cairo_surface_t *__ret = php_cairo_surface_get_content(, __surface);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_mark_dirty(cairo_surface_t surface) */
PHP_FUNCTION(cairo_surface_mark_dirty)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    php_cairo_surface_t *__ret = php_cairo_surface_mark_dirty(, __surface);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_mark_dirty_rectangle(cairo_surface_t surface, int x, int y, int width, int height) */
PHP_FUNCTION(cairo_surface_mark_dirty_rectangle)
{
    zval *zsurface = NULL;
    zval *zx = NULL;
    zval *zy = NULL;
    zval *zwidth = NULL;
    zval *zheight = NULL;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zx)
        Z_PARAM_ZVAL(zy)
        Z_PARAM_ZVAL(zwidth)
        Z_PARAM_ZVAL(zheight)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    zend_long  *__x = zx;
    zend_long  *__y = zy;
    zend_long  *__width = zwidth;
    zend_long  *__height = zheight;
    php_cairo_surface_t *__ret = php_cairo_surface_mark_dirty_rectangle(, __surface, __x, __y, __width, __height);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_set_device_offset(cairo_surface_t surface, mixed x_offset, mixed y_offset) */
PHP_FUNCTION(cairo_surface_set_device_offset)
{
    zval *zsurface = NULL;
    zval *zx_offset = NULL;
    zval *zy_offset = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zx_offset)
        Z_PARAM_ZVAL(zy_offset)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    zval * *__x_offset = zx_offset;
    zval * *__y_offset = zy_offset;
    php_cairo_surface_t *__ret = php_cairo_surface_set_device_offset(, __surface, __x_offset, __y_offset);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_get_device_offset(cairo_surface_t surface, mixed x_offset, mixed y_offset) */
PHP_FUNCTION(cairo_surface_get_device_offset)
{
    zval *zsurface = NULL;
    zval *zx_offset = NULL;
    zval *zy_offset = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zx_offset)
        Z_PARAM_ZVAL(zy_offset)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    zval * *__x_offset = zx_offset;
    zval * *__y_offset = zy_offset;
    php_cairo_surface_t *__ret = php_cairo_surface_get_device_offset(, __surface, __x_offset, __y_offset);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_get_device_scale(cairo_surface_t surface, mixed x_scale, mixed y_scale) */
PHP_FUNCTION(cairo_surface_get_device_scale)
{
    zval *zsurface = NULL;
    zval *zx_scale = NULL;
    zval *zy_scale = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zx_scale)
        Z_PARAM_ZVAL(zy_scale)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    zval * *__x_scale = zx_scale;
    zval * *__y_scale = zy_scale;
    php_cairo_surface_t *__ret = php_cairo_surface_get_device_scale(, __surface, __x_scale, __y_scale);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_set_device_scale(cairo_surface_t surface, mixed x_scale, mixed y_scale) */
PHP_FUNCTION(cairo_surface_set_device_scale)
{
    zval *zsurface = NULL;
    zval *zx_scale = NULL;
    zval *zy_scale = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zx_scale)
        Z_PARAM_ZVAL(zy_scale)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    zval * *__x_scale = zx_scale;
    zval * *__y_scale = zy_scale;
    php_cairo_surface_t *__ret = php_cairo_surface_set_device_scale(, __surface, __x_scale, __y_scale);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_set_fallback_resolution(cairo_surface_t surface, mixed x_pixels_per_inch, mixed y_pixels_per_inch) */
PHP_FUNCTION(cairo_surface_set_fallback_resolution)
{
    zval *zsurface = NULL;
    zval *zx_pixels_per_inch = NULL;
    zval *zy_pixels_per_inch = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zx_pixels_per_inch)
        Z_PARAM_ZVAL(zy_pixels_per_inch)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    zval * *__x_pixels_per_inch = zx_pixels_per_inch;
    zval * *__y_pixels_per_inch = zy_pixels_per_inch;
    php_cairo_surface_t *__ret = php_cairo_surface_set_fallback_resolution(, __surface, __x_pixels_per_inch, __y_pixels_per_inch);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_get_fallback_resolution(cairo_surface_t surface, mixed x_pixels_per_inch, mixed y_pixels_per_inch) */
PHP_FUNCTION(cairo_surface_get_fallback_resolution)
{
    zval *zsurface = NULL;
    zval *zx_pixels_per_inch = NULL;
    zval *zy_pixels_per_inch = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zx_pixels_per_inch)
        Z_PARAM_ZVAL(zy_pixels_per_inch)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    zval * *__x_pixels_per_inch = zx_pixels_per_inch;
    zval * *__y_pixels_per_inch = zy_pixels_per_inch;
    php_cairo_surface_t *__ret = php_cairo_surface_get_fallback_resolution(, __surface, __x_pixels_per_inch, __y_pixels_per_inch);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto mixed cairo_surface_get_type(cairo_surface_t surface) */
PHP_FUNCTION(cairo_surface_get_type)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    php_cairo_surface_t *__ret = php_cairo_surface_get_type(, __surface);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */
#endif

/* {{{ proto mixed cairo_surface_get_reference_count(cairo_surface_t surface) */
PHP_FUNCTION(cairo_surface_get_reference_count)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    cairo_surface_t *surface = php_surface==NULL ? NULL : php_surface->ptr;

    unsigned int ref = cairo_surface_get_reference_count(surface);

    RETURN_LONG(ref);
}/* }}} */

#if 0
/* {{{ proto mixed cairo_surface_set_user_data(cairo_surface_t surface, mixed key, void user_data, mixed destroy) */
PHP_FUNCTION(cairo_surface_set_user_data)
{
    zval *zsurface = NULL;
    zval *zkey = NULL;
    zval *zuser_data = NULL;
    zval *zdestroy = NULL;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zkey)
        Z_PARAM_ZVAL(zuser_data)
        Z_PARAM_ZVAL(zdestroy)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    zval * *__key = zkey;
    void  *__user_data = zuser_data;
    zval * *__destroy = zdestroy;
    php_cairo_surface_t *__ret = php_cairo_surface_set_user_data(, __surface, __key, __user_data, __destroy);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_get_user_data(cairo_surface_t surface, mixed key) */
PHP_FUNCTION(cairo_surface_get_user_data)
{
    zval *zsurface = NULL;
    zval *zkey = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zkey)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    zval * *__key = zkey;
    php_cairo_surface_t *__ret = php_cairo_surface_get_user_data(, __surface, __key);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_copy_page(cairo_surface_t surface) */
PHP_FUNCTION(cairo_surface_copy_page)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    php_cairo_surface_t *__ret = php_cairo_surface_copy_page(, __surface);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_show_page(cairo_surface_t surface) */
PHP_FUNCTION(cairo_surface_show_page)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    php_cairo_surface_t *__ret = php_cairo_surface_show_page(, __surface);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto mixed cairo_surface_has_show_text_glyphs(cairo_surface_t surface) */
PHP_FUNCTION(cairo_surface_has_show_text_glyphs)
{
    zval *zsurface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zsurface)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    php_cairo_surface_t *__ret = php_cairo_surface_has_show_text_glyphs(, __surface);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto mixed cairo_surface_set_mime_data(cairo_surface_t surface, mixed mime_type, mixed data, mixed length, mixed destroy, void closure) */
PHP_FUNCTION(cairo_surface_set_mime_data)
{
    zval *zsurface = NULL;
    zval *zmime_type = NULL;
    zval *zdata = NULL;
    zval *zlength = NULL;
    zval *zdestroy = NULL;
    zval *zclosure = NULL;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zmime_type)
        Z_PARAM_ZVAL(zdata)
        Z_PARAM_ZVAL(zlength)
        Z_PARAM_ZVAL(zdestroy)
        Z_PARAM_ZVAL(zclosure)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    zval * *__mime_type = zmime_type;
    zval * *__data = zdata;
    zval * *__length = zlength;
    zval * *__destroy = zdestroy;
    void  *__closure = zclosure;
    php_cairo_surface_t *__ret = php_cairo_surface_set_mime_data(, __surface, __mime_type, __data, __length, __destroy, __closure);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_get_mime_data(cairo_surface_t surface, mixed mime_type, mixed data, mixed length) */
PHP_FUNCTION(cairo_surface_get_mime_data)
{
    zval *zsurface = NULL;
    zval *zmime_type = NULL;
    zval *zdata = NULL;
    zval *zlength = NULL;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zmime_type)
        Z_PARAM_ZVAL(zdata)
        Z_PARAM_ZVAL(zlength)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    zval * *__mime_type = zmime_type;
    zval * *__data = zdata;
    zval * *__length = zlength;
    php_cairo_surface_t *__ret = php_cairo_surface_get_mime_data(, __surface, __mime_type, __data, __length);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto mixed cairo_surface_supports_mime_type(cairo_surface_t surface, mixed mime_type) */
PHP_FUNCTION(cairo_surface_supports_mime_type)
{
    zval *zsurface = NULL;
    zval *zmime_type = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zmime_type)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    zval * *__mime_type = zmime_type;
    php_cairo_surface_t *__ret = php_cairo_surface_supports_mime_type(, __surface, __mime_type);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto cairo_surface_t cairo_surface_map_to_image(cairo_surface_t surface, mixed extents) */
PHP_FUNCTION(cairo_surface_map_to_image)
{
    zval *zsurface = NULL;
    zval *zextents = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zextents)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    zval * *__extents = zextents;
    php_cairo_surface_t *__ret = php_cairo_surface_map_to_image(, __surface, __extents);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_surface_unmap_image(cairo_surface_t surface, cairo_surface_t image) */
PHP_FUNCTION(cairo_surface_unmap_image)
{
    zval *zsurface = NULL;
    zval *zimage = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zsurface)
        Z_PARAM_ZVAL(zimage)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t * *__surface = zsurface;
    php_cairo_surface_t * *__image = zimage;
    php_cairo_surface_t *__ret = php_cairo_surface_unmap_image(, __surface, __image);

    if(__list)
        GC_REFCOUNT(&__ret->std)++;
    RETURN_OBJ(&__ret->std);
}/* }}} */
#endif
