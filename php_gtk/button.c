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

#include "button.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_gtk_button_class_entry;
//HashTable             php_gtk_button_prop_handlers;
zend_object_handlers  php_gtk_button_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry php_gtk_button_methods[] = {
    PHP_ME(gtk_button, __construct, arginfo_gtk_button___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/
static void  php_gtk_button_unset_property(zval *object, zval *member, void **cache_slot);
static void  php_gtk_button_write_property(zval *object, zval *member, zval *value, void **cache_slot);
static zval* php_gtk_button_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv);
static char* php_gtk_button_dump(php_gtk_button *list, int tab);

static void
php_gtk_button_unset_dimension(zval *object, zval *offset) {
    //php_gobject *list = ZVAL_GET_PHP_GTK_BUTTON(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
        // @TODO
        //zend_hash_index_del(list->prop_handler, );
        // php_gobject
        break;
    case IS_STRING:
        php_gtk_button_unset_property(object, offset, &cache);
        break;
    default:
        break;
    }
}

static void
php_gtk_button_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_gtk_button_write_property(object, &member, value, &cache);
}

static zval*
php_gtk_button_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
        return NULL;
    }

    php_gtk_button *intern = ZVAL_GET_PHP_GTK_BUTTON(object);
    php_gtk_button *list;
    void *cache=NULL;

    if (Z_TYPE_P(offset)==IS_LONG) {
        ZVAL_NULL(rv);
        return rv;
    } else if (Z_TYPE_P(offset)==IS_STRING) {
        return php_gtk_button_read_property(object, offset, type, &cache, rv);
    } else {
        // error
    }

    return rv;
} /* }}} end php_g_hash_table_read_dimension */

static int
php_gtk_button_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

/* updates *count to hold the number of elements present and returns SUCCESS.
 * Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_gtk_button_count_elements(zval *object, zend_long *count) {

    *count = 0;

    return SUCCESS;
}

static int
php_gtk_button_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}

static HashTable*
php_gtk_button_get_properties(zval *object){
    php_gtk_button  *self =  ZVAL_GET_PHP_GTK_BUTTON(object);
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
    zend_long length = php_gtk_button_length(self);

    zend_hash_init(props, length, NULL, ZVAL_PTR_DTOR, 1);

    zval data;

    php_gtk_button *it;
    for(it=php_gtk_button_first(self); it; it = it->next){
        ZVAL_COPY(&data, &it->data);
        zend_hash_next_index_insert(props, &data);
    }
    */

    return props;
}

static HashTable*
php_gtk_button_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_gtk_button  *obj =  ZVAL_GET_PHP_GTK_BUTTON(object);
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
    zval prev; ZVAL_SET_PHP_GTK_BUTTON(&prev, obj->prev);
    zend_hash_str_update(debug_info, "prev", sizeof("prev")-1, &prev);

    zval data; ZVAL_COPY(&data, &obj->data);
    zend_hash_str_update(debug_info, "data", sizeof("data")-1, &data);

    zval next; ZVAL_SET_PHP_GTK_BUTTON(&next, obj->next);
    zend_hash_str_update(debug_info, "next", sizeof("next")-1, &next);
    */

    return debug_info;
}
/* }}} */

static void
php_gtk_button_unset_property(zval *object, zval *member, void **cache_slot) {
    php_gtk_button *obj = ZVAL_GET_PHP_GTK_BUTTON(object);
    zend_string *member_str = zval_get_string(member);
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}

/* {{{ php_gtk_button_write_property */
static void
php_gtk_button_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_gtk_button *obj = ZVAL_GET_PHP_GTK_BUTTON(object);
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
php_gtk_button_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_gtk_button *obj = ZVAL_GET_PHP_GTK_BUTTON(object);
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

/* {{{ php_gtk_button_free_object */
static void
php_gtk_button_free_object(zend_object *object)
{
    php_gtk_button *intern = ZOBJ_TO_PHP_GTK_BUTTON(object);
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(intern);
    TRACE("php_gtk_button_free_object(\"%s\") / %d\n", intern->data.value.str->val, object->gc.refcount);

#if 0
    // TODO connect on destroy
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
/* }}} php_gtk_button_free_object */

static void
php_gtk_button_dtor_object(zend_object *obj) {
    php_gtk_button *intern = ZOBJ_TO_PHP_GTK_BUTTON(obj);
    TRACE("php_gtk_button_dtor_object(\"%s\") / %d\n", intern->data.value.str->val, obj->gc.refcount);

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

/* {{{ php_gtk_button_create_object */
static zend_object*
php_gtk_button_create_object(zend_class_entry *class_type)
{
    php_gtk_button *intern = ecalloc(1, sizeof(php_gtk_button) + zend_object_properties_size(class_type));
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(intern);

    zend_object_std_init(&gobject->std, class_type);
    object_properties_init(&gobject->std, class_type);

    gobject->ptr = NULL;
    gobject->properties = NULL;

    gobject->std.handlers = &php_gtk_button_handlers;

    TRACE("php_gtk_button_create_object(%p) / %d\n", &gobject->std, gobject->std.gc.refcount);
    return &gobject->std;
}
/* }}} php_gtk_button_create_object */

/*
static void php_gtk_button_dtor_prop_handler(zval *zv)
{
    free(Z_PTR_P(zv));
}
*/

static zend_object_handlers*
php_gtk_button_get_handlers()
{
    memcpy(&php_gtk_button_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_gtk_button_handlers.offset = PHP_GTK_BUTTON_OFFSET;
    //php_gtk_button_handlers.clone_obj;
    //php_gtk_button_handlers.compare;
    //php_gtk_button_handlers.compare_objects;
    //php_gtk_button_handlers.get_constructor;
    php_gtk_button_handlers.dtor_obj = php_gtk_button_dtor_object;
    php_gtk_button_handlers.free_obj = php_gtk_button_free_object;
    php_gtk_button_handlers.read_property = php_gtk_button_read_property;
    php_gtk_button_handlers.write_property = php_gtk_button_write_property;
    php_gtk_button_handlers.unset_property = php_gtk_button_unset_property;
    //php_gtk_button_handlers.get_property_ptr_ptr = php_gtk_button_get_property_ptr_ptr;

    php_gtk_button_handlers.get_debug_info = php_gtk_button_get_debug_info;
    php_gtk_button_handlers.get_properties = php_gtk_button_get_properties;//get_properties_for TODO php 8.0
    //php_gtk_button_handlers.set = php_gtk_button_set;
    php_gtk_button_handlers.cast_object = php_gtk_button_cast_object;

    php_gtk_button_handlers.count_elements = php_gtk_button_count_elements;
    php_gtk_button_handlers.has_dimension = php_gtk_button_has_dimension;
    php_gtk_button_handlers.read_dimension = php_gtk_button_read_dimension;
    php_gtk_button_handlers.unset_dimension = php_gtk_button_unset_dimension;
    php_gtk_button_handlers.write_dimension = php_gtk_button_write_dimension;


    return &php_gtk_button_handlers;
}


/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/
/*{{{ php_gtk_button_class_init */
zend_class_entry*
php_gtk_button_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gtk_button_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "GtkButton", php_gtk_button_methods);
    php_gtk_button_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_gtk_button_class_entry->create_object = php_gtk_button_create_object;
    //ce->serialize;

    /*
    zend_hash_init(&php_gtk_button_prop_handlers, 0, NULL, php_gtk_button_dtor_prop_handler, 1);
    php_gtk_button_register_prop_handler(&php_gtk_button_prop_handlers, "prev", sizeof("prev")-1, php_gtk_button_read_prev, php_gtk_button_write_prev);
    php_gtk_button_register_prop_handler(&php_gtk_button_prop_handlers, "data", sizeof("data")-1, php_gtk_button_read_data, php_gtk_button_write_data);
    php_gtk_button_register_prop_handler(&php_gtk_button_prop_handlers, "next", sizeof("next")-1, php_gtk_button_read_next, php_gtk_button_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_gtk_button_prop_handlers);
    */

    return php_gtk_button_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/


//static php_gtk_button_class php_gtk_button_virtuals;
static GtkButtonClass php_gtk_button_klass = {G_TYPE_INVALID};

static void
php_gtk_button_override_widget_get_preferred_width(GtkWidget *widget,
                                                   gint      *minimum_width,
                                                   gint      *natural_width) {
    static GList *recursive_widget = NULL;
    zend_object *zobject = g_object_get_data(G_OBJECT(widget), "zend_object");

    zend_function *func = NULL;
    zend_bool is_override = FALSE;
    zend_bool is_recursive = NULL!=
    g_list_find(recursive_widget, widget);

    if (NULL==zobject) {
       g_print(" UNLIKELY REACHED : 2\n");
       //GtkWidgetClass *klass = GTK_WIDGET_CLASS(&php_gtk_button_klass);// <---------------------------
       //GtkWidgetClass *klass = GTK_WIDGET_GET_CLASS(widget);
       //klass->get_preferred_width(widget, minimum_width, natural_width);
       *minimum_width = 20;
       *natural_width = 20;
       return;
    }

    if (!is_recursive) {
        // try to find override user_function
        func = php_gobject_get_user_method(zobject, "GtkWidget::get_preferred_width");//<-------------
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

    if (is_override) {
        //g_print("  call override function\n");
        recursive_widget =
        g_list_append(recursive_widget, widget);

        zval retval;
        char *function_name = func->common.function_name->val;
#if 1
        zval zwidget; ZVAL_OBJ(&zwidget, zobject);
        zval zminimum_width;
        zval znatural_width;
        ZVAL_NEW_REF(&zminimum_width, &zminimum_width);//<------------------------------------------------------
        ZVAL_NEW_REF(&znatural_width, &znatural_width);
        int result = zend_call_method(&zwidget, NULL, NULL, function_name, strlen(function_name), &retval, 2, &zminimum_width, &znatural_width);
        if (FAILURE != result) {
            if (Z_TYPE(zminimum_width)==IS_REFERENCE) {
                if (Z_TYPE(zminimum_width.value.ref->val)==IS_DOUBLE) {
                    *minimum_width = zminimum_width.value.ref->val.value.dval;
                    *natural_width = znatural_width.value.ref->val.value.dval;
                } else if (Z_TYPE(zminimum_width.value.ref->val)==IS_LONG) {
                    //TODO check define(strict_types=1)
                    //zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
                    *minimum_width = zminimum_width.value.ref->val.value.lval;
                    *natural_width = znatural_width.value.ref->val.value.lval;
                }
            }
        } else {
            g_print("zend_call_method_ Failure\n");
        }
        zval_ptr_dtor(&zminimum_width);
        zval_ptr_dtor(&znatural_width);

#else
        int result;
        zend_fcall_info fci;
        //zval retval;
        zval zminimum; ZVAL_DOUBLE(&zminimum, *minimum_width);
        zval znatural; ZVAL_DOUBLE(&znatural, *natural_width);
        //zval zminimum_width;
        //zval znatural_width;
        //ZVAL_NEW_REF(&zminimum_width, &zminimum);
        //ZVAL_NEW_REF(&znatural_width, &znatural);
        zval params[2];
            //ZVAL_COPY_VALUE(&params[0], &zminimum_width);// ?
            //ZVAL_COPY_VALUE(&params[1], &znatural_width);// ?
            ZVAL_COPY_VALUE(&params[0], &zminimum);// ?
            ZVAL_COPY_VALUE(&params[1], &znatural);// ?

        ///zend_call_method()
        fci.size = sizeof(fci);
        fci.object = zobject;//Z_OBJ_P(zwidget);
        fci.retval = &retval;
        fci.param_count = 2;
        fci.params = params;
        fci.no_separation = 0;
            ZVAL_STRINGL(&fci.function_name, function_name, strlen(function_name));
            result = zend_call_function(&fci, NULL);
        zval_ptr_dtor(&fci.function_name);

        if (FAILURE != result) {

            double __minimum_width = 0;
            double __natural_width = 0;
            if (Z_TYPE(params[0])==IS_REFERENCE) {
                if (Z_TYPE(params[0].value.ref->val)==IS_DOUBLE) {
                    __minimum_width = params[0].value.ref->val.value.dval;
                    __natural_width = params[1].value.ref->val.value.dval;
                } else if (Z_TYPE(params[0].value.ref->val)==IS_LONG) {
                    __minimum_width = params[0].value.ref->val.value.lval;
                    __natural_width = params[1].value.ref->val.value.lval;
                }
            }
            //ZVAL_DOUBLE(zminimum_width, __minimum_width);
            //ZVAL_DOUBLE(znatural_width, __natural_width);
            *minimum_width = __minimum_width;
            *natural_width = __natural_width;
        } else {
            g_print("zend_call_method_ Failure\n");
        }
#endif

        recursive_widget =
        g_list_remove(recursive_widget, widget);
    } else {
        GtkWidgetClass *klass = GTK_WIDGET_CLASS(&php_gtk_button_klass);
        klass->get_preferred_width(widget, minimum_width, natural_width);
        //g_print(" %d; %d\n", *minimum_width, *natural_width);
    }

}


static void
php_gtk_button_class_init_override() {
    GtkButtonClass *button_klass = g_type_class_peek(GTK_TYPE_BUTTON);
    GtkBinClass *bin_klass = &button_klass->parent_class;
    GtkContainerClass *container_klass = &bin_klass->parent_class;
    GtkWidgetClass *widget_klass = &container_klass->parent_class;
    GObjectClass *object_klass = &widget_klass->parent_class;

    if (NULL==G_TYPE_FROM_CLASS(&php_gtk_button_klass)) {
        memcpy(&php_gtk_button_klass, button_klass, sizeof(GtkButtonClass));
        G_TYPE_FROM_CLASS(&php_gtk_button_klass) = GTK_TYPE_BUTTON;

        // override GObjectClass
        // override GtkWidgetClass
        widget_klass->get_preferred_width = php_gtk_button_override_widget_get_preferred_width;
        // override GtkContainerClass
        // override GtkBinClass
        // override GtkButtonClass
        //button_klass->clicked = php_gtk_button_override_clicked;
    }

}

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
void
php_gtk_button_new_with_label(php_gtk_button*self, zend_string *label) {
    php_gobject_object *object = PHP_GTK_BUTTON_TO_PHP_G_OBJECT(self);

    GtkWidget *button = gtk_button_new_with_label(label->val);
    object->ptr = G_OBJECT(button);
    g_object_set_data(G_OBJECT(button), "zend_object", &object->std);

    // See Widget ! create new class type ( php_GtkButton)
    //php_gtk_button_class_init_override();
}



/*----------------------------------------------------------------------+
| PHP_METHOD                                                           |
+----------------------------------------------------------------------*/

/* {{{ GObject::__construct() */
PHP_METHOD(gtk_button, __construct)
{

    zend_object *zobj = Z_OBJ_P(getThis());
    php_gtk_button *self = ZOBJ_TO_PHP_GTK_BUTTON(zobj);

    zend_string *label = zend_string_init("test", strlen("test"), 0);

    php_gtk_button_new_with_label(self, label);

    zend_string_release(label);


}
/* }}} */

/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/

/* {{{ proto GtkWidget gtk_button_new_with_label(label) */
PHP_FUNCTION(gtk_button_new_with_label)
{
    zval *zlabel = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zlabel)
    ZEND_PARSE_PARAMETERS_END();

    zend_string *label = zlabel==NULL || ZVAL_IS_NULL(zlabel) || Z_TYPE_P(zlabel)!=IS_STRING ? NULL : zlabel->value.str;

    zend_object *z_button = php_gtk_button_create_object(php_gtk_button_class_entry);
    php_gtk_button *button = ZOBJ_TO_PHP_GTK_BUTTON(z_button);
    php_gtk_button_new_with_label(button, label);

    ZVAL_OBJ(return_value, z_button);

    zval member; ZVAL_STRING(&member, "label");
    zval val; ZVAL_STRING(&val, label->val);
    void *slot = NULL;
    php_gtk_button_write_property(return_value, &member, &val, &slot);
    Z_TRY_DELREF(member);
    Z_TRY_DELREF(val);

    //GC_REFCOUNT(z_button)++;
    RETURN_OBJ(z_button);
}/* }}} */
