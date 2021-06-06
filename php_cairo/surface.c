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
/*
#include "php_cairo/content.h"
#include "php_cairo/format.h"*/
#include "php_cairo/status.h"
/*#include "php_cairo/device.h"
#include "php_cairo/font-options.h"
#include "php_cairo/surface-type.h"

#include "php_cairo/rectangle-int.h"
*/
#include "php_cairo/surface.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_surface_t_class_entry;// struct
zend_object_handlers  php_cairo_surface_t_handlers;







/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_surface_t_methods[] = {
    PHP_ME(cairo_surface_t, __construct, arginfo_cairo_surface_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_surface_t_create_object */
static zend_object*
php_cairo_surface_t_create_object(zend_class_entry *class_type)
{
    php_cairo_surface_t *intern = zend_object_alloc(sizeof(php_cairo_surface_t), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_cairo_surface_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_surface_t_create_object */

php_cairo_surface_t*
php_cairo_surface_t_new()
{
    zend_object *z_surface = php_cairo_surface_t_create_object(php_cairo_surface_t_class_entry);
    php_cairo_surface_t *php_surface = ZOBJ_TO_PHP_CAIRO_SURFACE_T(z_surface);
    return php_surface;
}


static void
php_cairo_surface_t_dtor_object(zend_object *obj) {
    //php_cairo_surface_t *intern = ZOBJ_TO_PHP_CAIRO_SURFACE_T(obj);

}

/* {{{ php_cairo_surface_t_free_object */
static void
php_cairo_surface_t_free_object(zend_object *object)
{
    php_cairo_surface_t *intern = ZOBJ_TO_PHP_CAIRO_SURFACE_T(object);

    if (intern->ptr) {
        cairo_surface_destroy(intern->ptr);
        intern->ptr = NULL;
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_surface_t_free_object */





/* {{{ php_cairo_surface_t_get_debug_info */
static HashTable*
php_cairo_surface_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_surface_t  *intern = ZOBJ_TO_PHP_CAIRO_SURFACE_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_surface_t_get_handlers()
{
    memcpy(&php_cairo_surface_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_surface_t_handlers.offset = PHP_CAIRO_SURFACE_T_OFFSET;
    php_cairo_surface_t_handlers.dtor_obj = php_cairo_surface_t_dtor_object;
    php_cairo_surface_t_handlers.free_obj = php_cairo_surface_t_free_object;


    php_cairo_surface_t_handlers.get_debug_info = php_cairo_surface_t_get_debug_info;


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
    php_cairo_surface_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_surface_t_class_entry->create_object = php_cairo_surface_t_create_object;

    return php_cairo_surface_t_class_entry;
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

 /* {{{ cairo_surface_t::__construct() */
PHP_METHOD(cairo_surface_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_surface_t *self = ZOBJ_TO_PHP_CAIRO_SURFACE_T(zobj);


}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
