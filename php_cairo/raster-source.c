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
#include "php_cairo/pattern.h"
#include "php_cairo/surface.h"
#include "php_cairo/rectangle-int.h"
#include "raster-source.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_raster_source_class_entry;// struct
zend_object_handlers  php_cairo_raster_source_handlers;



/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/


/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

#if CAIRO_VERSION >= 11200
/* {{{ proto php_cairo_pattern_t cairo_pattern_create_raster_source(void user_data, int content, int width, int height)
   Creates a new user pattern for providing pixel data. */
PHP_FUNCTION(cairo_pattern_create_raster_source)
{
    zval *zuser_data;
    zend_long zcontent;
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL(zuser_data);
        Z_PARAM_LONG(zcontent);
        Z_PARAM_LONG(width);
        Z_PARAM_LONG(height);
    ZEND_PARSE_PARAMETERS_END();

    cairo_content_t content = zcontent;
    php_cairo_raster_source_pattern_callback *callback = emalloc(sizeof(php_cairo_raster_source_pattern_callback));
    ZVAL_COPY(&callback->user_data, zuser_data);

    cairo_pattern_t *ret = cairo_pattern_create_raster_source((void *)callback, content, width, height);
    php_cairo_pattern_t *php_ret = php_cairo_pattern_t_new();
    zend_object *z_ret = &php_ret->std;
    php_ret->ptr = ret;
    php_ret->callback = callback;


    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto void cairo_raster_source_pattern_set_callback_data(php_cairo_pattern_t pattern, void data)
   Updates the user data that is provided to all callbacks. */
PHP_FUNCTION(cairo_raster_source_pattern_set_callback_data)
{
    zval *zpattern;
    zval *zdata;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 0, 0);
        Z_PARAM_ZVAL(zdata);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);


    ZVAL_COPY(&php_pattern->callback->user_data, zdata);
    //cairo_raster_source_pattern_set_callback_data(pattern, data);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_raster_source_pattern_get_callback_data(php_cairo_pattern_t pattern)
   Queries the current user data. */
PHP_FUNCTION(cairo_raster_source_pattern_get_callback_data)
{
    zval *zpattern;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    //cairo_raster_source_pattern_get_callback_data(pattern);
    RETURN_ZVAL(&php_pattern->callback->user_data, 1, 0);
}/* }}} */

static cairo_surface_t*
php_cairo_raster_source_pattern_acquire(cairo_pattern_t *pattern,
           void *callback_data,
           cairo_surface_t *target,
           const cairo_rectangle_int_t *extents)
{
    php_cairo_raster_source_pattern_callback *callback = callback_data;


    //------------------------------
    zend_fcall_info			*fci_acquire = &callback->fci_acquire;
    zend_fcall_info_cache	*fcc_acquire = &callback->fcc_acquire;
    zend_fcall_info			*fci_release = &callback->fci_release;
    zend_fcall_info_cache	*fcc_release = &callback->fcc_release;

    zval retval;

    php_cairo_pattern_t *php_pattern = php_cairo_pattern_t_new();
    php_pattern->ptr = pattern;
    //callback->user_data;
    php_cairo_surface_t *php_target = php_cairo_surface_t_new();
    php_target->ptr = target;
    php_cairo_rectangle_int_t *php_rectangle_int = php_cairo_rectangle_int_t_new();
    PHP_CAIRO_RECTANGLE_INT_T_SET(php_rectangle_int, extents);

    zval params[4];
    ZVAL_OBJ(&params[0], &php_pattern->std);
    ZVAL_COPY(&params[1], &callback->user_data);
    ZVAL_OBJ(&params[2], &php_target->std);
    ZVAL_OBJ(&params[3], &php_rectangle_int->std);

    fci_acquire->param_count = 4;
    fci_acquire->params = params;
    fci_acquire->named_params=NULL;
    fci_acquire->retval = &retval;

    if (zend_call_function(fci_acquire, fcc_acquire) == SUCCESS && Z_TYPE(retval) != IS_UNDEF) {
        if (Z_ISREF(retval)) {
            zend_unwrap_reference(&retval);
        }
        if (Z_TYPE_P(&retval)==IS_OBJECT) {
            php_cairo_surface_t *php_surface = ZOBJ_TO_PHP_CAIRO_SURFACE_T(retval.value.obj);
            cairo_surface_t *surface = php_surface->ptr;
            php_surface->ptr = NULL;

            zend_object_release(&php_surface->std);

            zend_object_release(&php_rectangle_int->std);

            php_pattern->ptr = NULL;
            zend_object_release(&php_pattern->std);

            php_target->ptr = NULL;
            zend_object_release(&php_target->std);

            callback->surface = surface;
            return surface;
        } else {
            php_printf("Error Type\n");
        }
    }
    //------------------------------


    return NULL;//cairo_image_surface_create_from_png (callback->user_data.value.str->val);
}

static void
php_cairo_raster_source_pattern_release(cairo_pattern_t *pattern,
           void *callback_data,
           cairo_surface_t *target)
{
    php_cairo_raster_source_pattern_callback *callback = callback_data;


    //------------------------------
    zend_fcall_info			*fci_acquire = &callback->fci_acquire;
    zend_fcall_info_cache	*fcc_acquire = &callback->fcc_acquire;
    zend_fcall_info			*fci_release = &callback->fci_release;
    zend_fcall_info_cache	*fcc_release = &callback->fcc_release;

    zval retval;

    php_cairo_pattern_t *php_pattern = php_cairo_pattern_t_new();
    php_pattern->ptr = pattern;
    //callback->user_data;
    php_cairo_surface_t *php_target = php_cairo_surface_t_new();
    php_target->ptr = target;


    zval params[3];
    ZVAL_OBJ(&params[0], &php_pattern->std);
    ZVAL_COPY(&params[1], &callback->user_data);
    ZVAL_OBJ(&params[2], &php_target->std);

    fci_release->param_count = 3;
    fci_release->params = params;
    fci_release->named_params=NULL;
    fci_release->retval = &retval;

    if (Z_TYPE(fci_release->function_name)==IS_STRING && zend_call_function(fci_release, fcc_release) == SUCCESS) {
        php_pattern->ptr = NULL;
        zend_object_release(&php_pattern->std);
        php_target->ptr = NULL;
        zend_object_release(&php_target->std);
    }
    //------------------------------

    //zval_delref_p(&callback->user_data);
    //callback->surface->;
    cairo_surface_destroy(callback->surface);

}

/* {{{ proto void cairo_raster_source_pattern_set_acquire(php_cairo_pattern_t pattern, cairo_raster_source_acquire_func_t acquire, cairo_raster_source_release_func_t release)
   Specifies the callbacks used to generate the image surface for a rend... */
PHP_FUNCTION(cairo_raster_source_pattern_set_acquire)
{
    zval *zpattern;


    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 0, 0);
        Z_PARAM_FUNC(ZOBJ_TO_PHP_CAIRO_PATTERN_T(zpattern->value.obj)->callback->fci_acquire, ZOBJ_TO_PHP_CAIRO_PATTERN_T(zpattern->value.obj)->callback->fcc_acquire);
        Z_PARAM_FUNC(ZOBJ_TO_PHP_CAIRO_PATTERN_T(zpattern->value.obj)->callback->fci_release, ZOBJ_TO_PHP_CAIRO_PATTERN_T(zpattern->value.obj)->callback->fcc_release);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_raster_source_pattern_set_acquire(pattern, php_cairo_raster_source_pattern_acquire, php_cairo_raster_source_pattern_release);

    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_raster_source_pattern_get_acquire(php_cairo_pattern_t pattern, cairo_raster_source_acquire_func_t acquire, cairo_raster_source_release_func_t release)
   Queries the current acquire and release callbacks. */
PHP_FUNCTION(cairo_raster_source_pattern_get_acquire)
{
    zval *zpattern;
    zval *zacquire;
    zval *zrelease;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 0, 0);
        Z_PARAM_ZVAL_EX2(zacquire, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_ZVAL_EX2(zrelease, 0, ZEND_SEND_BY_REF, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    if (NULL==php_pattern->callback->fci_acquire.object) {
        ZVAL_COPY(zacquire, &php_pattern->callback->fci_acquire.function_name);
    } else {
        // array
    }

    if (NULL==php_pattern->callback->fci_release.object) {
        ZVAL_COPY(zrelease, &php_pattern->callback->fci_release.function_name);
    } else {
        // array
    }

    RETURN_NULL();
}/* }}} */

static cairo_status_t
php_cairo_raster_source_pattern_snapshot(cairo_pattern_t *pattern,
                                         void *callback_data)
{
    php_cairo_raster_source_pattern_callback *callback = callback_data;


    //------------------------------
    zend_fcall_info			*fci_snapshot = &callback->fci_snapshot;
    zend_fcall_info_cache	*fcc_snapshot = &callback->fcc_snapshot;

    zval retval;

    php_cairo_pattern_t *php_pattern = php_cairo_pattern_t_new();
    php_pattern->ptr = pattern;
    //callback->user_data;

    zval params[2];
    ZVAL_OBJ(&params[0], &php_pattern->std);
    ZVAL_COPY(&params[1], &callback->user_data);

    fci_snapshot->param_count = 2;
    fci_snapshot->params = params;
    fci_snapshot->named_params=NULL;
    fci_snapshot->retval = &retval;

    if (zend_call_function(fci_snapshot, fcc_snapshot) == SUCCESS) {
        php_pattern->ptr = NULL;
        zend_object_release(&php_pattern->std);

        return retval.value.lval;
    }
    //------------------------------

    return CAIRO_STATUS_SUCCESS;
}

/* {{{ proto void cairo_raster_source_pattern_set_snapshot(php_cairo_pattern_t pattern, cairo_raster_source_snapshot_func_t snapshot)
   Sets the callback that will be used whenever a snapshot is taken of t... */
PHP_FUNCTION(cairo_raster_source_pattern_set_snapshot)
{
    zval *zpattern;
    zval *zsnapshot;


    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 0, 0);
        Z_PARAM_FUNC(ZOBJ_TO_PHP_CAIRO_PATTERN_T(zpattern->value.obj)->callback->fci_snapshot, ZOBJ_TO_PHP_CAIRO_PATTERN_T(zpattern->value.obj)->callback->fcc_snapshot);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_raster_source_pattern_set_snapshot(pattern, php_cairo_raster_source_pattern_snapshot);

    RETURN_NULL();
}/* }}} */
/* {{{ proto cairo_raster_source_snapshot_func_t cairo_raster_source_pattern_get_snapshot(php_cairo_pattern_t pattern)
   Queries the current snapshot callback. */
PHP_FUNCTION(cairo_raster_source_pattern_get_snapshot)
{
    zval *zpattern;


    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    if (NULL==php_pattern->callback->fci_release.object) {
        RETURN_ZVAL(&php_pattern->callback->fci_snapshot.function_name, 1, 0);
    } else {
        // array
    }

}/* }}} */
cairo_status_t
cairo_raster_source_pattern_copy (cairo_pattern_t *pattern,
                                    void *callback_data,
                                    const cairo_pattern_t *other)
{
    php_cairo_raster_source_pattern_callback *callback = callback_data;


    //------------------------------
    zend_fcall_info			*fci_copy = &callback->fci_copy;
    zend_fcall_info_cache	*fcc_copy = &callback->fcc_copy;

    zval retval;

    php_cairo_pattern_t *php_pattern = php_cairo_pattern_t_new();
    php_pattern->ptr = pattern;
    //callback->user_data;
    php_cairo_pattern_t *php_other = php_cairo_pattern_t_new();
    php_other->ptr = other;

    zval params[3];
    ZVAL_OBJ(&params[0], &php_pattern->std);
    ZVAL_COPY(&params[1], &callback->user_data);
    ZVAL_OBJ(&params[2], &php_other->std);

    fci_copy->param_count = 3;
    fci_copy->params = params;
    fci_copy->named_params=NULL;
    fci_copy->retval = &retval;

    if (zend_call_function(fci_copy, fcc_copy) == SUCCESS) {
        php_pattern->ptr = NULL;
        zend_object_release(&php_pattern->std);
        php_other->ptr = NULL;
        zend_object_release(&php_other->std);

        return retval.value.lval;
    }
    //------------------------------

    return CAIRO_STATUS_SUCCESS;
}

/* {{{ proto void cairo_raster_source_pattern_set_copy(php_cairo_pattern_t pattern, cairo_raster_source_copy_func_t copy)
   Updates the copy callback which is used whenever a temporary copy of ... */
PHP_FUNCTION(cairo_raster_source_pattern_set_copy)
{
    zval *zpattern;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 0, 0);
        Z_PARAM_FUNC(ZOBJ_TO_PHP_CAIRO_PATTERN_T(zpattern->value.obj)->callback->fci_copy, ZOBJ_TO_PHP_CAIRO_PATTERN_T(zpattern->value.obj)->callback->fcc_copy);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_raster_source_pattern_set_copy(pattern, cairo_raster_source_pattern_copy);

    RETURN_NULL();
}/* }}} */
/* {{{ proto cairo_raster_source_copy_func_t cairo_raster_source_pattern_get_copy(php_cairo_pattern_t pattern)
   Queries the current copy callback. */
PHP_FUNCTION(cairo_raster_source_pattern_get_copy)
{
    zval *zpattern;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    if (NULL==php_pattern->callback->fci_copy.object) {
        RETURN_ZVAL(&php_pattern->callback->fci_copy.function_name, 1, 0);
    } else {
        // array
    }


    RETURN_NULL();
}/* }}} */

static void
cairo_raster_source_pattern_finish (cairo_pattern_t *pattern,
                                    void *callback_data)
{
    php_cairo_raster_source_pattern_callback *callback = callback_data;

    /*
    //------------------------------
    zend_fcall_info			*fci_finish = &callback->fci_finish;
    zend_fcall_info_cache	*fcc_finish = &callback->fcc_finish;

    zval retval;

    php_cairo_pattern_t *php_pattern = php_cairo_pattern_t_new();
    php_pattern->ptr = pattern;
    //callback->user_data;

    zval params[2];
    ZVAL_OBJ(&params[0], &php_pattern->std);
    ZVAL_COPY(&params[1], &callback->user_data);

    fci_finish->param_count = 2;
    fci_finish->params = params;
    fci_finish->named_params=NULL;
    fci_finish->retval = &retval;

    if (zend_call_function(fci_finish, fcc_finish) == SUCCESS) {
        php_pattern->ptr = NULL;
        zend_object_release(&php_pattern->std);
    }
    //------------------------------
    */
}

/* {{{ proto void cairo_raster_source_pattern_set_finish(php_cairo_pattern_t pattern, cairo_raster_source_finish_func_t finish)
   Updates the finish callback which is used whenever a pattern (or a co... */
PHP_FUNCTION(cairo_raster_source_pattern_set_finish)
{
    zval *zpattern;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 0, 0);
        Z_PARAM_FUNC(ZOBJ_TO_PHP_CAIRO_PATTERN_T(zpattern->value.obj)->callback->fci_finish, ZOBJ_TO_PHP_CAIRO_PATTERN_T(zpattern->value.obj)->callback->fcc_finish);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    cairo_raster_source_pattern_set_finish(pattern, cairo_raster_source_pattern_finish);

    RETURN_NULL();
}/* }}} */
/* {{{ proto cairo_raster_source_finish_func_t cairo_raster_source_pattern_get_finish(php_cairo_pattern_t pattern)
   Queries the current finish callback. */
PHP_FUNCTION(cairo_raster_source_pattern_get_finish)
{
    zval *zpattern;


    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpattern, php_cairo_pattern_t_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_pattern_t *php_pattern = ZVAL_IS_PHP_CAIRO_PATTERN_T(zpattern)? ZVAL_GET_PHP_CAIRO_PATTERN_T(zpattern): NULL;
    DECL_PHP_CAIRO_PATTERN_T(pattern);

    if (NULL==php_pattern->callback->fci_finish.object) {
        RETURN_ZVAL(&php_pattern->callback->fci_finish.function_name, 1, 0);
    } else {
        // array
    }

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
