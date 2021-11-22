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
#include "php_cairo/rectangle-int.h"
#include "php_cairo/status.h"
#include "php_cairo/region-overlap.h"

#include "php_cairo/region.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_region_t_class_entry;// struct
zend_object_handlers  php_cairo_region_t_handlers;







/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_region_t_methods[] = {
    PHP_ME(cairo_region_t, __construct, arginfo_cairo_region_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_region_t_create_object */
static zend_object*
php_cairo_region_t_create_object(zend_class_entry *class_type)
{
    php_cairo_region_t *intern = zend_object_alloc(sizeof(php_cairo_region_t), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_cairo_region_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_region_t_create_object */


static void
php_cairo_region_t_dtor_object(zend_object *obj) {
    //php_cairo_region_t *intern = ZOBJ_TO_PHP_CAIRO_REGION_T(obj);

}

/* {{{ php_cairo_region_t_free_object */
static void
php_cairo_region_t_free_object(zend_object *object)
{
    php_cairo_region_t *intern = ZOBJ_TO_PHP_CAIRO_REGION_T(object);

    if (intern->ptr) {
        intern->ptr = NULL;
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_region_t_free_object */





/* {{{ php_cairo_region_t_get_debug_info */
static HashTable*
php_cairo_region_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_region_t  *intern = ZOBJ_TO_PHP_CAIRO_REGION_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_region_t_get_handlers()
{
    memcpy(&php_cairo_region_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_region_t_handlers.offset = PHP_CAIRO_REGION_T_OFFSET;
    php_cairo_region_t_handlers.dtor_obj = php_cairo_region_t_dtor_object;
    php_cairo_region_t_handlers.free_obj = php_cairo_region_t_free_object;


    php_cairo_region_t_handlers.get_debug_info = php_cairo_region_t_get_debug_info;


    return &php_cairo_region_t_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_region_t_class_init */
zend_class_entry*
php_cairo_region_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_region_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_region_t", php_cairo_region_t_methods);
    php_cairo_region_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_region_t_class_entry->create_object = php_cairo_region_t_create_object;

    return php_cairo_region_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

 /* {{{ cairo_region_t::__construct() */
PHP_METHOD(cairo_region_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_region_t *self = ZOBJ_TO_PHP_CAIRO_REGION_T(zobj);


}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

#if CAIRO_VERSION >= 11000
/* {{{ proto php_cairo_region_t cairo_region_create()
   Allocates a new empty region object. */
PHP_FUNCTION(cairo_region_create)
{


    cairo_region_t *ret = cairo_region_create();
    zend_object *z_ret = php_cairo_region_t_create_object(php_cairo_region_t_class_entry);
    php_cairo_region_t *php_ret = ZOBJ_TO_PHP_CAIRO_REGION_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto php_cairo_region_t cairo_region_create_rectangle(php_cairo_rectangle_int_t rectangle)
   Allocates a new region object containing rectangle . */
PHP_FUNCTION(cairo_region_create_rectangle)
{
    zval *zrectangle;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zrectangle, php_cairo_rectangle_int_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_rectangle_int_t *php_rectangle = ZVAL_IS_PHP_CAIRO_RECTANGLE_INT_T(zrectangle)? ZVAL_GET_PHP_CAIRO_RECTANGLE_INT_T(zrectangle): NULL;
    DECL_PHP_CAIRO_RECTANGLE_INT_T(rectangle);

    cairo_region_t *ret = cairo_region_create_rectangle(rectangle);
    zend_object *z_ret = php_cairo_region_t_create_object(php_cairo_region_t_class_entry);
    php_cairo_region_t *php_ret = ZOBJ_TO_PHP_CAIRO_REGION_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */

static uint32_t
php_cairo_region_create_rectangles_get_rects_array(zend_array *arr, cairo_rectangle_int_t **rectangles){
    uint32_t size = zend_array_count(arr);
    cairo_rectangle_int_t *array = emalloc(sizeof(cairo_rectangle_int_t)*size);
    php_cairo_rectangle_int_t *php_rectangle_int;
    int i=0;
    int j=0;
    zval *value;
    ZEND_HASH_FOREACH_VAL(arr, value) {
        if (Z_TYPE_P(value)==IS_OBJECT) {
            if (instanceof_function(value->value.obj, php_cairo_rectangle_int_t_class_entry)) {
                php_rectangle_int = ZOBJ_TO_PHP_CAIRO_RECTANGLE_INT_T(value->value.obj);
                PHP_CAIRO_RECTANGLE_INT_T_COPY(php_rectangle_int, &array[i]);
                i++;
            } else {
                php_printf("Error type: array[%d] is not glyph\n", j);
            }
        } else {
            php_printf("Error type: array[%d] is not glyph\n", j);
        }
        j++;
    } ZEND_HASH_FOREACH_END();
    *rectangles = array;
    return i;
}


/* {{{ proto php_cairo_region_t cairo_region_create_rectangles(php_cairo_rectangle_int_t rects, int count)
   Allocates a new region object containing the union of all given rects . */
PHP_FUNCTION(cairo_region_create_rectangles)
{
    zval *zrects;
    cairo_rectangle_int_t *rects;
    zend_long count;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ARRAY(zrects);
    ZEND_PARSE_PARAMETERS_END();

    count = php_cairo_region_create_rectangles_get_rects_array(zrects->value.arr, &rects);

    cairo_region_t *ret = cairo_region_create_rectangles(rects, count);
    zend_object *z_ret = php_cairo_region_t_create_object(php_cairo_region_t_class_entry);
    php_cairo_region_t *php_ret = ZOBJ_TO_PHP_CAIRO_REGION_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto php_cairo_region_t cairo_region_copy(php_cairo_region_t original)
   Allocates a new region object copying the area from original . */
PHP_FUNCTION(cairo_region_copy)
{
    zval *zoriginal;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoriginal, php_cairo_region_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_original = ZVAL_IS_PHP_CAIRO_REGION_T(zoriginal)? ZVAL_GET_PHP_CAIRO_REGION_T(zoriginal): NULL;
    DECL_PHP_CAIRO_REGION_T(original);

    cairo_region_t *ret = cairo_region_copy(original);
    zend_object *z_ret = php_cairo_region_t_create_object(php_cairo_region_t_class_entry);
    php_cairo_region_t *php_ret = ZOBJ_TO_PHP_CAIRO_REGION_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto php_cairo_region_t cairo_region_reference(php_cairo_region_t region)
   Increases the reference count on region by one. */
PHP_FUNCTION(cairo_region_reference)
{
    zval *zregion;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zregion, php_cairo_region_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_region = ZVAL_IS_PHP_CAIRO_REGION_T(zregion)? ZVAL_GET_PHP_CAIRO_REGION_T(zregion): NULL;
    DECL_PHP_CAIRO_REGION_T(region);

    cairo_region_t *ret = cairo_region_reference(region);
    zend_object *z_ret = php_cairo_region_t_create_object(php_cairo_region_t_class_entry);
    php_cairo_region_t *php_ret = ZOBJ_TO_PHP_CAIRO_REGION_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto void cairo_region_destroy(php_cairo_region_t region)
   Destroys a cairo_region_t object created with cairo_region_create(), ... */
PHP_FUNCTION(cairo_region_destroy)
{
    zval *zregion;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zregion, php_cairo_region_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_region = ZVAL_IS_PHP_CAIRO_REGION_T(zregion)? ZVAL_GET_PHP_CAIRO_REGION_T(zregion): NULL;
    DECL_PHP_CAIRO_REGION_T(region);

    cairo_region_destroy(region);
    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_region_status(php_cairo_region_t region)
   Checks whether an error has previous occurred for this region object. */
PHP_FUNCTION(cairo_region_status)
{
    zval *zregion;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zregion, php_cairo_region_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_region = ZVAL_IS_PHP_CAIRO_REGION_T(zregion)? ZVAL_GET_PHP_CAIRO_REGION_T(zregion): NULL;
    DECL_PHP_CAIRO_REGION_T(region);

    int ret = cairo_region_status(region);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto void cairo_region_get_extents(php_cairo_region_t region, php_cairo_rectangle_int_t extents)
   Gets the bounding rectangle of region as a cairo_rectangle_int_t */
PHP_FUNCTION(cairo_region_get_extents)
{
    zval *zregion;
    zval *zextents;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zregion, php_cairo_region_t_class_entry, 0, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zextents, php_cairo_rectangle_int_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_region = ZVAL_IS_PHP_CAIRO_REGION_T(zregion)? ZVAL_GET_PHP_CAIRO_REGION_T(zregion): NULL;
    DECL_PHP_CAIRO_REGION_T(region);
    php_cairo_rectangle_int_t *php_extents = ZVAL_IS_PHP_CAIRO_RECTANGLE_INT_T(zextents)? ZVAL_GET_PHP_CAIRO_RECTANGLE_INT_T(zextents): NULL;
    DECL_PHP_CAIRO_RECTANGLE_INT_T(extents);

    cairo_region_get_extents(region, extents);
    PHP_CAIRO_RECTANGLE_INT_T_SET(php_extents, extents);

    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_region_num_rectangles(php_cairo_region_t region)
   Returns the number of rectangles contained in region . */
PHP_FUNCTION(cairo_region_num_rectangles)
{
    zval *zregion;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zregion, php_cairo_region_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_region = ZVAL_IS_PHP_CAIRO_REGION_T(zregion)? ZVAL_GET_PHP_CAIRO_REGION_T(zregion): NULL;
    DECL_PHP_CAIRO_REGION_T(region);

    int ret = cairo_region_num_rectangles(region);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto void cairo_region_get_rectangle(php_cairo_region_t region, int nth, php_cairo_rectangle_int_t rectangle)
   Stores the nth rectangle from the region in rectangle . */
PHP_FUNCTION(cairo_region_get_rectangle)
{
    zval *zregion;
    zend_long nth;
    zval *zrectangle;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zregion, php_cairo_region_t_class_entry, 0, 0);
        Z_PARAM_LONG(nth);
        Z_PARAM_OBJECT_OF_CLASS_EX(zrectangle, php_cairo_rectangle_int_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_region = ZVAL_IS_PHP_CAIRO_REGION_T(zregion)? ZVAL_GET_PHP_CAIRO_REGION_T(zregion): NULL;
    DECL_PHP_CAIRO_REGION_T(region);
    php_cairo_rectangle_int_t *php_rectangle = ZVAL_IS_PHP_CAIRO_RECTANGLE_INT_T(zrectangle)? ZVAL_GET_PHP_CAIRO_RECTANGLE_INT_T(zrectangle): NULL;
    DECL_PHP_CAIRO_RECTANGLE_INT_T(rectangle);

    cairo_region_get_rectangle(region, nth, rectangle);
    PHP_CAIRO_RECTANGLE_INT_T_SET(php_rectangle, rectangle);

    RETURN_NULL();
}/* }}} */
/* {{{ proto cairo_bool_t cairo_region_is_empty(php_cairo_region_t region)
   Checks whether region is empty. */
PHP_FUNCTION(cairo_region_is_empty)
{
    zval *zregion;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zregion, php_cairo_region_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_region = ZVAL_IS_PHP_CAIRO_REGION_T(zregion)? ZVAL_GET_PHP_CAIRO_REGION_T(zregion): NULL;
    DECL_PHP_CAIRO_REGION_T(region);

    cairo_bool_t ret = cairo_region_is_empty(region);

    if (ret) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}/* }}} */
/* {{{ proto cairo_bool_t cairo_region_contains_point(php_cairo_region_t region, int x, int y)
   Checks whether (x , y ) is contained in region . */
PHP_FUNCTION(cairo_region_contains_point)
{
    zval *zregion;
    zend_long x;
    zend_long y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zregion, php_cairo_region_t_class_entry, 0, 0);
        Z_PARAM_LONG(x);
        Z_PARAM_LONG(y);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_region = ZVAL_IS_PHP_CAIRO_REGION_T(zregion)? ZVAL_GET_PHP_CAIRO_REGION_T(zregion): NULL;
    DECL_PHP_CAIRO_REGION_T(region);

    cairo_bool_t ret = cairo_region_contains_point(region, x, y);

    if (ret) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}/* }}} */
/* {{{ proto int cairo_region_contains_rectangle(php_cairo_region_t region, php_cairo_rectangle_int_t rectangle)
   Checks whether rectangle is inside, outside or partially contained in... */
PHP_FUNCTION(cairo_region_contains_rectangle)
{
    zval *zregion;
    zval *zrectangle;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zregion, php_cairo_region_t_class_entry, 0, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zrectangle, php_cairo_rectangle_int_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_region = ZVAL_IS_PHP_CAIRO_REGION_T(zregion)? ZVAL_GET_PHP_CAIRO_REGION_T(zregion): NULL;
    DECL_PHP_CAIRO_REGION_T(region);
    php_cairo_rectangle_int_t *php_rectangle = ZVAL_IS_PHP_CAIRO_RECTANGLE_INT_T(zrectangle)? ZVAL_GET_PHP_CAIRO_RECTANGLE_INT_T(zrectangle): NULL;
    DECL_PHP_CAIRO_RECTANGLE_INT_T(rectangle);

    int ret = cairo_region_contains_rectangle(region, rectangle);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto cairo_bool_t cairo_region_equal(php_cairo_region_t a, php_cairo_region_t b)
   Compares whether region_a is equivalent to region_b. */
PHP_FUNCTION(cairo_region_equal)
{
    zval *za;
    zval *zb;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(za, php_cairo_region_t_class_entry, 0, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zb, php_cairo_region_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_a = ZVAL_IS_PHP_CAIRO_REGION_T(za)? ZVAL_GET_PHP_CAIRO_REGION_T(za): NULL;
    DECL_PHP_CAIRO_REGION_T(a);
    php_cairo_region_t *php_b = ZVAL_IS_PHP_CAIRO_REGION_T(zb)? ZVAL_GET_PHP_CAIRO_REGION_T(zb): NULL;
    DECL_PHP_CAIRO_REGION_T(b);

    cairo_bool_t ret = cairo_region_equal(a, b);

    if (ret) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}/* }}} */
/* {{{ proto void cairo_region_translate(php_cairo_region_t region, int dx, int dy)
   Translates region by (dx , dy ). */
PHP_FUNCTION(cairo_region_translate)
{
    zval *zregion;
    zend_long dx;
    zend_long dy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zregion, php_cairo_region_t_class_entry, 0, 0);
        Z_PARAM_LONG(dx);
        Z_PARAM_LONG(dy);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_region = ZVAL_IS_PHP_CAIRO_REGION_T(zregion)? ZVAL_GET_PHP_CAIRO_REGION_T(zregion): NULL;
    DECL_PHP_CAIRO_REGION_T(region);

    cairo_region_translate(region, dx, dy);
    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_region_intersect(php_cairo_region_t dst, php_cairo_region_t other)
   Computes the intersection of dst with other and places the result in dst  */
PHP_FUNCTION(cairo_region_intersect)
{
    zval *zdst;
    zval *zother;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdst, php_cairo_region_t_class_entry, 0, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zother, php_cairo_region_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_dst = ZVAL_IS_PHP_CAIRO_REGION_T(zdst)? ZVAL_GET_PHP_CAIRO_REGION_T(zdst): NULL;
    DECL_PHP_CAIRO_REGION_T(dst);
    php_cairo_region_t *php_other = ZVAL_IS_PHP_CAIRO_REGION_T(zother)? ZVAL_GET_PHP_CAIRO_REGION_T(zother): NULL;
    DECL_PHP_CAIRO_REGION_T(other);

    int ret = cairo_region_intersect(dst, other);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto int cairo_region_intersect_rectangle(php_cairo_region_t dst, php_cairo_rectangle_int_t rectangle)
   Computes the intersection of dst with rectangle and places the result... */
PHP_FUNCTION(cairo_region_intersect_rectangle)
{
    zval *zdst;
    zval *zrectangle;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdst, php_cairo_region_t_class_entry, 0, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zrectangle, php_cairo_rectangle_int_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_dst = ZVAL_IS_PHP_CAIRO_REGION_T(zdst)? ZVAL_GET_PHP_CAIRO_REGION_T(zdst): NULL;
    DECL_PHP_CAIRO_REGION_T(dst);
    php_cairo_rectangle_int_t *php_rectangle = ZVAL_IS_PHP_CAIRO_RECTANGLE_INT_T(zrectangle)? ZVAL_GET_PHP_CAIRO_RECTANGLE_INT_T(zrectangle): NULL;
    DECL_PHP_CAIRO_RECTANGLE_INT_T(rectangle);

    int ret = cairo_region_intersect_rectangle(dst, rectangle);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto int cairo_region_subtract(php_cairo_region_t dst, php_cairo_region_t other)
   Subtracts other from dst and places the result in dst  */
PHP_FUNCTION(cairo_region_subtract)
{
    zval *zdst;
    zval *zother;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdst, php_cairo_region_t_class_entry, 0, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zother, php_cairo_region_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_dst = ZVAL_IS_PHP_CAIRO_REGION_T(zdst)? ZVAL_GET_PHP_CAIRO_REGION_T(zdst): NULL;
    DECL_PHP_CAIRO_REGION_T(dst);
    php_cairo_region_t *php_other = ZVAL_IS_PHP_CAIRO_REGION_T(zother)? ZVAL_GET_PHP_CAIRO_REGION_T(zother): NULL;
    DECL_PHP_CAIRO_REGION_T(other);

    int ret = cairo_region_subtract(dst, other);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto int cairo_region_subtract_rectangle(php_cairo_region_t dst, php_cairo_rectangle_int_t rectangle)
   Subtracts rectangle from dst and places the result in dst  */
PHP_FUNCTION(cairo_region_subtract_rectangle)
{
    zval *zdst;
    zval *zrectangle;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdst, php_cairo_region_t_class_entry, 0, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zrectangle, php_cairo_rectangle_int_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_dst = ZVAL_IS_PHP_CAIRO_REGION_T(zdst)? ZVAL_GET_PHP_CAIRO_REGION_T(zdst): NULL;
    DECL_PHP_CAIRO_REGION_T(dst);
    php_cairo_rectangle_int_t *php_rectangle = ZVAL_IS_PHP_CAIRO_RECTANGLE_INT_T(zrectangle)? ZVAL_GET_PHP_CAIRO_RECTANGLE_INT_T(zrectangle): NULL;
    DECL_PHP_CAIRO_RECTANGLE_INT_T(rectangle);

    int ret = cairo_region_subtract_rectangle(dst, rectangle);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto int cairo_region_union(php_cairo_region_t dst, php_cairo_region_t other)
   Computes the union of dst with other and places the result in dst  */
PHP_FUNCTION(cairo_region_union)
{
    zval *zdst;
    zval *zother;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdst, php_cairo_region_t_class_entry, 0, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zother, php_cairo_region_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_dst = ZVAL_IS_PHP_CAIRO_REGION_T(zdst)? ZVAL_GET_PHP_CAIRO_REGION_T(zdst): NULL;
    DECL_PHP_CAIRO_REGION_T(dst);
    php_cairo_region_t *php_other = ZVAL_IS_PHP_CAIRO_REGION_T(zother)? ZVAL_GET_PHP_CAIRO_REGION_T(zother): NULL;
    DECL_PHP_CAIRO_REGION_T(other);

    int ret = cairo_region_union(dst, other);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto int cairo_region_union_rectangle(php_cairo_region_t dst, php_cairo_rectangle_int_t rectangle)
   Computes the union of dst with rectangle and places the result in dst . */
PHP_FUNCTION(cairo_region_union_rectangle)
{
    zval *zdst;
    zval *zrectangle;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdst, php_cairo_region_t_class_entry, 0, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zrectangle, php_cairo_rectangle_int_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_dst = ZVAL_IS_PHP_CAIRO_REGION_T(zdst)? ZVAL_GET_PHP_CAIRO_REGION_T(zdst): NULL;
    DECL_PHP_CAIRO_REGION_T(dst);
    php_cairo_rectangle_int_t *php_rectangle = ZVAL_IS_PHP_CAIRO_RECTANGLE_INT_T(zrectangle)? ZVAL_GET_PHP_CAIRO_RECTANGLE_INT_T(zrectangle): NULL;
    DECL_PHP_CAIRO_RECTANGLE_INT_T(rectangle);

    int ret = cairo_region_union_rectangle(dst, rectangle);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto int cairo_region_xor(php_cairo_region_t dst, php_cairo_region_t other)
   Computes the exclusive difference of dst with other and places the re... */
PHP_FUNCTION(cairo_region_xor)
{
    zval *zdst;
    zval *zother;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdst, php_cairo_region_t_class_entry, 0, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zother, php_cairo_region_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_dst = ZVAL_IS_PHP_CAIRO_REGION_T(zdst)? ZVAL_GET_PHP_CAIRO_REGION_T(zdst): NULL;
    DECL_PHP_CAIRO_REGION_T(dst);
    php_cairo_region_t *php_other = ZVAL_IS_PHP_CAIRO_REGION_T(zother)? ZVAL_GET_PHP_CAIRO_REGION_T(zother): NULL;
    DECL_PHP_CAIRO_REGION_T(other);

    int ret = cairo_region_xor(dst, other);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto int cairo_region_xor_rectangle(php_cairo_region_t dst, php_cairo_rectangle_int_t rectangle)
   Computes the exclusive difference of dst with rectangle and places th... */
PHP_FUNCTION(cairo_region_xor_rectangle)
{
    zval *zdst;
    zval *zrectangle;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdst, php_cairo_region_t_class_entry, 0, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zrectangle, php_cairo_rectangle_int_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_region_t *php_dst = ZVAL_IS_PHP_CAIRO_REGION_T(zdst)? ZVAL_GET_PHP_CAIRO_REGION_T(zdst): NULL;
    DECL_PHP_CAIRO_REGION_T(dst);
    php_cairo_rectangle_int_t *php_rectangle = ZVAL_IS_PHP_CAIRO_RECTANGLE_INT_T(zrectangle)? ZVAL_GET_PHP_CAIRO_RECTANGLE_INT_T(zrectangle): NULL;
    DECL_PHP_CAIRO_RECTANGLE_INT_T(rectangle);

    int ret = cairo_region_xor_rectangle(dst, rectangle);

    RETURN_LONG(ret);
}/* }}} */
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
