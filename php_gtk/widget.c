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

#include <gtk/gtk.h>
#include "php_gtk.h"

#include "php_gobject/object.h"
#include "php_gobject/type.h"
#include "php_gobject/object-extends.h"
#include "php_cairo/cairo.h"
#include "php_gdk/rectangle.h"

#include "widget.h"

#include "widget-extends.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;

zend_class_entry     *php_gtk_widget_class_entry;
//HashTable             php_gtk_widget_prop_handlers;
zend_object_handlers  php_gtk_widget_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry php_gtk_widget_methods[] = {
    PHP_ME(gtk_widget, __construct, arginfo_gtk_widget___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/
static void  php_gtk_widget_unset_property(zval *object, zval *member, void **cache_slot);
static zval *php_gtk_widget_write_property(zend_object *object, zend_string *member_str, zval *value, void **cache_slot);
static zval* php_gtk_widget_read_property(zend_object *object, zend_string *member_str, int type, void **cache_slot, zval *rv);
static char* php_gtk_widget_dump(php_gtk_widget *list, int tab);

static void
php_gtk_widget_unset_dimension(zval *object, zval *offset) {
    //php_gobject *list = ZVAL_GET_PHP_GTK_WIDGET(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
        // @TODO
        //zend_hash_index_del(list->prop_handler, );
        // php_gobject
        break;
    case IS_STRING:
        php_gtk_widget_unset_property(object, offset, &cache);
        break;
    default:
        break;
    }

}

static void
php_gtk_widget_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_gtk_widget_write_property(object, &member, value, &cache);
}

static zval*
php_gtk_widget_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
        return NULL;
    }

    php_gtk_widget *intern = ZVAL_GET_PHP_GTK_WIDGET(object);
    php_gtk_widget *list;
    void *cache=NULL;

    if (Z_TYPE_P(offset)==IS_LONG) {
        ZVAL_NULL(rv);
        return rv;
    } else if (Z_TYPE_P(offset)==IS_STRING) {
        return php_gtk_widget_read_property(object, offset, type, &cache, rv);
    } else {
        // error
    }

    return rv;
} /* }}} end php_g_hash_table_read_dimension */

static int
php_gtk_widget_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

/* updates *count to hold the number of elements present and returns SUCCESS.
 * Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_gtk_widget_count_elements(zval *object, zend_long *count) {

    *count = 0;

    return SUCCESS;
}

static int
php_gtk_widget_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}

static HashTable*
php_gtk_widget_get_properties(zval *object){
    php_gtk_widget  *self =  ZVAL_GET_PHP_GTK_WIDGET(object);
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
    zend_long length = php_gtk_widget_length(self);

    zend_hash_init(props, length, NULL, ZVAL_PTR_DTOR, 1);

    zval data;

    php_gtk_widget *it;
    for(it=php_gtk_widget_first(self); it; it = it->next){
        ZVAL_COPY(&data, &it->data);
        zend_hash_next_index_insert(props, &data);
    }
    */

    return props;
}

static HashTable*
php_gtk_widget_get_debug_info(zend_object *object, int *is_temp) /* {{{ */
{
    php_gtk_widget  *obj =  ZOBJ_TO_PHP_GTK_WIDGET(object);
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
    zval prev; ZVAL_SET_PHP_GTK_WIDGET(&prev, obj->prev);
    zend_hash_str_update(debug_info, "prev", sizeof("prev")-1, &prev);

    zval data; ZVAL_COPY(&data, &obj->data);
    zend_hash_str_update(debug_info, "data", sizeof("data")-1, &data);

    zval next; ZVAL_SET_PHP_GTK_WIDGET(&next, obj->next);
    zend_hash_str_update(debug_info, "next", sizeof("next")-1, &next);
    */

    return debug_info;
}
/* }}} */

static void
php_gtk_widget_unset_property(zval *object, zval *member, void **cache_slot) {
    php_gtk_widget *obj = ZVAL_GET_PHP_GTK_WIDGET(object);
    zend_string *member_str = zval_get_string(member);
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (zend_string_equals_literal(member->value.str, "next")
     || zend_string_equals_literal(member->value.str, "prev")
     || zend_string_equals_literal(member->value.str, "data") ) {
#if 0
        if (ZVAL_IS_PHP_GTK_WIDGET(value)) {
            // do unset(object->next) and php_gtk_widget_insert(object, value, 0);
        } else {
            zend_string *type = zend_zval_get_type(value);
            zend_error(E_USER_WARNING, "Cannot assign %s to property GObject::$next of type GObject", type->val);
        }
#else
        zend_error(E_USER_WARNING, "Readonly property GObject::$%s", member->value.str->val);
#endif
        return;
    }
    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}

/* {{{ php_gtk_widget_write_property */
static zval*
php_gtk_widget_write_property(zend_object *object, zend_string *member_str, zval *value, void **cache_slot)
{
    php_gtk_widget *obj = ZOBJ_TO_PHP_GTK_WIDGET(object);
    TRACE("%s(%s)\n", __FUNCTION__, member_str->val);


    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->write_property(object, member_str, value, cache_slot);

    zend_string_release(member_str);
}
/* }}} */

static zval zval_ret;
/* {{{ gtk_read_property */
static zval*
php_gtk_widget_read_property(zend_object *object, zend_string *member_str, int type, void **cache_slot, zval *rv)
{
    php_gtk_widget *obj = ZOBJ_TO_PHP_GTK_WIDGET(object);
    zval *retval;
    TRACE("%s(%s)\n", __FUNCTION__, member_str->val);

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
    retval = std_hnd->read_property(object, member_str, type, cache_slot, rv);

    //zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ php_gtk_widget_free_object */
static void
php_gtk_widget_free_object(zend_object *object)
{
    php_gtk_widget *intern = ZOBJ_TO_PHP_GTK_WIDGET(object);
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(intern);
    TRACE("php_gtk_widget_free_object(\"%s\") / %d\n", intern->data.value.str->val, object->gc.refcount);

    /**
     * GtkWidget are floating ref, GObject are counted ref
     * When main_quit() => GtkWidgets's are free by Gtk and
     * zend can't release zval of $widget
     */
    if (gobject->ptr) {
        /*
        if (g_object_is_floating(gobject->ptr)) {
            g_object_ref_sink(gobject->ptr);
        }
        g_clear_object(&gobject->ptr);
        */
    }

    if (gobject->properties!=NULL) {
        zend_hash_destroy(gobject->properties);
        efree(gobject->properties);
        gobject->properties=NULL;
    }

    zend_object_std_dtor(&gobject->std);
    //efree(intern);
}
/* }}} php_gtk_widget_free_object */

static void
php_gtk_widget_dtor_object(zend_object *obj) {
    php_gtk_widget *intern = ZOBJ_TO_PHP_GTK_WIDGET(obj);
    TRACE("php_gtk_widget_dtor_object(\"%s\") / %d\n", intern->data.value.str->val, obj->gc.refcount);

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

/// ######################################################################
//GtkWidgetClass *l;
GHashTable *gtk_widget_classes=NULL;


#if 0
GtkWidget my_widget;
GtkWidgetClass my_widget_classes;

//G_DEFINE_TYPE(MyCpu, my_cpu, GTK_TYPE_WIDGET)
typedef struct _MyWidget {
    GtkWidget widget;
    GdkWindow *window;
} MyWidget;

typedef struct _MyWidgetClass {
    GtkWidgetClass widget;
} MyWidgetClass;

static void     my_widget_init              (MyWidget      *self);
static void     my_widget_class_init        (MyWidgetClass *klass);
static gpointer my_widget_parent_class = NULL;
static gint     MyWidget_private_offset;

//_G_DEFINE_TYPE_EXTENDED_CLASS_INIT(MyWidget, my_widget)
static void
my_widget_class_intern_init (gpointer klass)
{
  my_widget_parent_class = g_type_class_peek_parent (klass);
  if (MyWidget_private_offset != 0)
    g_type_class_adjust_private_offset (klass, &MyWidget_private_offset);
  my_widget_class_init ((MyWidgetClass*) klass);
}

static inline gpointer
my_widget_get_instance_private (MyWidget *self)
{
  return (G_STRUCT_MEMBER_P (self, MyWidget_private_offset));
}

GType
my_widget_get_type (const char *key)
{
    gpointer type_id = g_hash_table_lookup(gtk_widget_classes, key);
    //gsize g_define_type_id__volatile = GPOINTER_TO_SIZE(type_id);
    if (type_id!=NULL) {
        g_print("Error: unexpected case\n");
    }

    gsize id = 0;

  if (g_once_init_enter (&id))
    {
      GType g_define_type_id =
        g_type_register_static_simple (GTK_TYPE_WIDGET,
                                       g_intern_static_string (key),
                                       sizeof (MyWidgetClass),
                                       (GClassInitFunc)(void (*)(void)) my_widget_class_intern_init,
                                       sizeof (MyWidget),
                                       (GInstanceInitFunc)(void (*)(void)) my_widget_init,
                                       (GTypeFlags) 0);
        {
          /* custom code follows */
          /* following custom code */
        }
        g_once_init_leave (&id, g_define_type_id);
    }

    g_hash_table_insert(gtk_widget_classes, key, GSIZE_TO_POINTER(id));
    return id;
} /* closes type_name##_get_type() */

static void
my_widget_realize(GtkWidget *widget) {

    MyWidget *priv = (MyWidget *)widget;
    //MyCpuPrivate *priv = MY_CPU(widget)->priv;
    GtkAllocation alloc;
    GdkWindowAttr attrs;
    guint attrs_mask;

    gtk_widget_set_realized(widget, TRUE);

    gtk_widget_get_allocation(widget, &alloc);

    attrs.x           = alloc.x;
    attrs.y           = alloc.y;
    attrs.width       = alloc.width;
    attrs.height      = alloc.height;
    attrs.window_type = GDK_WINDOW_CHILD;
    attrs.wclass      = GDK_INPUT_OUTPUT;
    attrs.event_mask  = gtk_widget_get_events(widget) | GDK_EXPOSURE_MASK;

    attrs_mask = GDK_WA_X | GDK_WA_Y;

    priv->window = gdk_window_new(gtk_widget_get_parent_window(widget),
                &attrs, attrs_mask);
    gdk_window_set_user_data(priv->window, widget);
    gtk_widget_set_window(widget, priv->window);

    /*
    widget->style = gtk_style_attach(gtk_widget_get_style( widget ),
                              priv->window);
    gtk_style_set_background(widget->style, priv->window, GTK_STATE_NORMAL);
    */

}
static void
my_widget_size_allocate(GtkWidget *widget,
                 GtkAllocation *allocation) {

   MyWidget *priv;

   priv = (MyWidget*)widget;

   gtk_widget_set_allocation(widget, allocation);

   if (gtk_widget_get_realized(widget)) {
      gdk_window_move_resize(priv->window, allocation->x, allocation->y,
          80, 100);
   }

}
static gboolean
my_widget_draw(GtkWidget *widget, cairo_t *cr) {

   MyWidget *priv = (MyWidget *)widget;
   gint limit;
   gint i;

   //GtkWidgetClass*parent = (GtkWidgetClass*)my_widget_parent_class;
   //parent->draw(widget, cr);

   cairo_translate(cr, 0, 7);

   //cairo_set_source_rgb(cr, 0, 0, 0);
   //cairo_paint(cr);

   limit = 20 -      50                / 5;

   for (i = 1; i <= 20; i++) {

      if (i > limit) {
         cairo_set_source_rgb(cr, 0.6, 1.0, 0);
      } else {
         cairo_set_source_rgb(cr, 0.2, 0.4, 0);
      }

      cairo_rectangle(cr, 8,  i * 4, 30, 3);
      cairo_rectangle(cr, 42, i * 4, 30, 3);
      cairo_fill(cr);
   }


   return FALSE;
}

/* Initialization */
static void my_widget_init(MyWidget *widget) {
}

static GtkWidgetClass php_gtk_widget_klass = {G_TYPE_INVALID};

static void
php_gtk_widget_override_get_preferred_width(GtkWidget *widget,
                                            gint      *minimum_width,
                                            gint      *natural_width) {
    if (TRUE) {
       GtkWidgetClass *klass = GTK_WIDGET_CLASS(&php_gtk_widget_klass);
       klass->get_preferred_width(widget, minimum_width, natural_width);
    }
}

extern zend_class_entry *php_cairo_t_class_entry;
static gboolean
php_gtk_widget_override_draw(GtkWidget *widget,
                             cairo_t *cr) {
    static GList *recursive_widget = NULL;
    zend_object *zobject = g_object_get_data(G_OBJECT(widget), "zend_object");
    //php_printf("php_gtk_widget_override_draw\n");

    zend_function *func = NULL;
    zend_bool is_override = FALSE;
    zend_bool is_recursive = NULL!=
    g_list_find(recursive_widget, widget);

    if (NULL==zobject) {
       php_printf(" UNLIKELY REACHED 1\n");
       //GtkWidgetClass *klass = GTK_WIDGET_CLASS(&php_gtk_widget_klass);// <---------------------------
       GtkWidgetClass *klass = GTK_WIDGET_GET_CLASS(widget);
       return klass->draw(widget, cr);
    }

    if (!is_recursive) {
        //php_printf(" isn't recursive\n");
        // try to find override user_function
        func = php_gobject_object_get_user_method(zobject, "GtkWidgetClass.draw");//<-------------

        if (func) {
            is_override = TRUE;
            //php_printf(" is_override\n");
        }
        zend_execute_data *current_execute = EG(current_execute_data);
        zend_execute_data *execute = NULL;
        if (NULL!=current_execute) {
            execute = current_execute->prev_execute_data;
        }// else on est mode GTKML

        if (func && execute && execute->func->common.function_name) {
            //php_printf("... %s\n", current_execute->func->common.function_name->val);// TODO
            //php_printf("Same object ? %d\n", zobject == execute->This.value.obj);// TODO
            if (0==g_strcmp0(execute->func->common.function_name->val, func->common.function_name->val)) {
                if (ZVAL_IS_PHP_GTK_WIDGET(&execute->This)) {
                    is_override = FALSE;
                }
            }
        }
        //php_printf("Call is not recusive\n");
    } else {
        //php_printf("Call is recusive\n");
    }

    zval retval; ZVAL_TRUE(&retval);
    if (is_override) {
        //php_printf("  call override function\n");
        recursive_widget =
        g_list_append(recursive_widget, widget);

        char *function_name = func->common.function_name->val;
        char *function_name_len = func->common.function_name->len;
#if 0
        zval zwidget; ZVAL_OBJ(&zwidget, zobject);
        zval zcr;
        zend_object *z_cr = zend_objects_new(php_cairo_t_class_entry);
        php_cairo_t *php_cr = ZOBJ_TO_PHP_CAIRO_T(z_cr);
        php_cr->ptr = cr;
        ZVAL_OBJ(&zcr, z_cr);

        int result = zend_call_method(&zwidget, NULL, NULL, function_name, strlen(function_name), &retval, 1, &zcr, NULL);
        if (FAILURE != result) {

        } else {
            g_print("zend_call_method_ Failure\n");
        }
        php_cr->ptr = NULL;
        zend_object_std_dtor(z_cr);
        //zend_objects_destroy_object(z_cr);

#elif 1

        zend_fcall_info_cache fci_cache;
        fci_cache.function_handler = func;
        fci_cache.object = zobject;
        fci_cache.called_scope = zobject->ce;

        int result;
        zend_fcall_info fci;
        zval zcairo;
        php_cairo_t *zcr = php_cairo_t_new(); zcr->ptr = cr;
        ZVAL_OBJ(&zcairo, &zcr->std);
        cairo_reference(cr);

        zval params[1];
        ZVAL_COPY_VALUE(&params[0], &zcairo);

        fci.size = sizeof(fci);
        fci.object = zobject;//Z_OBJ_P(zwidget);
        fci.retval = &retval;
        fci.param_count = 1;
        fci.params = params;
        fci.named_params = 0;
        ZVAL_STRINGL(&fci.function_name, function_name, function_name_len);
            result = zend_call_function(&fci, &fci_cache);
        zval_ptr_dtor(&fci.function_name);

        zend_object_release(&zcr->std);

#else

        int result;
        zend_fcall_info fci;
        php_cairo_t *php_cr = php_cairo_new();
        zend_object *z_cr = &php_cr->std;
        php_cr->ptr = cr;

        zval params[1];
            ZVAL_OBJ(&params[0], z_cr);

        ///zend_call_method()
        fci.size = sizeof(fci);
        fci.object = zobject;//Z_OBJ_P(zwidget);
        fci.retval = &retval;
        fci.param_count = 1;
        fci.params = params;
        fci.no_separation = 0;
            ZVAL_STRINGL(&fci.function_name, function_name, strlen(function_name));
            result = zend_call_function(&fci, NULL);
        zval_ptr_dtor(&fci.function_name);
        if (FAILURE != result) {
        } else {
            g_print("zend_call_method_ Failure\n");
        }

        php_cr->ptr = NULL;
        zend_object_release(z_cr);


#endif

        recursive_widget =
        g_list_remove(recursive_widget, widget);
    } else {
        php_printf("   OK\n");

        GtkWidgetClass *klass = GTK_WIDGET_CLASS(&php_gtk_widget_klass);
        return klass->draw(widget, cr);
    }

    if (Z_TYPE(retval)==IS_TRUE) return TRUE;
    if (Z_TYPE(retval)==IS_FALSE) return FALSE;

    return TRUE;
}
//...

static void
php_gtk_widget_class_init_override(GType type) {
    GtkWidgetClass *widget_klass = g_type_class_peek(type);

    if (G_TYPE_INVALID==php_gtk_widget_klass.parent_class.g_type_class.g_type) {
        memcpy(&php_gtk_widget_klass, widget_klass, sizeof(GtkWidgetClass));
        php_gtk_widget_klass.parent_class.g_type_class.g_type = type;

        // TODO: browse PHP class method...
        widget_klass->get_preferred_width = php_gtk_widget_override_get_preferred_width;
        widget_klass->draw = php_gtk_widget_override_draw;
        //...
    }
}

static void my_widget_class_init(MyWidgetClass *klass) {

   GObjectClass *g_class;
   GtkWidgetClass *w_class;
   GParamSpec *pspec;

   g_class = G_OBJECT_CLASS(klass);
   w_class = GTK_WIDGET_CLASS(klass);

   /* Override widget class methods */
   w_class->realize = my_widget_realize;
   w_class->size_allocate = my_widget_size_allocate;
   w_class->draw = my_widget_draw;

   /* Install property */

   //g_object_class_install_property(g_class, P_PERCENT, pspec);

   /* Add private data */
   //g_type_class_add_private(g_class, sizeof(MyCpuPrivate));
}

static GType
php_gtk_widget_register()
{
    GType type = G_TYPE_INVALID;

    return type;
}
#endif

/// ######################################################################

/* {{{ php_gtk_widget_create_object */
static zend_object*
php_gtk_widget_create_object(zend_class_entry *class_type)
{
    php_gtk_widget *intern = zend_object_alloc(sizeof(php_gtk_widget), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->properties = NULL;
    intern->std.handlers = &php_gtk_widget_handlers;
    intern->ptr = php_gtk_widget_extends(intern);


    TRACE("php_gtk_widget_create_object(%p) / %d\n", &gobject->std, gobject->std.gc.refcount);
    return &intern->std;
}
/* }}} php_gtk_widget_create_object */

/*
static void php_gtk_widget_dtor_prop_handler(zval *zv)
{
    free(Z_PTR_P(zv));
}
*/

static zend_object_handlers*
php_gtk_widget_get_handlers()
{
    memcpy(&php_gtk_widget_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_gtk_widget_handlers.offset = PHP_GTK_WIDGET_OFFSET;
    //php_gtk_widget_handlers.clone_obj;
    //php_gtk_widget_handlers.compare;
    //php_gtk_widget_handlers.compare_objects;
    //php_gtk_widget_handlers.get_constructor;
    php_gtk_widget_handlers.dtor_obj = php_gtk_widget_dtor_object;
    php_gtk_widget_handlers.free_obj = php_gtk_widget_free_object;
    php_gtk_widget_handlers.read_property = php_gtk_widget_read_property;
    php_gtk_widget_handlers.write_property = php_gtk_widget_write_property;
    //php_gtk_widget_handlers.unset_property = php_gtk_widget_unset_property;
    //php_gtk_widget_handlers.get_property_ptr_ptr = php_gtk_widget_get_property_ptr_ptr;

    php_gtk_widget_handlers.get_debug_info = php_gtk_widget_get_debug_info;
/*
    php_gtk_widget_handlers.get_properties = php_gtk_widget_get_properties;//get_properties_for TODO php 8.0
    //php_gtk_widget_handlers.set = php_gtk_widget_set;
    php_gtk_widget_handlers.cast_object = php_gtk_widget_cast_object;

    php_gtk_widget_handlers.count_elements = php_gtk_widget_count_elements;
    php_gtk_widget_handlers.has_dimension = php_gtk_widget_has_dimension;
    php_gtk_widget_handlers.read_dimension = php_gtk_widget_read_dimension;
    php_gtk_widget_handlers.unset_dimension = php_gtk_widget_unset_dimension;
    php_gtk_widget_handlers.write_dimension = php_gtk_widget_write_dimension;
*/

    return &php_gtk_widget_handlers;
}


/*----------------------------------------------------------------------+
| PHP_MINIT                                                            |
+----------------------------------------------------------------------*/
/*{{{ zend_gtk_widget_class_minit */
zend_class_entry*
php_gtk_widget_class_minit(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gtk_widget_get_handlers();
    //INIT_NS_CLASS_ENTRY((*ce), "Gnome\\G", "Object", php_gtk_widget_methods);
    INIT_CLASS_ENTRY((*container_ce), "GtkWidget", php_gtk_widget_methods);
    php_gtk_widget_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_gtk_widget_class_entry->create_object = php_gtk_widget_create_object;
    ///php_gtk_widget_class_entry->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;
    php_gtk_widget_class_entry->ce_flags |= ZEND_ACC_ABSTRACT;

    zend_register_long_constant("GTK_WIDGET_HELP_TOOLTIP", sizeof("GTK_WIDGET_HELP_TOOLTIP")-1,
        GTK_WIDGET_HELP_TOOLTIP, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_WIDGET_HELP_WHATS_THIS", sizeof("GTK_WIDGET_HELP_WHATS_THIS")-1,
        GTK_WIDGET_HELP_WHATS_THIS, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);

    zend_register_long_constant("GTK_TEXT_DIR_NONE", sizeof("GTK_TEXT_DIR_NONE")-1,
        GTK_TEXT_DIR_NONE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_TEXT_DIR_LTR", sizeof("GTK_TEXT_DIR_LTR")-1,
        GTK_TEXT_DIR_LTR, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_TEXT_DIR_RTL", sizeof("GTK_TEXT_DIR_RTL")-1,
        GTK_TEXT_DIR_RTL, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);

    zend_register_long_constant("GTK_STATE_NORMAL", sizeof("GTK_STATE_NORMAL")-1,
        GTK_STATE_NORMAL, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_STATE_ACTIVE", sizeof("GTK_STATE_ACTIVE")-1,
        GTK_STATE_ACTIVE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_STATE_PRELIGHT", sizeof("GTK_STATE_PRELIGHT")-1,
        GTK_STATE_PRELIGHT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_STATE_SELECTED", sizeof("GTK_STATE_SELECTED")-1,
        GTK_STATE_SELECTED, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_STATE_INSENSITIVE", sizeof("GTK_STATE_INSENSITIVE")-1,
        GTK_STATE_INSENSITIVE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_STATE_INCONSISTENT", sizeof("GTK_STATE_INCONSISTENT")-1,
        GTK_STATE_INCONSISTENT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_STATE_FOCUSED", sizeof("GTK_STATE_FOCUSED")-1,
        GTK_STATE_FOCUSED, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);

    zend_register_long_constant("GTK_SIZE_REQUEST_HEIGHT_FOR_WIDTH", sizeof("GTK_SIZE_REQUEST_HEIGHT_FOR_WIDTH")-1,
        GTK_SIZE_REQUEST_HEIGHT_FOR_WIDTH, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_SIZE_REQUEST_WIDTH_FOR_HEIGHT", sizeof("GTK_SIZE_REQUEST_WIDTH_FOR_HEIGHT")-1,
        GTK_SIZE_REQUEST_WIDTH_FOR_HEIGHT, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_SIZE_REQUEST_CONSTANT_SIZE", sizeof("GTK_SIZE_REQUEST_CONSTANT_SIZE")-1,
        GTK_SIZE_REQUEST_CONSTANT_SIZE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);

    zend_register_long_constant("GTK_ALIGN_FILL", sizeof("GTK_ALIGN_FILL")-1,
        GTK_ALIGN_FILL, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_ALIGN_START", sizeof("GTK_ALIGN_START")-1,
        GTK_ALIGN_START, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_ALIGN_END", sizeof("GTK_ALIGN_END")-1,
        GTK_ALIGN_END, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_ALIGN_CENTER", sizeof("GTK_ALIGN_CENTER")-1,
        GTK_ALIGN_CENTER, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("GTK_ALIGN_BASELINE", sizeof("GTK_ALIGN_BASELINE")-1,
        GTK_ALIGN_BASELINE, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);


#if 0
    char *comment = "/**"
                    " * Base class for all widgets"
                    " * @package Gtk"
                    " */";
    php_gtk_widget_class_entry->type == ZEND_USER_CLASS;
    php_gtk_widget_class_entry->info.user.doc_comment = zend_string_init(comment, strlen(comment), 1);
    php_gtk_widget_class_entry->info.user.doc_comment = NULL;
#endif

#if 0
    char *doc = "/**"
                    " * The constructor"
                    " * @package Gtk"
                    " */";
    php_gtk_widget_class_entry->constructor->op_array.doc_comment  = zend_string_init(doc, strlen(doc), 1);
#endif

    gtk_widget_classes = g_hash_table_new(g_direct_hash, g_direct_hash);

    return php_gtk_widget_class_entry;
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

/* {{{ GObject::__construct() */
PHP_METHOD(gtk_widget, __construct)
{
    zval *data=NULL;


    /*
    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();
    */

    zend_object *zobj = Z_OBJ_P(getThis());
    php_gtk_widget *self = ZOBJ_TO_PHP_GTK_WIDGET(zobj);
    //php_gobject_object *obj = ZOBJ_TO_PHP_GOBJECT_OBJECT(zobj);
    //obj->ptr = gtk_widget_new(GTK_TYPE_WIDGET, NULL);


}
/* }}} */


/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/

#if 0

/* {{{ proto GtkWidget gtk_widget_new(mixed type, string first_property_name) */
PHP_FUNCTION(gtk_widget_new)
{
    zval *ztype;
    char *first_property_name;
    int first_property_name_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(ztype, php_GType_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, first_property_name, first_property_name_len)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_new(type, first_property_name);


}/* }}} */

/* {{{ proto void gtk_widget_destroy(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_destroy)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_destroy(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_in_destruction(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_in_destruction)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_in_destruction(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_destroyed(GtkWidget widget, GtkWidget widget_pointer) */
PHP_FUNCTION(gtk_widget_destroyed)
{
    zval *zwidget;
    zval *zwidget_pointer;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget_pointer, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;
    php_gtk_widget *widget_pointer = ZVAL_IS_PHP_GTK_WIDGET(zwidget_pointer)? ZVAL_GET_PHP_GTK_WIDGET(zwidget_pointer): NULL;

    gtk_widget_destroyed(widget->ptr, widget_pointer->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_unparent(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_unparent)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_unparent(widget->ptr);


}/* }}} */
#endif


/* {{{ proto void gtk_widget_show(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_show)
{
    zval *zwidget = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();


    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget) ? ZVAL_GET_PHP_GTK_WIDGET(zwidget) : NULL;
    php_gobject_object *gwidget = PHP_GOBJECT_OBJECT(widget);
    GtkWidget *gtk_widget = GTK_WIDGET(gwidget->ptr);

    gtk_widget_show(gtk_widget);

}/* }}} */

#if 0
/* {{{ proto void gtk_widget_show_now(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_show_now)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_show_now(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_hide(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_hide)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_hide(widget->ptr);


}/* }}} */
#endif

/* {{{ proto GObject gtk_widget_show_all(GObject list, mixed data) */
PHP_FUNCTION(gtk_widget_show_all)
{
    zval *zwidget = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();


    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget) ? ZVAL_GET_PHP_GTK_WIDGET(zwidget) : NULL;
    php_gobject_object *gwidget = PHP_GOBJECT_OBJECT(widget);
    GtkWidget *gtk_widget = GTK_WIDGET(gwidget->ptr);

    gtk_widget_show_all(gtk_widget);

}/* }}} */

#if 0
/* {{{ proto void gtk_widget_map(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_map)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_map(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_unmap(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_unmap)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_unmap(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_realize(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_realize)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_realize(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_unrealize(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_unrealize)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_unrealize(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_draw(GtkWidget widget, mixed cr) */
PHP_FUNCTION(gtk_widget_draw)
{
    zval *zwidget;
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_draw(widget->ptr, cr);


}/* }}} */

/* {{{ proto void gtk_widget_queue_draw(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_queue_draw)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_queue_draw(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_queue_resize(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_queue_resize)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_queue_resize(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_queue_resize_no_redraw(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_queue_resize_no_redraw)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_queue_resize_no_redraw(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_queue_allocate(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_queue_allocate)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_queue_allocate(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_frame_clock(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_frame_clock)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_frame_clock(widget->ptr);


}/* }}} */

/* {{{ proto int gtk_widget_get_scale_factor(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_scale_factor)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_scale_factor(widget->ptr);


}/* }}} */

/* {{{ proto int gtk_widget_add_tick_callback(GtkWidget widget, mixed callback, mixed user_data, mixed notify) */
PHP_FUNCTION(gtk_widget_add_tick_callback)
{
    zval *zwidget;
    zval *zcallback;
    zval *zuser_data;
    zval *znotify;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcallback, php_GtkTickCallback_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zuser_data, php_gpointer_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(znotify, php_GDestroyNotify_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_add_tick_callback(widget->ptr, callback, user_data, notify);


}/* }}} */

/* {{{ proto void gtk_widget_remove_tick_callback(GtkWidget widget, int id) */
PHP_FUNCTION(gtk_widget_remove_tick_callback)
{
    zval *zwidget;
    zval *zid;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zid, php_guint_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_remove_tick_callback(widget->ptr, id);


}/* }}} */

/* {{{ proto void gtk_widget_size_request(GtkWidget widget, GtkRequisition requisition) */
PHP_FUNCTION(gtk_widget_size_request)
{
    zval *zwidget;
    zval *zrequisition;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zrequisition, php_GtkRequisition_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;
    php_gtk_requisition *requisition = ZVAL_IS_PHP_GTK_REQUISITION(zrequisition)? ZVAL_GET_PHP_GTK_REQUISITION(zrequisition): NULL;

    gtk_widget_size_request(widget->ptr, requisition->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_get_child_requisition(GtkWidget widget, GtkRequisition requisition) */
PHP_FUNCTION(gtk_widget_get_child_requisition)
{
    zval *zwidget;
    zval *zrequisition;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zrequisition, php_GtkRequisition_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;
    php_gtk_requisition *requisition = ZVAL_IS_PHP_GTK_REQUISITION(zrequisition)? ZVAL_GET_PHP_GTK_REQUISITION(zrequisition): NULL;

    gtk_widget_get_child_requisition(widget->ptr, requisition->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_size_allocate(GtkWidget widget, mixed allocation) */
PHP_FUNCTION(gtk_widget_size_allocate)
{
    zval *zwidget;
    zval *zallocation;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zallocation, php_GtkAllocation_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_size_allocate(widget->ptr, allocation);


}/* }}} */

/* {{{ proto void gtk_widget_size_allocate_with_baseline(GtkWidget widget, mixed allocation, int baseline) */
PHP_FUNCTION(gtk_widget_size_allocate_with_baseline)
{
    zval *zwidget;
    zval *zallocation;
    zend_long baseline;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zallocation, php_GtkAllocation_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, baseline)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_size_allocate_with_baseline(widget->ptr, allocation, baseline);


}/* }}} */

/* {{{ proto void gtk_widget_add_accelerator(GtkWidget widget, string accel_signal, mixed accel_group, int accel_key, mixed accel_mods, mixed accel_flags) */
PHP_FUNCTION(gtk_widget_add_accelerator)
{
    zval *zwidget;
    char *accel_signal;
    int accel_signal_len;
    zval *zaccel_group;
    zval *zaccel_key;
    zval *zaccel_mods;
    zval *zaccel_flags;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, accel_signal, accel_signal_len)
        Z_PARAM_OBJECT_OF_CLASS_EX(zaccel_group, php_GtkAccelGroup_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zaccel_key, php_guint_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zaccel_mods, php_GdkModifierType_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zaccel_flags, php_GtkAccelFlags_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_add_accelerator(widget->ptr, accel_signal, accel_group, accel_key, accel_mods, accel_flags);


}/* }}} */

/* {{{ proto bool gtk_widget_remove_accelerator(GtkWidget widget, mixed accel_group, int accel_key, mixed accel_mods) */
PHP_FUNCTION(gtk_widget_remove_accelerator)
{
    zval *zwidget;
    zval *zaccel_group;
    zval *zaccel_key;
    zval *zaccel_mods;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zaccel_group, php_GtkAccelGroup_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zaccel_key, php_guint_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zaccel_mods, php_GdkModifierType_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_remove_accelerator(widget->ptr, accel_group, accel_key, accel_mods);


}/* }}} */

/* {{{ proto void gtk_widget_set_accel_path(GtkWidget widget, string accel_path, mixed accel_group) */
PHP_FUNCTION(gtk_widget_set_accel_path)
{
    zval *zwidget;
    char *accel_path;
    int accel_path_len;
    zval *zaccel_group;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, accel_path, accel_path_len)
        Z_PARAM_OBJECT_OF_CLASS_EX(zaccel_group, php_GtkAccelGroup_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_accel_path(widget->ptr, accel_path, accel_group);


}/* }}} */

/* {{{ proto mixed gtk_widget_list_accel_closures(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_list_accel_closures)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_list_accel_closures(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_can_activate_accel(GtkWidget widget, int signal_id) */
PHP_FUNCTION(gtk_widget_can_activate_accel)
{
    zval *zwidget;
    zval *zsignal_id;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsignal_id, php_guint_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_can_activate_accel(widget->ptr, signal_id);


}/* }}} */

/* {{{ proto bool gtk_widget_event(GtkWidget widget, mixed event) */
PHP_FUNCTION(gtk_widget_event)
{
    zval *zwidget;
    zval *zevent;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zevent, php_GdkEvent_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_event(widget->ptr, event);


}/* }}} */

/* {{{ proto bool gtk_widget_activate(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_activate)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_activate(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_reparent(GtkWidget widget, GtkWidget new_parent) */
PHP_FUNCTION(gtk_widget_reparent)
{
    zval *zwidget;
    zval *znew_parent;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(znew_parent, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;
    php_gtk_widget *new_parent = ZVAL_IS_PHP_GTK_WIDGET(znew_parent)? ZVAL_GET_PHP_GTK_WIDGET(znew_parent): NULL;

    gtk_widget_reparent(widget->ptr, new_parent->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_intersect(GtkWidget widget, GdkRectangle area, GdkRectangle intersection) */
PHP_FUNCTION(gtk_widget_intersect)
{
    zval *zwidget;
    zval *zarea;
    zval *zintersection;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zarea, php_GdkRectangle_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zintersection, php_GdkRectangle_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;
    php_gdk_rectangle *area = ZVAL_IS_PHP_GDK_RECTANGLE(zarea)? ZVAL_GET_PHP_GDK_RECTANGLE(zarea): NULL;
    php_gdk_rectangle *intersection = ZVAL_IS_PHP_GDK_RECTANGLE(zintersection)? ZVAL_GET_PHP_GDK_RECTANGLE(zintersection): NULL;

    gtk_widget_intersect(widget->ptr, area->ptr, intersection->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_is_focus(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_is_focus)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_is_focus(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_grab_focus(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_grab_focus)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_grab_focus(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_grab_default(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_grab_default)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_grab_default(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_name(GtkWidget widget, string name) */
PHP_FUNCTION(gtk_widget_set_name)
{
    zval *zwidget;
    char *name;
    int name_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, name, name_len)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_name(widget->ptr, name);


}/* }}} */

/* {{{ proto string gtk_widget_get_name(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_name)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_name(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_state(GtkWidget widget, mixed state) */
PHP_FUNCTION(gtk_widget_set_state)
{
    zval *zwidget;
    zval *zstate;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zstate, php_GtkStateType_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_state(widget->ptr, state);


}/* }}} */

/* {{{ proto void gtk_widget_set_sensitive(GtkWidget widget, bool sensitive) */
PHP_FUNCTION(gtk_widget_set_sensitive)
{
    zval *zwidget;
    zval *zsensitive;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsensitive, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_sensitive(widget->ptr, sensitive);


}/* }}} */

/* {{{ proto void gtk_widget_set_parent(GtkWidget widget, GtkWidget parent) */
PHP_FUNCTION(gtk_widget_set_parent)
{
    zval *zwidget;
    zval *zparent;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zparent, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;
    php_gtk_widget *parent = ZVAL_IS_PHP_GTK_WIDGET(zparent)? ZVAL_GET_PHP_GTK_WIDGET(zparent): NULL;

    gtk_widget_set_parent(widget->ptr, parent->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_parent_window(GtkWidget widget, mixed parent_window) */
PHP_FUNCTION(gtk_widget_set_parent_window)
{
    zval *zwidget;
    zval *zparent_window;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zparent_window, php_GdkWindow_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_parent_window(widget->ptr, parent_window);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_parent_window(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_parent_window)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_parent_window(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_events(GtkWidget widget, int events) */
PHP_FUNCTION(gtk_widget_set_events)
{
    zval *zwidget;
    zend_long events;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, events)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_events(widget->ptr, events);


}/* }}} */

/* {{{ proto int gtk_widget_get_events(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_events)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_events(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_add_events(GtkWidget widget, int events) */
PHP_FUNCTION(gtk_widget_add_events)
{
    zval *zwidget;
    zend_long events;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, events)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_add_events(widget->ptr, events);


}/* }}} */

/* {{{ proto void gtk_widget_set_device_events(GtkWidget widget, mixed device, mixed events) */
PHP_FUNCTION(gtk_widget_set_device_events)
{
    zval *zwidget;
    zval *zdevice;
    zval *zevents;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_GdkDevice_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zevents, php_GdkEventMask_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_device_events(widget->ptr, device, events);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_device_events(GtkWidget widget, mixed device) */
PHP_FUNCTION(gtk_widget_get_device_events)
{
    zval *zwidget;
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_GdkDevice_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_device_events(widget->ptr, device);


}/* }}} */

/* {{{ proto void gtk_widget_add_device_events(GtkWidget widget, mixed device, mixed events) */
PHP_FUNCTION(gtk_widget_add_device_events)
{
    zval *zwidget;
    zval *zdevice;
    zval *zevents;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_GdkDevice_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zevents, php_GdkEventMask_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_add_device_events(widget->ptr, device, events);


}/* }}} */

/* {{{ proto void gtk_widget_set_device_enabled(GtkWidget widget, mixed device, bool enabled) */
PHP_FUNCTION(gtk_widget_set_device_enabled)
{
    zval *zwidget;
    zval *zdevice;
    zval *zenabled;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_GdkDevice_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zenabled, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_device_enabled(widget->ptr, device, enabled);


}/* }}} */

/* {{{ proto bool gtk_widget_get_device_enabled(GtkWidget widget, mixed device) */
PHP_FUNCTION(gtk_widget_get_device_enabled)
{
    zval *zwidget;
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_GdkDevice_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_device_enabled(widget->ptr, device);


}/* }}} */

/* {{{ proto GtkWidget gtk_widget_get_toplevel(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_toplevel)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_toplevel(widget->ptr);


}/* }}} */

/* {{{ proto GtkWidget gtk_widget_get_ancestor(GtkWidget widget, mixed widget_type) */
PHP_FUNCTION(gtk_widget_get_ancestor)
{
    zval *zwidget;
    zval *zwidget_type;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget_type, php_GType_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_ancestor(widget->ptr, widget_type);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_visual(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_visual)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_visual(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_visual(GtkWidget widget, mixed visual) */
PHP_FUNCTION(gtk_widget_set_visual)
{
    zval *zwidget;
    zval *zvisual;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zvisual, php_GdkVisual_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_visual(widget->ptr, visual);


}/* }}} */

/* {{{ proto void gtk_widget_get_pointer(GtkWidget widget, int x, int y) */
PHP_FUNCTION(gtk_widget_get_pointer)
{
    zval *zwidget;
    zend_long x;
    zend_long y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, x)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, y)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_pointer(widget->ptr, x, y);


}/* }}} */

/* {{{ proto bool gtk_widget_is_ancestor(GtkWidget widget, GtkWidget ancestor) */
PHP_FUNCTION(gtk_widget_is_ancestor)
{
    zval *zwidget;
    zval *zancestor;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zancestor, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;
    php_gtk_widget *ancestor = ZVAL_IS_PHP_GTK_WIDGET(zancestor)? ZVAL_GET_PHP_GTK_WIDGET(zancestor): NULL;

    gtk_widget_is_ancestor(widget->ptr, ancestor->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_translate_coordinates(GtkWidget src_widget, GtkWidget dest_widget, int src_x, int src_y, int dest_x, int dest_y) */
PHP_FUNCTION(gtk_widget_translate_coordinates)
{
    zval *zsrc_widget;
    zval *zdest_widget;
    zend_long src_x;
    zend_long src_y;
    zend_long dest_x;
    zend_long dest_y;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsrc_widget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdest_widget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, src_x)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, src_y)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, dest_x)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, dest_y)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *src_widget = ZVAL_IS_PHP_GTK_WIDGET(zsrc_widget)? ZVAL_GET_PHP_GTK_WIDGET(zsrc_widget): NULL;
    php_gtk_widget *dest_widget = ZVAL_IS_PHP_GTK_WIDGET(zdest_widget)? ZVAL_GET_PHP_GTK_WIDGET(zdest_widget): NULL;

    gtk_widget_translate_coordinates(src_widget->ptr, dest_widget->ptr, src_x, src_y, dest_x, dest_y);


}/* }}} */

/* {{{ proto bool gtk_widget_hide_on_delete(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_hide_on_delete)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_hide_on_delete(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_style(GtkWidget widget, mixed style) */
PHP_FUNCTION(gtk_widget_set_style)
{
    zval *zwidget;
    zval *zstyle;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zstyle, php_GtkStyle_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_style(widget->ptr, style);


}/* }}} */

/* {{{ proto void gtk_widget_ensure_style(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_ensure_style)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_ensure_style(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_style(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_style)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_style(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_reset_rc_styles(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_reset_rc_styles)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_reset_rc_styles(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_default_style() */
PHP_FUNCTION(gtk_widget_get_default_style)
{

    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_get_default_style();


}/* }}} */

/* {{{ proto void gtk_widget_set_direction(GtkWidget widget, mixed dir) */
PHP_FUNCTION(gtk_widget_set_direction)
{
    zval *zwidget;
    zval *zdir;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdir, php_GtkTextDirection_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_direction(widget->ptr, dir);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_direction(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_direction)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_direction(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_default_direction(mixed dir) */
PHP_FUNCTION(gtk_widget_set_default_direction)
{
    zval *zdir;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdir, php_GtkTextDirection_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_set_default_direction(dir);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_default_direction() */
PHP_FUNCTION(gtk_widget_get_default_direction)
{

    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_get_default_direction();


}/* }}} */

/* {{{ proto void gtk_widget_shape_combine_region(GtkWidget widget, mixed region) */
PHP_FUNCTION(gtk_widget_shape_combine_region)
{
    zval *zwidget;
    zval *zregion;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zregion, php_cairo_region_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_shape_combine_region(widget->ptr, region);


}/* }}} */

/* {{{ proto void gtk_widget_input_shape_combine_region(GtkWidget widget, mixed region) */
PHP_FUNCTION(gtk_widget_input_shape_combine_region)
{
    zval *zwidget;
    zval *zregion;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zregion, php_cairo_region_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_input_shape_combine_region(widget->ptr, region);


}/* }}} */

/* {{{ proto void gtk_widget_path(GtkWidget widget, int path_length, string path, string path_reversed) */
PHP_FUNCTION(gtk_widget_path)
{
    zval *zwidget;
    zval *zpath_length;
    char *path;
    int path_len;
    char *path_reversed;
    int path_reversed_len;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpath_length, php_guint_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, path, path_len)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, path_reversed, path_reversed_len)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_path(widget->ptr, path_length, path, path_reversed);


}/* }}} */

/* {{{ proto void gtk_widget_class_path(GtkWidget widget, int path_length, string path, string path_reversed) */
PHP_FUNCTION(gtk_widget_class_path)
{
    zval *zwidget;
    zval *zpath_length;
    char *path;
    int path_len;
    char *path_reversed;
    int path_reversed_len;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpath_length, php_guint_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, path, path_len)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, path_reversed, path_reversed_len)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_class_path(widget->ptr, path_length, path, path_reversed);


}/* }}} */

/* {{{ proto string gtk_widget_get_composite_name(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_composite_name)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_composite_name(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_override_background_color(GtkWidget widget, mixed state, mixed color) */
PHP_FUNCTION(gtk_widget_override_background_color)
{
    zval *zwidget;
    zval *zstate;
    zval *zcolor;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zstate, php_GtkStateFlags_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcolor, php_GdkRGBA_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_override_background_color(widget->ptr, state, color);


}/* }}} */

/* {{{ proto void gtk_widget_override_color(GtkWidget widget, mixed state, mixed color) */
PHP_FUNCTION(gtk_widget_override_color)
{
    zval *zwidget;
    zval *zstate;
    zval *zcolor;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zstate, php_GtkStateFlags_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcolor, php_GdkRGBA_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_override_color(widget->ptr, state, color);


}/* }}} */

/* {{{ proto void gtk_widget_override_font(GtkWidget widget, mixed font_desc) */
PHP_FUNCTION(gtk_widget_override_font)
{
    zval *zwidget;
    zval *zfont_desc;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zfont_desc, php_PangoFontDescription_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_override_font(widget->ptr, font_desc);


}/* }}} */

/* {{{ proto void gtk_widget_override_symbolic_color(GtkWidget widget, string name, mixed color) */
PHP_FUNCTION(gtk_widget_override_symbolic_color)
{
    zval *zwidget;
    char *name;
    int name_len;
    zval *zcolor;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, name, name_len)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcolor, php_GdkRGBA_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_override_symbolic_color(widget->ptr, name, color);


}/* }}} */

/* {{{ proto void gtk_widget_override_cursor(GtkWidget widget, mixed cursor, mixed secondary_cursor) */
PHP_FUNCTION(gtk_widget_override_cursor)
{
    zval *zwidget;
    zval *zcursor;
    zval *zsecondary_cursor;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcursor, php_GdkRGBA_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsecondary_cursor, php_GdkRGBA_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_override_cursor(widget->ptr, cursor, secondary_cursor);


}/* }}} */

/* {{{ proto void gtk_widget_modify_style(GtkWidget widget, mixed style) */
PHP_FUNCTION(gtk_widget_modify_style)
{
    zval *zwidget;
    zval *zstyle;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zstyle, php_GtkRcStyle_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_modify_style(widget->ptr, style);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_modifier_style(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_modifier_style)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_modifier_style(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_modify_fg(GtkWidget widget, mixed state, mixed color) */
PHP_FUNCTION(gtk_widget_modify_fg)
{
    zval *zwidget;
    zval *zstate;
    zval *zcolor;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zstate, php_GtkStateType_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcolor, php_GdkColor_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_modify_fg(widget->ptr, state, color);


}/* }}} */

/* {{{ proto void gtk_widget_modify_bg(GtkWidget widget, mixed state, mixed color) */
PHP_FUNCTION(gtk_widget_modify_bg)
{
    zval *zwidget;
    zval *zstate;
    zval *zcolor;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zstate, php_GtkStateType_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcolor, php_GdkColor_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_modify_bg(widget->ptr, state, color);


}/* }}} */

/* {{{ proto void gtk_widget_modify_text(GtkWidget widget, mixed state, mixed color) */
PHP_FUNCTION(gtk_widget_modify_text)
{
    zval *zwidget;
    zval *zstate;
    zval *zcolor;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zstate, php_GtkStateType_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcolor, php_GdkColor_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_modify_text(widget->ptr, state, color);


}/* }}} */

/* {{{ proto void gtk_widget_modify_base(GtkWidget widget, mixed state, mixed color) */
PHP_FUNCTION(gtk_widget_modify_base)
{
    zval *zwidget;
    zval *zstate;
    zval *zcolor;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zstate, php_GtkStateType_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcolor, php_GdkColor_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_modify_base(widget->ptr, state, color);


}/* }}} */

/* {{{ proto void gtk_widget_modify_font(GtkWidget widget, mixed font_desc) */
PHP_FUNCTION(gtk_widget_modify_font)
{
    zval *zwidget;
    zval *zfont_desc;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zfont_desc, php_PangoFontDescription_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_modify_font(widget->ptr, font_desc);


}/* }}} */

/* {{{ proto void gtk_widget_modify_cursor(GtkWidget widget, mixed primary, mixed secondary) */
PHP_FUNCTION(gtk_widget_modify_cursor)
{
    zval *zwidget;
    zval *zprimary;
    zval *zsecondary;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zprimary, php_GdkColor_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsecondary, php_GdkColor_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_modify_cursor(widget->ptr, primary, secondary);


}/* }}} */

/* {{{ proto mixed gtk_widget_create_pango_context(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_create_pango_context)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_create_pango_context(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_pango_context(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_pango_context)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_pango_context(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_font_options(GtkWidget widget, mixed options) */
PHP_FUNCTION(gtk_widget_set_font_options)
{
    zval *zwidget;
    zval *zoptions;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zoptions, php_cairo_font_options_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_font_options(widget->ptr, options);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_font_options(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_font_options)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_font_options(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_font_map(GtkWidget widget, mixed font_map) */
PHP_FUNCTION(gtk_widget_set_font_map)
{
    zval *zwidget;
    zval *zfont_map;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zfont_map, php_PangoFontMap_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_font_map(widget->ptr, font_map);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_font_map(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_font_map)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_font_map(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_create_pango_layout(GtkWidget widget, string text) */
PHP_FUNCTION(gtk_widget_create_pango_layout)
{
    zval *zwidget;
    char *text;
    int text_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, text, text_len)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_create_pango_layout(widget->ptr, text);


}/* }}} */

/* {{{ proto mixed gtk_widget_render_icon(GtkWidget widget, string stock_id, mixed size, string detail) */
PHP_FUNCTION(gtk_widget_render_icon)
{
    zval *zwidget;
    char *stock_id;
    int stock_id_len;
    zval *zsize;
    char *detail;
    int detail_len;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, stock_id, stock_id_len)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsize, php_GtkIconSize_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, detail, detail_len)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_render_icon(widget->ptr, stock_id, size, detail);


}/* }}} */

/* {{{ proto mixed gtk_widget_render_icon_pixbuf(GtkWidget widget, string stock_id, mixed size) */
PHP_FUNCTION(gtk_widget_render_icon_pixbuf)
{
    zval *zwidget;
    char *stock_id;
    int stock_id_len;
    zval *zsize;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, stock_id, stock_id_len)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsize, php_GtkIconSize_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_render_icon_pixbuf(widget->ptr, stock_id, size);


}/* }}} */

/* {{{ proto void gtk_widget_pop_composite_child() */
PHP_FUNCTION(gtk_widget_pop_composite_child)
{

    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_pop_composite_child();


}/* }}} */

/* {{{ proto void gtk_widget_push_composite_child() */
PHP_FUNCTION(gtk_widget_push_composite_child)
{

    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_push_composite_child();


}/* }}} */

/* {{{ proto void gtk_widget_queue_draw_area(GtkWidget widget, int x, int y, int width, int height) */
PHP_FUNCTION(gtk_widget_queue_draw_area)
{
    zval *zwidget;
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, x)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, y)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, width)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, height)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_queue_draw_area(widget->ptr, x, y, width, height);


}/* }}} */

/* {{{ proto void gtk_widget_queue_draw_region(GtkWidget widget, mixed region) */
PHP_FUNCTION(gtk_widget_queue_draw_region)
{
    zval *zwidget;
    zval *zregion;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zregion, php_cairo_region_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_queue_draw_region(widget->ptr, region);


}/* }}} */

/* {{{ proto void gtk_widget_set_app_paintable(GtkWidget widget, bool app_paintable) */
PHP_FUNCTION(gtk_widget_set_app_paintable)
{
    zval *zwidget;
    zval *zapp_paintable;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zapp_paintable, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_app_paintable(widget->ptr, app_paintable);


}/* }}} */

/* {{{ proto void gtk_widget_set_double_buffered(GtkWidget widget, bool double_buffered) */
PHP_FUNCTION(gtk_widget_set_double_buffered)
{
    zval *zwidget;
    zval *zdouble_buffered;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdouble_buffered, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_double_buffered(widget->ptr, double_buffered);


}/* }}} */

/* {{{ proto void gtk_widget_set_redraw_on_allocate(GtkWidget widget, bool redraw_on_allocate) */
PHP_FUNCTION(gtk_widget_set_redraw_on_allocate)
{
    zval *zwidget;
    zval *zredraw_on_allocate;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zredraw_on_allocate, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_redraw_on_allocate(widget->ptr, redraw_on_allocate);


}/* }}} */

/* {{{ proto void gtk_widget_set_composite_name(GtkWidget widget, string name) */
PHP_FUNCTION(gtk_widget_set_composite_name)
{
    zval *zwidget;
    char *name;
    int name_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, name, name_len)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_composite_name(widget->ptr, name);


}/* }}} */

/* {{{ proto bool gtk_widget_mnemonic_activate(GtkWidget widget, bool group_cycling) */
PHP_FUNCTION(gtk_widget_mnemonic_activate)
{
    zval *zwidget;
    zval *zgroup_cycling;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zgroup_cycling, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_mnemonic_activate(widget->ptr, group_cycling);


}/* }}} */

/* {{{ proto void gtk_widget_class_install_style_property(mixed klass, mixed pspec) */
PHP_FUNCTION(gtk_widget_class_install_style_property)
{
    zval *zklass;
    zval *zpspec;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zklass, php_GtkWidgetClass_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpspec, php_GParamSpec_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_class_install_style_property(klass, pspec);


}/* }}} */

/* {{{ proto void gtk_widget_class_install_style_property_parser(mixed klass, mixed pspec, mixed parser) */
PHP_FUNCTION(gtk_widget_class_install_style_property_parser)
{
    zval *zklass;
    zval *zpspec;
    zval *zparser;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zklass, php_GtkWidgetClass_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpspec, php_GParamSpec_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zparser, php_GtkRcPropertyParser_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_class_install_style_property_parser(klass, pspec, parser);


}/* }}} */

/* {{{ proto mixed gtk_widget_class_find_style_property(mixed klass, string property_name) */
PHP_FUNCTION(gtk_widget_class_find_style_property)
{
    zval *zklass;
    char *property_name;
    int property_name_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zklass, php_GtkWidgetClass_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, property_name, property_name_len)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_class_find_style_property(klass, property_name);


}/* }}} */

/* {{{ proto mixed gtk_widget_class_list_style_properties(mixed klass, int n_properties) */
PHP_FUNCTION(gtk_widget_class_list_style_properties)
{
    zval *zklass;
    zval *zn_properties;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zklass, php_GtkWidgetClass_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zn_properties, php_guint_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_class_list_style_properties(klass, n_properties);


}/* }}} */

/* {{{ proto mixed gtk_widget_region_intersect(GtkWidget widget, mixed region) */
PHP_FUNCTION(gtk_widget_region_intersect)
{
    zval *zwidget;
    zval *zregion;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zregion, php_cairo_region_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_region_intersect(widget->ptr, region);


}/* }}} */

/* {{{ proto int gtk_widget_send_expose(GtkWidget widget, mixed event) */
PHP_FUNCTION(gtk_widget_send_expose)
{
    zval *zwidget;
    zval *zevent;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zevent, php_GdkEvent_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_send_expose(widget->ptr, event);


}/* }}} */

/* {{{ proto bool gtk_widget_send_focus_change(GtkWidget widget, mixed event) */
PHP_FUNCTION(gtk_widget_send_focus_change)
{
    zval *zwidget;
    zval *zevent;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zevent, php_GdkEvent_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_send_focus_change(widget->ptr, event);


}/* }}} */

/* {{{ proto void gtk_widget_style_get(GtkWidget widget, string first_property_name) */
PHP_FUNCTION(gtk_widget_style_get)
{
    zval *zwidget;
    char *first_property_name;
    int first_property_name_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, first_property_name, first_property_name_len)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_style_get(widget->ptr, first_property_name);


}/* }}} */

/* {{{ proto void gtk_widget_style_get_property(GtkWidget widget, string property_name, mixed value) */
PHP_FUNCTION(gtk_widget_style_get_property)
{
    zval *zwidget;
    char *property_name;
    int property_name_len;
    zval *zvalue;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, property_name, property_name_len)
        Z_PARAM_OBJECT_OF_CLASS_EX(zvalue, php_GValue_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_style_get_property(widget->ptr, property_name, value);


}/* }}} */

/* {{{ proto void gtk_widget_style_get_valist(GtkWidget widget, string first_property_name, mixed var_args) */
PHP_FUNCTION(gtk_widget_style_get_valist)
{
    zval *zwidget;
    char *first_property_name;
    int first_property_name_len;
    zval *zvar_args;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, first_property_name, first_property_name_len)
        Z_PARAM_OBJECT_OF_CLASS_EX(zvar_args, php_va_list_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_style_get_valist(widget->ptr, first_property_name, var_args);


}/* }}} */

/* {{{ proto void gtk_widget_style_attach(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_style_attach)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_style_attach(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_class_set_accessible_type(mixed widget_class, mixed type) */
PHP_FUNCTION(gtk_widget_class_set_accessible_type)
{
    zval *zwidget_class;
    zval *ztype;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget_class, php_GtkWidgetClass_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(ztype, php_GType_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_class_set_accessible_type(widget_class, type);


}/* }}} */

/* {{{ proto void gtk_widget_class_set_accessible_role(mixed widget_class, mixed role) */
PHP_FUNCTION(gtk_widget_class_set_accessible_role)
{
    zval *zwidget_class;
    zval *zrole;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget_class, php_GtkWidgetClass_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zrole, php_AtkRole_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_class_set_accessible_role(widget_class, role);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_accessible(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_accessible)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_accessible(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_child_focus(GtkWidget widget, mixed direction) */
PHP_FUNCTION(gtk_widget_child_focus)
{
    zval *zwidget;
    zval *zdirection;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdirection, php_GtkDirectionType_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_child_focus(widget->ptr, direction);


}/* }}} */

/* {{{ proto void gtk_widget_child_notify(GtkWidget widget, string child_property) */
PHP_FUNCTION(gtk_widget_child_notify)
{
    zval *zwidget;
    char *child_property;
    int child_property_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, child_property, child_property_len)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_child_notify(widget->ptr, child_property);


}/* }}} */

/* {{{ proto void gtk_widget_freeze_child_notify(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_freeze_child_notify)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_freeze_child_notify(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_get_child_visible(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_child_visible)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_child_visible(widget->ptr);


}/* }}} */

/* {{{ proto GtkWidget gtk_widget_get_parent(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_parent)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_parent(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_settings(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_settings)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_settings(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_clipboard(GtkWidget widget, mixed selection) */
PHP_FUNCTION(gtk_widget_get_clipboard)
{
    zval *zwidget;
    zval *zselection;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zselection, php_GdkAtom_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_clipboard(widget->ptr, selection);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_display(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_display)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_display(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_root_window(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_root_window)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_root_window(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_screen(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_screen)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_screen(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_has_screen(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_has_screen)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_has_screen(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_get_size_request(GtkWidget widget, int width, int height) */
PHP_FUNCTION(gtk_widget_get_size_request)
{
    zval *zwidget;
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, width)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, height)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_size_request(widget->ptr, width, height);


}/* }}} */

/* {{{ proto void gtk_widget_set_child_visible(GtkWidget widget, bool is_visible) */
PHP_FUNCTION(gtk_widget_set_child_visible)
{
    zval *zwidget;
    zval *zis_visible;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zis_visible, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_child_visible(widget->ptr, is_visible);


}/* }}} */

/* {{{ proto void gtk_widget_set_size_request(GtkWidget widget, int width, int height) */
PHP_FUNCTION(gtk_widget_set_size_request)
{
    zval *zwidget;
    zend_long width;
    zend_long height;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, width)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, height)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_size_request(widget->ptr, width, height);


}/* }}} */

/* {{{ proto void gtk_widget_thaw_child_notify(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_thaw_child_notify)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_thaw_child_notify(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_no_show_all(GtkWidget widget, bool no_show_all) */
PHP_FUNCTION(gtk_widget_set_no_show_all)
{
    zval *zwidget;
    zval *zno_show_all;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zno_show_all, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_no_show_all(widget->ptr, no_show_all);


}/* }}} */

/* {{{ proto bool gtk_widget_get_no_show_all(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_no_show_all)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_no_show_all(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_list_mnemonic_labels(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_list_mnemonic_labels)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_list_mnemonic_labels(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_add_mnemonic_label(GtkWidget widget, GtkWidget label) */
PHP_FUNCTION(gtk_widget_add_mnemonic_label)
{
    zval *zwidget;
    zval *zlabel;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zlabel, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;
    php_gtk_widget *label = ZVAL_IS_PHP_GTK_WIDGET(zlabel)? ZVAL_GET_PHP_GTK_WIDGET(zlabel): NULL;

    gtk_widget_add_mnemonic_label(widget->ptr, label->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_remove_mnemonic_label(GtkWidget widget, GtkWidget label) */
PHP_FUNCTION(gtk_widget_remove_mnemonic_label)
{
    zval *zwidget;
    zval *zlabel;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zlabel, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;
    php_gtk_widget *label = ZVAL_IS_PHP_GTK_WIDGET(zlabel)? ZVAL_GET_PHP_GTK_WIDGET(zlabel): NULL;

    gtk_widget_remove_mnemonic_label(widget->ptr, label->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_is_composited(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_is_composited)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_is_composited(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_error_bell(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_error_bell)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_error_bell(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_keynav_failed(GtkWidget widget, mixed direction) */
PHP_FUNCTION(gtk_widget_keynav_failed)
{
    zval *zwidget;
    zval *zdirection;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdirection, php_GtkDirectionType_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_keynav_failed(widget->ptr, direction);


}/* }}} */

/* {{{ proto string gtk_widget_get_tooltip_markup(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_tooltip_markup)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_tooltip_markup(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_tooltip_markup(GtkWidget widget, string markup) */
PHP_FUNCTION(gtk_widget_set_tooltip_markup)
{
    zval *zwidget;
    char *markup;
    int markup_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, markup, markup_len)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_tooltip_markup(widget->ptr, markup);


}/* }}} */

/* {{{ proto string gtk_widget_get_tooltip_text(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_tooltip_text)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_tooltip_text(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_tooltip_text(GtkWidget widget, string text) */
PHP_FUNCTION(gtk_widget_set_tooltip_text)
{
    zval *zwidget;
    char *text;
    int text_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, text, text_len)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_tooltip_text(widget->ptr, text);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_tooltip_window(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_tooltip_window)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_tooltip_window(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_tooltip_window(GtkWidget widget, mixed custom_window) */
PHP_FUNCTION(gtk_widget_set_tooltip_window)
{
    zval *zwidget;
    zval *zcustom_window;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcustom_window, php_GtkWindow_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_tooltip_window(widget->ptr, custom_window);


}/* }}} */

/* {{{ proto bool gtk_widget_get_has_tooltip(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_has_tooltip)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_has_tooltip(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_has_tooltip(GtkWidget widget, bool has_tooltip) */
PHP_FUNCTION(gtk_widget_set_has_tooltip)
{
    zval *zwidget;
    zval *zhas_tooltip;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zhas_tooltip, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_has_tooltip(widget->ptr, has_tooltip);


}/* }}} */

/* {{{ proto void gtk_widget_trigger_tooltip_query(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_trigger_tooltip_query)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_trigger_tooltip_query(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_window(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_window)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_window(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_register_window(GtkWidget widget, mixed window) */
PHP_FUNCTION(gtk_widget_register_window)
{
    zval *zwidget;
    zval *zwindow;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwindow, php_GdkWindow_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_register_window(widget->ptr, window);


}/* }}} */

/* {{{ proto void gtk_widget_unregister_window(GtkWidget widget, mixed window) */
PHP_FUNCTION(gtk_widget_unregister_window)
{
    zval *zwidget;
    zval *zwindow;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwindow, php_GdkWindow_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_unregister_window(widget->ptr, window);


}/* }}} */

/* {{{ proto bool gtk_cairo_should_draw_window(mixed cr, mixed window) */
PHP_FUNCTION(gtk_cairo_should_draw_window)
{
    zval *zcr;
    zval *zwindow;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwindow, php_GdkWindow_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_cairo_should_draw_window(cr, window);


}/* }}} */

/* {{{ proto void gtk_cairo_transform_to_window(mixed cr, GtkWidget widget, mixed window) */
PHP_FUNCTION(gtk_cairo_transform_to_window)
{
    zval *zcr;
    zval *zwidget;
    zval *zwindow;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwindow, php_GdkWindow_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_cairo_transform_to_window(cr, widget->ptr, window);


}/* }}} */

/* {{{ proto int gtk_widget_get_allocated_width(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_allocated_width)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_allocated_width(widget->ptr);


}/* }}} */

/* {{{ proto int gtk_widget_get_allocated_height(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_allocated_height)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_allocated_height(widget->ptr);


}/* }}} */
#endif

/* {{{ proto void gtk_widget_get_allocation(GtkWidget widget, mixed allocation) */
PHP_FUNCTION(gtk_widget_get_allocation)
{
    zval *zwidget;
    zval *zallocation;


    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_ZVAL_EX2(zallocation, 0, 1, 0)
        //Z_PARAM_ZVAL_DEREF(zallocation)
        //Z_PARAM_OBJECT_OF_CLASS_EX2(zallocation, php_gdk_rectangle_class_entry, 0, 1, 0)
        //Z_PARAM_OBJECT_OF_CLASS_EX(zallocation, php_gtk_allocation_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;
    php_gobject_object *object = PHP_GOBJECT_OBJECT(widget);

    php_gdk_rectangle *alloc = ZVAL_IS_PHP_GDK_RECTANGLE(zallocation)? ZVAL_GET_PHP_GDK_RECTANGLE(zallocation): NULL;

    GdkRectangle *allocation;
    if (alloc) {
        allocation = alloc->ptr;
    } else {
        php_gdk_rectangle *alloc = php_gdk_rectangle_new();
        ZVAL_OBJ(zallocation, &alloc->std);
        allocation = alloc->ptr;
    }

    gtk_widget_get_allocation(object->ptr, (GtkAllocation*)allocation);

}/* }}} */

#if 0
/* {{{ proto void gtk_widget_set_allocation(GtkWidget widget, mixed allocation) */
PHP_FUNCTION(gtk_widget_set_allocation)
{
    zval *zwidget;
    zval *zallocation;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zallocation, php_GtkAllocation_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_allocation(widget->ptr, allocation);


}/* }}} */

/* {{{ proto int gtk_widget_get_allocated_baseline(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_allocated_baseline)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_allocated_baseline(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_get_allocated_size(GtkWidget widget, mixed allocation, int baseline) */
PHP_FUNCTION(gtk_widget_get_allocated_size)
{
    zval *zwidget;
    zval *zallocation;
    zend_long baseline;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zallocation, php_GtkAllocation_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, baseline)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_allocated_size(widget->ptr, allocation, baseline);


}/* }}} */

/* {{{ proto void gtk_widget_get_clip(GtkWidget widget, mixed clip) */
PHP_FUNCTION(gtk_widget_get_clip)
{
    zval *zwidget;
    zval *zclip;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zclip, php_GtkAllocation_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_clip(widget->ptr, clip);


}/* }}} */

/* {{{ proto void gtk_widget_set_clip(GtkWidget widget, mixed clip) */
PHP_FUNCTION(gtk_widget_set_clip)
{
    zval *zwidget;
    zval *zclip;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zclip, php_GtkAllocation_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_clip(widget->ptr, clip);


}/* }}} */

/* {{{ proto bool gtk_widget_get_app_paintable(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_app_paintable)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_app_paintable(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_get_can_default(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_can_default)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_can_default(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_can_default(GtkWidget widget, bool can_default) */
PHP_FUNCTION(gtk_widget_set_can_default)
{
    zval *zwidget;
    zval *zcan_default;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcan_default, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_can_default(widget->ptr, can_default);


}/* }}} */

/* {{{ proto bool gtk_widget_get_can_focus(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_can_focus)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_can_focus(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_can_focus(GtkWidget widget, bool can_focus) */
PHP_FUNCTION(gtk_widget_set_can_focus)
{
    zval *zwidget;
    zval *zcan_focus;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcan_focus, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_can_focus(widget->ptr, can_focus);


}/* }}} */

/* {{{ proto bool gtk_widget_get_focus_on_click(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_focus_on_click)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_focus_on_click(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_focus_on_click(GtkWidget widget, bool focus_on_click) */
PHP_FUNCTION(gtk_widget_set_focus_on_click)
{
    zval *zwidget;
    zval *zfocus_on_click;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zfocus_on_click, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_focus_on_click(widget->ptr, focus_on_click);


}/* }}} */

/* {{{ proto bool gtk_widget_get_double_buffered(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_double_buffered)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_double_buffered(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_get_has_window(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_has_window)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_has_window(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_has_window(GtkWidget widget, bool has_window) */
PHP_FUNCTION(gtk_widget_set_has_window)
{
    zval *zwidget;
    zval *zhas_window;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zhas_window, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_has_window(widget->ptr, has_window);


}/* }}} */

/* {{{ proto bool gtk_widget_get_sensitive(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_sensitive)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_sensitive(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_is_sensitive(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_is_sensitive)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_is_sensitive(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_state(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_state)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_state(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_get_visible(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_visible)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_visible(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_is_visible(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_is_visible)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_is_visible(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_visible(GtkWidget widget, bool visible) */
PHP_FUNCTION(gtk_widget_set_visible)
{
    zval *zwidget;
    zval *zvisible;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zvisible, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_visible(widget->ptr, visible);


}/* }}} */

/* {{{ proto void gtk_widget_set_state_flags(GtkWidget widget, mixed flags, bool clear) */
PHP_FUNCTION(gtk_widget_set_state_flags)
{
    zval *zwidget;
    zval *zflags;
    zval *zclear;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zflags, php_GtkStateFlags_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zclear, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_state_flags(widget->ptr, flags, clear);


}/* }}} */

/* {{{ proto void gtk_widget_unset_state_flags(GtkWidget widget, mixed flags) */
PHP_FUNCTION(gtk_widget_unset_state_flags)
{
    zval *zwidget;
    zval *zflags;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zflags, php_GtkStateFlags_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_unset_state_flags(widget->ptr, flags);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_state_flags(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_state_flags)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_state_flags(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_has_default(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_has_default)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_has_default(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_has_focus(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_has_focus)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_has_focus(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_has_visible_focus(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_has_visible_focus)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_has_visible_focus(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_has_grab(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_has_grab)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_has_grab(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_has_rc_style(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_has_rc_style)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_has_rc_style(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_is_drawable(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_is_drawable)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_is_drawable(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_is_toplevel(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_is_toplevel)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_is_toplevel(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_window(GtkWidget widget, mixed window) */
PHP_FUNCTION(gtk_widget_set_window)
{
    zval *zwidget;
    zval *zwindow;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwindow, php_GdkWindow_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_window(widget->ptr, window);


}/* }}} */

/* {{{ proto void gtk_widget_set_receives_default(GtkWidget widget, bool receives_default) */
PHP_FUNCTION(gtk_widget_set_receives_default)
{
    zval *zwidget;
    zval *zreceives_default;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zreceives_default, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_receives_default(widget->ptr, receives_default);


}/* }}} */

/* {{{ proto bool gtk_widget_get_receives_default(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_receives_default)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_receives_default(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_support_multidevice(GtkWidget widget, bool support_multidevice) */
PHP_FUNCTION(gtk_widget_set_support_multidevice)
{
    zval *zwidget;
    zval *zsupport_multidevice;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsupport_multidevice, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_support_multidevice(widget->ptr, support_multidevice);


}/* }}} */

/* {{{ proto bool gtk_widget_get_support_multidevice(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_support_multidevice)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_support_multidevice(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_realized(GtkWidget widget, bool realized) */
PHP_FUNCTION(gtk_widget_set_realized)
{
    zval *zwidget;
    zval *zrealized;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zrealized, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_realized(widget->ptr, realized);


}/* }}} */

/* {{{ proto bool gtk_widget_get_realized(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_realized)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_realized(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_mapped(GtkWidget widget, bool mapped) */
PHP_FUNCTION(gtk_widget_set_mapped)
{
    zval *zwidget;
    zval *zmapped;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmapped, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_mapped(widget->ptr, mapped);


}/* }}} */

/* {{{ proto bool gtk_widget_get_mapped(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_mapped)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_mapped(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_get_requisition(GtkWidget widget, GtkRequisition requisition) */
PHP_FUNCTION(gtk_widget_get_requisition)
{
    zval *zwidget;
    zval *zrequisition;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zrequisition, php_GtkRequisition_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;
    php_gtk_requisition *requisition = ZVAL_IS_PHP_GTK_REQUISITION(zrequisition)? ZVAL_GET_PHP_GTK_REQUISITION(zrequisition): NULL;

    gtk_widget_get_requisition(widget->ptr, requisition->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_device_is_shadowed(GtkWidget widget, mixed device) */
PHP_FUNCTION(gtk_widget_device_is_shadowed)
{
    zval *zwidget;
    zval *zdevice;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zdevice, php_GdkDevice_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_device_is_shadowed(widget->ptr, device);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_modifier_mask(GtkWidget widget, mixed intent) */
PHP_FUNCTION(gtk_widget_get_modifier_mask)
{
    zval *zwidget;
    zval *zintent;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zintent, php_GdkModifierIntent_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_modifier_mask(widget->ptr, intent);


}/* }}} */

/* {{{ proto void gtk_widget_insert_action_group(GtkWidget widget, string name, mixed group) */
PHP_FUNCTION(gtk_widget_insert_action_group)
{
    zval *zwidget;
    char *name;
    int name_len;
    zval *zgroup;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, name, name_len)
        Z_PARAM_OBJECT_OF_CLASS_EX(zgroup, php_GActionGroup_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_insert_action_group(widget->ptr, name, group);


}/* }}} */

/* {{{ proto int gtk_widget_get_opacity(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_opacity)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_opacity(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_opacity(GtkWidget widget, int opacity) */
PHP_FUNCTION(gtk_widget_set_opacity)
{
    zval *zwidget;
    double opacity;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_DOUBLE(opacity)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_opacity(widget->ptr, opacity);


}/* }}} */

/* {{{ proto string gtk_widget_list_action_prefixes(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_list_action_prefixes)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_list_action_prefixes(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_action_group(GtkWidget widget, string prefix) */
PHP_FUNCTION(gtk_widget_get_action_group)
{
    zval *zwidget;
    char *prefix;
    int prefix_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, prefix, prefix_len)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_action_group(widget->ptr, prefix);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_path(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_path)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_path(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_style_context(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_style_context)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_style_context(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_reset_style(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_reset_style)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_reset_style(widget->ptr);


}/* }}} */

/* {{{ proto string gtk_widget_class_get_css_name(mixed widget_class) */
PHP_FUNCTION(gtk_widget_class_get_css_name)
{
    zval *zwidget_class;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget_class, php_GtkWidgetClass_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_class_get_css_name(widget_class);


}/* }}} */

/* {{{ proto void gtk_widget_class_set_css_name(mixed widget_class, string name) */
PHP_FUNCTION(gtk_widget_class_set_css_name)
{
    zval *zwidget_class;
    char *name;
    int name_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget_class, php_GtkWidgetClass_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, name, name_len)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_class_set_css_name(widget_class, name);


}/* }}} */

/* {{{ proto GtkRequisition gtk_requisition_new() */
PHP_FUNCTION(gtk_requisition_new)
{

    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_requisition_new();


}/* }}} */

/* {{{ proto GtkRequisition gtk_requisition_copy(GtkRequisition requisition) */
PHP_FUNCTION(gtk_requisition_copy)
{
    zval *zrequisition;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zrequisition, php_GtkRequisition_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_requisition *requisition = ZVAL_IS_PHP_GTK_REQUISITION(zrequisition)? ZVAL_GET_PHP_GTK_REQUISITION(zrequisition): NULL;

    gtk_requisition_copy(requisition->ptr);


}/* }}} */

/* {{{ proto void gtk_requisition_free(GtkRequisition requisition) */
PHP_FUNCTION(gtk_requisition_free)
{
    zval *zrequisition;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zrequisition, php_GtkRequisition_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_requisition *requisition = ZVAL_IS_PHP_GTK_REQUISITION(zrequisition)? ZVAL_GET_PHP_GTK_REQUISITION(zrequisition): NULL;

    gtk_requisition_free(requisition->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_get_preferred_height(GtkWidget widget, int minimum_height, int natural_height) */
PHP_FUNCTION(gtk_widget_get_preferred_height)
{
    zval *zwidget;
    zend_long minimum_height;
    zend_long natural_height;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, minimum_height)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, natural_height)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_preferred_height(widget->ptr, minimum_height, natural_height);


}/* }}} */
#endif

/* {{{ proto void gtk_widget_get_preferred_width(GtkWidget widget, int minimum_width, int natural_width) */
PHP_FUNCTION(gtk_widget_get_preferred_width)
{
    zval *zwidget = NULL;
    zval *zminimum_width = NULL;
    zval *znatural_width = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_ZVAL_EX2(zminimum_width, 0, 1, 0)
        Z_PARAM_ZVAL_EX2(znatural_width, 0, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget) ? ZVAL_GET_PHP_GTK_WIDGET(zwidget) : NULL;

    GtkWidget *__widget = PHP_GOBJECT_OBJECT(widget)->ptr;
    int __minimum_width;
    int __natural_width;

    /*
    // May be PHP developper do not undestand very well Gtk+ ... Try to help ?
    if (!gtk_widget_get_visible(__widget))
        zend_error(E_USER_WARNING, "Can't get %s for %s#%d: GtkWidget is not visible. Try to use \"show\" signal.\n", "preferred size", widget->parent_instance.std.ce->name->val, widget->parent_instance.std.handle);
    */
    gtk_widget_get_preferred_width(__widget, &__minimum_width, &__natural_width);


    ZVAL_DOUBLE(zminimum_width, __minimum_width);
    ZVAL_DOUBLE(znatural_width, __natural_width);


}/* }}} */


#if 0
/* {{{ proto void gtk_widget_get_preferred_height_for_width(GtkWidget widget, int width, int minimum_height, int natural_height) */
PHP_FUNCTION(gtk_widget_get_preferred_height_for_width)
{
    zval *zwidget;
    zend_long width;
    zend_long minimum_height;
    zend_long natural_height;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, width)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, minimum_height)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, natural_height)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_preferred_height_for_width(widget->ptr, width, minimum_height, natural_height);


}/* }}} */

/* {{{ proto void gtk_widget_get_preferred_width_for_height(GtkWidget widget, int height, int minimum_width, int natural_width) */
PHP_FUNCTION(gtk_widget_get_preferred_width_for_height)
{
    zval *zwidget;
    zend_long height;
    zend_long minimum_width;
    zend_long natural_width;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, height)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, minimum_width)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, natural_width)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_preferred_width_for_height(widget->ptr, height, minimum_width, natural_width);


}/* }}} */

/* {{{ proto void gtk_widget_get_preferred_height_and_baseline_for_width(GtkWidget widget, int width, int minimum_height, int natural_height, int minimum_baseline, int natural_baseline) */
PHP_FUNCTION(gtk_widget_get_preferred_height_and_baseline_for_width)
{
    zval *zwidget;
    zend_long width;
    zend_long minimum_height;
    zend_long natural_height;
    zend_long minimum_baseline;
    zend_long natural_baseline;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, width)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, minimum_height)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, natural_height)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, minimum_baseline)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, natural_baseline)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_preferred_height_and_baseline_for_width(widget->ptr, width, minimum_height, natural_height, minimum_baseline, natural_baseline);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_request_mode(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_request_mode)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_request_mode(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_get_preferred_size(GtkWidget widget, GtkRequisition minimum_size, GtkRequisition natural_size) */
PHP_FUNCTION(gtk_widget_get_preferred_size)
{
    zval *zwidget;
    zval *zminimum_size;
    zval *znatural_size;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zminimum_size, php_GtkRequisition_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(znatural_size, php_GtkRequisition_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;
    php_gtk_requisition *minimum_size = ZVAL_IS_PHP_GTK_REQUISITION(zminimum_size)? ZVAL_GET_PHP_GTK_REQUISITION(zminimum_size): NULL;
    php_gtk_requisition *natural_size = ZVAL_IS_PHP_GTK_REQUISITION(znatural_size)? ZVAL_GET_PHP_GTK_REQUISITION(znatural_size): NULL;

    gtk_widget_get_preferred_size(widget->ptr, minimum_size->ptr, natural_size->ptr);


}/* }}} */

/* {{{ proto int gtk_distribute_natural_allocation(int extra_space, int n_requested_sizes, GtkRequestedSize sizes) */
PHP_FUNCTION(gtk_distribute_natural_allocation)
{
    zend_long extra_space;
    zval *zn_requested_sizes;
    zval *zsizes;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, extra_space)
        Z_PARAM_OBJECT_OF_CLASS_EX(zn_requested_sizes, php_guint_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zsizes, php_GtkRequestedSize_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_requested_size *sizes = ZVAL_IS_PHP_GTK_REQUESTED_SIZE(zsizes)? ZVAL_GET_PHP_GTK_REQUESTED_SIZE(zsizes): NULL;

    gtk_distribute_natural_allocation(extra_space, n_requested_sizes, sizes->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_halign(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_halign)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_halign(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_halign(GtkWidget widget, mixed align) */
PHP_FUNCTION(gtk_widget_set_halign)
{
    zval *zwidget;
    zval *zalign;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zalign, php_GtkAlign_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_halign(widget->ptr, align);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_valign(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_valign)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_valign(widget->ptr);


}/* }}} */

/* {{{ proto mixed gtk_widget_get_valign_with_baseline(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_valign_with_baseline)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_valign_with_baseline(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_valign(GtkWidget widget, mixed align) */
PHP_FUNCTION(gtk_widget_set_valign)
{
    zval *zwidget;
    zval *zalign;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zalign, php_GtkAlign_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_valign(widget->ptr, align);


}/* }}} */

/* {{{ proto int gtk_widget_get_margin_left(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_margin_left)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_margin_left(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_margin_left(GtkWidget widget, int margin) */
PHP_FUNCTION(gtk_widget_set_margin_left)
{
    zval *zwidget;
    zend_long margin;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, margin)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_margin_left(widget->ptr, margin);


}/* }}} */

/* {{{ proto int gtk_widget_get_margin_right(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_margin_right)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_margin_right(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_margin_right(GtkWidget widget, int margin) */
PHP_FUNCTION(gtk_widget_set_margin_right)
{
    zval *zwidget;
    zend_long margin;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, margin)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_margin_right(widget->ptr, margin);


}/* }}} */

/* {{{ proto int gtk_widget_get_margin_start(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_margin_start)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_margin_start(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_margin_start(GtkWidget widget, int margin) */
PHP_FUNCTION(gtk_widget_set_margin_start)
{
    zval *zwidget;
    zend_long margin;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, margin)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_margin_start(widget->ptr, margin);


}/* }}} */

/* {{{ proto int gtk_widget_get_margin_end(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_margin_end)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_margin_end(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_margin_end(GtkWidget widget, int margin) */
PHP_FUNCTION(gtk_widget_set_margin_end)
{
    zval *zwidget;
    zend_long margin;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, margin)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_margin_end(widget->ptr, margin);


}/* }}} */

/* {{{ proto int gtk_widget_get_margin_top(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_margin_top)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_margin_top(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_margin_top(GtkWidget widget, int margin) */
PHP_FUNCTION(gtk_widget_set_margin_top)
{
    zval *zwidget;
    zend_long margin;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, margin)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_margin_top(widget->ptr, margin);


}/* }}} */

/* {{{ proto int gtk_widget_get_margin_bottom(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_margin_bottom)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_margin_bottom(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_margin_bottom(GtkWidget widget, int margin) */
PHP_FUNCTION(gtk_widget_set_margin_bottom)
{
    zval *zwidget;
    zend_long margin;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_LONG(ZEND_SEND_BY_VAL, margin)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_margin_bottom(widget->ptr, margin);


}/* }}} */

/* {{{ proto bool gtk_widget_get_hexpand(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_hexpand)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_hexpand(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_hexpand(GtkWidget widget, bool expand) */
PHP_FUNCTION(gtk_widget_set_hexpand)
{
    zval *zwidget;
    zval *zexpand;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zexpand, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_hexpand(widget->ptr, expand);


}/* }}} */

/* {{{ proto bool gtk_widget_get_hexpand_set(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_hexpand_set)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_hexpand_set(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_hexpand_set(GtkWidget widget, bool set) */
PHP_FUNCTION(gtk_widget_set_hexpand_set)
{
    zval *zwidget;
    zval *zset;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zset, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_hexpand_set(widget->ptr, set);


}/* }}} */

/* {{{ proto bool gtk_widget_get_vexpand(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_vexpand)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_vexpand(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_vexpand(GtkWidget widget, bool expand) */
PHP_FUNCTION(gtk_widget_set_vexpand)
{
    zval *zwidget;
    zval *zexpand;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zexpand, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_vexpand(widget->ptr, expand);


}/* }}} */

/* {{{ proto bool gtk_widget_get_vexpand_set(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_get_vexpand_set)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_vexpand_set(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_set_vexpand_set(GtkWidget widget, bool set) */
PHP_FUNCTION(gtk_widget_set_vexpand_set)
{
    zval *zwidget;
    zval *zset;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zset, php_gboolean_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_set_vexpand_set(widget->ptr, set);


}/* }}} */

/* {{{ proto void gtk_widget_queue_compute_expand(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_queue_compute_expand)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_queue_compute_expand(widget->ptr);


}/* }}} */

/* {{{ proto bool gtk_widget_compute_expand(GtkWidget widget, mixed orientation) */
PHP_FUNCTION(gtk_widget_compute_expand)
{
    zval *zwidget;
    zval *zorientation;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zorientation, php_GtkOrientation_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_compute_expand(widget->ptr, orientation);


}/* }}} */

/* {{{ proto void gtk_widget_init_template(GtkWidget widget) */
PHP_FUNCTION(gtk_widget_init_template)
{
    zval *zwidget;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_init_template(widget->ptr);


}/* }}} */

/* {{{ proto void gtk_widget_class_set_template(mixed widget_class, mixed template_bytes) */
PHP_FUNCTION(gtk_widget_class_set_template)
{
    zval *zwidget_class;
    zval *ztemplate_bytes;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget_class, php_GtkWidgetClass_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(ztemplate_bytes, php_GBytes_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_class_set_template(widget_class, template_bytes);


}/* }}} */

/* {{{ proto void gtk_widget_class_set_template_from_resource(mixed widget_class, string resource_name) */
PHP_FUNCTION(gtk_widget_class_set_template_from_resource)
{
    zval *zwidget_class;
    char *resource_name;
    int resource_name_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget_class, php_GtkWidgetClass_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, resource_name, resource_name_len)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_class_set_template_from_resource(widget_class, resource_name);


}/* }}} */

/* {{{ proto GObject gtk_widget_get_template_child(GtkWidget widget, mixed widget_type, string name) */
PHP_FUNCTION(gtk_widget_get_template_child)
{
    zval *zwidget;
    zval *zwidget_type;
    char *name;
    int name_len;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget_type, php_GType_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, name, name_len)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget)? ZVAL_GET_PHP_GTK_WIDGET(zwidget): NULL;

    gtk_widget_get_template_child(widget->ptr, widget_type, name);


}/* }}} */

/* {{{ proto void gtk_widget_class_bind_template_child_full(mixed widget_class, string name, bool internal_child, mixed struct_offset) */
PHP_FUNCTION(gtk_widget_class_bind_template_child_full)
{
    zval *zwidget_class;
    char *name;
    int name_len;
    zval *zinternal_child;
    zval *zstruct_offset;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget_class, php_GtkWidgetClass_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, name, name_len)
        Z_PARAM_OBJECT_OF_CLASS_EX(zinternal_child, php_gboolean_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zstruct_offset, php_gssize_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_class_bind_template_child_full(widget_class, name, internal_child, struct_offset);


}/* }}} */

/* {{{ proto void gtk_widget_class_bind_template_callback_full(mixed widget_class, string callback_name, mixed callback_symbol) */
PHP_FUNCTION(gtk_widget_class_bind_template_callback_full)
{
    zval *zwidget_class;
    char *callback_name;
    int callback_name_len;
    zval *zcallback_symbol;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget_class, php_GtkWidgetClass_class_entry, 1, 0)
        Z_PARAM_STRING(ZEND_SEND_BY_VAL, callback_name, callback_name_len)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcallback_symbol, php_GCallback_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_class_bind_template_callback_full(widget_class, callback_name, callback_symbol);


}/* }}} */

/* {{{ proto void gtk_widget_class_set_connect_func(mixed widget_class, mixed connect_func, mixed connect_data, mixed connect_data_destroy) */
PHP_FUNCTION(gtk_widget_class_set_connect_func)
{
    zval *zwidget_class;
    zval *zconnect_func;
    zval *zconnect_data;
    zval *zconnect_data_destroy;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_OBJECT_OF_CLASS_EX(zwidget_class, php_GtkWidgetClass_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zconnect_func, php_GtkBuilderConnectFunc_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zconnect_data, php_gpointer_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zconnect_data_destroy, php_GDestroyNotify_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();


    gtk_widget_class_set_connect_func(widget_class, connect_func, connect_data, connect_data_destroy);


}/* }}} */

#endif
