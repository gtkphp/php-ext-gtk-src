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
  | Author:                                                              |
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

#include <gtk/gtk.h>

/// include "php_gtkml.h"
#include "php_gtk.h"

/// include "php_cairo.h"
#include "php_cairo/cairo.h"
#include "php_cairo/status.h"
#include "php_cairo/antialias.h"
#include "php_cairo/content.h"
#include "php_cairo/device-type.h"
#include "php_cairo/extend.h"
#include "php_cairo/fill-rule.h"
#include "php_cairo/filter.h"
#include "php_cairo/font-slant.h"
#include "php_cairo/font-type.h"
#include "php_cairo/font-weight.h"
#include "php_cairo/hint-metrics.h"
#include "php_cairo/hint-style.h"
#include "php_cairo/line-cap.h"
#include "php_cairo/line-join.h"
#include "php_cairo/operator.h"
#include "php_cairo/pattern-type.h"
#include "php_cairo/region-overlap.h"
#include "php_cairo/subpixel-order.h"
#include "php_cairo/surface-type.h"
#include "php_cairo/text-cluster-flags.h"
#include "php_cairo/ft-synthesize.h"

#include "php_cairo/rectangle.h"
#include "php_cairo/rectangle-int.h"
#include "php_cairo/path-data-type.h"
#include "php_cairo/path-data.h"
#include "php_cairo/path.h"
#include "php_cairo/png.h"
#include "php_cairo/font-options.h"
#include "php_cairo/matrix.h"
#include "php_cairo/device.h"
#include "php_cairo/font-face.h"
#include "php_cairo/font-extents.h"
#include "php_cairo/text-cluster.h"
#include "php_cairo/text-extents.h"
#include "php_cairo/scaled-font.h"
#include "php_cairo/glyph.h"
#include "php_cairo/pattern.h"
#include "php_cairo/surface.h"
#include "php_cairo/region.h"
#include "php_cairo/transformations.h"
#include "php_cairo/ft.h"
#include "php_cairo/raster-source.h"

#if CAIRO_HAS_IMAGE_SURFACE
#include "php_cairo/format.h"
#include "php_cairo/image-surface.h"
#include "php_cairo/image-data.h"
#endif
#if CAIRO_HAS_SVG_SURFACE
#include "php_cairo/svg.h"
#include "php_cairo/svg-version.h"
#endif
#if CAIRO_VERSION >= 11600
//#include "php_cairo/pdf-metadata.h"
#endif


/// include "php_doc.h"
#include "php_doc/comment.h"


/// include "php_glib.h"
#include "php_glib/str.h"
#include "php_glib/hash-table.h"
#include "php_glib/list.h"
#include "php_glib/quark.h"
#include "php_glib/error.h"



/// include "php_gobject.h"
#include "php_gobject/object.h"
#include "php_gobject/object-extends.h"
#include "php_gobject/signal.h"
#include "php_gobject/value.h"
#include "php_gobject/paramspecs.h"



/// include "php_gdk.h"
#include "php_gdk/pixbuf.h"
#include "php_gdk/rectangle.h"



/// include "php_gtk.h"
#include "php_gtk/widget.h"
#include "php_gtk/widget-extends.h"
#include "php_gtk/requisition.h"
#include "php_gtk/requested-size.h"
#include "php_gtk/container.h"
#include "php_gtk/bin.h"
#include "php_gtk/box.h"
#include "php_gtk/window.h"
#include "php_gtk/button.h"
#include "php_gtk/main.h"


HashTable classes;

/* If you declare any globals in php_gtk.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(gtk)
*/

/* True global resources - no need for thread safety here */
static int le_gtk;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("gtk.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_gtk_globals, gtk_globals)
    STD_PHP_INI_ENTRY("gtk.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_gtk_globals, gtk_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */
ZEND_BEGIN_ARG_INFO_EX(arginfo_confirm_gtk_compiled, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, msg)
ZEND_END_ARG_INFO()
PHP_FUNCTION(confirm_gtk_compiled)
{

    php_doc_comment_tests_suite();

}




/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_gtk_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_gtk_init_globals(zend_gtk_globals *gtk_globals)
{
	gtk_globals->global_value = 0;
	gtk_globals->global_string = NULL;
}
*/
/* }}} */


//extern zend_object_handlers php_glib_object_handlers;


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(gtk)
{
    //int zm_startup_gtk(int type, int module_number)

	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/

	zend_class_entry ce;
    //zend_class_entry *g_hash_table_ce;
    //zend_class_entry *g_list_ce;
    zend_class_entry *gobject_object_ce;
    zend_class_entry *gdk_pixbuf_ce;
    zend_class_entry *gdk_rectangle_ce;
    zend_class_entry *gtk_widget_ce;
    zend_class_entry *gtk_container_ce;
    zend_class_entry *gtk_bin_ce;
    zend_class_entry *gtk_window_ce;
    zend_class_entry *gtk_box_ce;
    zend_class_entry *gtk_button_ce;


    zend_hash_init(&classes, 0, NULL, NULL, 1);

    //                  PHP_GLIB_MINIT_FUNCTION(&ce);
    //                  PHP_CAIRO_MINIT_FUNCTION(&ce);

    zend_register_long_constant("CAIRO_VERSION", sizeof("CAIRO_VERSION")-1,
        CAIRO_VERSION, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_HAS_IMAGE_SURFACE", sizeof("CAIRO_HAS_IMAGE_SURFACE")-1,
        CAIRO_HAS_IMAGE_SURFACE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);

                        PHP_CAIRO_T_MINIT_FUNCTION(&ce, NULL);

                        PHP_CAIRO_ANTIALIAS_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_FILL_RULE_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_LINE_CAP_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_LINE_JOIN_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_OPERATOR_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_PATH_DATA_TYPE_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_EXTEND_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_FILTER_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_PATTERN_TYPE_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_REGION_OVERLAP_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_FONT_SLANT_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_FONT_WEIGHT_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_TEXT_CLUSTER_FLAGS_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_FONT_TYPE_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_SUBPIXEL_ORDER_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_HINT_STYLE_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_HINT_METRICS_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_DEVICE_TYPE_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_CONTENT_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_SURFACE_TYPE_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_FORMAT_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_STATUS_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_FT_SYNTHESIZE_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_FT_MINIT_FUNCTION(NULL, NULL);

                        PHP_CAIRO_RECTANGLE_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_RECTANGLE_INT_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_PATH_DATA_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_PATH_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_FONT_OPTIONS_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_MATRIX_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_DEVICE_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_FONT_FACE_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_FONT_EXTENTS_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_TEXT_CLUSTER_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_TEXT_EXTENTS_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_SCALED_FONT_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_GLYPH_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_PATTERN_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_SURFACE_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_REGION_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_IMAGE_DATA_T_MINIT_FUNCTION(&ce, NULL);
#if CAIRO_HAS_IMAGE_SURFACE
    //                    PHP_CAIRO_FORMAT_T_MINIT_FUNCTION(NULL, NULL);
    //                    PHP_CAIRO_IMAGE_SURFACE_MINIT_FUNCTION(NULL, NULL);
#endif
                        PHP_CAIRO_PNG_T_MINIT_FUNCTION(NULL, NULL);
#if CAIRO_HAS_SVG_SURFACE
                        PHP_CAIRO_SVG_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_SVG_VERSION_T_MINIT_FUNCTION(NULL, NULL);
#endif
#if CAIRO_VERSION >= 11600
    //                    PHP_CAIRO_PDF_METADATA_T_MINIT_FUNCTION(NULL, NULL);
#endif
    //                  PHP_PANGO_MINIT_FUNCTION(&ce);
                        PHP_G_STR_MINIT_FUNCTION(NULL, NULL);
                        PHP_G_HASH_TABLE_MINIT_FUNCTION(&ce, NULL);
                        PHP_G_LIST_MINIT_FUNCTION(&ce, NULL);
                        PHP_G_ERROR_MINIT_FUNCTION(&ce, NULL);

    gobject_object_ce = PHP_GOBJECT_OBJECT_MINIT_FUNCTION(&ce, NULL);
                        PHP_GOBJECT_SIGNAL_MINIT_FUNCTION(&ce, NULL);
                        PHP_GOBJECT_VALUE_MINIT_FUNCTION(&ce, NULL);
                        PHP_GOBJECT_PARAM_SPEC_MINIT_FUNCTION(&ce, NULL);


    gdk_pixbuf_ce     = PHP_GDK_PIXBUF_MINIT_FUNCTION(&ce, gobject_object_ce);
    gdk_rectangle_ce  = PHP_GDK_RECTANGLE_MINIT_FUNCTION(&ce, NULL);

    gtk_widget_ce     = PHP_GTK_WIDGET_MINIT_FUNCTION(&ce, gobject_object_ce);
                        PHP_GTK_REQUESTED_SIZE_MINIT_FUNCTION(&ce, NULL);
                        PHP_GTK_REQUISITION_MINIT_FUNCTION(&ce, NULL);
    gtk_container_ce  = PHP_GTK_CONTAINER_MINIT_FUNCTION(&ce, gtk_widget_ce);
    gtk_bin_ce        = PHP_GTK_BIN_MINIT_FUNCTION(&ce, gtk_container_ce);
    gtk_box_ce        = PHP_GTK_BOX_MINIT_FUNCTION(&ce, gtk_container_ce);
    gtk_window_ce     = PHP_GTK_WINDOW_MINIT_FUNCTION(&ce, gtk_bin_ce);
    gtk_button_ce     = PHP_GTK_BUTTON_MINIT_FUNCTION(&ce, gtk_bin_ce);

    zend_register_long_constant("GTK_ORIENTATION_HORIZONTAL", sizeof("GTK_ORIENTATION_HORIZONTAL")-1, GTK_ORIENTATION_HORIZONTAL, CONST_CS | CONST_PERSISTENT, module_number);
    zend_register_long_constant("GTK_ORIENTATION_VERTICAL", sizeof("GTK_ORIENTATION_VERTICAL")-1, GTK_ORIENTATION_VERTICAL, CONST_CS | CONST_PERSISTENT, module_number);

    zend_register_long_constant("G_TYPE_NONE", sizeof("G_TYPE_NONE")-1, G_TYPE_NONE, CONST_CS | CONST_PERSISTENT, module_number);
    zend_register_long_constant("G_TYPE_UINT", sizeof("G_TYPE_UINT")-1, G_TYPE_UINT, CONST_CS | CONST_PERSISTENT, module_number);
    zend_register_long_constant("G_TYPE_POINTER", sizeof("G_TYPE_POINTER")-1, G_TYPE_POINTER, CONST_CS | CONST_PERSISTENT, module_number);
    zend_register_long_constant("G_TYPE_DOUBLE", sizeof("G_TYPE_DOUBLE")-1, G_TYPE_DOUBLE, CONST_CS | CONST_PERSISTENT, module_number);
    zend_register_long_constant("G_TYPE_INT", sizeof("G_TYPE_INT")-1, G_TYPE_INT, CONST_CS | CONST_PERSISTENT, module_number);
    zend_register_long_constant("G_TYPE_OBJECT", sizeof("G_TYPE_OBJECT")-1, G_TYPE_OBJECT, CONST_CS | CONST_PERSISTENT, module_number);

	return SUCCESS;
}
/* }}} */


extern GArray *php_gtk_widget_once_init_array;

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(gtk)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/

    PHP_CAIRO_T_MSHUTDOWN_FUNCTION();

    PHP_CAIRO_ANTIALIAS_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_FILL_RULE_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_LINE_CAP_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_LINE_JOIN_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_OPERATOR_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_PATH_DATA_TYPE_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_EXTEND_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_FILTER_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_PATTERN_TYPE_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_REGION_OVERLAP_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_FONT_SLANT_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_FONT_WEIGHT_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_TEXT_CLUSTER_FLAGS_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_FONT_TYPE_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_SUBPIXEL_ORDER_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_HINT_STYLE_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_HINT_METRICS_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_DEVICE_TYPE_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_CONTENT_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_SURFACE_TYPE_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_FORMAT_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_STATUS_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_FT_SYNTHESIZE_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_FT_MSHUTDOWN_FUNCTION();

    PHP_CAIRO_RECTANGLE_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_RECTANGLE_INT_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_PATH_DATA_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_PATH_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_FONT_OPTIONS_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_MATRIX_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_DEVICE_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_FONT_FACE_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_FONT_EXTENTS_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_TEXT_CLUSTER_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_TEXT_EXTENTS_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_SCALED_FONT_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_GLYPH_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_PATTERN_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_SURFACE_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_REGION_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_IMAGE_DATA_T_MSHUTDOWN_FUNCTION();

#if CAIRO_HAS_IMAGE_SURFACE
    //PHP_CAIRO_FORMAT_T_MSHUTDOWN_FUNCTION();
    //PHP_CAIRO_IMAGE_SURFACE_MSHUTDOWN_FUNCTION();
#endif
    PHP_CAIRO_PNG_T_MSHUTDOWN_FUNCTION();
#if CAIRO_HAS_SVG_SURFACE
    PHP_CAIRO_SVG_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_SVG_VERSION_T_MSHUTDOWN_FUNCTION();
#endif

#if CAIRO_VERSION >= 11600
    //PHP_CAIRO_PDF_METADATA_T_MSHUTDOWN_FUNCTION(NULL, NULL);
#endif

    PHP_G_STR_MSHUTDOWN_FUNCTION();
    PHP_G_HASH_TABLE_MSHUTDOWN_FUNCTION();
    PHP_G_LIST_MSHUTDOWN_FUNCTION();
    PHP_G_ERROR_MSHUTDOWN_FUNCTION();
    PHP_GLIB_QUARK_MSHUTDOWN_FUNCTION();


    PHP_GOBJECT_OBJECT_MSHUTDOWN_FUNCTION();
    PHP_GOBJECT_SIGNAL_MSHUTDOWN_FUNCTION();
    PHP_GOBJECT_VALUE_MSHUTDOWN_FUNCTION();
    PHP_GOBJECT_PARAM_SPEC_MSHUTDOWN_FUNCTION();


    PHP_GDK_PIXBUF_MSHUTDOWN_FUNCTION();
    PHP_GDK_RECTANGLE_MSHUTDOWN_FUNCTION();


    PHP_GTK_WIDGET_MSHUTDOWN_FUNCTION();
    PHP_GTK_REQUESTED_SIZE_MSHUTDOWN_FUNCTION();
    PHP_GTK_REQUISITION_MSHUTDOWN_FUNCTION();
    PHP_GTK_CONTAINER_MSHUTDOWN_FUNCTION();
    PHP_GTK_BIN_MSHUTDOWN_FUNCTION();
    PHP_GTK_WINDOW_MSHUTDOWN_FUNCTION();
    PHP_GTK_BUTTON_MSHUTDOWN_FUNCTION();
    PHP_GTK_BOX_MSHUTDOWN_FUNCTION();

    if (php_gtk_widget_once_init_array != NULL) {
        g_array_free(php_gtk_widget_once_init_array, TRUE);
    }

    //zend_hash_destroy(&php_glib_object_handlers);
    zend_hash_destroy(&classes);

	return SUCCESS;
}
/* }}} */



/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(gtk)
{
#if defined(COMPILE_DL_GTK) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(gtk)
{

    PHP_CAIRO_T_RSHUTDOWN_FUNCTION();

    PHP_CAIRO_ANTIALIAS_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_FILL_RULE_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_LINE_CAP_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_LINE_JOIN_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_OPERATOR_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_PATH_DATA_TYPE_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_EXTEND_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_FILTER_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_PATTERN_TYPE_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_REGION_OVERLAP_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_FONT_SLANT_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_FONT_WEIGHT_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_TEXT_CLUSTER_FLAGS_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_FONT_TYPE_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_SUBPIXEL_ORDER_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_HINT_STYLE_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_HINT_METRICS_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_DEVICE_TYPE_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_CONTENT_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_SURFACE_TYPE_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_FORMAT_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_STATUS_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_FT_SYNTHESIZE_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_FT_RSHUTDOWN_FUNCTION();

    PHP_CAIRO_RECTANGLE_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_RECTANGLE_INT_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_PATH_DATA_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_PATH_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_FONT_OPTIONS_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_MATRIX_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_DEVICE_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_FONT_FACE_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_FONT_EXTENTS_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_TEXT_CLUSTER_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_TEXT_EXTENTS_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_SCALED_FONT_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_GLYPH_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_PATTERN_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_SURFACE_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_REGION_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_IMAGE_DATA_T_RSHUTDOWN_FUNCTION();

#if CAIRO_HAS_IMAGE_SURFACE
    //PHP_CAIRO_FORMAT_T_RSHUTDOWN_FUNCTION();
    //PHP_CAIRO_IMAGE_SURFACE_RSHUTDOWN_FUNCTION();
#endif
    PHP_CAIRO_PNG_T_RSHUTDOWN_FUNCTION();
#if CAIRO_HAS_SVG_SURFACE
    PHP_CAIRO_SVG_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_SVG_VERSION_T_RSHUTDOWN_FUNCTION();
#endif

#if CAIRO_VERSION >= 11600
    //PHP_CAIRO_PDF_METADATA_T_RSHUTDOWN_FUNCTION(NULL, NULL);
#endif

    PHP_G_STR_RSHUTDOWN_FUNCTION();
    PHP_G_HASH_TABLE_RSHUTDOWN_FUNCTION();
    PHP_G_LIST_RSHUTDOWN_FUNCTION();
    PHP_G_ERROR_RSHUTDOWN_FUNCTION();
    PHP_GLIB_QUARK_RSHUTDOWN_FUNCTION();

    PHP_GOBJECT_OBJECT_RSHUTDOWN_FUNCTION();
    PHP_GOBJECT_SIGNAL_RSHUTDOWN_FUNCTION();
    PHP_GOBJECT_VALUE_RSHUTDOWN_FUNCTION();
    PHP_GOBJECT_PARAM_SPEC_RSHUTDOWN_FUNCTION();


    PHP_GDK_PIXBUF_RSHUTDOWN_FUNCTION();
    PHP_GDK_RECTANGLE_RSHUTDOWN_FUNCTION();

    PHP_GTK_WIDGET_RSHUTDOWN_FUNCTION();
    PHP_GTK_REQUESTED_SIZE_RSHUTDOWN_FUNCTION();
    PHP_GTK_REQUISITION_RSHUTDOWN_FUNCTION();
    PHP_GTK_CONTAINER_RSHUTDOWN_FUNCTION();
    PHP_GTK_BIN_RSHUTDOWN_FUNCTION();
    PHP_GTK_BOX_RSHUTDOWN_FUNCTION();
    PHP_GTK_WINDOW_RSHUTDOWN_FUNCTION();
    PHP_GTK_BUTTON_RSHUTDOWN_FUNCTION();

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(gtk)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "gtk support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */



/* {{{ gtk_functions[]
 *
 * Every user visible function must have an entry in gtk_functions[].
 */
const zend_function_entry gtk_functions[] = {
    PHP_GTK_FE(confirm_gtk_compiled,	arginfo_confirm_gtk_compiled)		     /* For testing, remove later. */
    PHP_CAIRO_T_FE()
    PHP_CAIRO_ANTIALIAS_T_FE()
    PHP_CAIRO_FILL_RULE_T_FE()
    PHP_CAIRO_LINE_CAP_T_FE()
    PHP_CAIRO_LINE_JOIN_T_FE()
    PHP_CAIRO_OPERATOR_T_FE()
    PHP_CAIRO_PATH_DATA_TYPE_T_FE()
    PHP_CAIRO_EXTEND_T_FE()
    PHP_CAIRO_FILTER_T_FE()
    PHP_CAIRO_PATTERN_TYPE_T_FE()
    PHP_CAIRO_REGION_OVERLAP_T_FE()
    PHP_CAIRO_FONT_SLANT_T_FE()
    PHP_CAIRO_FONT_WEIGHT_T_FE()
    PHP_CAIRO_TEXT_CLUSTER_FLAGS_T_FE()
    PHP_CAIRO_FONT_TYPE_T_FE()
    PHP_CAIRO_SUBPIXEL_ORDER_T_FE()
    PHP_CAIRO_HINT_STYLE_T_FE()
    PHP_CAIRO_HINT_METRICS_T_FE()
    PHP_CAIRO_DEVICE_TYPE_T_FE()
    PHP_CAIRO_CONTENT_T_FE()
    PHP_CAIRO_SURFACE_TYPE_T_FE()
    PHP_CAIRO_FORMAT_T_FE()
    PHP_CAIRO_STATUS_T_FE()
    PHP_CAIRO_RECTANGLE_T_FE()
    PHP_CAIRO_RECTANGLE_INT_T_FE()
    PHP_CAIRO_PATH_DATA_T_FE()
    PHP_CAIRO_PATH_T_FE()
    PHP_CAIRO_FONT_OPTIONS_T_FE()
    PHP_CAIRO_MATRIX_T_FE()
    PHP_CAIRO_DEVICE_T_FE()
    PHP_CAIRO_FONT_FACE_T_FE()
    PHP_CAIRO_FONT_EXTENTS_T_FE()
    PHP_CAIRO_TEXT_CLUSTER_T_FE()
    PHP_CAIRO_TEXT_EXTENTS_T_FE()
    PHP_CAIRO_SCALED_FONT_T_FE()
    PHP_CAIRO_FT_SYNTHESIZE_T_FE()
    PHP_CAIRO_FT_FE()
    PHP_CAIRO_GLYPH_T_FE()
    PHP_CAIRO_PATTERN_T_FE()
    PHP_CAIRO_SURFACE_T_FE()
    PHP_CAIRO_REGION_T_FE()
    PHP_CAIRO_IMAGE_DATA_T_FE()
    PHP_CAIRO_RASTER_SOURCE_FE()

    PHP_CAIRO_TRANSFORMS_FE()

#if CAIRO_HAS_IMAGE_SURFACE
    //PHP_CAIRO_FORMAT_T_FE()
    PHP_CAIRO_IMAGE_SURFACE_FE()
#endif
    PHP_CAIRO_PNG_T_FE()
#if CAIRO_HAS_SVG_SURFACE
    PHP_CAIRO_SVG_FE()
    PHP_CAIRO_SVG_VERSION_T_FE()
#endif
#if CAIRO_VERSION >= 11600
    //PHP_CAIRO_PDF_METADATA_T_FE(NULL, NULL);
#endif

    PHP_G_STR_FE()
    PHP_G_HASH_TABLE_FE()
    PHP_G_LIST_FE()
    PHP_G_ERROR_FE()
    PHP_GLIB_QUARK_FE()

    PHP_GOBJECT_OBJECT_FE()
    PHP_GOBJECT_SIGNAL_FE()
    PHP_GOBJECT_VALUE_FE()
    PHP_GOBJECT_PARAM_SPEC_FE()

    PHP_GDK_PIXBUF_FE()
    PHP_GDK_RECTANGLE_FE()

    PHP_GTK_WIDGET_FE()
    PHP_GTK_REQUISITION_FE()
    PHP_GTK_CONTAINER_FE()
    PHP_GTK_BIN_FE()
    PHP_GTK_BOX_FE()
    PHP_GTK_WINDOW_FE()
    PHP_GTK_BUTTON_FE()
    PHP_GTK_MAIN_FE()


    PHP_FE_END	/* Must be the last line in gtk_functions[] */
};
/* }}} */



/* {{{ gtk_module_entry
 */
zend_module_entry gtk_module_entry = {
	STANDARD_MODULE_HEADER,
	"gtk",
	gtk_functions,
    PHP_MINIT(gtk),// zm_startup_gtk callback
	PHP_MSHUTDOWN(gtk),
	PHP_RINIT(gtk),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(gtk),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(gtk),
	PHP_GTK_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/*}}} */



#ifdef COMPILE_DL_GTK
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(gtk)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

