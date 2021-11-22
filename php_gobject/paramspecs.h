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

#ifndef PHP_GOBJECT_PARAM_SPECS_H
#define PHP_GOBJECT_PARAM_SPECS_H


#define PHP_GOBJECT_PARAM_SPEC(ptr)           ((php_gobject_param_spec*)(ptr))
#define PHP_GOBJECT_PARAM_SPEC_CLASS          php_gobject_param_spec_class_entry
#define PHP_GOBJECT_PARAM_SPEC_OFFSET         (sizeof(php_gobject_param_spec) - sizeof(zend_object))

#define ZOBJ_IS_PHP_GOBJECT_PARAM_SPEC(obj)   ((obj)!=NULL && obj->ce == php_gobject_param_spec_class_entry)
#define ZOBJ_TO_PHP_GOBJECT_PARAM_SPEC(std)   PHP_GOBJECT_PARAM_SPEC( ((void*)(std))-PHP_GOBJECT_PARAM_SPEC_OFFSET )

#define ZVAL_IS_PHP_GOBJECT_PARAM_SPEC(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GOBJECT_PARAM_SPEC((val)->value.obj))
#define ZVAL_GET_PHP_GOBJECT_PARAM_SPEC(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GOBJECT_PARAM_SPEC((val)->value.obj))

#define ZVAL_SET_PHP_GOBJECT_PARAM_SPEC(z, o) do {        \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)


#define PHP_GOBJECT_PARAM_SPEC_COPY(src, dest) \


#define PHP_GOBJECT_PARAM_SPEC_SET(dest, src) \



#define DECL_PHP_GOBJECT_PARAM_SPEC(name) \
    g_value __##name; \
    g_value *name = &__##name; \
    PHP_GOBJECT_VALUE_COPY(php_##name, name);




#define PHP_GOBJECT_PARAM_SPEC_FE() \



#define PHP_GOBJECT_PARAM_SPEC_MINIT_FUNCTION(container_ce, parent_ce) \
    php_gobject_param_spec_class_init(container_ce, parent_ce)

#define PHP_GOBJECT_PARAM_SPEC_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GOBJECT_PARAM_SPEC_RSHUTDOWN_FUNCTION() {\
}

extern zend_class_entry     *php_gobject_param_spec_class_entry;


typedef struct _php_gobject_param_spec php_gobject_param_spec;
struct _php_gobject_param_spec {
    GParamSpec *ptr;

    zend_object std;
};

zend_object *php_gobject_param_spec_new(GParamSpec *pspec);

zend_class_entry*
php_gobject_param_spec_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);


ZEND_BEGIN_ARG_INFO_EX(arginfo_g_param_spec___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(g_param_spec, __construct);


#endif	/* PHP_GOBJECT_PARAM_SPECS_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
