/*
+----------------------------------------------------------------------+
| PHP Version 8                                                        |
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

#include "php_cairo/surface.h"
#include "php_cairo/status.h"
#include "php_cairo/content.h"
#include "php_cairo/pattern.h"
#include "php_cairo/antialias.h"
#include "php_cairo/fill-rule.h"
#include "php_cairo/line-cap.h"
#include "php_cairo/line-join.h"
#include "php_cairo/operator.h"
/*#include "php_cairo/rectangle-list.h"*/
#include "php_cairo/rectangle.h"

#include "php_cairo/cairo.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_t_class_entry;// struct
zend_object_handlers  php_cairo_t_handlers;







/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_t_methods[] = {
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
    php_cairo_t *intern = zend_object_alloc(sizeof(php_cairo_t), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_cairo_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_t_create_object */

static void
php_cairo_t_dtor_object(zend_object *obj) {
    //php_cairo_t *intern = ZOBJ_TO_PHP_CAIRO_T(obj);

}

/* {{{ php_cairo_t_free_object */
static void
php_cairo_t_free_object(zend_object *object)
{
    php_cairo_t *intern = ZOBJ_TO_PHP_CAIRO_T(object);

    if (intern->ptr) {
        cairo_destroy(intern->ptr);
        intern->ptr = NULL;
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_t_free_object */





/** {{{ php_cairo_t_get_debug_info() */
static HashTable*
php_cairo_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_t  *obj = ZOBJ_TO_PHP_CAIRO_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    zval zstatus; ZVAL_LONG(&zstatus, cairo_status(obj->ptr));
    zend_hash_str_update(debug_info, "status", sizeof("status")-1, &zstatus);

    return debug_info;
}
/* }}} */




static zend_object_handlers*
php_cairo_t_get_handlers()
{
    memcpy(&php_cairo_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_t_handlers.offset = PHP_CAIRO_T_OFFSET;
    php_cairo_t_handlers.dtor_obj = php_cairo_t_dtor_object;
    php_cairo_t_handlers.free_obj = php_cairo_t_free_object;


    php_cairo_t_handlers.get_debug_info = php_cairo_t_get_debug_info;


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

    return php_cairo_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/
php_cairo_t*
php_cairo_t_new()
{
    zend_object *z_cairo_t = php_cairo_t_create_object(php_cairo_t_class_entry);
    php_cairo_t *php_cairo = ZOBJ_TO_PHP_CAIRO_T(z_cairo_t);
    return php_cairo;
}

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

 /* {{{ cairo_t::__construct() */
PHP_METHOD(cairo_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_t *self = ZOBJ_TO_PHP_CAIRO_T(zobj);


}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

/* {{{ proto php_cairo_t cairo_create(php_cairo_surface_t target)
   Creates a new cairo_t with all graphics state parameters set to defau... */
PHP_FUNCTION(cairo_create)
{
    zval *ztarget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(ztarget, php_cairo_surface_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_surface_t *php_target = ZVAL_IS_PHP_CAIRO_SURFACE_T(ztarget)? ZVAL_GET_PHP_CAIRO_SURFACE_T(ztarget): NULL;
    //DECL_PHP_CAIRO_SURFACE_T(target);
    cairo_surface_t *target = php_target->ptr;

    cairo_t *ret = cairo_create(target);

    php_cairo_t *php_ret = php_cairo_t_new();
    php_ret->ptr = ret;
    zend_object *z_ret = &php_ret->std;
    RETURN_OBJ(z_ret);
}/* }}} */

/* {{{ proto php_cairo_t cairo_reference(php_cairo_t cr)
   Increases the reference count on cr by one. */
PHP_FUNCTION(cairo_reference)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_t *ret = cairo_reference(cr);


    zend_object *z_ret = php_cairo_t_create_object(php_cairo_t_class_entry);
    php_cairo_t *php_ret = ZOBJ_TO_PHP_CAIRO_T(z_ret);
    php_ret->ptr = ret;
    RETURN_OBJ(z_ret);
}/* }}} */

/* {{{ proto void cairo_destroy(php_cairo_t cr)
   Decreases the reference count on cr by one. */
PHP_FUNCTION(cairo_destroy)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_destroy(cr);
    php_cr->ptr = NULL;

    RETURN_NULL();
}/* }}} */

/* {{{ proto int cairo_status(php_cairo_t cr)
   Checks whether an error has previously occurred for this context. */
PHP_FUNCTION(cairo_status)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    int ret = cairo_status(cr);

    RETURN_LONG(ret);
}/* }}} */

/* {{{ proto void cairo_save(php_cairo_t cr)
   Makes a copy of the current state of cr and saves it on an internal s... */
PHP_FUNCTION(cairo_save)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_save(cr);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_restore(php_cairo_t cr)
   Restores cr to the state saved by a preceding call to cairo_save() an... */
PHP_FUNCTION(cairo_restore)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_restore(cr);
    RETURN_NULL();
}/* }}} */

/* {{{ proto php_cairo_surface_t cairo_get_target(php_cairo_t cr)
   Gets the target surface for the cairo context as passed to cairo_create(). */
PHP_FUNCTION(cairo_get_target)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_surface_t *ret = cairo_get_target(cr);

    php_cairo_surface_t *php_ret = php_cairo_surface_t_new();
    zend_object *z_ret = &php_ret->std;
    php_ret->ptr = ret;
    RETURN_OBJ(z_ret);
}/* }}} */

/* {{{ proto void cairo_push_group(php_cairo_t cr)
   Temporarily redirects drawing to an intermediate surface known as a g... */
PHP_FUNCTION(cairo_push_group)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_push_group(cr);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_push_group_with_content(php_cairo_t cr, int content)
   Temporarily redirects drawing to an intermediate surface known as a g... */
PHP_FUNCTION(cairo_push_group_with_content)
{
    zval *zcr;
    zend_long zcontent;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_LONG(zcontent);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    cairo_content_t content = zcontent;

    cairo_push_group_with_content(cr, content);
    RETURN_NULL();
}/* }}} */

/* {{{ proto php_cairo_pattern_t cairo_pop_group(php_cairo_t cr)
   Terminates the redirection begun by a call to cairo_push_group() or c... */
PHP_FUNCTION(cairo_pop_group)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_pattern_t *ret = cairo_pop_group(cr);

    zend_object *z_ret = zend_objects_new(php_cairo_pattern_t_class_entry);
    php_cairo_pattern_t *php_ret = ZOBJ_TO_PHP_CAIRO_PATTERN_T(z_ret);
    php_ret->ptr = z_ret;
    RETURN_OBJ(z_ret);
#endif
}/* }}} */

/* {{{ proto void cairo_pop_group_to_source(php_cairo_t cr)
   Terminates the redirection begun by a call to cairo_push_group() or c... */
PHP_FUNCTION(cairo_pop_group_to_source)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_pop_group_to_source(cr);
    RETURN_NULL();
}/* }}} */

/* {{{ proto php_cairo_surface_t cairo_get_group_target(php_cairo_t cr)
   Gets the current destination surface for the context. */
PHP_FUNCTION(cairo_get_group_target)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_surface_t *ret = cairo_get_group_target(cr);

    php_cairo_surface_t *php_ret = php_cairo_surface_t_new();
    zend_object *z_ret = &php_ret->std;
    php_ret->ptr = ret;
    RETURN_OBJ(z_ret);
}/* }}} */

/* {{{ proto void cairo_set_source_rgb(php_cairo_t cr, double red, double green, double blue)
   Sets the source pattern within cr to an opaque color. */
PHP_FUNCTION(cairo_set_source_rgb)
{
    zval *zcr;
    double red;
    double green;
    double blue;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(red);
        Z_PARAM_DOUBLE(green);
        Z_PARAM_DOUBLE(blue);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_set_source_rgb(cr, red, green, blue);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_set_source_rgba(php_cairo_t cr, double red, double green, double blue, double alpha)
   Sets the source pattern within cr to a translucent color. */
PHP_FUNCTION(cairo_set_source_rgba)
{
    zval *zcr;
    double red;
    double green;
    double blue;
    double alpha;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(red);
        Z_PARAM_DOUBLE(green);
        Z_PARAM_DOUBLE(blue);
        Z_PARAM_DOUBLE(alpha);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_set_source_rgba(cr, red, green, blue, alpha);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_set_source(php_cairo_t cr, php_cairo_pattern_t source)
   Sets the source pattern within cr to source . */
PHP_FUNCTION(cairo_set_source)
{
    zval *zcr;
    zval *zsource;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zsource, php_cairo_pattern_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_pattern_t *php_source = ZVAL_IS_PHP_CAIRO_PATTERN_T(zsource)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zsource): NULL;
    DECL_PHP_CAIRO_PATTERN_T(source);

    cairo_set_source(cr, source);
    RETURN_NULL();

}/* }}} */

/* {{{ proto void cairo_set_source_surface(php_cairo_t cr, php_cairo_surface_t surface, double x, double y)
   This is a convenience function for creating a pattern from surface an... */
PHP_FUNCTION(cairo_set_source_surface)
{
    zval *zcr;
    zval *zsurface;
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x);
        Z_PARAM_DOUBLE(y);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_set_source_surface(cr, surface, x, y);
    RETURN_NULL();
}/* }}} */

/* {{{ proto php_cairo_pattern_t cairo_get_source(php_cairo_t cr)
   Gets the current source pattern for cr . */
PHP_FUNCTION(cairo_get_source)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

#if 0
    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_pattern_t *ret = cairo_get_source(cr);

    zend_object *z_ret = zend_objects_new(php_cairo_pattern_t_class_entry);
    php_cairo_pattern_t *php_ret = ZOBJ_TO_PHP_CAIRO_PATTERN_T(z_ret);
    php_ret->ptr = z_ret;
    RETURN_OBJ(z_ret);
#endif
}/* }}} */

/* {{{ proto void cairo_set_antialias(php_cairo_t cr, int antialias)
   Set the antialiasing mode of the rasterizer used for drawing shapes. */
PHP_FUNCTION(cairo_set_antialias)
{
    zval *zcr;
    zend_long zantialias;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_LONG(zantialias);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    cairo_antialias_t antialias = zantialias;

    cairo_set_antialias(cr, antialias);
    RETURN_NULL();
}/* }}} */

/* {{{ proto int cairo_get_antialias(php_cairo_t cr)
   Gets the current shape antialiasing mode, as set by cairo_set_antialias(). */
PHP_FUNCTION(cairo_get_antialias)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    int ret = cairo_get_antialias(cr);

    RETURN_LONG(ret);
}/* }}} */


static double *
zval_get_array_double(zval *zarray, zend_long *num_dashes) {
    double *array;

    int i=0;
    int length = zend_array_count(zarray->value.arr);
    array = emalloc(sizeof(double)*length);

    zval *value;

    //g_print("php_cairo_path_t_get_path: %d\n", data->value.arr->nNumOfElements);
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(zarray), value) {
        if (IS_DOUBLE==Z_TYPE_P(value)) {
            array[i] = Z_DVAL_P(value);
            i++;
        }
    } ZEND_HASH_FOREACH_END();

    if (*num_dashes!=i) {
        *num_dashes = i;
        // echo Error : fix size of num_data
    }


    return array;
}

/* {{{ proto void cairo_set_dash(php_cairo_t cr, double dashes, int num_dashes, double offset)
   Sets the dash pattern to be used by cairo_stroke(). */
PHP_FUNCTION(cairo_set_dash)
{
    zval *zcr;
    zval *zdashes;
    zend_long num_dashes;
    double offset;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_ARRAY_EX(zdashes, 1, 0);
        Z_PARAM_LONG(num_dashes);
        Z_PARAM_DOUBLE(offset);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    const double *dashes = zval_get_array_double(zdashes, &num_dashes);

    cairo_set_dash(cr, dashes, num_dashes, offset);
    efree(dashes);

    RETURN_NULL();
}/* }}} */

/* {{{ proto int cairo_get_dash_count(php_cairo_t cr)
   This function returns the length of the dash array in cr (0 if dashin... */
PHP_FUNCTION(cairo_get_dash_count)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    int ret = cairo_get_dash_count(cr);

    RETURN_LONG(ret);
}/* }}} */

/* {{{ proto void cairo_get_dash(php_cairo_t cr, double dashes, double offset)
   Gets the current dash array. */
PHP_FUNCTION(cairo_get_dash)
{
    zval *zcr;
    zval *zdashes;
    zval *zoffset;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zdashes, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zoffset, 0, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    double dashes = zdashes->value.dval;
    double offset = zoffset->value.dval;

    cairo_get_dash(cr, &dashes, &offset);
    ZVAL_DOUBLE(zdashes, dashes);
    ZVAL_DOUBLE(zoffset, offset);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_set_fill_rule(php_cairo_t cr, int fill_rule)
   Set the current fill rule within the cairo context. */
PHP_FUNCTION(cairo_set_fill_rule)
{
    zval *zcr;
    zend_long zfill_rule;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_LONG(zfill_rule);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    cairo_fill_rule_t fill_rule = zfill_rule;

    cairo_set_fill_rule(cr, fill_rule);
    RETURN_NULL();
}/* }}} */

/* {{{ proto int cairo_get_fill_rule(php_cairo_t cr)
   Gets the current fill rule, as set by cairo_set_fill_rule(). */
PHP_FUNCTION(cairo_get_fill_rule)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    int ret = cairo_get_fill_rule(cr);

    RETURN_LONG(ret);
}/* }}} */

/* {{{ proto void cairo_set_line_cap(php_cairo_t cr, int line_cap)
   Sets the current line cap style within the cairo context. */
PHP_FUNCTION(cairo_set_line_cap)
{
    zval *zcr;
    zend_long zline_cap;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_LONG(zline_cap);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    cairo_line_cap_t line_cap = zline_cap;

    cairo_set_line_cap(cr, line_cap);
    RETURN_NULL();
}/* }}} */

/* {{{ proto int cairo_get_line_cap(php_cairo_t cr)
   Gets the current line cap style, as set by cairo_set_line_cap(). */
PHP_FUNCTION(cairo_get_line_cap)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    int ret = cairo_get_line_cap(cr);

    RETURN_LONG(ret);
}/* }}} */

/* {{{ proto void cairo_set_line_join(php_cairo_t cr, int line_join)
   Sets the current line join style within the cairo context. */
PHP_FUNCTION(cairo_set_line_join)
{
    zval *zcr;
    zend_long zline_join;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_LONG(zline_join);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    cairo_line_join_t line_join = zline_join;

    cairo_set_line_join(cr, line_join);
    RETURN_NULL();
}/* }}} */

/* {{{ proto int cairo_get_line_join(php_cairo_t cr)
   Gets the current line join style, as set by cairo_set_line_join(). */
PHP_FUNCTION(cairo_get_line_join)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    int ret = cairo_get_line_join(cr);

    RETURN_LONG(ret);
}/* }}} */

/* {{{ proto void cairo_set_line_width(php_cairo_t cr, double width)
   Sets the current line width within the cairo context. */
PHP_FUNCTION(cairo_set_line_width)
{
    zval *zcr;
    double width;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(width);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_set_line_width(cr, width);
    RETURN_NULL();
}/* }}} */

/* {{{ proto double cairo_get_line_width(php_cairo_t cr)
   This function returns the current line width value exactly as set by ... */
PHP_FUNCTION(cairo_get_line_width)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    double ret = cairo_get_line_width(cr);

    RETURN_DOUBLE(ret);
}/* }}} */

/* {{{ proto void cairo_set_miter_limit(php_cairo_t cr, double limit)
   Sets the current miter limit within the cairo context. */
PHP_FUNCTION(cairo_set_miter_limit)
{
    zval *zcr;
    double limit;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(limit);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_set_miter_limit(cr, limit);
    RETURN_NULL();
}/* }}} */

/* {{{ proto double cairo_get_miter_limit(php_cairo_t cr)
   Gets the current miter limit, as set by cairo_set_miter_limit(). */
PHP_FUNCTION(cairo_get_miter_limit)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    double ret = cairo_get_miter_limit(cr);

    RETURN_DOUBLE(ret);
}/* }}} */

/* {{{ proto void cairo_set_operator(php_cairo_t cr, int op)
   Sets the compositing operator to be used for all drawing operations. */
PHP_FUNCTION(cairo_set_operator)
{
    zval *zcr;
    zend_long zop;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_LONG(zop);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    cairo_operator_t op = zop;

    cairo_set_operator(cr, op);
    RETURN_NULL();
}/* }}} */

/* {{{ proto int cairo_get_operator(php_cairo_t cr)
   Gets the current compositing operator for a cairo context. */
PHP_FUNCTION(cairo_get_operator)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    int ret = cairo_get_operator(cr);

    RETURN_LONG(ret);
}/* }}} */

/* {{{ proto void cairo_set_tolerance(php_cairo_t cr, double tolerance)
   Sets the tolerance used when converting paths into trapezoids. */
PHP_FUNCTION(cairo_set_tolerance)
{
    zval *zcr;
    double tolerance;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(tolerance);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_set_tolerance(cr, tolerance);
    RETURN_NULL();
}/* }}} */

/* {{{ proto double cairo_get_tolerance(php_cairo_t cr)
   Gets the current tolerance value, as set by cairo_set_tolerance(). */
PHP_FUNCTION(cairo_get_tolerance)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    double ret = cairo_get_tolerance(cr);

    RETURN_DOUBLE(ret);
}/* }}} */

/* {{{ proto void cairo_clip(php_cairo_t cr)
   Establishes a new clip region by intersecting the current clip region... */
PHP_FUNCTION(cairo_clip)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_clip(cr);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_clip_preserve(php_cairo_t cr)
   Establishes a new clip region by intersecting the current clip region... */
PHP_FUNCTION(cairo_clip_preserve)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_clip_preserve(cr);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_clip_extents(php_cairo_t cr, double x1, double y1, double x2, double y2)
   Computes a bounding box in user coordinates covering the area inside ... */
PHP_FUNCTION(cairo_clip_extents)
{
    zval *zcr;
    zval *zx1;
    zval *zy1;
    zval *zx2;
    zval *zy2;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zx1, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zy1, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zx2, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zy2, 0, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    double x1 = zx1->value.dval;
    double y1 = zy1->value.dval;
    double x2 = zx2->value.dval;
    double y2 = zy2->value.dval;

    cairo_clip_extents(cr, &x1, &y1, &x2, &y2);
    ZVAL_DOUBLE(zx1, x1);
    ZVAL_DOUBLE(zy1, y1);
    ZVAL_DOUBLE(zx2, x2);
    ZVAL_DOUBLE(zy2, y2);
    RETURN_NULL();
}/* }}} */

/* {{{ proto cairo_bool_t cairo_in_clip(php_cairo_t cr, double x, double y)
   Tests whether the given point is inside the area that would be visibl... */
PHP_FUNCTION(cairo_in_clip)
{
    zval *zcr;
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x);
        Z_PARAM_DOUBLE(y);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_bool_t ret = cairo_in_clip(cr, x, y);

    if (ret) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}/* }}} */

/* {{{ proto void cairo_reset_clip(php_cairo_t cr)
   Reset the current clip region to its original, unrestricted state. */
PHP_FUNCTION(cairo_reset_clip)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_reset_clip(cr);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_rectangle_list_destroy(php_cairo_rectangle_list_t rectangle_list)
   Unconditionally frees rectangle_list and all associated references. */
PHP_FUNCTION(cairo_rectangle_list_destroy)
{
    zval *zrectangle_list;

#if 0
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zrectangle_list, php_cairo_rectangle_list_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_rectangle_list_t *php_rectangle_list = ZVAL_IS_PHP_CAIRO_RECTANGLE_LIST_T(zrectangle_list)? ZVAL_GET_PHP_CAIRO_RECTANGLE_LIST_T(zrectangle_list): NULL;
    DECL_PHP_CAIRO_RECTANGLE_LIST_T(rectangle_list);

    cairo_rectangle_list_destroy(rectangle_list);
    RETURN_NULL();
#endif
}/* }}} */

/* {{{ proto php_cairo_rectangle_list_t cairo_copy_clip_rectangle_list(php_cairo_t cr)
   Gets the current clip region as a list of rectangles in user coordina... */
PHP_FUNCTION(cairo_copy_clip_rectangle_list)
{
    zval *zcr;

#if 0
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_rectangle_list_t *ret = cairo_copy_clip_rectangle_list(cr);

    zend_object *z_ret = zend_objects_new(php_cairo_rectangle_list_t_class_entry);
    php_cairo_rectangle_list_t *php_ret = ZOBJ_TO_PHP_CAIRO_RECTANGLE_LIST_T(z_ret);
    php_ret->ptr = z_ret;
    RETURN_OBJ(z_ret);
#endif
}/* }}} */

/* {{{ proto void cairo_fill(php_cairo_t cr)
   A drawing operator that fills the current path according to the curre... */
PHP_FUNCTION(cairo_fill)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_fill(cr);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_fill_preserve(php_cairo_t cr)
   A drawing operator that fills the current path according to the curre... */
PHP_FUNCTION(cairo_fill_preserve)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_fill_preserve(cr);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_fill_extents(php_cairo_t cr, double x1, double y1, double x2, double y2)
   Computes a bounding box in user coordinates covering the area that wo... */
PHP_FUNCTION(cairo_fill_extents)
{
    zval *zcr;
    zval *zx1;
    zval *zy1;
    zval *zx2;
    zval *zy2;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zx1, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zy1, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zx2, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zy2, 0, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    double x1 = zx1->value.dval;
    double y1 = zy1->value.dval;
    double x2 = zx2->value.dval;
    double y2 = zy2->value.dval;

    cairo_fill_extents(cr, &x1, &y1, &x2, &y2);
    ZVAL_DOUBLE(zx1, x1);
    ZVAL_DOUBLE(zy1, y1);
    ZVAL_DOUBLE(zx2, x2);
    ZVAL_DOUBLE(zy2, y2);
    RETURN_NULL();
}/* }}} */

/* {{{ proto cairo_bool_t cairo_in_fill(php_cairo_t cr, double x, double y)
   Tests whether the given point is inside the area that would be affect... */
PHP_FUNCTION(cairo_in_fill)
{
    zval *zcr;
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x);
        Z_PARAM_DOUBLE(y);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_bool_t ret = cairo_in_fill(cr, x, y);

    if (ret) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}/* }}} */

/* {{{ proto void cairo_mask(php_cairo_t cr, php_cairo_pattern_t pattern)
   A drawing operator that paints the current source using the alpha cha... */
PHP_FUNCTION(cairo_mask)
{
    zval *zcr;
    zval *zpattern;

#if 0
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_mask(cr, pattern);
    RETURN_NULL();
#endif
}/* }}} */

/* {{{ proto void cairo_mask_surface(php_cairo_t cr, php_cairo_surface_t surface, double surface_x, double surface_y)
   A drawing operator that paints the current source using the alpha cha... */
PHP_FUNCTION(cairo_mask_surface)
{
    zval *zcr;
    zval *zsurface;
    double surface_x;
    double surface_y;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zsurface, php_cairo_surface_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(surface_x);
        Z_PARAM_DOUBLE(surface_y);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_surface_t *php_surface = ZVAL_IS_PHP_CAIRO_SURFACE_T(zsurface)? ZVAL_GET_PHP_CAIRO_SURFACE_T(zsurface): NULL;
    DECL_PHP_CAIRO_SURFACE_T(surface);

    cairo_mask_surface(cr, surface, surface_x, surface_y);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_paint(php_cairo_t cr)
   A drawing operator that paints the current source everywhere within t... */
PHP_FUNCTION(cairo_paint)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_paint(cr);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_paint_with_alpha(php_cairo_t cr, double alpha)
   A drawing operator that paints the current source everywhere within t... */
PHP_FUNCTION(cairo_paint_with_alpha)
{
    zval *zcr;
    double alpha;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(alpha);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_paint_with_alpha(cr, alpha);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_stroke(php_cairo_t cr)
   A drawing operator that strokes the current path according to the cur... */
PHP_FUNCTION(cairo_stroke)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_stroke(cr);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_stroke_preserve(php_cairo_t cr)
   A drawing operator that strokes the current path according to the cur... */
PHP_FUNCTION(cairo_stroke_preserve)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_stroke_preserve(cr);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_stroke_extents(php_cairo_t cr, double x1, double y1, double x2, double y2)
   Computes a bounding box in user coordinates covering the area that wo... */
PHP_FUNCTION(cairo_stroke_extents)
{
    zval *zcr;
    zval *zx1;
    zval *zy1;
    zval *zx2;
    zval *zy2;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zx1, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zy1, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zx2, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zy2, 0, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    double x1 = zx1->value.dval;
    double y1 = zy1->value.dval;
    double x2 = zx2->value.dval;
    double y2 = zy2->value.dval;

    cairo_stroke_extents(cr, &x1, &y1, &x2, &y2);
    ZVAL_DOUBLE(zx1, x1);
    ZVAL_DOUBLE(zy1, y1);
    ZVAL_DOUBLE(zx2, x2);
    ZVAL_DOUBLE(zy2, y2);
    RETURN_NULL();
}/* }}} */

/* {{{ proto cairo_bool_t cairo_in_stroke(php_cairo_t cr, double x, double y)
   Tests whether the given point is inside the area that would be affect... */
PHP_FUNCTION(cairo_in_stroke)
{
    zval *zcr;
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x);
        Z_PARAM_DOUBLE(y);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_bool_t ret = cairo_in_stroke(cr, x, y);

    if (ret) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}/* }}} */

/* {{{ proto void cairo_copy_page(php_cairo_t cr)
   Emits the current page for backends that support multiple pages, but ... */
PHP_FUNCTION(cairo_copy_page)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_copy_page(cr);
    RETURN_NULL();
}/* }}} */

/* {{{ proto void cairo_show_page(php_cairo_t cr)
   Emits and clears the current page for backends that support multiple ... */
PHP_FUNCTION(cairo_show_page)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_show_page(cr);
    RETURN_NULL();
}/* }}} */

/* {{{ proto int cairo_get_reference_count(php_cairo_t cr)
   Returns the current reference count of cr . */
PHP_FUNCTION(cairo_get_reference_count)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    int ret = cairo_get_reference_count(cr);

    RETURN_LONG(ret);
}/* }}} */

/* {{{ proto int cairo_set_user_data(php_cairo_t cr, php_cairo_user_data_key_t key, void user_data, cairo_destroy_func_t destroy)
   Attach user data to cr . */
PHP_FUNCTION(cairo_set_user_data)
{
    zval *zcr;
    zval *zkey;
    zval *zuser_data;
    zval *zdestroy;

#if 0
    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zkey, php_cairo_user_data_key_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zuser_data, php_void_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zdestroy, php_cairo_destroy_func_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_user_data_key_t *php_key = ZVAL_IS_PHP_CAIRO_USER_DATA_KEY_T(zkey)? ZVAL_GET_PHP_CAIRO_USER_DATA_KEY_T(zkey): NULL;
    DECL_PHP_CAIRO_USER_DATA_KEY_T(key);
    php_void *php_user_data = ZVAL_IS_PHP_VOID(zuser_data)? ZVAL_GET_PHP_VOID(zuser_data): NULL;
    DECL_PHP_VOID(user_data);
    php_cairo_destroy_func_t *php_destroy = ZVAL_IS_PHP_CAIRO_DESTROY_FUNC_T(zdestroy)? ZVAL_GET_PHP_CAIRO_DESTROY_FUNC_T(zdestroy): NULL;
    DECL_PHP_CAIRO_DESTROY_FUNC_T(destroy);

    int ret = cairo_set_user_data(cr, key, user_data, destroy);

    RETURN_LONG(ret);
#endif
}/* }}} */

/* {{{ proto void cairo_get_user_data(php_cairo_t cr, php_cairo_user_data_key_t key)
   Return user data previously attached to cr using the specified key. */
PHP_FUNCTION(cairo_get_user_data)
{
    zval *zcr;
    zval *zkey;

#if 0
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zkey, php_cairo_user_data_key_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_user_data_key_t *php_key = ZVAL_IS_PHP_CAIRO_USER_DATA_KEY_T(zkey)? ZVAL_GET_PHP_CAIRO_USER_DATA_KEY_T(zkey): NULL;
    DECL_PHP_CAIRO_USER_DATA_KEY_T(key);

    cairo_get_user_data(cr, key);
#endif
    RETURN_NULL();
}/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
