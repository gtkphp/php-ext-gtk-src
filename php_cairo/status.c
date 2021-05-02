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

#include "status.h"

extern zend_module_entry gtk_module_entry;

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

/*{{{ php_cairo_status_t_class_init */
zend_class_entry*
php_cairo_status_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    zend_register_long_constant("CAIRO_STATUS_SUCCESS", sizeof("CAIRO_STATUS_SUCCESS")-1,
        CAIRO_STATUS_SUCCESS, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_NO_MEMORY", sizeof("CAIRO_STATUS_NO_MEMORY")-1,
        CAIRO_STATUS_NO_MEMORY, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_RESTORE", sizeof("CAIRO_STATUS_INVALID_RESTORE")-1,
        CAIRO_STATUS_INVALID_RESTORE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_POP_GROUP", sizeof("CAIRO_STATUS_INVALID_POP_GROUP")-1,
        CAIRO_STATUS_INVALID_POP_GROUP, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_NO_CURRENT_POINT", sizeof("CAIRO_STATUS_NO_CURRENT_POINT")-1,
        CAIRO_STATUS_NO_CURRENT_POINT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_MATRIX", sizeof("CAIRO_STATUS_INVALID_MATRIX")-1,
        CAIRO_STATUS_INVALID_MATRIX, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_STATUS", sizeof("CAIRO_STATUS_INVALID_STATUS")-1,
        CAIRO_STATUS_INVALID_STATUS, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_NULL_POINTER", sizeof("CAIRO_STATUS_NULL_POINTER")-1,
        CAIRO_STATUS_NULL_POINTER, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_STRING", sizeof("CAIRO_STATUS_INVALID_STRING")-1,
        CAIRO_STATUS_INVALID_STRING, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_PATH_DATA", sizeof("CAIRO_STATUS_INVALID_PATH_DATA")-1,
        CAIRO_STATUS_INVALID_PATH_DATA, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_READ_ERROR", sizeof("CAIRO_STATUS_READ_ERROR")-1,
        CAIRO_STATUS_READ_ERROR, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_WRITE_ERROR", sizeof("CAIRO_STATUS_WRITE_ERROR")-1,
        CAIRO_STATUS_WRITE_ERROR, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_SURFACE_FINISHED", sizeof("CAIRO_STATUS_SURFACE_FINISHED")-1,
        CAIRO_STATUS_SURFACE_FINISHED, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_SURFACE_TYPE_MISMATCH", sizeof("CAIRO_STATUS_SURFACE_TYPE_MISMATCH")-1,
        CAIRO_STATUS_SURFACE_TYPE_MISMATCH, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_PATTERN_TYPE_MISMATCH", sizeof("CAIRO_STATUS_PATTERN_TYPE_MISMATCH")-1,
        CAIRO_STATUS_PATTERN_TYPE_MISMATCH, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_CONTENT", sizeof("CAIRO_STATUS_INVALID_CONTENT")-1,
        CAIRO_STATUS_INVALID_CONTENT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_FORMAT", sizeof("CAIRO_STATUS_INVALID_FORMAT")-1,
        CAIRO_STATUS_INVALID_FORMAT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_VISUAL", sizeof("CAIRO_STATUS_INVALID_VISUAL")-1,
        CAIRO_STATUS_INVALID_VISUAL, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_FILE_NOT_FOUND", sizeof("CAIRO_STATUS_FILE_NOT_FOUND")-1,
        CAIRO_STATUS_FILE_NOT_FOUND, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_DASH", sizeof("CAIRO_STATUS_INVALID_DASH")-1,
        CAIRO_STATUS_INVALID_DASH, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_DSC_COMMENT", sizeof("CAIRO_STATUS_INVALID_DSC_COMMENT")-1,
        CAIRO_STATUS_INVALID_DSC_COMMENT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_INDEX", sizeof("CAIRO_STATUS_INVALID_INDEX")-1,
        CAIRO_STATUS_INVALID_INDEX, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_CLIP_NOT_REPRESENTABLE", sizeof("CAIRO_STATUS_CLIP_NOT_REPRESENTABLE")-1,
        CAIRO_STATUS_CLIP_NOT_REPRESENTABLE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_TEMP_FILE_ERROR", sizeof("CAIRO_STATUS_TEMP_FILE_ERROR")-1,
        CAIRO_STATUS_TEMP_FILE_ERROR, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_STRIDE", sizeof("CAIRO_STATUS_INVALID_STRIDE")-1,
        CAIRO_STATUS_INVALID_STRIDE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_FONT_TYPE_MISMATCH", sizeof("CAIRO_STATUS_FONT_TYPE_MISMATCH")-1,
        CAIRO_STATUS_FONT_TYPE_MISMATCH, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_USER_FONT_IMMUTABLE", sizeof("CAIRO_STATUS_USER_FONT_IMMUTABLE")-1,
        CAIRO_STATUS_USER_FONT_IMMUTABLE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_USER_FONT_ERROR", sizeof("CAIRO_STATUS_USER_FONT_ERROR")-1,
        CAIRO_STATUS_USER_FONT_ERROR, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_NEGATIVE_COUNT", sizeof("CAIRO_STATUS_NEGATIVE_COUNT")-1,
        CAIRO_STATUS_NEGATIVE_COUNT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_CLUSTERS", sizeof("CAIRO_STATUS_INVALID_CLUSTERS")-1,
        CAIRO_STATUS_INVALID_CLUSTERS, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_SLANT", sizeof("CAIRO_STATUS_INVALID_SLANT")-1,
        CAIRO_STATUS_INVALID_SLANT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_WEIGHT", sizeof("CAIRO_STATUS_INVALID_WEIGHT")-1,
        CAIRO_STATUS_INVALID_WEIGHT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_SIZE", sizeof("CAIRO_STATUS_INVALID_SIZE")-1,
        CAIRO_STATUS_INVALID_SIZE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED", sizeof("CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED")-1,
        CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_DEVICE_TYPE_MISMATCH", sizeof("CAIRO_STATUS_DEVICE_TYPE_MISMATCH")-1,
        CAIRO_STATUS_DEVICE_TYPE_MISMATCH, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_DEVICE_ERROR", sizeof("CAIRO_STATUS_DEVICE_ERROR")-1,
        CAIRO_STATUS_DEVICE_ERROR, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_INVALID_MESH_CONSTRUCTION", sizeof("CAIRO_STATUS_INVALID_MESH_CONSTRUCTION")-1,
        CAIRO_STATUS_INVALID_MESH_CONSTRUCTION, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_DEVICE_FINISHED", sizeof("CAIRO_STATUS_DEVICE_FINISHED")-1,
        CAIRO_STATUS_DEVICE_FINISHED, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_JBIG2_GLOBAL_MISSING", sizeof("CAIRO_STATUS_JBIG2_GLOBAL_MISSING")-1,
        CAIRO_STATUS_JBIG2_GLOBAL_MISSING, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_PNG_ERROR", sizeof("CAIRO_STATUS_PNG_ERROR")-1,
        CAIRO_STATUS_PNG_ERROR, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_FREETYPE_ERROR", sizeof("CAIRO_STATUS_FREETYPE_ERROR")-1,
        CAIRO_STATUS_FREETYPE_ERROR, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_WIN32_GDI_ERROR", sizeof("CAIRO_STATUS_WIN32_GDI_ERROR")-1,
        CAIRO_STATUS_WIN32_GDI_ERROR, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_TAG_ERROR", sizeof("CAIRO_STATUS_TAG_ERROR")-1,
        CAIRO_STATUS_TAG_ERROR, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_STATUS_LAST_STATUS", sizeof("CAIRO_STATUS_LAST_STATUS")-1,
        CAIRO_STATUS_LAST_STATUS, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);


    return NULL;
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

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

/* {{{ proto string cairo_status_to_string(mixed status) */
PHP_FUNCTION(cairo_status_to_string)
{
    zend_long zstatus;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(zstatus)
    ZEND_PARSE_PARAMETERS_END();

    cairo_status_t status = zstatus;

    char *ret = cairo_status_to_string(status);
    RETURN_STRING(ret);


}/* }}} */

/* {{{ proto void cairo_debug_reset_static_data() */
PHP_FUNCTION(cairo_debug_reset_static_data)
{


    cairo_debug_reset_static_data();

}/* }}} */


