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
#include "php_cairo/font-face.h"
#include "php_cairo/matrix.h"
#include "php_cairo/font-options.h"
#include "php_cairo/status.h"
#include "php_cairo/font-extents.h"
#include "php_cairo/text-extents.h"
#include "php_cairo/glyph.h"
#include "php_cairo/text-cluster.h"
#include "php_cairo/text-cluster-flags.h"
#include "php_cairo/font-type.h"

#include "php_cairo/scaled-font.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_scaled_font_t_class_entry;// struct
zend_object_handlers  php_cairo_scaled_font_t_handlers;







/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_scaled_font_t_methods[] = {
    PHP_ME(cairo_scaled_font_t, __construct, arginfo_cairo_scaled_font_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_scaled_font_t_create_object */
static zend_object*
php_cairo_scaled_font_t_create_object(zend_class_entry *class_type)
{
    php_cairo_scaled_font_t *intern = zend_object_alloc(sizeof(php_cairo_scaled_font_t), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_cairo_scaled_font_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_scaled_font_t_create_object */


static void
php_cairo_scaled_font_t_dtor_object(zend_object *obj) {
    //php_cairo_scaled_font_t *intern = ZOBJ_TO_PHP_CAIRO_SCALED_FONT_T(obj);

}

/* {{{ php_cairo_scaled_font_t_free_object */
static void
php_cairo_scaled_font_t_free_object(zend_object *object)
{
    php_cairo_scaled_font_t *intern = ZOBJ_TO_PHP_CAIRO_SCALED_FONT_T(object);

    if (intern->ptr) {
        intern->ptr = NULL;
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_scaled_font_t_free_object */





/* {{{ php_cairo_scaled_font_t_get_debug_info */
static HashTable*
php_cairo_scaled_font_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_scaled_font_t  *intern = ZOBJ_TO_PHP_CAIRO_SCALED_FONT_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_scaled_font_t_get_handlers()
{
    memcpy(&php_cairo_scaled_font_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_scaled_font_t_handlers.offset = PHP_CAIRO_SCALED_FONT_T_OFFSET;
    php_cairo_scaled_font_t_handlers.dtor_obj = php_cairo_scaled_font_t_dtor_object;
    php_cairo_scaled_font_t_handlers.free_obj = php_cairo_scaled_font_t_free_object;


    php_cairo_scaled_font_t_handlers.get_debug_info = php_cairo_scaled_font_t_get_debug_info;


    return &php_cairo_scaled_font_t_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_scaled_font_t_class_init */
zend_class_entry*
php_cairo_scaled_font_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_scaled_font_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_scaled_font_t", php_cairo_scaled_font_t_methods);
    php_cairo_scaled_font_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_scaled_font_t_class_entry->create_object = php_cairo_scaled_font_t_create_object;

    return php_cairo_scaled_font_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
php_cairo_scaled_font_t*
php_cairo_scaled_font_t_new() {
    zend_object *zobj = php_cairo_scaled_font_t_create_object(php_cairo_scaled_font_t_class_entry);
    return ZOBJ_TO_PHP_CAIRO_SCALED_FONT_T(zobj);
}

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

 /* {{{ cairo_scaled_font_t::__construct() */
PHP_METHOD(cairo_scaled_font_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_scaled_font_t *self = ZOBJ_TO_PHP_CAIRO_SCALED_FONT_T(zobj);


}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

#if CAIRO_VERSION >= 10000
/* {{{ proto php_cairo_scaled_font_t cairo_scaled_font_create(php_cairo_font_face_t font_face, php_cairo_matrix_t font_matrix, php_cairo_matrix_t ctm, php_cairo_font_options_t options)
   Creates a cairo_scaled_font_t object from a font face and matrices th... */
PHP_FUNCTION(cairo_scaled_font_create)
{
    zval *zfont_face;
    zval *zfont_matrix;
    zval *zctm;
    zval *zoptions;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zfont_face, php_cairo_font_face_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zfont_matrix, php_cairo_matrix_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zctm, php_cairo_matrix_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_font_face_t *php_font_face = ZVAL_IS_PHP_CAIRO_FONT_FACE_T(zfont_face)? ZVAL_GET_PHP_CAIRO_FONT_FACE_T(zfont_face): NULL;
    DECL_PHP_CAIRO_FONT_FACE_T(font_face);
    php_cairo_matrix_t *php_font_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zfont_matrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zfont_matrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(font_matrix);
    php_cairo_matrix_t *php_ctm = ZVAL_IS_PHP_CAIRO_MATRIX_T(zctm)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zctm): NULL;
    DECL_PHP_CAIRO_MATRIX_T(ctm);
    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);

    cairo_scaled_font_t *ret = cairo_scaled_font_create(font_face, font_matrix, ctm, options);
    zend_object *z_ret = php_cairo_scaled_font_t_create_object(php_cairo_scaled_font_t_class_entry);
    php_cairo_scaled_font_t *php_ret = ZOBJ_TO_PHP_CAIRO_SCALED_FONT_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto php_cairo_scaled_font_t cairo_scaled_font_reference(php_cairo_scaled_font_t scaled_font)
   Increases the reference count on scaled_font by one. */
PHP_FUNCTION(cairo_scaled_font_reference)
{
    zval *zscaled_font;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);

    cairo_scaled_font_t *ret = cairo_scaled_font_reference(scaled_font);
    zend_object *z_ret = php_cairo_scaled_font_t_create_object(php_cairo_scaled_font_t_class_entry);
    php_cairo_scaled_font_t *php_ret = ZOBJ_TO_PHP_CAIRO_SCALED_FONT_T(z_ret);
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto void cairo_scaled_font_destroy(php_cairo_scaled_font_t scaled_font)
   Decreases the reference count on font by one. */
PHP_FUNCTION(cairo_scaled_font_destroy)
{
    zval *zscaled_font;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);

    cairo_scaled_font_destroy(scaled_font);
    RETURN_NULL();
}/* }}} */
/* {{{ proto int cairo_scaled_font_status(php_cairo_scaled_font_t scaled_font)
   Checks whether an error has previously occurred for this scaled_font. */
PHP_FUNCTION(cairo_scaled_font_status)
{
    zval *zscaled_font;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);

    int ret = cairo_scaled_font_status(scaled_font);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto void cairo_scaled_font_extents(php_cairo_scaled_font_t scaled_font, php_cairo_font_extents_t extents)
   Gets the metrics for a cairo_scaled_font_t. */
PHP_FUNCTION(cairo_scaled_font_extents)
{
    zval *zscaled_font;
    zval *zextents;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zextents, php_cairo_font_extents_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);
    php_cairo_font_extents_t *php_extents = ZVAL_IS_PHP_CAIRO_FONT_EXTENTS_T(zextents)? ZVAL_GET_PHP_CAIRO_FONT_EXTENTS_T(zextents): NULL;
    DECL_PHP_CAIRO_FONT_EXTENTS_T(extents);

    cairo_scaled_font_extents(scaled_font, extents);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10200
/* {{{ proto void cairo_scaled_font_text_extents(php_cairo_scaled_font_t scaled_font, char utf8, php_cairo_text_extents_t extents)
   Gets the extents for a string of text. */
PHP_FUNCTION(cairo_scaled_font_text_extents)
{
    zval *zscaled_font;
    char *utf8;
    size_t utf8_len;
    zval *zextents;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
        Z_PARAM_STRING(utf8, utf8_len);
        Z_PARAM_OBJECT_OF_CLASS_EX(zextents, php_cairo_text_extents_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);
    php_cairo_text_extents_t *php_extents = ZVAL_IS_PHP_CAIRO_TEXT_EXTENTS_T(zextents)? ZVAL_GET_PHP_CAIRO_TEXT_EXTENTS_T(zextents): NULL;
    DECL_PHP_CAIRO_TEXT_EXTENTS_T(extents);

    cairo_scaled_font_text_extents(scaled_font, utf8, extents);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10000
/* {{{ proto void cairo_scaled_font_glyph_extents(php_cairo_scaled_font_t scaled_font, php_cairo_glyph_t glyphs, int num_glyphs, php_cairo_text_extents_t extents)
   Gets the extents for an array of glyphs. */
PHP_FUNCTION(cairo_scaled_font_glyph_extents)
{
    zval *zscaled_font;
    zval *zglyphs;
    zend_long num_glyphs;
    zval *zextents;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zglyphs, php_cairo_glyph_t_class_entry, 1, 0);
        Z_PARAM_LONG(num_glyphs);
        Z_PARAM_OBJECT_OF_CLASS_EX(zextents, php_cairo_text_extents_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);
    php_cairo_glyph_t *php_glyphs = ZVAL_IS_PHP_CAIRO_GLYPH_T(zglyphs)? ZVAL_GET_PHP_CAIRO_GLYPH_T(zglyphs): NULL;
    DECL_PHP_CAIRO_GLYPH_T(glyphs);
    php_cairo_text_extents_t *php_extents = ZVAL_IS_PHP_CAIRO_TEXT_EXTENTS_T(zextents)? ZVAL_GET_PHP_CAIRO_TEXT_EXTENTS_T(zextents): NULL;
    DECL_PHP_CAIRO_TEXT_EXTENTS_T(extents);

    cairo_scaled_font_glyph_extents(scaled_font, glyphs, num_glyphs, extents);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10800
/* {{{ proto int cairo_scaled_font_text_to_glyphs(php_cairo_scaled_font_t scaled_font, double x, double y, char utf8, int utf8_len, php_cairo_glyph_t glyphs, int num_glyphs, php_cairo_text_cluster_t clusters, int num_clusters, int cluster_flags)
   Converts UTF-8 text to an array of glyphs, optionally with cluster ma... */
PHP_FUNCTION(cairo_scaled_font_text_to_glyphs)
{
    zval *zscaled_font;
    double x;
    double y;
    char *utf8;
    size_t utf8_len;
    zval *zglyphs;
    size_t num_glyphs;
    zval *zclusters;
    size_t num_clusters;
    zend_long zcluster_flags;

    ZEND_PARSE_PARAMETERS_START(10, 10)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x);
        Z_PARAM_DOUBLE(y);
        Z_PARAM_STRING(utf8, utf8_len);
        Z_PARAM_ARRAY(zglyphs);
        Z_PARAM_OPTIONAL
        Z_PARAM_ARRAY(zclusters);
        Z_PARAM_LONG(zcluster_flags);
    ZEND_PARSE_PARAMETERS_END();
#if 0
    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);
    php_cairo_glyph_t *php_glyphs = ZVAL_IS_PHP_CAIRO_GLYPH_T(zglyphs)? ZVAL_GET_PHP_CAIRO_GLYPH_T(zglyphs): NULL;
    DECL_PHP_CAIRO_GLYPH_T(glyphs);
    php_cairo_text_cluster_t *php_clusters = ZVAL_IS_PHP_CAIRO_TEXT_CLUSTER_T(zclusters)? ZVAL_GET_PHP_CAIRO_TEXT_CLUSTER_T(zclusters): NULL;
    DECL_PHP_CAIRO_TEXT_CLUSTER_T(clusters);
    cairo_text_cluster_flags_t cluster_flags = zcluster_flags;

    int ret = cairo_scaled_font_text_to_glyphs(scaled_font, x, y, utf8, utf8_len, glyphs, num_glyphs, clusters, num_clusters, cluster_flags);
    RETURN_LONG(ret);
#endif
}/* }}} */
#endif
#if CAIRO_VERSION >= 10200
/* {{{ proto php_cairo_font_face_t cairo_scaled_font_get_font_face(php_cairo_scaled_font_t scaled_font)
   Gets the font face that this scaled font uses. */
PHP_FUNCTION(cairo_scaled_font_get_font_face)
{
    zval *zscaled_font;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);

    cairo_font_face_t *ret = cairo_scaled_font_get_font_face(scaled_font);
    php_cairo_font_face_t *php_ret = php_cairo_font_face_t_new();
    zend_object *z_ret = &php_ret->std;
    php_ret->ptr = ret;

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto void cairo_scaled_font_get_font_options(php_cairo_scaled_font_t scaled_font, php_cairo_font_options_t options)
   Stores the font options with which scaled_font was created into options . */
PHP_FUNCTION(cairo_scaled_font_get_font_options)
{
    zval *zscaled_font;
    zval *zoptions;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);
    php_cairo_font_options_t *php_options = ZVAL_IS_PHP_CAIRO_FONT_OPTIONS_T(zoptions)? ZVAL_GET_PHP_CAIRO_FONT_OPTIONS_T(zoptions): NULL;
    DECL_PHP_CAIRO_FONT_OPTIONS_T(options);

    cairo_scaled_font_get_font_options(scaled_font, options);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_scaled_font_get_font_matrix(php_cairo_scaled_font_t scaled_font, php_cairo_matrix_t font_matrix)
   Stores the font matrix with which scaled_font was created into matrix . */
PHP_FUNCTION(cairo_scaled_font_get_font_matrix)
{
    zval *zscaled_font;
    zval *zfont_matrix;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zfont_matrix, php_cairo_matrix_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);
    php_cairo_matrix_t *php_font_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zfont_matrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zfont_matrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(font_matrix);

    cairo_scaled_font_get_font_matrix(scaled_font, font_matrix);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_scaled_font_get_ctm(php_cairo_scaled_font_t scaled_font, php_cairo_matrix_t ctm)
   Stores the CTM with which scaled_font was created into ctm . */
PHP_FUNCTION(cairo_scaled_font_get_ctm)
{
    zval *zscaled_font;
    zval *zctm;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zctm, php_cairo_matrix_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);
    php_cairo_matrix_t *php_ctm = ZVAL_IS_PHP_CAIRO_MATRIX_T(zctm)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zctm): NULL;
    DECL_PHP_CAIRO_MATRIX_T(ctm);

    cairo_scaled_font_get_ctm(scaled_font, ctm);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10800
/* {{{ proto void cairo_scaled_font_get_scale_matrix(php_cairo_scaled_font_t scaled_font, php_cairo_matrix_t scale_matrix)
   Stores the scale matrix of scaled_font into matrix . */
PHP_FUNCTION(cairo_scaled_font_get_scale_matrix)
{
    zval *zscaled_font;
    zval *zscale_matrix;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zscale_matrix, php_cairo_matrix_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);
    php_cairo_matrix_t *php_scale_matrix = ZVAL_IS_PHP_CAIRO_MATRIX_T(zscale_matrix)? ZVAL_GET_PHP_CAIRO_MATRIX_T(zscale_matrix): NULL;
    DECL_PHP_CAIRO_MATRIX_T(scale_matrix);

    cairo_scaled_font_get_scale_matrix(scaled_font, scale_matrix);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10200
/* {{{ proto int cairo_scaled_font_get_type(php_cairo_scaled_font_t scaled_font)
   This function returns the type of the backend used to create a scaled... */
PHP_FUNCTION(cairo_scaled_font_get_type)
{
    zval *zscaled_font;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);

    int ret = cairo_scaled_font_get_type(scaled_font);

    RETURN_LONG(ret);
}/* }}} */
#endif
#if CAIRO_VERSION >= 10400
/* {{{ proto int cairo_scaled_font_get_reference_count(php_cairo_scaled_font_t scaled_font)
   Returns the current reference count of scaled_font . */
PHP_FUNCTION(cairo_scaled_font_get_reference_count)
{
    zval *zscaled_font;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);

    int ret = cairo_scaled_font_get_reference_count(scaled_font);

    RETURN_LONG(ret);
}/* }}} */
/* {{{ proto int cairo_scaled_font_set_user_data(php_cairo_scaled_font_t scaled_font, php_cairo_user_data_key_t key, void user_data, cairo_destroy_func_t destroy)
   Attach user data to scaled_font . */
PHP_FUNCTION(cairo_scaled_font_set_user_data)
{
    zval *zscaled_font;
    zval *zkey;
    zval *zuser_data;
    zval *zdestroy;
#if 0
    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zkey, php_cairo_user_data_key_t_class_entry, 1, 0);
        Z_PARAM_ZVAL(zuser_data);
        Z_PARAM_OBJECT_OF_CLASS_EX(zdestroy, php_cairo_destroy_func_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);
    php_cairo_user_data_key_t *php_key = ZVAL_IS_PHP_CAIRO_USER_DATA_KEY_T(zkey)? ZVAL_GET_PHP_CAIRO_USER_DATA_KEY_T(zkey): NULL;
    DECL_PHP_CAIRO_USER_DATA_KEY_T(key);
    php_cairo_destroy_func_t *php_destroy = ZVAL_IS_PHP_CAIRO_DESTROY_FUNC_T(zdestroy)? ZVAL_GET_PHP_CAIRO_DESTROY_FUNC_T(zdestroy): NULL;
    DECL_PHP_CAIRO_DESTROY_FUNC_T(destroy);

    int ret = cairo_scaled_font_set_user_data(scaled_font, key, user_data, destroy);

    RETURN_LONG(ret);
#endif
}/* }}} */
/* {{{ proto void cairo_scaled_font_get_user_data(php_cairo_scaled_font_t scaled_font, php_cairo_user_data_key_t key)
   Return user data previously attached to scaled_font using the specifi... */
PHP_FUNCTION(cairo_scaled_font_get_user_data)
{
    zval *zscaled_font;
    zval *zkey;
#if 0
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zscaled_font, php_cairo_scaled_font_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zkey, php_cairo_user_data_key_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_scaled_font_t *php_scaled_font = ZVAL_IS_PHP_CAIRO_SCALED_FONT_T(zscaled_font)? ZVAL_GET_PHP_CAIRO_SCALED_FONT_T(zscaled_font): NULL;
    DECL_PHP_CAIRO_SCALED_FONT_T(scaled_font);
    php_cairo_user_data_key_t *php_key = ZVAL_IS_PHP_CAIRO_USER_DATA_KEY_T(zkey)? ZVAL_GET_PHP_CAIRO_USER_DATA_KEY_T(zkey): NULL;
    DECL_PHP_CAIRO_USER_DATA_KEY_T(key);

    cairo_scaled_font_get_user_data(scaled_font, key);
#endif
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
