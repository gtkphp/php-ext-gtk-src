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
#include "php_cairo/font-type.h"

#include "php_cairo/font-face.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_font_face_t_class_entry;// struct
zend_object_handlers  php_cairo_font_face_t_handlers;







/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_font_face_t_methods[] = {
    PHP_ME(cairo_font_face_t, __construct, arginfo_cairo_font_face_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_font_face_t_create_object */
static zend_object*
php_cairo_font_face_t_create_object(zend_class_entry *class_type)
{
    php_cairo_font_face_t *intern = zend_object_alloc(sizeof(php_cairo_font_face_t), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_cairo_font_face_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_font_face_t_create_object */


static void
php_cairo_font_face_t_dtor_object(zend_object *obj) {
    //php_cairo_font_face_t *intern = ZOBJ_TO_PHP_CAIRO_FONT_FACE_T(obj);

}

/* {{{ php_cairo_font_face_t_free_object */
static void
php_cairo_font_face_t_free_object(zend_object *object)
{
    php_cairo_font_face_t *intern = ZOBJ_TO_PHP_CAIRO_FONT_FACE_T(object);

    if (intern->ptr) {
        intern->ptr = NULL;
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_font_face_t_free_object */





/* {{{ php_cairo_font_face_t_get_debug_info */
static HashTable*
php_cairo_font_face_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_font_face_t  *intern = ZOBJ_TO_PHP_CAIRO_FONT_FACE_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_font_face_t_get_handlers()
{
    memcpy(&php_cairo_font_face_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_font_face_t_handlers.offset = PHP_CAIRO_FONT_FACE_T_OFFSET;
    php_cairo_font_face_t_handlers.dtor_obj = php_cairo_font_face_t_dtor_object;
    php_cairo_font_face_t_handlers.free_obj = php_cairo_font_face_t_free_object;


    php_cairo_font_face_t_handlers.get_debug_info = php_cairo_font_face_t_get_debug_info;


    return &php_cairo_font_face_t_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_font_face_t_class_init */
zend_class_entry*
php_cairo_font_face_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_font_face_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_font_face_t", php_cairo_font_face_t_methods);
    php_cairo_font_face_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_font_face_t_class_entry->create_object = php_cairo_font_face_t_create_object;

    return php_cairo_font_face_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
php_cairo_font_face_t*
php_cairo_font_face_t_new() {
    zend_object *zobj = php_cairo_font_face_t_create_object(php_cairo_font_face_t_class_entry);
    return ZOBJ_TO_PHP_CAIRO_FONT_FACE_T(zobj);
}

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

 /* {{{ cairo_font_face_t::__construct() */
PHP_METHOD(cairo_font_face_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_font_face_t *self = ZOBJ_TO_PHP_CAIRO_FONT_FACE_T(zobj);


}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

#if CAIRO_VERSION >= 10000
/* {{{ proto int cairo_font_face_status(php_cairo_font_face_t font_face)
   Checks whether an error has previously occurred for this font face */
PHP_FUNCTION(cairo_font_face_status)
{
    zval *zfont_face;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zfont_face, php_cairo_font_face_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_face_t *php_font_face = ZVAL_IS_PHP_CAIRO_FONT_FACE_T(zfont_face)? ZVAL_GET_PHP_CAIRO_FONT_FACE_T(zfont_face): NULL;
    DECL_PHP_CAIRO_FONT_FACE_T(font_face);

    int ret = cairo_font_face_status(font_face);

    RETURN_LONG(ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10200
/* {{{ proto int cairo_font_face_get_type(php_cairo_font_face_t font_face)
   This function returns the type of the backend used to create a font f... */
PHP_FUNCTION(cairo_font_face_get_type)
{
    zval *zfont_face;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zfont_face, php_cairo_font_face_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_face_t *php_font_face = ZVAL_IS_PHP_CAIRO_FONT_FACE_T(zfont_face)? ZVAL_GET_PHP_CAIRO_FONT_FACE_T(zfont_face): NULL;
    DECL_PHP_CAIRO_FONT_FACE_T(font_face);

    int ret = cairo_font_face_get_type(font_face);

    RETURN_LONG(ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10400
/* {{{ proto int cairo_font_face_get_reference_count(php_cairo_font_face_t font_face)
   Returns the current reference count of font_face . */
PHP_FUNCTION(cairo_font_face_get_reference_count)
{
    zval *zfont_face;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zfont_face, php_cairo_font_face_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_face_t *php_font_face = ZVAL_IS_PHP_CAIRO_FONT_FACE_T(zfont_face)? ZVAL_GET_PHP_CAIRO_FONT_FACE_T(zfont_face): NULL;
    DECL_PHP_CAIRO_FONT_FACE_T(font_face);

    int ret = cairo_font_face_get_reference_count(font_face);

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
