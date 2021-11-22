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
#include "php_cairo/status.h"
#include "php_cairo/antialias.h"
#include "php_cairo/subpixel-order.h"
#include "php_cairo/hint-style.h"
#include "php_cairo/hint-metrics.h"

#include "php_cairo/font-options.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_font_options_t_class_entry;// struct
zend_object_handlers  php_cairo_font_options_t_handlers;







/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_font_options_t_methods[] = {
    PHP_ME(cairo_font_options_t, __construct, arginfo_cairo_font_options_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_font_options_t_create_object */
static zend_object*
php_cairo_font_options_t_create_object(zend_class_entry *class_type)
{
    php_cairo_font_options_t *intern = zend_object_alloc(sizeof(php_cairo_font_options_t), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_cairo_font_options_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_font_options_t_create_object */


static void
php_cairo_font_options_t_dtor_object(zend_object *obj) {
    //php_cairo_font_options_t *intern = ZOBJ_TO_PHP_CAIRO_FONT_OPTIONS_T(obj);

}

/* {{{ php_cairo_font_options_t_free_object */
static void
php_cairo_font_options_t_free_object(zend_object *object)
{
    php_cairo_font_options_t *intern = ZOBJ_TO_PHP_CAIRO_FONT_OPTIONS_T(object);

    if (intern->ptr) {
        cairo_font_options_destroy(intern->ptr);
        intern->ptr = NULL;
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_font_options_t_free_object */





/* {{{ php_cairo_font_options_t_get_debug_info */
static HashTable*
php_cairo_font_options_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_font_options_t  *intern = ZOBJ_TO_PHP_CAIRO_FONT_OPTIONS_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_font_options_t_get_handlers()
{
    memcpy(&php_cairo_font_options_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_font_options_t_handlers.offset = PHP_CAIRO_FONT_OPTIONS_T_OFFSET;
    php_cairo_font_options_t_handlers.dtor_obj = php_cairo_font_options_t_dtor_object;
    php_cairo_font_options_t_handlers.free_obj = php_cairo_font_options_t_free_object;


    php_cairo_font_options_t_handlers.get_debug_info = php_cairo_font_options_t_get_debug_info;


    return &php_cairo_font_options_t_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_font_options_t_class_init */
zend_class_entry*
php_cairo_font_options_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_font_options_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_font_options_t", php_cairo_font_options_t_methods);
    php_cairo_font_options_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_font_options_t_class_entry->create_object = php_cairo_font_options_t_create_object;

    return php_cairo_font_options_t_class_entry;
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

 /* {{{ cairo_font_options_t::__construct() */
PHP_METHOD(cairo_font_options_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_font_options_t *self = ZOBJ_TO_PHP_CAIRO_FONT_OPTIONS_T(zobj);


}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

#if CAIRO_VERSION >= 10000
/* {{{ proto php_cairo_font_options_t cairo_font_options_create()
   Allocates a new font options object with all options initialized to d... */
PHP_FUNCTION(cairo_font_options_create)
{


    cairo_font_options_t *ret = cairo_font_options_create();
    zend_object *z_ret = php_cairo_font_options_t_create_object(php_cairo_font_options_t_class_entry);
    php_cairo_font_options_t *php_ret = ZOBJ_TO_PHP_CAIRO_FONT_OPTIONS_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto php_cairo_font_options_t cairo_font_options_copy(php_cairo_font_options_t original)
   Allocates a new font options object copying the option values from or... */
PHP_FUNCTION(cairo_font_options_copy)
{
    zval *zoriginal;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoriginal, php_cairo_font_options_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_original = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoriginal)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoriginal): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(original);

    cairo_font_options_t *ret = cairo_font_options_copy(original);
    zend_object *z_ret = php_cairo_font_options_t_create_object(php_cairo_font_options_t_class_entry);
    php_cairo_font_options_t *php_ret = ZOBJ_TO_PHP_CAIRO_FONT_OPTIONS_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto void cairo_font_options_destroy(php_cairo_font_options_t options)
   Destroys a cairo_font_options_t object created with cairo_font_option... */
PHP_FUNCTION(cairo_font_options_destroy)
{
    zval *zoptions;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);

    cairo_font_options_destroy(options);
    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_font_options_status(php_cairo_font_options_t options)
   Checks whether an error has previously occurred for this font options... */
PHP_FUNCTION(cairo_font_options_status)
{
    zval *zoptions;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);

    int ret = cairo_font_options_status(options);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto void cairo_font_options_merge(php_cairo_font_options_t options, php_cairo_font_options_t other)
   Merges non-default options from other into options , replacing existi... */
PHP_FUNCTION(cairo_font_options_merge)
{
    zval *zoptions;
    zval *zother;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zother, php_cairo_font_options_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);
    php_cairo_font_options_t *php_other = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zother)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zother): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(other);

    cairo_font_options_merge(options, other);
    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_font_options_hash(php_cairo_font_options_t options)
   Compute a hash for the font options object; this value will be useful... */
PHP_FUNCTION(cairo_font_options_hash)
{
    zval *zoptions;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);

    int ret = cairo_font_options_hash(options);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto cairo_bool_t cairo_font_options_equal(php_cairo_font_options_t options, php_cairo_font_options_t other)
   Compares two font options objects for equality. */
PHP_FUNCTION(cairo_font_options_equal)
{
    zval *zoptions;
    zval *zother;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zother, php_cairo_font_options_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);
    php_cairo_font_options_t *php_other = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zother)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zother): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(other);

    cairo_bool_t ret = cairo_font_options_equal(options, other);

    if (ret) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}/* }}} */
/* {{{ proto void cairo_font_options_set_antialias(php_cairo_font_options_t options, int antialias)
   Sets the antialiasing mode for the font options object. */
PHP_FUNCTION(cairo_font_options_set_antialias)
{
    zval *zoptions;
    zend_long zantialias;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
        Z_PARAM_LONG(zantialias);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);
    cairo_antialias_t antialias = zantialias;

    cairo_font_options_set_antialias(options, antialias);
    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_font_options_get_antialias(php_cairo_font_options_t options)
   Gets the antialiasing mode for the font options object. */
PHP_FUNCTION(cairo_font_options_get_antialias)
{
    zval *zoptions;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);

    int ret = cairo_font_options_get_antialias(options);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto void cairo_font_options_set_subpixel_order(php_cairo_font_options_t options, int subpixel_order)
   Sets the subpixel order for the font options object. */
PHP_FUNCTION(cairo_font_options_set_subpixel_order)
{
    zval *zoptions;
    zend_long zsubpixel_order;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
        Z_PARAM_LONG(zsubpixel_order);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);
    cairo_subpixel_order_t subpixel_order = zsubpixel_order;

    cairo_font_options_set_subpixel_order(options, subpixel_order);
    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_font_options_get_subpixel_order(php_cairo_font_options_t options)
   Gets the subpixel order for the font options object. */
PHP_FUNCTION(cairo_font_options_get_subpixel_order)
{
    zval *zoptions;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);

    int ret = cairo_font_options_get_subpixel_order(options);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto void cairo_font_options_set_hint_style(php_cairo_font_options_t options, int hint_style)
   Sets the hint style for font outlines for the font options object. */
PHP_FUNCTION(cairo_font_options_set_hint_style)
{
    zval *zoptions;
    zend_long zhint_style;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
        Z_PARAM_LONG(zhint_style);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);
    cairo_hint_style_t hint_style = zhint_style;

    cairo_font_options_set_hint_style(options, hint_style);
    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_font_options_get_hint_style(php_cairo_font_options_t options)
   Gets the hint style for font outlines for the font options object. */
PHP_FUNCTION(cairo_font_options_get_hint_style)
{
    zval *zoptions;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);

    int ret = cairo_font_options_get_hint_style(options);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto void cairo_font_options_set_hint_metrics(php_cairo_font_options_t options, int hint_metrics)
   Sets the metrics hinting mode for the font options object. */
PHP_FUNCTION(cairo_font_options_set_hint_metrics)
{
    zval *zoptions;
    zend_long zhint_metrics;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
        Z_PARAM_LONG(zhint_metrics);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);
    cairo_hint_metrics_t hint_metrics = zhint_metrics;

    cairo_font_options_set_hint_metrics(options, hint_metrics);
    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_font_options_get_hint_metrics(php_cairo_font_options_t options)
   Gets the metrics hinting mode for the font options object. */
PHP_FUNCTION(cairo_font_options_get_hint_metrics)
{
    zval *zoptions;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);

    int ret = cairo_font_options_get_hint_metrics(options);

    RETURN_LONG(ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 11600
/* {{{ proto char cairo_font_options_get_variations(php_cairo_font_options_t options)
   Gets the OpenType font variations for the font options object. */
PHP_FUNCTION(cairo_font_options_get_variations)
{
    zval *zoptions;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);

    const char *ret = cairo_font_options_get_variations(options);

    RETURN_STR(z_ret);
}/* }}} */
/* {{{ proto void cairo_font_options_set_variations(php_cairo_font_options_t options, char variations)
   Sets the OpenType font variations for the font options object. */
PHP_FUNCTION(cairo_font_options_set_variations)
{
    zval *zoptions;
    char *variations;
    size_t variations_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
        Z_PARAM_STRING(variations, variations_len);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);

    cairo_font_options_set_variations(options, variations);
    RETURN_NULL();
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
