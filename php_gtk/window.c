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

#include "window.h"

#include "php_gdk/pixbuf.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_gtk_window_class_entry;
//HashTable             php_gtk_window_prop_handlers;
zend_object_handlers  php_gtk_window_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry php_gtk_window_methods[] = {
    PHP_ME(gtk_window, __construct, arginfo_gtk_window___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/
static void  php_gtk_window_unset_property(zval *object, zval *member, void **cache_slot);
static void  php_gtk_window_write_property(zval *object, zval *member, zval *value, void **cache_slot);
static zval* php_gtk_window_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv);
static char* php_gtk_window_dump(php_gtk_window *list, int tab);

static void
php_gtk_window_unset_dimension(zval *object, zval *offset) {
    //php_gobject *list = ZVAL_GET_PHP_GTK_WINDOW(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
        // @TODO
        //zend_hash_index_del(list->prop_handler, );
        // php_gobject
        break;
    case IS_STRING:
        php_gtk_window_unset_property(object, offset, &cache);
        break;
    default:
        break;
    }
}

static void
php_gtk_window_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_gtk_window_write_property(object, &member, value, &cache);
}

static zval*
php_gtk_window_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
        return NULL;
    }

    php_gtk_window *intern = ZVAL_GET_PHP_GTK_WINDOW(object);
    php_gtk_window *list;
    void *cache=NULL;

    if (Z_TYPE_P(offset)==IS_LONG) {
        ZVAL_NULL(rv);
        return rv;
    } else if (Z_TYPE_P(offset)==IS_STRING) {
        return php_gtk_window_read_property(object, offset, type, &cache, rv);
    } else {
        // error
    }

    return rv;
} /* }}} end php_g_hash_table_read_dimension */

static int
php_gtk_window_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

/* updates *count to hold the number of elements present and returns SUCCESS.
 * Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_gtk_window_count_elements(zval *object, zend_long *count) {

    *count = 0;

    return SUCCESS;
}

static int
php_gtk_window_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}

static HashTable*
php_gtk_window_get_properties(zval *object){
    php_gtk_window  *self =  ZVAL_GET_PHP_GTK_WINDOW(object);
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(self);
    HashTable *props = gobject->properties;
    if (props==NULL) {
        ALLOC_HASHTABLE(gobject->properties);
        props = gobject->properties;
    } else {
        // TODO: rebuild the props( update)
        return props;// Else leaks : zend_hash_next_index_insert
    }

    /*
    zend_long length = php_gtk_window_length(self);

    zend_hash_init(props, length, NULL, ZVAL_PTR_DTOR, 1);

    zval data;

    php_gtk_window *it;
    for(it=php_gtk_window_first(self); it; it = it->next){
        ZVAL_COPY(&data, &it->data);
        zend_hash_next_index_insert(props, &data);
    }
    */

    return props;
}

static HashTable*
php_gtk_window_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_gtk_window  *obj =  ZVAL_GET_PHP_GTK_WINDOW(object);
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(obj);
    HashTable   *debug_info,
                *std_props;
    zend_string *string_key = NULL;
    zval *value;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    ZEND_HASH_FOREACH_STR_KEY_VAL(gobject->std.properties, string_key, value) {
        zend_hash_add(debug_info, string_key, value);
    } ZEND_HASH_FOREACH_END();

    /*
    zval prev; ZVAL_SET_PHP_GTK_WINDOW(&prev, obj->prev);
    zend_hash_str_update(debug_info, "prev", sizeof("prev")-1, &prev);

    zval data; ZVAL_COPY(&data, &obj->data);
    zend_hash_str_update(debug_info, "data", sizeof("data")-1, &data);

    zval next; ZVAL_SET_PHP_GTK_WINDOW(&next, obj->next);
    zend_hash_str_update(debug_info, "next", sizeof("next")-1, &next);
    */

    return debug_info;
}
/* }}} */

static void
php_gtk_window_unset_property(zval *object, zval *member, void **cache_slot) {
    php_gtk_window *obj = ZVAL_GET_PHP_GTK_WINDOW(object);
    zend_string *member_str = zval_get_string(member);
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}

/* {{{ php_gtk_window_write_property */
static void
php_gtk_window_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_gtk_window *obj = ZVAL_GET_PHP_GTK_WINDOW(object);
    zend_string *member_str = zval_get_string(member);
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->write_property(object, member, value, cache_slot);

    zend_string_release(member_str);
}
/* }}} */

static zval zval_ret;
/* {{{ gtk_read_property */
static zval*
php_gtk_window_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_gtk_window *obj = ZVAL_GET_PHP_GTK_WINDOW(object);
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    /*
    if (zend_string_equals_literal(member_str, "next")) {
        if (NULL==obj->next) {
            ZVAL_NULL(&zval_ret);
            return &zval_ret;
        }
        ZVAL_OBJ(&zval_ret, &obj->next->std);
        return &zval_ret;
    }
    if (zend_string_equals_literal(member_str, "prev")) {
        if (NULL==obj->prev) {
            ZVAL_NULL(&zval_ret);
            return &zval_ret;
        }
        ZVAL_OBJ(&zval_ret, &obj->prev->std);
        return &zval_ret;
    }
    if (zend_string_equals_literal(member_str, "data")) {
        ZVAL_COPY(&zval_ret, &obj->data);
        return &zval_ret;
    }
    */

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    retval = std_hnd->read_property(object, member, type, cache_slot, rv);

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ php_gtk_window_free_object */
static void
php_gtk_window_free_object(zend_object *object)
{
    php_gtk_window *intern = ZOBJ_TO_PHP_GTK_WINDOW(object);
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(intern);
    TRACE("php_gtk_window_free_object(\"%s\") / %d\n", intern->data.value.str->val, object->gc.refcount);

#if 0
    if (gobject->ptr && G_IS_OBJECT(gobject->ptr)) {
        //g_object_unref(gobject->ptr);
        g_clear_object(&gobject->ptr);// Window is destroyed befor zval
    }
#endif
    if (gobject->properties!=NULL) {
        zend_hash_destroy(gobject->properties);
        efree(gobject->properties);
        gobject->properties=NULL;
    }

    zend_object_std_dtor(&gobject->std);
    //efree(intern);
}
/* }}} php_gtk_window_free_object */

static void
php_gtk_window_dtor_object(zend_object *obj) {
    php_gtk_window *intern = ZOBJ_TO_PHP_GTK_WINDOW(obj);
    TRACE("php_gtk_window_dtor_object(\"%s\") / %d\n", intern->data.value.str->val, obj->gc.refcount);

    /*
    if (!ZVAL_IS_NULL(&intern->data)) {
        Z_TRY_DELREF_P(&intern->data);
        //zval_ptr_dtor(&intern->data);
        //g_print("zend_string: %p\n", intern->data.value.str);
        //g_print("            (%d)\n", intern->data.value.str->gc.refcount);
        //zend_string_release(intern->data.value.str);
        ZVAL_NULL(&intern->data);
    }

    if (intern->next) {
        zend_object_release(&intern->next->std);
        intern->next=NULL;
    }

    if (intern->prev!=NULL) {
        zend_object_release(&intern->prev->std);
        intern->prev=NULL;
    }
    */

}

/* {{{ php_gtk_window_create_object */
static zend_object*
php_gtk_window_create_object(zend_class_entry *class_type)
{
    php_gtk_window *intern = ecalloc(1, sizeof(php_gtk_window) + zend_object_properties_size(class_type));
    php_gobject_object *gobject =  PHP_GTK_WINDOW_TO_PHP_G_OBJECT(intern);

    zend_object_std_init(&gobject->std, class_type);
    object_properties_init(&gobject->std, class_type);

    gobject->ptr = NULL;
    gobject->properties = NULL;

    gobject->std.handlers = &php_gtk_window_handlers;

    TRACE("php_gtk_window_create_object(%p) / %d\n", &gobject->std, gobject->std.gc.refcount);
    return &gobject->std;
}
/* }}} php_gtk_window_create_object */

/*
static void php_gtk_window_dtor_prop_handler(zval *zv)
{
    free(Z_PTR_P(zv));
}
*/

static zend_object_handlers*
php_gtk_window_get_handlers()
{
    memcpy(&php_gtk_window_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_gtk_window_handlers.offset = PHP_GTK_WINDOW_OFFSET;
    //php_gtk_window_handlers.clone_obj;
    //php_gtk_window_handlers.compare;
    //php_gtk_window_handlers.compare_objects;
    //php_gtk_window_handlers.get_constructor;
    php_gtk_window_handlers.dtor_obj = php_gtk_window_dtor_object;
    php_gtk_window_handlers.free_obj = php_gtk_window_free_object;
    php_gtk_window_handlers.read_property = php_gtk_window_read_property;
    php_gtk_window_handlers.write_property = php_gtk_window_write_property;
    php_gtk_window_handlers.unset_property = php_gtk_window_unset_property;
    //php_gtk_window_handlers.get_property_ptr_ptr = php_gtk_window_get_property_ptr_ptr;

    php_gtk_window_handlers.get_debug_info = php_gtk_window_get_debug_info;
    php_gtk_window_handlers.get_properties = php_gtk_window_get_properties;//get_properties_for TODO php 8.0
    //php_gtk_window_handlers.set = php_gtk_window_set;
    php_gtk_window_handlers.cast_object = php_gtk_window_cast_object;

    php_gtk_window_handlers.count_elements = php_gtk_window_count_elements;
    php_gtk_window_handlers.has_dimension = php_gtk_window_has_dimension;
    php_gtk_window_handlers.read_dimension = php_gtk_window_read_dimension;
    php_gtk_window_handlers.unset_dimension = php_gtk_window_unset_dimension;
    php_gtk_window_handlers.write_dimension = php_gtk_window_write_dimension;


    return &php_gtk_window_handlers;
}



/*----------------------------------------------------------------------+
| PHP_MINIT                                                            |
+----------------------------------------------------------------------*/
/*{{{ php_gtk_window_class_init */
zend_class_entry*
php_gtk_window_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gtk_window_get_handlers();
    //INIT_NS_CLASS_ENTRY((*ce), "Gnome\\G", "Object", php_gtk_window_methods);
    INIT_CLASS_ENTRY((*container_ce), "GtkWindow", php_gtk_window_methods);
    php_gtk_window_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_gtk_window_class_entry->create_object = php_gtk_window_create_object;
    /*
    zend_hash_init(&php_gtk_window_prop_handlers, 0, NULL, php_gtk_window_dtor_prop_handler, 1);
    php_gtk_window_register_prop_handler(&php_gtk_window_prop_handlers, "prev", sizeof("prev")-1, php_gtk_window_read_prev, php_gtk_window_write_prev);
    php_gtk_window_register_prop_handler(&php_gtk_window_prop_handlers, "data", sizeof("data")-1, php_gtk_window_read_data, php_gtk_window_write_data);
    php_gtk_window_register_prop_handler(&php_gtk_window_prop_handlers, "next", sizeof("next")-1, php_gtk_window_read_next, php_gtk_window_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_gtk_window_prop_handlers);
    */

    return php_gtk_window_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/


/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
void
php_gtk_window_new(php_gtk_window *self, zend_long type) {
    php_gobject_object *object = PHP_GTK_WINDOW_TO_PHP_G_OBJECT(self);

    GtkWidget *window = gtk_window_new(type);
    object->ptr = G_OBJECT(window);
    g_object_set_data(G_OBJECT(window), "zend_object", &object->std);


    //zend_make_compiled_string_description(const char *name) /* {{{ */
    const char *cur_filename = zend_get_executed_filename();
    gchar *file_name = g_path_get_basename (cur_filename);
    gtk_window_set_title(GTK_WINDOW(window), file_name);
    g_free(file_name);

    //gtk_window_set_icon_from_file(GTK_WINDOW(window), "/home/dev/Images/logo-6.png", NULL);
    //gtk_window_set_icon_from_file(GTK_WINDOW(window), "/home/dev/Images/php-icon.png", NULL);
    /*
    gtk_window_set_icon_from_file(GTK_WINDOW(window), "/home/dev/Images/vigne/vigne-transparent.png", NULL);

    GList *list = gtk_window_get_icon_list(GTK_WINDOW(window));
    g_print("list: %p, %d\n", list, g_list_length(list));
    */

#if 0
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *titlebar = gtk_header_bar_new();
    gtk_window_set_titlebar (window, titlebar);
    gtk_widget_show(titlebar);
    //gtk_widget_set_visible(titlebar, FALSE);

    char *css = "window, window.background, *>.titlebar, >* {"
                "border-radius: 30px;"
            "}"
            ;

    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    //gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider),"styles.css",NULL);
    gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider), css, strlen(css), NULL);

    GtkStyleContext *context;
    context = gtk_widget_get_style_context(window);
    gtk_style_context_add_class(context,"my");

    //gtk_window_set_interactive_debugging (TRUE);
#endif
}



/*----------------------------------------------------------------------+
| PHP_METHOD                                                           |
+----------------------------------------------------------------------*/

/* {{{ GObject::__construct() */
PHP_METHOD(gtk_window, __construct)
{

    zend_object *zobj = Z_OBJ_P(getThis());
    php_gtk_window *self = ZOBJ_TO_PHP_GTK_WINDOW(zobj);

    php_gtk_window_new(self, GTK_WINDOW_TOPLEVEL);

}
/* }}} */

/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/

/* {{{ proto GObject gtk_window_new(GObject list, mixed data) */
PHP_FUNCTION(gtk_window_new)
{
    zval *ztype = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(ztype)
    ZEND_PARSE_PARAMETERS_END();

    zend_long type = ztype==NULL || ZVAL_IS_NULL(ztype) || Z_TYPE_P(ztype)!=IS_LONG ? GTK_WINDOW_TOPLEVEL : ztype->value.lval;

    zend_object *z_window = php_gtk_window_create_object(php_gtk_window_class_entry);
    php_gtk_window *gtk_window = ZOBJ_TO_PHP_GTK_WINDOW(z_window);

    php_gtk_window_new(gtk_window, type);


    //GC_REFCOUNT(z_window)++;
    RETURN_OBJ(z_window);
}/* }}} */

/* {{{ proto GObject gtk_window_new(GObject list, mixed data) */
PHP_FUNCTION(gtk_window_set_icon)
{
    zval *zwindow = NULL;
    zval *zpixbuf = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zwindow)
        Z_PARAM_ZVAL(zpixbuf)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_window *window = ZVAL_IS_PHP_GTK_WINDOW(zwindow) ? ZVAL_GET_PHP_GTK_WINDOW(zwindow) : NULL;
    php_gdk_pixbuf *pixbuf = ZVAL_IS_PHP_GDK_PIXBUF(zpixbuf) ? ZVAL_GET_PHP_GDK_PIXBUF(zpixbuf) : NULL;

    gtk_window_set_icon(GTK_WINDOW(PHP_GTK_WINDOW_TO_PHP_G_OBJECT(window)->ptr),
                        GDK_PIXBUF(pixbuf->parent_instance.ptr));

}/* }}} */
