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

#include <glib-object.h>
#include <gtk/gtk.h>

/*
#include "php_doc/parameter.h"
#include "php_doc/tag.h"
#include "php_doc/comment.h"
#include "php_doc/scanner.h"
*/

#include "php_gobject/object.h"
#include "php_gobject/value.h"
#include "php_gobject/paramspecs.h"
#include "php_gobject/type.h"
#include "php_gobject/object-extends.h"

#include "php_cairo/cairo.h"

#include "php_gdk/rectangle.h"

//php_gtk/
#include "widget.h"
#include "widget-extends.h"

GHashTable *php_gtk_widget_classes=NULL;
//PhpGObjectObject php_gtk_widget_instance;
//PhpGObjectObjectClass php_gtk_widget_classe;

static PhpGObjectObjectClass php_gtk_widget_class = {G_TYPE_INVALID};


extern zend_class_entry *php_cairo_t_class_entry;

typedef struct _PhpGtkWidgetPrivate {
    GdkWindow *window;
} PhpGtkWidgetPrivate;

PHP_GOBJECT_DEFINE_TYPE_EXTENDED(PhpGtkWidget, php_gtk_widget,
                                 GTK_TYPE_WIDGET, 0,
                                 G_ADD_PRIVATE(PhpGtkWidget))

static void
php_gtk_widget_size_allocate(GtkWidget *widget,
                             GtkAllocation *allocation) {

   //= (PhpGtkWidget*)widget;
   PhpGtkWidgetPrivate *priv= php_gtk_widget_get_instance_private(widget);

   gtk_widget_set_allocation(widget, allocation);

   if (gtk_widget_get_realized(widget)) {
      gdk_window_move_resize(priv->window, allocation->x, allocation->y,
          80, 100);
   }
}

static void
php_gtk_widget_realize(GtkWidget *widget) {

    PhpGtkWidgetPrivate *priv = php_gtk_widget_get_instance_private (widget);

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
php_gtk_widget_extends_realize(GtkWidget *widget) {
    zend_object *zobject = g_object_get_data(G_OBJECT(widget), "zend_object");
    php_printf("php_gtk_widget_extends_realize\n");

    PhpGtkWidgetClass *klass = (PhpGtkWidgetClass *) GTK_WIDGET_GET_CLASS(widget);

    zend_function *func = klass->realize;
    zend_bool is_override = NULL!=func;

    if (NULL==zobject) {
       php_printf(" FATAL ERROR REACHED 1\n");
       return TRUE;
    }

    zval retval; ZVAL_TRUE(&retval);
    if (is_override) {

        char *function_name = func->common.function_name->val;
        char *function_name_len = func->common.function_name->len;

        zend_fcall_info_cache fci_cache;
        fci_cache.function_handler = func;
        fci_cache.object = zobject;
        fci_cache.called_scope = zobject->ce;

        int result;
        zend_fcall_info fci;
        zval zwidget;
        ZVAL_OBJ(&zwidget, zobject);
        //cairo_reference(cr);

        zval params[1];
        ZVAL_COPY_VALUE(&params[0], &zwidget);

        fci.size = sizeof(fci);
        fci.object = zobject;//Z_OBJ_P(zwidget);
        fci.retval = &retval;
        fci.param_count = 1;
        fci.params = params;
        fci.named_params = 0;
        ZVAL_STRINGL(&fci.function_name, function_name, function_name_len);
            result = zend_call_function(&fci, &fci_cache);
        zval_ptr_dtor(&fci.function_name);
        if (!result) {
            php_printf(" zend_call_function failled\n");
            /** assertion failed: (_gtk_widget_get_realized (widget)) */
            php_gtk_widget_realize(widget);
        }

        //zend_object_release(&zcr->std);
    } else {
        php_printf(" FATAL ERROR REACHED 2\n");
     }
}

static gboolean
php_gtk_widget_extends_draw(GtkWidget *widget,
                             cairo_t *cr) {
    static GList *recursive_widget = NULL;
    zend_object *zobject = g_object_get_data(G_OBJECT(widget), "zend_object");
    //php_printf("php_gtk_widget_extends_draw\n");

    PhpGtkWidgetClass *klass = (PhpGtkWidgetClass *) GTK_WIDGET_GET_CLASS(widget);

    zend_function *func = klass->draw;
    zend_bool is_override = NULL!=func;
    zend_bool is_recursive = NULL!=
    g_list_find(recursive_widget, widget);

    if (NULL==zobject) {
       php_printf(" FATAL ERROR REACHED 1\n");
       return TRUE;
    }
#if 0
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
#endif
    zval retval; ZVAL_TRUE(&retval);
    if (is_override) {
        //php_printf("  call override function\n");
        recursive_widget =
        g_list_append(recursive_widget, widget);

        char *function_name = func->common.function_name->val;
        char *function_name_len = func->common.function_name->len;

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

        recursive_widget =
        g_list_remove(recursive_widget, widget);
    } else {
        php_printf("   OK\n");
        GtkWidgetClass *gtkwidget_klass = g_type_class_peek(GTK_TYPE_WIDGET);
        //GtkWidgetClass *klass = GTK_WIDGET_CLASS(&php_gtk_widget_klass);
        return gtkwidget_klass->draw(widget, cr);
    }

    if (Z_TYPE(retval)==IS_TRUE) return TRUE;
    if (Z_TYPE(retval)==IS_FALSE) return FALSE;

    return TRUE;
}

void php_gtk_widget_init(PhpGtkWidget *widget) {
}

static void php_gtk_widget_class_finalize(PhpGtkWidgetClass *klass) {
}

void php_gtk_widget_class_init(PhpGtkWidgetClass *klass) {

   GObjectClass *gobject_klass;
   GtkWidgetClass *widget_klass;

   gobject_klass = G_OBJECT_CLASS(klass);
   widget_klass = GTK_WIDGET_CLASS(klass);
   //php_printf("  TODO override class GtkWidget+GObject\n");

   /*
   php_gtk_widget_extends_parent_class = g_type_class_peek_parent (klass);
   if (php_gtk_widget_extends_private_offset != 0)// GLIB_VERSION_MAX_ALLOWED >= GLIB_VERSION_2_38
     g_type_class_adjust_private_offset (klass, &php_gtk_widget_extends_private_offset);
   */

   /* Override widget class methods */
   //w_class->realize = my_widget_realize;
   //w_class->size_allocate = my_widget_size_allocate;

   zend_object   *zobject = pop_zend();
   zend_function *func_draw;

   klass->draw = php_gobject_object_get_user_method(zobject, "GtkWidgetClass.draw");//<-------------
   if (klass->draw) widget_klass->draw = php_gtk_widget_extends_draw;
   klass->realize = php_gobject_object_get_user_method(zobject, "GtkWidgetClass.realize");//<-------------
   if (klass->realize) widget_klass->realize = php_gtk_widget_extends_realize;
   else                widget_klass->realize = php_gtk_widget_realize;
   widget_klass->size_allocate = php_gtk_widget_size_allocate;
   //else widget_klass->draw = php_gtk_widget_draw;

   /*
   func = php_gobject_object_get_user_method(zobject, "GObjectClass.get_property");//<-------------
   if (func) widget_klass->size_allocate = php_gtk_widget_size_allocate;
   func = php_gobject_object_get_user_method(zobject, "GObjectClass.set_property");//<-------------
   if (func) widget_klass->realize = php_gtk_widget_realize;
   */

   /*
   gobject_klass->get_property = php_gobject_object_get_property;
   gobject_klass->set_property = php_gobject_object_set_property;
   */

   /* Install property */

   //g_object_class_install_property(g_class, P_PERCENT, pspec);

   /* Add private data */
   //g_type_class_add_private(g_class, sizeof(MyCpuPrivate));
}



#if 0

typedef struct _pair_type_name_t {
    GType type;
    gchar *name;
} pair_type_name_t;

static GMutex  php_gtk_widget_once_mutex;
static GCond   php_gtk_widget_once_cond;
static GArray *php_gtk_widget_once_init_array = NULL;// Array of pair_type_name_t( Store a stack of GType==G_TYPE_INVALID)
// un tableau de reference de GType en cours de construction

gboolean
php_gtk_widget_once_init_enter (const char *name, GType *type)
{
  pair_type_name_t pair = {G_TYPE_INVALID, NULL};// string name memory freed!
  gboolean need_init = TRUE;
  g_mutex_lock (&php_gtk_widget_once_mutex);

  if (php_gtk_widget_once_init_array==NULL) {
      php_gtk_widget_once_init_array = g_array_sized_new(FALSE, FALSE, sizeof(pair_type_name_t), 60);// concurrent reallocation
      php_gtk_widget_once_init_array = g_array_append_val(php_gtk_widget_once_init_array, pair);
      g_array_index(php_gtk_widget_once_init_array, pair_type_name_t, php_gtk_widget_once_init_array->len).type = G_TYPE_INVALID;
      g_array_index(php_gtk_widget_once_init_array, pair_type_name_t, php_gtk_widget_once_init_array->len).name = g_strdup(name);
      need_init = TRUE;
  } else {
      for (int i=0; i<php_gtk_widget_once_init_array->len; i++) {
          pair_type_name_t *pair = &g_array_index(php_gtk_widget_once_init_array, pair_type_name_t, i);
          if (0==g_strcmp0(pair->name, name)) {
              need_init = FALSE;// occurence found
              //value_location = &pair->type;
              if (G_TYPE_INVALID!=type) {
                  *type = pair->type;
                  break;
              }
              do
                g_cond_wait (&php_gtk_widget_once_cond, &php_gtk_widget_once_mutex);//<<----- concurrent
              while (G_TYPE_INVALID!=pair->type);// if array realloc( append_val) pair poiter is out-of-memory
              *type = pair->type;                // todo: fix => redo the search

              break;
          }
      }
      if (need_init) {// not found
          //if realloc( ex: 3 types remaind waiting)
          php_gtk_widget_once_init_array = g_array_append_val(php_gtk_widget_once_init_array, pair);//<<----------------------------------- $->data concurrent
          g_array_index(php_gtk_widget_once_init_array, pair_type_name_t, php_gtk_widget_once_init_array->len).type = G_TYPE_INVALID;
          g_array_index(php_gtk_widget_once_init_array, pair_type_name_t, php_gtk_widget_once_init_array->len).name = g_strdup(name);
          need_init = TRUE;
      }

  }

  g_mutex_unlock (&php_gtk_widget_once_mutex);
  return need_init;
}

void
php_gtk_widget_once_init_leave (const gchar *name,
                                gsize result)
{
  //g_return_if_fail (value_location);
  g_return_if_fail (result != G_TYPE_INVALID);

  for (int i=0; i<php_gtk_widget_once_init_array->len; i++) {
      pair_type_name_t *pair = &g_array_index(php_gtk_widget_once_init_array, pair_type_name_t, i);
      if (0==g_strcmp0(pair->name, name)) {
          // occurence found
          pair->type = result;
          break;
      }
  }// else error

  g_mutex_lock (&php_gtk_widget_once_mutex);
  //g_return_if_fail (php_gtk_widget_once_init_array != NULL);
  //php_gtk_widget_once_init_array = g_slist_remove (php_gtk_widget_once_init_array, (void*) value_location);
  g_cond_broadcast (&php_gtk_widget_once_cond);
  g_mutex_unlock (&php_gtk_widget_once_mutex);
}


// How to get type ?
GType
php_gtk_widget_get_type(const char *name)
{
  GType type_id = G_TYPE_INVALID;

  if (php_gtk_widget_once_init_enter (name, &type_id))
    {
      type_id =
        g_type_register_static_simple (GTK_TYPE_WIDGET,
                                       g_intern_string(name),//g_intern_static_string (ce_name),
                                       sizeof (PhpGtkWidgetClass),
                                       (GClassInitFunc)(void (*)(void)) php_gtk_widget_extends_class_init,
                                       sizeof (PhpGtkWidget),
                                       (GInstanceInitFunc)(void (*)(void)) php_gtk_widget_extends_init,
                                       (GTypeFlags) 0);

      php_gtk_widget_extends_private_offset =
        g_type_add_instance_private (type_id, sizeof (PhpGtkWidgetPrivate));

      php_gtk_widget_once_init_leave (name, type_id);
    }

  return type_id;
}

#define canonical_replace(name, search, replace) for(unsigned int i=0; name[i]!='\0'; i++){if (name[i]==search) name[i]=replace; }

GObject *php_gtk_widget_extends(php_gtk_widget *widget)
{
    // char name[buffer_len]
    // if widget->std.ce->name->len > buffer_len
    char *name = g_strdup(widget->std.ce->name->val);
    canonical_replace(name, '\\', '_')
    //php_printf("php_gtk_widget_extends(%s)\n", name);
    //else canonical_copy(dest, src);

    GType type = g_type_from_name(name);
    if (type==G_TYPE_INVALID) {
        g_print("  Create new type : %s\n", name);

        type = php_gtk_widget_get_type(name);
        push_zend(&widget->std);// used in get_property when G_PARAM_CONSTRUCT
        widget->ptr = gtk_widget_new(type, NULL);
    } else {
        //if (0==g_strcmp0(name, "GtkWidget")) { gtk_widget_new(PHP_TYPE_GTK_WIDGET, NULL);
        widget->ptr = gtk_widget_new(type, NULL);
    }
    g_object_set_data(G_OBJECT(widget->ptr), "zend_object", &widget->std);

    g_free(name);
    return widget->ptr;
}
#endif
