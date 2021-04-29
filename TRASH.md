config.m4

--------------------------------------------------------------
- Reflection for override GtkWidget::get_prefered_width
--------------------------------------------------------------
Howto do it for GtkWidget from Module ?
- Binding php for module
- GIntrospection ?

GtkWidgetClass *klass;
origin = klass->get_prefered_width;
klass->get_prefered_width = function() {

  zend_call_user_function();
    -> parent::get_prefered_width()
         -> origin();
}

#if 0
    zend_object *zobj = Z_OBJ_P(getThis());
    zval obj;
    zend_reflection_class_factory(zobj->ce, &obj);
    zend_class_entry *ref = obj.value.obj->ce;
    g_print("reflection: %s\n", ref->name->val);


    zend_string *lc_method_name = zend_string_init("getDocComment", strlen("getDocComment"), 0);
    zend_function *fbc;
    fbc = zend_hash_find_ptr(&ref->function_table, lc_method_name);

    zval retval_ptr;
    zval function_name; ZVAL_STR(&function_name, lc_method_name);
    uint32_t param_count = 0;
    zval params[0];
    int no_separation = 0;
    int ret = _call_user_function_ex(&obj, &function_name, &retval_ptr, param_count, params, no_separation);
    g_print("%d == %d\n", IS_STRING, Z_TYPE(retval_ptr));
    g_print("%s\n", retval_ptr.value.str->val);


    zend_function *fdecl;
    ZEND_HASH_FOREACH_PTR(&zobj->ce->function_table, fdecl) {
        g_print("  + %s\n", fdecl->common.function_name->val);
        // $reflector->getMethod('get_preferred_width')->getDocComment();
    } ZEND_HASH_FOREACH_END();
#endif

--------------------------------------------------------------
-
--------------------------------------------------------------

PKG_CONFIG_PATH="" && configure --with-gtk=Gnome\Gtk,4

```
define([GTK_HELP_TEXT],[[
             ^  ^-------- Use the Gtk+ version installed on your systeme.
             |              - version can be one of: 2, 3, 4.
             +----------- Associate the gtk extension with the namespace of your choice.
                            - ns can be any valide PHP namespace.
                          Exemple, use Gtk+3 with "Gnome" namespace:
                            --with-gtk=Gnome,3
                          Exemple, use Gtk+2 without namespace:
                            --with-gtk=,2]])

PHP_ARG_WITH(gtk, for gtk support,
dnl Make sure that the comment is aligned:
[  --with-gtk=ns,version  Include gtk support]GTK_HELP_TEXT)

ext_ns="`echo $PHP_GTK | cut -d, -f1`"
gtk_version="`echo $PHP_GTK | cut -d, -f2`"

PHP_NEW_EXTENSION(gtk, gtk.c $glib_sources $g_sources, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1 -DGTK_NS="\\\"$ext_ns\\\"")
```
refactor `if test "$PHP_GTK" = "yes"`


##########################################################################
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
  | Author: Sergio de Vasconcelos                                        |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_GLIB_H
#define PHP_GLIB_H

#include <glib.h>

#ifdef PHP_WIN32
#	ifdef GLIB_EXPORTS
#		define PHP_GLIB_EXPORT __declspec(dllexport)
#	elif !defined(DOM_LOCAL_DEFINES) /* Allow to counteract LNK4049 warning. */
#		define PHP_GLIB_EXPORT __declspec(dllimport)
#	else
#		define PHP_GLIB_EXPORT
#	endif /* GLIB_EXPORTS */
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_GLIB_EXPORT __attribute__ ((visibility("default")))
#elif defined(PHPAPI)
#   define PHP_GLIB_EXPORT PHPAPI
#else
#   define PHP_GLIB_EXPORT
#endif

#define TRACE()
//#define TRACE() g_print("%s\n", __FUNCTION__)


extern zend_object_handlers php_glib_handlers;

typedef enum _PhpGlibType {
    PHP_GLIB_NONE_TYPE = 0x00,
    /* ------ */
    PHP_GLIB_G_HASH_TABLE_TYPE,
    PHP_GLIB_G_LIST_TYPE,
    PHP_GLIB_G_OBJECT_TYPE,
    PHP_GLIB_GDK_EVENT_TYPE,
    PHP_GLIB_GTK_OBJECT_TYPE,// UnownedType...
    /* ------ */
    PHP_GLIB_LAST_TYPE,
} PhpGlibType;


typedef struct _php_glib_object {
    void *ptr;
    PhpGlibType type;

    HashTable *prop_handler;//TODO remove
    zend_object std;
} php_glib_object;

/**
struct php_g_object {
    php_glib_object
}
struct php_gtk_widget {
    php_g_object parent_instance;
    // parent;
    // previousSibling;
    // nextSibling;
    // children;
    php_g_object
}
*/

#define PHP_GLIB_OBJECT_FROM_STD(ptr) \
    (php_glib_object*) (((void*)(ptr))-(sizeof(php_glib_object) - sizeof(zend_object)))

#define PHP_GLIB_OBJECT(ptr)  ((php_glib_object*)(ptr))

typedef int (*glib_read_t)(php_glib_object *obj, zval *retval);
typedef int (*glib_write_t)(php_glib_object *obj, zval *newval);

typedef struct _php_glib_prop_handler {
    glib_read_t read_func;
    glib_write_t write_func;
} php_glib_prop_handler;


zend_object     *php_glib_create_object(zend_class_entry *class_type);
php_glib_object *php_glib_from_zend(zend_object *obj);

void             php_glib_copy_prop_handler(zval *zv);
void             php_glib_dtor_prop_handler(zval *zv);

zend_object_handlers *php_glib_get_obj_handlers(void);
php_glib_object      *php_glib_set_class(zend_class_entry *class_type, zend_bool hash_copy);
void                  php_glib_free_storage(zend_object *object);
zval *php_glib_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot);
void  php_glib_register_prop_handler(HashTable *prop_handler, char *name, size_t name_len, glib_read_t read_func, glib_write_t write_func);
zval *php_glib_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv);
void  php_glib_write_property(zval *object, zval *member, zval *value, void **cache_slot);
int   php_glib_read_na(php_glib_object *obj, zval *retval);
int   php_glib_write_na(php_glib_object *obj, zval *newval);

HashTable *php_glib_get_debug_info(zval *object, int *is_temp);

zend_class_entry *php_glib_class_init(zend_class_entry *ce);
PHP_GLIB_EXPORT zend_object_handlers *php_glib_object_get_handlers();

#endif	/* PHP_GLIB_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */


##########################################################################

#include <php.h>
#include <php_ini.h>
#include <zend_interfaces.h>
#include <ext/standard/info.h>

#include "glib.h"

extern zend_module_entry gtk_module_entry;
extern HashTable classes;

zend_class_entry *php_glib_class_entry;
zend_object_handlers php_glib_object_handlers;

void php_glib_copy_prop_handler(zval *zv) /* {{{ */
{
        TRACE();
    php_glib_prop_handler *hnd = Z_PTR_P(zv);
    Z_PTR_P(zv) = malloc(sizeof(php_glib_prop_handler));
    memcpy(Z_PTR_P(zv), hnd, sizeof(php_glib_prop_handler));
}
/* }}} */

void php_glib_dtor_prop_handler(zval *zv) /* {{{ */
{
        TRACE();
    free(Z_PTR_P(zv));
}

// @see MACRO like in PHP 8.0
php_glib_object*
php_glib_from_zend(zend_object *obj) {
        TRACE();
    return (php_glib_object*)((char*)(obj) - XtOffsetOf(php_glib_object, std));
}

/* {{{ php_glib_create_object */
zend_object *php_glib_create_object(zend_class_entry *class_type)
{
        TRACE();
    php_glib_object *intern = php_glib_set_class(class_type, 1);
    intern->type = PHP_GLIB_NONE_TYPE;
    intern->std.handlers = &php_glib_object_handlers;
    return &intern->std;
}
/* }}} */

php_glib_object* php_glib_set_class(zend_class_entry *class_type, zend_bool hash_copy) /* {{{ */
{
        TRACE();
    php_glib_object *intern = ecalloc(1, sizeof(php_glib_object) + zend_object_properties_size(class_type));
    zend_class_entry *base_class = class_type;
    while ((   base_class->type != ZEND_INTERNAL_CLASS
            || base_class->info.internal.module->module_number != gtk_module_entry.module_number
           )
           && base_class->parent != NULL) {
        base_class = base_class->parent;
    }

    intern->prop_handler = zend_hash_find_ptr(&classes, base_class->name);

    zend_object_std_init(&intern->std, class_type);

    if (hash_copy) {
        object_properties_init(&intern->std, class_type);
    }

    return intern;
}
/* }}} */



/* {{{ dom_objects_free_storage */
void php_glib_free_storage(zend_object *object)
{
        TRACE();

    php_glib_object *intern = php_glib_from_zend(object);
#if defined(__GNUC__) && __GNUC__ >= 3
    int retcount __attribute__((unused)); /* keep compiler quiet */
#else
    int retcount;
#endif

    zend_object_std_dtor(&intern->std);
    efree(intern);
// FIXME
#if 0
    if (intern->ptr != NULL ) {

        /*
        if (((xmlNodePtr) ((php_libxml_node_ptr *)intern->ptr)->node)->type != XML_DOCUMENT_NODE && ((xmlNodePtr) ((php_libxml_node_ptr *)intern->ptr)->node)->type != XML_HTML_DOCUMENT_NODE) {
            php_libxml_node_decrement_resource((php_libxml_node_object *) intern);
        } else {
            php_libxml_decrement_node_ptr((php_libxml_node_object *) intern);
            retcount = php_libxml_decrement_doc_ref((php_libxml_node_object *)intern);
        }
        */
        intern->ptr = NULL;
    }
#endif
}
/* }}} */

zval *php_glib_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
        TRACE();
    php_glib_object *obj = php_glib_from_zend(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    zval *retval = NULL;

    g_print("%s\n", "php_glib_get_property_ptr_ptr");
    if (!obj->prop_handler || !zend_hash_exists(obj->prop_handler, member_str)) {
        zend_object_handlers *std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->get_property_ptr_ptr(object, member, type, cache_slot);
    }

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ gtk_read_property */
zval *php_glib_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
        TRACE();
    php_glib_object *obj = php_glib_from_zend(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    php_glib_prop_handler *hnd = NULL;
    g_print("%s(%s)\n", "php_glib_read_property", member->value.str->val);

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member_str);
    } else if (instanceof_function(obj->std.ce, php_glib_class_entry)) {
        php_error(E_WARNING, "Couldn't fetch %s. Widget no longer exists", ZSTR_VAL(obj->std.ce->name));
    }

    if (hnd) {
        int ret = hnd->read_func(obj, rv);
        if (ret == SUCCESS) {
            retval = rv;
        } else {
            retval = &EG(uninitialized_zval);
        }
    } else {
        zend_object_handlers *std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->read_property(object, member, type, cache_slot, rv);
    }

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ gtk_write_property */
void php_glib_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
        TRACE();
    php_glib_object *obj = php_glib_from_zend(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    php_glib_prop_handler *hnd = NULL;

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member_str);
    }
    if (hnd) {
        hnd->write_func(obj, value);
    } else {
        zend_object_handlers *std_hnd = zend_get_std_object_handlers();
        std_hnd->write_property(object, member, value, cache_slot);
    }

    zend_string_release(member_str);
}
/* }}} */



/* {{{ dom_read_na */
int php_glib_read_na(php_glib_object *obj, zval *retval)
{
        TRACE();
    zend_throw_error(NULL, "Cannot read property");
    return FAILURE;
}
/* }}} */

/* {{{ dom_write_na */
int php_glib_write_na(php_glib_object *obj, zval *newval)
{
        TRACE();
    zend_throw_error(NULL, "Cannot write property");
    return FAILURE;
}
/* }}} */

/* {{{ dom_register_prop_handler */
void php_glib_register_prop_handler(HashTable *prop_handler, char *name, size_t name_len, glib_read_t read_func, glib_write_t write_func)
{
        TRACE();
    php_glib_prop_handler hnd;

    hnd.read_func = read_func ? read_func : php_glib_read_na;
    hnd.write_func = write_func ? write_func : php_glib_write_na;
    zend_hash_str_add_mem(prop_handler, name, name_len, &hnd, sizeof(php_glib_prop_handler));
}
/* }}} */

static HashTable*
php_glib_get_debug_info_helper(zval *object, int *is_temp) /* {{{ */
{
        TRACE();

    php_glib_object *obj =  php_glib_from_zend(Z_OBJ_P(object));
    HashTable              *debug_info,
                           *prop_handlers = obj->prop_handler,
                           *std_props;
    zend_string            *string_key;
    php_glib_prop_handler  *entry;
    zend_string            *object_str;

    *is_temp = 1;

    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    if (!prop_handlers) {
        return debug_info;
    }

    object_str = zend_string_init("(object value omitted)", sizeof("(object value omitted)")-1, 0);

    ZEND_HASH_FOREACH_STR_KEY_PTR(prop_handlers, string_key, entry) {
        zval value;

        if (entry->read_func(obj, &value) == FAILURE || !string_key) {
            continue;
        }

        if (Z_TYPE(value) == IS_OBJECT) {
            zval_dtor(&value);
            ZVAL_NEW_STR(&value, object_str);
            zend_string_addref(object_str);
        }

        zend_hash_add(debug_info, string_key, &value);
    } ZEND_HASH_FOREACH_END();

    zend_string_release(object_str);

    return debug_info;
}
/* }}} */

HashTable*
php_glib_get_debug_info(zval *object, int *is_temp)
{
        TRACE();
    return php_glib_get_debug_info_helper(object, is_temp);
}

zend_object_handlers*
php_glib_object_get_handlers()
{
        TRACE();
        memcpy(&php_glib_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
        php_glib_object_handlers.offset = XtOffsetOf(php_glib_object, std);
        php_glib_object_handlers.free_obj = php_glib_free_storage;
        php_glib_object_handlers.read_property = php_glib_read_property;
        php_glib_object_handlers.write_property = php_glib_write_property;
        php_glib_object_handlers.get_property_ptr_ptr = php_glib_get_property_ptr_ptr;
        php_glib_object_handlers.get_debug_info = php_glib_get_debug_info;

        return &php_glib_object_handlers;
}



##########################################################################































































dnl $Id$
dnl config.m4 for extension gtk

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(gtk, for gtk support,
dnl Make sure that the comment is aligned:
dnl [  --with-gtk             Include gtk support])

dnl Otherwise use enable:

PHP_ARG_WITH(gtk, for gtk support,
dnl Make sure that the comment is aligned:
[  --with-gtk              Include gtk support])

dnl --with-gui-gtk=3,Gnome

if test "$PHP_GTK" != "no"; then
  dnl Write more examples of tests here...

  dnl # get library FOO build options from pkg-config output
  dnl AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  dnl AC_MSG_CHECKING(for libfoo)
  dnl if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists foo; then
  dnl   if $PKG_CONFIG foo --atleast-version 1.2.3; then
  dnl     LIBFOO_CFLAGS=`$PKG_CONFIG foo --cflags`
  dnl     LIBFOO_LIBDIR=`$PKG_CONFIG foo --libs`
  dnl     LIBFOO_VERSON=`$PKG_CONFIG foo --modversion`
  dnl     AC_MSG_RESULT(from pkgconfig: version $LIBFOO_VERSON)
  dnl   else
  dnl     AC_MSG_ERROR(system libfoo is too old: version 1.2.3 required)
  dnl   fi
  dnl else
  dnl   AC_MSG_ERROR(pkg-config not found)
  dnl fi
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBDIR, GTK_SHARED_LIBADD)
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)

  dnl # --with-gtk -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/gtk.h"  # you most likely want to change this
  dnl if test -r $PHP_GTK/$SEARCH_FOR; then # path given as parameter
  dnl   GTK_DIR=$PHP_GTK
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for gtk files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       GTK_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$GTK_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the gtk distribution])
  dnl fi

  dnl # --with-gtk -> add include path
  dnl PHP_ADD_INCLUDE($GTK_DIR/include)

  dnl # --with-gtk -> check for lib and symbol presence
  dnl LIBNAME=gtk # you may want to change this
  dnl LIBSYMBOL=gtk # you most likely want to change this

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $GTK_DIR/$PHP_LIBDIR, GTK_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_GTKLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong gtk lib version or lib not found])
  dnl ],[
  dnl   -L$GTK_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(GTK_SHARED_LIBADD)


  if test -z "$PKG_CONFIG"; then
    AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  fi

  if test -x "$PKG_CONFIG"; then
    dnl using pkg-config output

    AC_MSG_CHECKING(for gtk+-3.0.pc)
    if test "$PHP_GTK" = "yes" -o "$PHP_GTK" = "/usr"; then
      PKNAME=gtk+-3.0
      AC_MSG_RESULT(using default path)
    elif test -r $PHP_GTK/$PHP_LIBDIR/pkgconfig/gtk+-3.0.pc; then
      PKNAME=$PHP_GTK/$PHP_LIBDIR/pkgconfig/gtk+-3.0.pc
      AC_MSG_RESULT(using $PKNAME)
    elif test -r $PHP_GTK/lib/pkgconfig/gtk+-3.0.pc; then
      PKNAME=$PHP_GTK/lib/pkgconfig/gtk+-3.0.pc
      AC_MSG_RESULT(using $PKNAME)
    else
      AC_MSG_RESULT(not found)
      AC_MSG_WARN(Could not find gtk+-3.0.pc. Try without $PHP_GTK or set PKG_CONFIG_PATH)
    fi
  fi

  if test -n "$PKNAME"; then
    AC_MSG_CHECKING(for gtk+ 3.22.30 or greater)
    if $PKG_CONFIG --atleast-version 3.22.30 $PKNAME; then
      gtk_version_full=`$PKG_CONFIG --modversion $PKNAME`
      AC_MSG_RESULT($gtk_version_full)
    else
      AC_MSG_ERROR(gtk+ version 3.22.30 or later is required to compile php with Gtk+ support)
    fi

    GTK_LIBS=`$PKG_CONFIG --libs   $PKNAME`
    GTK_INCL=`$PKG_CONFIG --cflags $PKNAME`
  fi

  PHP_EVAL_LIBLINE($GTK_LIBS, GTK_SHARED_LIBADD)
  PHP_EVAL_INCLINE($GTK_INCL, GTK_SHARED_LIBADD)

  PHP_ADD_INCLUDE($PHP_GTK)

  PHP_SUBST(GTK_SHARED_LIBADD)

  cairo_sources="php_cairo/cairo.c \
                 php_cairo/path-data.c \
                 php_cairo/path.c \
                 php_cairo/matrix.c \
                 php_cairo/png.c \
                 php_cairo/image-surface.c \
                 php_cairo/surface.c "

  doc_sources="php_doc/parser.c \
               php_doc/comment.c "

  glib_sources="php_glib/list.c \
                php_glib/quark.c \
                php_glib/error.c \
                php_glib/hash-table.c"

  gobject_sources="php_gobject/object.c \
                   php_gobject/signal.c"

  gdk_sources="php_gdk/pixbuf.c \
               php_gdk/rectangle.c "

  gtk_sources="php_gtk/widget.c \
               php_gtk/requisition.c \
               php_gtk/requested-size.c \
               php_gtk/container.c \
               php_gtk/bin.c \
               php_gtk/box.c \
               php_gtk/window.c \
               php_gtk/button.c \
               php_gtk/main.c "

  sources="gtk.c"

  ext_ns="`echo \\\"$PHP_GTK\\\"`"

  PHP_NEW_EXTENSION(gtk, gtk.c $cairo_sources $doc_sources $glib_sources $gobject_sources $gdk_sources $gtk_sources, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1 -DGTK_NS="$ext_ns")
  PHP_ADD_BUILD_DIR($ext_builddir/php_doc, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/php_cairo, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/php_glib, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/php_gobject, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/php_gdk, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/php_gtk, 1)
fi
