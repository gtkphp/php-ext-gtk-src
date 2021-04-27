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

#include "php_gobject/object.h"

#include "widget.h"

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
static void  php_gtk_widget_write_property(zval *object, zval *member, zval *value, void **cache_slot);
static zval* php_gtk_widget_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv);
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
php_gtk_widget_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_gtk_widget  *obj =  ZVAL_GET_PHP_GTK_WIDGET(object);
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
static void
php_gtk_widget_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
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
    std_hnd->write_property(object, member, value, cache_slot);

    zend_string_release(member_str);
}
/* }}} */

static zval zval_ret;
/* {{{ gtk_read_property */
static zval*
php_gtk_widget_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_gtk_widget *obj = ZVAL_GET_PHP_GTK_WIDGET(object);
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

/* {{{ php_gtk_widget_free_object */
static void
php_gtk_widget_free_object(zend_object *object)
{
    php_gtk_widget *intern = ZOBJ_TO_PHP_GTK_WIDGET(object);
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(intern);
    TRACE("php_gtk_widget_free_object(\"%s\") / %d\n", intern->data.value.str->val, object->gc.refcount);

    if (gobject->ptr) {
        //g_free(gobject->ptr);
        gobject->ptr = NULL;
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
#include "php_cairo/cairo.h"
extern zend_class_entry *php_cairo_t_class_entry;
static gboolean
php_gtk_widget_override_draw(GtkWidget *widget,
                             cairo_t *cr) {
    static GList *recursive_widget = NULL;
    zend_object *zobject = g_object_get_data(G_OBJECT(widget), "zend_object");

    zend_function *func = NULL;
    zend_bool is_override = FALSE;
    zend_bool is_recursive = NULL!=
    g_list_find(recursive_widget, widget);

    if (NULL==zobject) {
       g_print(" UNLIKELY REACHED\n");
       GtkWidgetClass *klass = GTK_WIDGET_CLASS(&php_gtk_widget_klass);// <---------------------------
       return klass->draw(widget, cr);
    }

    if (!is_recursive) {
        // try to find override user_function
        func = php_gobject_get_user_method(zobject, "GtkWidget::draw");//<-------------
        if (func) {
            is_override = TRUE;
        }
        zend_execute_data *current_execute = EG(current_execute_data);
        zend_execute_data *execute = NULL;
        if (NULL!=current_execute) {
            execute = current_execute->prev_execute_data;
        }// else on est mode GTKML

        if (func && execute && execute->func->common.function_name) {
            g_print("... %s\n", current_execute->func->common.function_name->val);// TODO
            g_print("Same object ? %d\n", zobject == execute->This.value.obj);// TODO
            if (0==g_strcmp0(execute->func->common.function_name->val, func->common.function_name->val)) {
                if (ZVAL_IS_PHP_GTK_WIDGET(&execute->This)) {
                    is_override = FALSE;
                }
            }
        }
        //g_print("Call is not recusive\n");
    } else {
        //g_print("Call is recusive\n");
    }

    zval retval; ZVAL_TRUE(&retval);
    if (is_override) {
        //g_print("  call override function\n");
        recursive_widget =
        g_list_append(recursive_widget, widget);

        char *function_name = func->common.function_name->val;
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

    if (NULL==G_TYPE_FROM_CLASS(&php_gtk_widget_klass)) {
        memcpy(&php_gtk_widget_klass, widget_klass, sizeof(GtkWidgetClass));
        G_TYPE_FROM_CLASS(&php_gtk_widget_klass) = type;

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

/// ######################################################################

/* {{{ php_gtk_widget_create_object */
static zend_object*
php_gtk_widget_create_object(zend_class_entry *class_type)
{
    php_gtk_widget *intern = ecalloc(1, sizeof(php_gtk_widget) + zend_object_properties_size(class_type));
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(intern);

    zend_object_std_init(&gobject->std, class_type);
    object_properties_init(&gobject->std, class_type);

    gobject->ptr = NULL;// new GObject ?
    gobject->properties = NULL;

    gobject->std.handlers = &php_gtk_widget_handlers;

    char *key = class_type->name->val;// use prefix 'php__' My\Ns\Widget
    g_print("ce: %s\n", key);
    GType type = g_type_from_name(key);
    if (type==G_TYPE_INVALID) {
        GType type = my_widget_get_type(key);
        gobject->ptr = gtk_widget_new(type, NULL);
        php_gtk_widget_class_init_override(type);
        g_object_set_data(G_OBJECT(gobject->ptr), "zend_object", &gobject->std);

    }


    TRACE("php_gtk_widget_create_object(%p) / %d\n", &gobject->std, gobject->std.gc.refcount);
    return &gobject->std;
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
    php_gtk_widget_handlers.unset_property = php_gtk_widget_unset_property;
    //php_gtk_widget_handlers.get_property_ptr_ptr = php_gtk_widget_get_property_ptr_ptr;

    php_gtk_widget_handlers.get_debug_info = php_gtk_widget_get_debug_info;
    php_gtk_widget_handlers.get_properties = php_gtk_widget_get_properties;//get_properties_for TODO php 8.0
    //php_gtk_widget_handlers.set = php_gtk_widget_set;
    php_gtk_widget_handlers.cast_object = php_gtk_widget_cast_object;

    php_gtk_widget_handlers.count_elements = php_gtk_widget_count_elements;
    php_gtk_widget_handlers.has_dimension = php_gtk_widget_has_dimension;
    php_gtk_widget_handlers.read_dimension = php_gtk_widget_read_dimension;
    php_gtk_widget_handlers.unset_dimension = php_gtk_widget_unset_dimension;
    php_gtk_widget_handlers.write_dimension = php_gtk_widget_write_dimension;


    return &php_gtk_widget_handlers;
}



/*----------------------------------------------------------------------+
| PHP_MINIT                                                            |
+----------------------------------------------------------------------*/
/*{{{ php_gtk_widget_class_init */
zend_class_entry*
php_gtk_widget_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gtk_widget_get_handlers();
    //INIT_NS_CLASS_ENTRY((*ce), "Gnome\\G", "Object", php_gtk_widget_methods);
    INIT_CLASS_ENTRY((*container_ce), "GtkWidget", php_gtk_widget_methods);
    php_gtk_widget_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_gtk_widget_class_entry->create_object = php_gtk_widget_create_object;
    php_gtk_widget_class_entry->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

    /*
    zend_hash_init(&php_gtk_widget_prop_handlers, 0, NULL, php_gtk_widget_dtor_prop_handler, 1);
    php_gtk_widget_register_prop_handler(&php_gtk_widget_prop_handlers, "prev", sizeof("prev")-1, php_gtk_widget_read_prev, php_gtk_widget_write_prev);
    php_gtk_widget_register_prop_handler(&php_gtk_widget_prop_handlers, "data", sizeof("data")-1, php_gtk_widget_read_data, php_gtk_widget_write_data);
    php_gtk_widget_register_prop_handler(&php_gtk_widget_prop_handlers, "next", sizeof("next")-1, php_gtk_widget_read_next, php_gtk_widget_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_gtk_widget_prop_handlers);
    */

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
void
php_gtk_widget_show_all(php_gtk_widget *list, zval *data) {
    zend_object *new_std = php_gtk_widget_create_object(php_gtk_widget_class_entry);
    php_gtk_widget *new_list = ZOBJ_TO_PHP_GTK_WIDGET(new_std);

}



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

/* {{{ proto GObject gtk_widget_show_all(GObject list, mixed data) */
PHP_FUNCTION(gtk_widget_show_all)
{
    zval *zwidget = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zwidget)
    ZEND_PARSE_PARAMETERS_END();


    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget) ? ZVAL_GET_PHP_GTK_WIDGET(zwidget) : NULL;
    php_gobject_object *gwidget = PHP_GOBJECT_OBJECT(widget);
    GtkWidget *gtk_widget = GTK_WIDGET(gwidget->ptr);

    gtk_widget_show_all(gtk_widget);

}/* }}} */

/* {{{ proto GObject gtk_widget_show_all(GObject list, mixed data) */
PHP_FUNCTION(gtk_widget_show)
{
    zval *zwidget = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zwidget)
    ZEND_PARSE_PARAMETERS_END();


    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget) ? ZVAL_GET_PHP_GTK_WIDGET(zwidget) : NULL;
    php_gobject_object *gwidget = PHP_GOBJECT_OBJECT(widget);
    GtkWidget *gtk_widget = GTK_WIDGET(gwidget->ptr);

    gtk_widget_show(gtk_widget);

}/* }}} */

/* {{{ proto GObject gtk_widget_show_all(GObject list, mixed data) */
PHP_FUNCTION(gtk_widget_get_preferred_width)
{
    zval *zwidget = NULL;
    zval *zminimum_width = NULL;
    zval *znatural_width = NULL;

    //Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zwidget)
        Z_PARAM_ZVAL_DEREF(zminimum_width)
        Z_PARAM_ZVAL_DEREF(znatural_width)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget) ? ZVAL_GET_PHP_GTK_WIDGET(zwidget) : NULL;
    if (NULL==widget) {
        //zend_error( TypeError);
        return;
    }

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

