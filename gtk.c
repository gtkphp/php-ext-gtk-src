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

/// include "php_glib.h"
#include "php_cairo/cairo.h"
#include "php_cairo/path.h"
#include "php_cairo/matrix.h"
#include "php_cairo/png.h"
#include "php_cairo/surface.h"
#include "php_cairo/image-surface.h"

/// include "php_glib.h"
#include "php_glib/hash-table.h"
#include "php_glib/list.h"
#include "php_glib/quark.h"
#include "php_glib/error.h"

/// include "php_gobject.h"
#include "php_gobject/object.h"
#include "php_gobject/signal.h"

/// include "php_gdk.h"
#include "php_gdk/pixbuf.h"
#include "php_gdk/rectangle.h"

/// include "php_gtk.h"
#include "php_gtk/widget.h"
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

static void
print_g_list(GList *list) {
    GList *it;
    for(it = list/*g_list_first(list)*/; it; it = it->next) {
        g_print("GList{prev: %p, %s, next: %p}\n", it->prev, (char *)it->data, it->next);
    }
}
/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_gtk_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_gtk_compiled)
{
	char *arg = NULL;
    size_t arg_len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

//#define TEST_NUM_1 "04-g_list-0-insert.c"
//#define TEST_NUM_2 "04-g_list-1-insert.c"
//#define TEST_NUM_3 "04-g_list-2-insert.c"

//#define TEST_NUM TEST_NUM_1

    //$error=new GError();// Must be null


    /*
    GError *error=NULL;
    g_set_error(&error, g_quark_from_string("MY"), 403, "'%s' do not exist", "Application", NULL);
    g_set_error(&error, g_quark_from_string("YOU"), 404, "'%s' unvalid", "Application", NULL);
    //g_prefix_error(&error, "GNOME", NULL);
    g_print("%s\n", error->message);
    */


#if 0
    // Check the bahavior of GList
    gchar *key1 = "key1";
    gchar *key2 = "key2";
    gchar *key3 = "key3";
    gchar *key4 = "key4";

    typedef GList GList_CStr;
    GList_CStr *first=NULL, *list = NULL;


    first = g_list_append(NULL, key1);
    first = g_list_append(first, key2);
    list = first->next;
    first = g_list_remove_link(first, list);
    g_print("%p\n", first);// 600
    print_g_list(list);

    /*
    list = g_list_insert(list, key1, 0);
    list = g_list_insert(list, key2, 1);
    list = g_list_insert(list->next, key3, 0);
    //print_g_list(g_list_first(list));
    print_g_list(list);
    */

    /*
    list = g_list_insert(list, key1, 0);
    list = g_list_insert(list, key2, 1);
    list = g_list_insert(list, key3, 2);
    list = g_list_insert(list, key4, 3);
    print_g_list(list);//g_list_first()
    */

    /*
    list = g_list_insert(list, key1, 0);
    list = g_list_insert(list, key2, 0);
    list = g_list_insert(list, key3, 0);
    list = g_list_insert(list, key4, 0);
    print_g_list(g_list_first(list));
    //print_g_list(list);//g_list_first()
    */


    /*
    first = g_list_append(first, key1);
    g_print("%p\n", first);// 600
    first = g_list_append(first, key2);
    g_print("%p\n", first);// 600
    list = g_list_nth(first, 1);
    g_print("%p\n", list);// 620
    list = g_list_append(list, key3);
    g_print("%p\n", list);// 620
    list = g_list_insert(list, "key", 0);
    g_print("%p\n", list);
    */

    /*
    first = list = g_list_append(list, key1);
    g_print("%p\n", list);
    list = g_list_append(list, key2);
    list = g_list_append(list, key3);
    list = g_list_nth(list, 2);
    g_print("%p\n", list);
    list = g_list_insert(list, "key", 0);
    g_print("%p\n", list);
    */


    /*
    list = g_list_prepend(list, key2);
    g_print("%p\n", list);
    list = g_list_prepend(list, key3);
    g_print("%p\n", list);
    */

    /*
    list = g_list_append(list, key1);
    g_print("%p\n", list);
    list = g_list_append(list, key2);
    g_print("%p\n", list);
    list = g_list_nth(list, 1);
    list = g_list_append(list, key3);
    g_print("%p\n", list);
    */

    //print_g_list(first);

#endif

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "gtk", arg);

	RETURN_STR(strg);
}
/* }}} */



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


extern zend_object_handlers php_glib_object_handlers;


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
                        PHP_CAIRO_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_PATH_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_MATRIX_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_SURFACE_T_MINIT_FUNCTION(&ce, NULL);
                        PHP_CAIRO_IMAGE_SURFACE_T_MINIT_FUNCTION(NULL, NULL);
                        PHP_CAIRO_PNG_T_MINIT_FUNCTION(NULL, NULL);
    //                  PHP_PANGO_MINIT_FUNCTION(&ce);
                        PHP_GLIB_HASH_TABLE_MINIT_FUNCTION(&ce, NULL);
                        PHP_GLIB_LIST_MINIT_FUNCTION(&ce, NULL);
                        PHP_GLIB_ERROR_MINIT_FUNCTION(&ce, NULL);
    gobject_object_ce = PHP_GOBJECT_OBJECT_MINIT_FUNCTION(&ce, NULL);
                        PHP_GOBJECT_SIGNAL_MINIT_FUNCTION(&ce, NULL);
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

    //REGISTER_GTK_ENUM(GTK_ORIENTATION_HORIZONTAL);
    zend_register_long_constant("GTK_ORIENTATION_HORIZONTAL", sizeof("GTK_ORIENTATION_HORIZONTAL")-1,
                                GTK_ORIENTATION_HORIZONTAL, CONST_CS | CONST_PERSISTENT, module_number);
    //REGISTER_GTK_ENUM(GTK_ORIENTATION_VERTICAL);
    zend_register_long_constant("GTK_ORIENTATION_VERTICAL", sizeof("GTK_ORIENTATION_VERTICAL")-1,
                                GTK_ORIENTATION_VERTICAL, CONST_CS | CONST_PERSISTENT, module_number);

	return SUCCESS;
}
/* }}} */




/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(gtk)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/

    PHP_CAIRO_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_PATH_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_MATRIX_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_SURFACE_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_IMAGE_SURFACE_T_MSHUTDOWN_FUNCTION();
    PHP_CAIRO_PNG_T_MSHUTDOWN_FUNCTION();

    PHP_GLIB_LIST_MSHUTDOWN_FUNCTION();
    PHP_GLIB_HASH_TABLE_MSHUTDOWN_FUNCTION();
    PHP_GLIB_ERROR_MSHUTDOWN_FUNCTION();
    PHP_GLIB_QUARK_MSHUTDOWN_FUNCTION();

    PHP_GOBJECT_OBJECT_MSHUTDOWN_FUNCTION();
    PHP_GOBJECT_SIGNAL_MSHUTDOWN_FUNCTION();

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
    PHP_CAIRO_PATH_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_MATRIX_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_SURFACE_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_IMAGE_SURFACE_T_RSHUTDOWN_FUNCTION();
    PHP_CAIRO_PNG_T_RSHUTDOWN_FUNCTION();

    PHP_GLIB_HASH_TABLE_RSHUTDOWN_FUNCTION();
    PHP_GLIB_LIST_RSHUTDOWN_FUNCTION();
    PHP_GLIB_ERROR_RSHUTDOWN_FUNCTION();
    PHP_GLIB_QUARK_RSHUTDOWN_FUNCTION();

    PHP_GOBJECT_OBJECT_RSHUTDOWN_FUNCTION();
    PHP_GOBJECT_SIGNAL_RSHUTDOWN_FUNCTION();

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
    PHP_FE(confirm_gtk_compiled,	NULL)		     /* For testing, remove later. */
    PHP_CAIRO_T_FE()
    PHP_CAIRO_PATH_T_FE()
    PHP_CAIRO_MATRIX_FE()
    PHP_CAIRO_SURFACE_T_FE()
    PHP_CAIRO_IMAGE_SURFACE_T_FE()
    PHP_CAIRO_PNG_T_FE()

    PHP_GLIB_LIST_FE()
    PHP_GLIB_HASH_TABLE_FE()
    PHP_GLIB_ERROR_FE()
    PHP_GLIB_QUARK_FE()

    PHP_GOBJECT_OBJECT_FE()
    PHP_GOBJECT_SIGNAL_FE()

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

