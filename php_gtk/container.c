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

#include <gtk/gtk.h>
#include "php_gtk.h"

#include "php_gobject/type.h"
#include "php_gobject/object.h"
#include "php_gobject/object-extends.h"

#include "php_gtk/widget.h"
#include "php_gtk/widget-extends.h"

#include "container.h"

//#include "container-extends.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_gtk_container_class_entry;// class
zend_object_handlers  php_gtk_container_handlers;


PHP_GOBJECT_DEFINE_TYPE(PhpGtkContainer, php_gtk_container, GTK_TYPE_CONTAINER)

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/
void php_gtk_container_init(PhpGtkContainer *widget) {

}
//static void php_gtk_container_class_finalize(PhpGtkContainerClass *klass);
void php_gtk_container_class_init(PhpGtkContainerClass *klass) {

}

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_gtk_container_methods[] = {
    PHP_ME(gtk_container, __construct, arginfo_gtk_container___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};



/* {{{ php_gtk_container_create_object */
static zend_object*
php_gtk_container_create_object(zend_class_entry *class_type)
{
    php_gtk_container *intern = zend_object_alloc(sizeof(php_gtk_container), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->properties = NULL;

    intern->std.handlers = &php_gtk_container_handlers;

    //GType type = php_gtk_widget_get_type(class_type);
    //gobject->ptr = php_gtk_widget_new(type, NULL);
    //gobject->ptr = php_gtk_widget_factory(intern);
    intern->ptr = php_gtk_container_extends(intern);// after handlers

    return &intern->std;
}
/* }}} php_gtk_container_create_object */


static void
php_gtk_container_dtor_object(zend_object *obj) {
    php_gtk_container *intern = ZOBJ_TO_PHP_GTK_CONTAINER(obj);

}

/* {{{ php_gtk_container_free_object */
static void
php_gtk_container_free_object(zend_object *object)
{
    php_gtk_container *intern = ZOBJ_TO_PHP_GTK_CONTAINER(object);

    if (intern->ptr) {
        intern->ptr = NULL;
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} php_gtk_container_free_object */





/* {{{ php_gtk_container_get_debug_info */
static HashTable*
php_gtk_container_get_debug_info(zend_object *object, int *is_temp)
{
    php_gtk_container  *intern = ZOBJ_TO_PHP_GTK_CONTAINER(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_gtk_container_get_handlers()
{
    memcpy(&php_gtk_container_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_gtk_container_handlers.offset = PHP_GTK_CONTAINER_OFFSET;
    php_gtk_container_handlers.dtor_obj = php_gtk_container_dtor_object;
    php_gtk_container_handlers.free_obj = php_gtk_container_free_object;


    php_gtk_container_handlers.get_debug_info = php_gtk_container_get_debug_info;


    return &php_gtk_container_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_gtk_container_class_init */
zend_class_entry*
php_gtk_container_class_minit(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gtk_container_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "GtkContainer", php_gtk_container_methods);
    php_gtk_container_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_gtk_container_class_entry->create_object = php_gtk_container_create_object;
    ///php_gtk_widget_class_entry->ce_flags ^= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;
    php_gtk_container_class_entry->ce_flags |= ZEND_ACC_ABSTRACT;

    return php_gtk_container_class_entry;
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

 /* {{{ gtk_container::__construct() */
PHP_METHOD(gtk_container, __construct)
{
    zend_object *zobj = Z_OBJ_P(getThis());
    php_gtk_container *self = ZOBJ_TO_PHP_GTK_CONTAINER(zobj);

}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

/* {{{ proto void gtk_container_add(GtkWidget widget, GtkWidget widget) */
PHP_FUNCTION(gtk_container_add)
{
    zval *container = NULL;
    zval *widget = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(container, php_gtk_container_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(widget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_container *php_container = ZVAL_IS_PHP_GTK_CONTAINER(container) ? ZVAL_GET_PHP_GTK_CONTAINER(container) : NULL;
    php_gtk_widget *php_widget = ZVAL_IS_PHP_GTK_WIDGET(widget) ? ZVAL_GET_PHP_GTK_WIDGET(widget) : NULL;

    GtkContainer *gtk_container = GTK_CONTAINER(php_container->ptr);
    GtkWidget *gtk_widget = GTK_WIDGET(php_widget->ptr);
    gtk_container_add(gtk_container, gtk_widget);

}/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
