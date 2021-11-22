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

#ifndef PHP_GOBJECT_OBJECT_EXTENDS_H
#define PHP_GOBJECT_OBJECT_EXTENDS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

typedef struct _PhpGObjectObject {
    GObject parent_instance;
} PhpGObjectObject;


#define _PHP_GOBJECT_OBJECT_TRAIT() \
    zend_function *get_property; \
    zend_function *set_property

typedef struct _PhpGObjectObjectTrait {
    _PHP_GOBJECT_OBJECT_TRAIT();
} PhpGObjectObjectTrait;

typedef struct _PhpGObjectObjectClass {
    GObjectClass parent_class;
    int (*changed)(gpointer user_data);

    _PHP_GOBJECT_OBJECT_TRAIT();
} PhpGObjectObjectClass;

/*
void
php_gobject_object_marshaler_INT__POINTER (GClosure     *closure,
                                           GValue       *return_value G_GNUC_UNUSED,
                                           guint         n_param_values,
                                           const GValue *param_values,
                                           gpointer      invocation_hint G_GNUC_UNUSED,
                                           gpointer      marshal_data);

int php_gobject_object_changed(gpointer user_data);
*/
void     php_gobject_object_init(PhpGObjectObject *self);
void     php_gobject_object_class_init(PhpGObjectObjectClass *klass);

GType    php_gobject_object_get_type (const char *name);
GObject *php_gobject_object_extends(php_gobject_object *zobject);
void     php_gobject_object_class_override (GType type, zend_object *zobject);

zend_function *php_gobject_object_get_user_method(zend_object *zobject, char *name);

GType php_gobject_object_create_type(zend_class_entry *class_type, GType parent);

#endif	/* PHP_GOBJECT_OBJECT_EXTENDS_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
