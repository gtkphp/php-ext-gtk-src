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
| Author: Gname                                                        |
+----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_GTK_WIDGET_EXTENDS_H
#define PHP_GTK_WIDGET_EXTENDS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

typedef struct _PhpGtkWidget {
    GtkWidget parent_instance;
} PhpGtkWidget;


#define _PHP_GTK_WIDGET_TRAIT() \
    PhpGObjectObjectTrait parent_trait; \
    zend_function *draw; \
    zend_function *realize

typedef struct _PhpGtkWidgetTrait {
    _PHP_GTK_WIDGET_TRAIT();
} PhpGtkWidgetTrait;

typedef struct _PhpGtkWidgetClass {
    GtkWidgetClass parent_class;
    _PHP_GTK_WIDGET_TRAIT();
} PhpGtkWidgetClass;

void php_gtk_widget_init(PhpGtkWidget *widget);
//void php_gtk_widget_class_finalize(PhpGtkWidgetClass *klass);
void php_gtk_widget_class_init(PhpGtkWidgetClass *klass);

GObject *php_gtk_widget_extends(php_gtk_widget *widget);
GType    php_gtk_widget_get_type(const char *php_class_name);// "Zn_Widget" Zend in C/C++

#endif	/* PHP_GTK_WIDGET_EXTENDS_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
