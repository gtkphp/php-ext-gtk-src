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

#include <glib-object.h>
#include "php_gtk.h"

#include "value.h"
//#include "php_gobject/value.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_gobject_value_class_entry;// struct
zend_object_handlers  php_gobject_value_handlers;




enum _php_gobject_value_properties {
    PHP_GOBJECT_VALUE_NAME = 1,
    PHP_GOBJECT_VALUE_VALUE = 2
};
//typedef enum php_gobject_value_properties php_gobject_value_properties;



/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_gobject_value_methods[] = {
    PHP_ME(g_value, __construct, arginfo_g_value___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_gobject_value_create_object */
static zend_object*
php_gobject_value_create_object(zend_class_entry *class_type)
{
    php_gobject_value *intern = zend_object_alloc(sizeof(php_gobject_value), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    //ZVAL_???(intern->value, src.value);

    intern->std.handlers = &php_gobject_value_handlers;

    return &intern->std;
}
/* }}} php_gobject_value_create_object */


static void
php_gobject_value_dtor_object(zend_object *obj) {
    //php_gobject_value *intern = ZOBJ_TO_PHP_GOBJECT_VALUE(obj);

}

/* {{{ php_gobject_value_free_object */
static void
php_gobject_value_free_object(zend_object *object)
{
    php_gobject_value *intern = ZOBJ_TO_PHP_GOBJECT_VALUE(object);

    //zval_ptr_dtor(&intern->value);

    zend_object_std_dtor(&intern->std);
}
/* }}} php_gobject_value_free_object */




/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_gobject_value_setter_char(php_gobject_value *intern, zval *value, char *name, zval *dest) {
    ZVAL_COPY(dest, value);//"char"
}




/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_gobject_value_setter_gvalue(php_gobject_value *intern, zval *value, char *name, zval *dest) {
    ZVAL_COPY(dest, value);//"GValue"
}




struct PhpGObjectValueProperty {
  const char *name;
  int code;
  void (*setter) (php_gobject_value *intern, zval *rvalue, char *name, zval *dest);
};

static const struct PhpGObjectValueProperty php_gobject_value_properties[] = {
    {"name", PHP_GOBJECT_VALUE_NAME, php_gobject_value_setter_char},
    {"value", PHP_GOBJECT_VALUE_VALUE, php_gobject_value_setter_gvalue}
};


const struct PhpGObjectValueProperty*
php_gobject_value_properties_lookup (const char *str, size_t len)
{
    if (len == 4) {
        if (str[0] == 'n' && str[1] == 'a' && str[2] == 'm' && str[3] == 'e') {
            return &php_gobject_value_properties[0];
        }
    } else if (len == 5) {
        if (str[0] == 'v' && str[1] == 'a' && str[2] == 'l' && str[3] == 'u'
         && str[4] == 'e') {
            return &php_gobject_value_properties[1];
        }
    }

    return 0;
}

/* {{{ php_gobject_value_read_property */
static zval*
php_gobject_value_read_property(zend_object *object, zend_string *member_str, int type, void **cache_slot, zval *rv)
{
    php_gobject_value *intern = ZOBJ_TO_PHP_GOBJECT_VALUE(object);

    const struct PhpGObjectValueProperty *cmd = php_gobject_value_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_GOBJECT_VALUE_VALUE:
            //ZVAL_COPY(rv, &intern->gvalue);
            return rv;
            break;
        default:
            //zend_internal_type_error(1, "Internal bug,");
            //zend_error(E_USER_NOTICE, "Internal bug,");
            break;
        }
    } else {
        // property not found
    }

    return rv;
}
/* }}} */

/* {{{ php_gobject_value_write_property */
static zval*
php_gobject_value_write_property(zend_object *object, zend_string *member_str, zval *value, void **cache_slot)
{
    php_gobject_value *intern = ZOBJ_TO_PHP_GOBJECT_VALUE(object);
    // struct
    const struct PhpGObjectValueProperty *cmd = php_gobject_value_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_GOBJECT_VALUE_VALUE:
            //cmd->setter(intern, value, member_str->val, &intern->gvalue);
        break;
        }
    } else {
        // property not found
    }
    return value;
}
/* }}} */

/* {{{ php_gobject_value_get_property_ptr_ptr */
static zval*
php_gobject_value_get_property_ptr_ptr(zend_object *object, zend_string *member_str, int type, void **cache_slot)
{
    php_gobject_value *intern = ZOBJ_TO_PHP_GOBJECT_VALUE(object);
    zval *retval = NULL;

    const struct PhpGObjectValueProperty *cmd = php_gobject_value_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_GOBJECT_VALUE_VALUE:
            //return &intern->value;
            break;
        }
    } else {
        // Error
    }

    return retval;
}/* }}} */





/* {{{ php_gobject_value_get_debug_info */
static HashTable*
php_gobject_value_get_debug_info(zend_object *object, int *is_temp)
{
    php_gobject_value  *intern = ZOBJ_TO_PHP_GOBJECT_VALUE(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    //zval zvalue; ZVAL_COPY(&zvalue, &intern->value);
    //zend_hash_str_update(debug_info, "value", sizeof("value")-1, &zvalue);

    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_gobject_value_get_handlers()
{
    memcpy(&php_gobject_value_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_gobject_value_handlers.offset = PHP_GOBJECT_VALUE_OFFSET;
    php_gobject_value_handlers.dtor_obj = php_gobject_value_dtor_object;
    php_gobject_value_handlers.free_obj = php_gobject_value_free_object;

    php_gobject_value_handlers.read_property = php_gobject_value_read_property;
    php_gobject_value_handlers.write_property = php_gobject_value_write_property;
    php_gobject_value_handlers.get_property_ptr_ptr = php_gobject_value_get_property_ptr_ptr;

    php_gobject_value_handlers.get_debug_info = php_gobject_value_get_debug_info;


    return &php_gobject_value_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_gobject_value_class_init */
zend_class_entry*
php_gobject_value_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gobject_value_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "GValue", php_gobject_value_methods);
    php_gobject_value_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_gobject_value_class_entry->create_object = php_gobject_value_create_object;

    return php_gobject_value_class_entry;
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

 /* {{{ g_value::__construct() */
PHP_METHOD(g_value, __construct)
{
    zend_long  g_type;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(g_type)
    ZEND_PARSE_PARAMETERS_END();

    zend_object *zobj = Z_OBJ_P(getThis());
    php_gobject_value *self = ZOBJ_TO_PHP_GOBJECT_VALUE(zobj);
    g_value_init(&self->gvalue, g_type);

}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

/* {{{ proto g_value_init( ...) */
PHP_FUNCTION(g_value_init)
{
    zval      *instance;
    zend_long  g_type;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL_EX2(instance, 0, 1, 0)
        Z_PARAM_LONG(g_type)
    ZEND_PARSE_PARAMETERS_END();

    if (Z_TYPE(instance->value) == IS_NULL) {
        zend_object *intern = php_gobject_value_create_object(PHP_GOBJECT_VALUE_CLASS);
        php_gobject_value *value = ZOBJ_TO_PHP_GOBJECT_VALUE(intern);

        g_value_init(&value->gvalue, G_TYPE_UINT);

        //ZVAL_MAKE_REF(instance);
        //ZVAL_OBJ(&Z_REF_P(instance)->val, intern);
        ZVAL_OBJ(instance, intern);

        //zval_add_ref(instance);

        //zend_object_release(intern);
    } else {
        // TODO: new GValue(G_TYPE_UINT);
    }

    //g_value_init(&instance_and_params[0], G_TYPE_OBJECT);
    //g_value_set_object(&instance_and_params[0], ZOBJ_TO_PHP_GOBJECT_OBJECT(instance)->ptr);

}


/* {{{ proto g_value_set_uint( ...) */
PHP_FUNCTION(g_value_set_uint)
{
    zval *value;
    zend_long  v_uint;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(value, php_gobject_value_class_entry, 0, 0);
        Z_PARAM_LONG(v_uint)
    ZEND_PARSE_PARAMETERS_END();

    if (ZVAL_IS_PHP_GOBJECT_VALUE(value)) {
        php_gobject_value *zvalue = ZVAL_GET_PHP_GOBJECT_VALUE(value);
        g_value_set_uint(&zvalue->gvalue, v_uint);
        //php_printf("-> %d\n", zvalue->gvalue.data[0].v_uint);
        //php_printf("-> %d\n", zvalue->gvalue.data[1].v_uint);
    } else { }

}

/* {{{ proto g_value_get_uint( ...) */
PHP_FUNCTION(g_value_get_uint)
{
    zval *value;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(value)
    ZEND_PARSE_PARAMETERS_END();

    if (ZVAL_IS_PHP_GOBJECT_VALUE(value)) {
        php_gobject_value *zvalue = ZVAL_GET_PHP_GOBJECT_VALUE(value);
        guint v_uint = g_value_get_uint(&zvalue->gvalue);
        RETURN_LONG(v_uint);
    } else { }

    RETURN_LONG(0);
}



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
