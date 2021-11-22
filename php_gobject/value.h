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

#ifndef PHP_GOBJECT_VALUE_H
#define PHP_GOBJECT_VALUE_H


#define PHP_GOBJECT_VALUE(ptr)           ((php_gobject_value*)(ptr))
#define PHP_GOBJECT_VALUE_CLASS          php_gobject_value_class_entry
#define PHP_GOBJECT_VALUE_OFFSET         (sizeof(php_gobject_value) - sizeof(zend_object))

#define ZOBJ_IS_PHP_GOBJECT_VALUE(obj)   ((obj)!=NULL && obj->ce == php_gobject_value_class_entry)
#define ZOBJ_TO_PHP_GOBJECT_VALUE(std)   PHP_GOBJECT_VALUE( ((void*)(std))-PHP_GOBJECT_VALUE_OFFSET )

#define ZVAL_IS_PHP_GOBJECT_VALUE(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GOBJECT_VALUE((val)->value.obj))
#define ZVAL_GET_PHP_GOBJECT_VALUE(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GOBJECT_VALUE((val)->value.obj))

#define ZVAL_SET_PHP_GOBJECT_VALUE(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)


#define PHP_GOBJECT_VALUE_COPY(src, dest) \


#define PHP_GOBJECT_VALUE_SET(dest, src) \



#define DECL_PHP_GOBJECT_VALUE(name) \
    g_value __##name; \
    g_value *name = &__##name; \
    PHP_GOBJECT_VALUE_COPY(php_##name, name);




#define PHP_GOBJECT_VALUE_FE() \
    PHP_GTK_FE(g_value_init,                           arginfo_g_value_init) \
    PHP_GTK_FE(g_value_set_uint,                       arginfo_g_value_set_uint) \
    PHP_GTK_FE(g_value_get_uint,                       arginfo_g_value_get_uint) \



#define PHP_GOBJECT_VALUE_MINIT_FUNCTION(container_ce, parent_ce) \
    php_gobject_value_class_init(container_ce, parent_ce)

#define PHP_GOBJECT_VALUE_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GOBJECT_VALUE_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_gobject_value_class_entry;


typedef struct _php_gobject_value php_gobject_value;
struct _php_gobject_value {
    GValue gvalue;// of php_gobject_value -> zend_object

    zend_object std;
};

zend_class_entry*
php_gobject_value_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_g_value___construct, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, g_type, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(g_value, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_value_init, 0, 0, 2)
    ZEND_ARG_INFO(ZEND_SEND_BY_REF, instance)
    ZEND_ARG_TYPE_INFO(0, g_type, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_value_init);

ZEND_BEGIN_ARG_INFO_EX(arginfo_g_value_set_uint, 0, 0, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, value, GValue, 0)
    ZEND_ARG_TYPE_INFO(0, v_uint, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_value_set_uint);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_g_value_get_uint, ZEND_RETURN_VALUE, 1, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, value, GValue, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_value_get_uint);


#endif	/* PHP_GOBJECT_VALUE_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
