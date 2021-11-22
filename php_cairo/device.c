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
#include "php_cairo/device-type.h"


#include "php_cairo/device.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_device_t_class_entry;// struct
zend_object_handlers  php_cairo_device_t_handlers;







/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_device_t_methods[] = {
    PHP_ME(cairo_device_t, __construct, arginfo_cairo_device_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_device_t_create_object */
static zend_object*
php_cairo_device_t_create_object(zend_class_entry *class_type)
{
    php_cairo_device_t *intern = zend_object_alloc(sizeof(php_cairo_device_t), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_cairo_device_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_device_t_create_object */


static void
php_cairo_device_t_dtor_object(zend_object *obj) {
    //php_cairo_device_t *intern = ZOBJ_TO_PHP_CAIRO_DEVICE_T(obj);

}

/* {{{ php_cairo_device_t_free_object */
static void
php_cairo_device_t_free_object(zend_object *object)
{
    php_cairo_device_t *intern = ZOBJ_TO_PHP_CAIRO_DEVICE_T(object);

    if (intern->ptr) {
        intern->ptr = NULL;
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_device_t_free_object */





/* {{{ php_cairo_device_t_get_debug_info */
static HashTable*
php_cairo_device_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_device_t  *intern = ZOBJ_TO_PHP_CAIRO_DEVICE_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_device_t_get_handlers()
{
    memcpy(&php_cairo_device_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_device_t_handlers.offset = PHP_CAIRO_DEVICE_T_OFFSET;
    php_cairo_device_t_handlers.dtor_obj = php_cairo_device_t_dtor_object;
    php_cairo_device_t_handlers.free_obj = php_cairo_device_t_free_object;


    php_cairo_device_t_handlers.get_debug_info = php_cairo_device_t_get_debug_info;


    return &php_cairo_device_t_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_device_t_class_init */
zend_class_entry*
php_cairo_device_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_device_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_device_t", php_cairo_device_t_methods);
    php_cairo_device_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_device_t_class_entry->create_object = php_cairo_device_t_create_object;

    return php_cairo_device_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
php_cairo_device_t*
php_cairo_device_t_new() {
    zend_object *z_device = php_cairo_device_t_create_object(php_cairo_device_t_class_entry);
    return ZOBJ_TO_PHP_CAIRO_DEVICE_T(z_device);
}

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

 /* {{{ cairo_device_t::__construct() */
PHP_METHOD(cairo_device_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_device_t *self = ZOBJ_TO_PHP_CAIRO_DEVICE_T(zobj);


}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

#if CAIRO_VERSION >= 11000
/* {{{ proto php_cairo_device_t cairo_device_reference(php_cairo_device_t device)
   Increases the reference count on device by one. */
PHP_FUNCTION(cairo_device_reference)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    cairo_device_t *ret = cairo_device_reference(device);
    zend_object *z_ret = php_cairo_device_t_create_object(php_cairo_device_t_class_entry);
    php_cairo_device_t *php_ret = ZOBJ_TO_PHP_CAIRO_DEVICE_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto void cairo_device_destroy(php_cairo_device_t device)
   Decreases the reference count on device by one. */
PHP_FUNCTION(cairo_device_destroy)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    cairo_device_destroy(device);
    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_device_status(php_cairo_device_t device)
   Checks whether an error has previously occurred for this device. */
PHP_FUNCTION(cairo_device_status)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    int ret = cairo_device_status(device);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto void cairo_device_finish(php_cairo_device_t device)
   This function finishes the device and drops all references to externa... */
PHP_FUNCTION(cairo_device_finish)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    cairo_device_finish(device);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_device_flush(php_cairo_device_t device)
   Finish any pending operations for the device and also restore any tem... */
PHP_FUNCTION(cairo_device_flush)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    cairo_device_flush(device);
    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_device_get_type(php_cairo_device_t device)
   This function returns the type of the device. */
PHP_FUNCTION(cairo_device_get_type)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    int ret = cairo_device_get_type(device);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto int cairo_device_get_reference_count(php_cairo_device_t device)
   Returns the current reference count of device . */
PHP_FUNCTION(cairo_device_get_reference_count)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    int ret = cairo_device_get_reference_count(device);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto int cairo_device_acquire(php_cairo_device_t device)
   Acquires the device for the current thread. */
PHP_FUNCTION(cairo_device_acquire)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    int ret = cairo_device_acquire(device);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto void cairo_device_release(php_cairo_device_t device)
   Releases a device previously acquired using cairo_device_acquire(). */
PHP_FUNCTION(cairo_device_release)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    cairo_device_release(device);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 11200
/* {{{ proto double cairo_device_observer_elapsed(php_cairo_device_t device)
   TODO: Undocumented. */
PHP_FUNCTION(cairo_device_observer_elapsed)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    double ret = cairo_device_observer_elapsed(device);

    RETURN_DOUBLE(ret);
}/* }}} */
/* {{{ proto double cairo_device_observer_fill_elapsed(php_cairo_device_t device)
   TODO: Undocumented. */
PHP_FUNCTION(cairo_device_observer_fill_elapsed)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    double ret = cairo_device_observer_fill_elapsed(device);

    RETURN_DOUBLE(ret);
}/* }}} */
/* {{{ proto double cairo_device_observer_glyphs_elapsed(php_cairo_device_t device)
   TODO: Undocumented. */
PHP_FUNCTION(cairo_device_observer_glyphs_elapsed)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    double ret = cairo_device_observer_glyphs_elapsed(device);

    RETURN_DOUBLE(ret);
}/* }}} */
/* {{{ proto double cairo_device_observer_mask_elapsed(php_cairo_device_t device)
   TODO: Undocumented. */
PHP_FUNCTION(cairo_device_observer_mask_elapsed)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    double ret = cairo_device_observer_mask_elapsed(device);

    RETURN_DOUBLE(ret);
}/* }}} */
/* {{{ proto double cairo_device_observer_paint_elapsed(php_cairo_device_t device)
   TODO: Undocumented. */
PHP_FUNCTION(cairo_device_observer_paint_elapsed)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    double ret = cairo_device_observer_paint_elapsed(device);

    RETURN_DOUBLE(ret);
}/* }}} */
/* {{{ proto double cairo_device_observer_stroke_elapsed(php_cairo_device_t device)
   TODO: Undocumented. */
PHP_FUNCTION(cairo_device_observer_stroke_elapsed)
{
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_cairo_device_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_device_t *php_device = ZVAL_IS_PHP_CAIRO_DEVICE_T(zdevice)? ZVAL_GET_PHP_CAIRO_DEVICE_T(zdevice): NULL;
    DECL_PHP_CAIRO_DEVICE_T(device);

    double ret = cairo_device_observer_stroke_elapsed(device);

    RETURN_DOUBLE(ret);
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
