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

#include "paramspecs.h"
//#include "php_gobject/value.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_gobject_param_spec_class_entry;// struct
zend_object_handlers  php_gobject_param_spec_handlers;




enum _php_gobject_param_spec_properties {
    PHP_GOBJECT_PARAM_SPEC_NAME = 1,
    PHP_GOBJECT_PARAM_SPEC_VALUE = 2
};
//typedef enum php_gobject_param_spec_properties php_gobject_param_spec_properties;



/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_gobject_param_spec_methods[] = {
    PHP_ME(g_param_spec, __construct, arginfo_g_param_spec___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_gobject_param_spec_create_object */
static zend_object*
php_gobject_param_spec_create_object(zend_class_entry *class_type)
{
    php_gobject_param_spec *intern = zend_object_alloc(sizeof(php_gobject_param_spec), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    //ZVAL_???(intern->value, src.value);

    intern->std.handlers = &php_gobject_param_spec_handlers;

    return &intern->std;
}
/* }}} php_gobject_param_spec_create_object */


static void
php_gobject_param_spec_dtor_object(zend_object *obj) {
    //php_gobject_param_spec *intern = ZOBJ_TO_PHP_GOBJECT_PARAM_SPEC(obj);

}

/* {{{ php_gobject_param_spec_free_object */
static void
php_gobject_param_spec_free_object(zend_object *object)
{
    php_gobject_param_spec *intern = ZOBJ_TO_PHP_GOBJECT_PARAM_SPEC(object);

    //zval_ptr_dtor(&intern->value);

    zend_object_std_dtor(&intern->std);
}
/* }}} php_gobject_param_spec_free_object */




/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_gobject_param_spec_setter_char(php_gobject_param_spec *intern, zval *value, char *name, zval *dest) {
    ZVAL_COPY(dest, value);//"char"
}




/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_gobject_param_spec_setter_gvalue(php_gobject_param_spec *intern, zval *value, char *name, zval *dest) {
    ZVAL_COPY(dest, value);//"GValue"
}




struct PhpGObjectParamSpecProperty {
  const char *name;
  int code;
  void (*setter) (php_gobject_param_spec *intern, zval *rvalue, char *name, zval *dest);
};

static const struct PhpGObjectParamSpecProperty php_gobject_param_spec_properties[] = {
    {"name", PHP_GOBJECT_PARAM_SPEC_NAME, php_gobject_param_spec_setter_char},
    {"value", PHP_GOBJECT_PARAM_SPEC_VALUE, php_gobject_param_spec_setter_gvalue}
};


const struct PhpGObjectParamSpecProperty*
php_gobject_param_spec_properties_lookup (const char *str, size_t len)
{
    if (len == 4) {
        if (str[0] == 'n' && str[1] == 'a' && str[2] == 'm' && str[3] == 'e') {
            return &php_gobject_param_spec_properties[0];
        }
    } else if (len == 5) {
        if (str[0] == 'v' && str[1] == 'a' && str[2] == 'l' && str[3] == 'u'
         && str[4] == 'e') {
            return &php_gobject_param_spec_properties[1];
        }
    }

    return 0;
}

/* {{{ php_gobject_param_spec_read_property */
static zval*
php_gobject_param_spec_read_property(zend_object *object, zend_string *member_str, int type, void **cache_slot, zval *rv)
{
    //php_printf("param_spec_read_property(%s)\n", member_str->val);
    php_gobject_param_spec *intern = ZOBJ_TO_PHP_GOBJECT_PARAM_SPEC(object);
    GParamSpec *spec = intern->ptr;

    const struct PhpGObjectParamSpecProperty *cmd = php_gobject_param_spec_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_GOBJECT_PARAM_SPEC_VALUE:
            break;
        case PHP_GOBJECT_PARAM_SPEC_NAME: {
                ZVAL_STRING(rv, spec->name);
                return rv;
            }
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

/* {{{ php_gobject_param_spec_write_property */
static zval*
php_gobject_param_spec_write_property(zend_object *object, zend_string *member_str, zval *value, void **cache_slot)
{
    php_gobject_param_spec *intern = ZOBJ_TO_PHP_GOBJECT_PARAM_SPEC(object);
    // struct
    const struct PhpGObjectParamSpecProperty *cmd = php_gobject_param_spec_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_GOBJECT_PARAM_SPEC_VALUE:
            //cmd->setter(intern, value, member_str->val, &intern->gvalue);
        break;
        case PHP_GOBJECT_PARAM_SPEC_NAME:
            //cmd->setter(intern, value, member_str->val, &intern->gvalue);
            //php_gobject_param_spec_setter_char(intern, zval *value, char *name, zval *dest)
        break;
        default:
            break;
        }
    } else {
        // property not found
    }
    return value;
}
/* }}} */

/* {{{ php_gobject_param_spec_get_property_ptr_ptr */
static zval*
php_gobject_param_spec_get_property_ptr_ptr(zend_object *object, zend_string *member_str, int type, void **cache_slot)
{
    php_gobject_param_spec *intern = ZOBJ_TO_PHP_GOBJECT_PARAM_SPEC(object);
    zval *retval = NULL;
    php_printf("param_spec_get_property_ptr_ptr( %s)\n", member_str->val);

    const struct PhpGObjectParamSpecProperty *cmd = php_gobject_param_spec_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_GOBJECT_PARAM_SPEC_VALUE:
            //return &intern->value;
            break;
        }
    } else {
        // Error
    }

    return retval;
}/* }}} */

static zend_array*
php_gobject_param_spec_get_properties_for(zend_object *object, zend_prop_purpose purpose) {
    php_printf("param_spec_get_properties_for()\n");
    php_gobject_param_spec *intern = ZOBJ_TO_PHP_GOBJECT_PARAM_SPEC(object);
    zend_array *properties; ALLOC_HASHTABLE(properties);

    GParamSpec *spec = intern->ptr;
    zval zname; ZVAL_STRING(&zname, spec->name);
    zend_hash_str_update(properties, "name", sizeof("name")-1, &zname);

    zval zflags; ZVAL_LONG(&zflags, spec->flags);
    zend_hash_str_update(properties, "flags", sizeof("flags")-1, &zflags);

    zval zvalue_type; ZVAL_STRING(&zvalue_type, g_type_name_from_instance(spec->value_type));
    zend_hash_str_update(properties, "value_type", sizeof("value_type")-1, &zvalue_type);

    zval zowner_type; ZVAL_LONG(&zowner_type, g_type_name_from_instance(spec->owner_type));
    zend_hash_str_update(properties, "owner_type", sizeof("owner_type")-1, &zowner_type);

    return properties;
}

static HashTable*
php_gobject_param_spec_get_properties(zend_object *object) {
    php_gobject_param_spec *intern = ZOBJ_TO_PHP_GOBJECT_PARAM_SPEC(object);
    zend_array *properties; ALLOC_HASHTABLE(properties);
    php_printf("param_spec_get_properties()\n");


    return properties;
}

/* {{{ php_gobject_param_spec_get_debug_info */
static HashTable*
php_gobject_param_spec_get_debug_info(zend_object *object, int *is_temp)
{
    php_gobject_param_spec  *intern = ZOBJ_TO_PHP_GOBJECT_PARAM_SPEC(object);
    HashTable   *debug_info,
    *std_props;
    //php_printf("param_spec_get_debug_info()\n");

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    GParamSpec *spec = intern->ptr;
    zval zname; ZVAL_STRING(&zname, spec->name);
    zend_hash_str_update(debug_info, "name", sizeof("name")-1, &zname);

    zval zflags; ZVAL_LONG(&zflags, spec->flags);
    zend_hash_str_update(debug_info, "flags", sizeof("flags")-1, &zflags);

    zval zvalue_type; ZVAL_STRING(&zvalue_type, g_type_name(spec->value_type));
    zend_hash_str_update(debug_info, "value_type", sizeof("value_type")-1, &zvalue_type);

    zval zowner_type; ZVAL_STRING(&zowner_type, g_type_name(spec->owner_type));
    zend_hash_str_update(debug_info, "owner_type", sizeof("owner_type")-1, &zowner_type);

    return debug_info;
}
/* }}} */

static zend_object_handlers*
php_gobject_param_spec_get_handlers()
{
    memcpy(&php_gobject_param_spec_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_gobject_param_spec_handlers.offset = PHP_GOBJECT_PARAM_SPEC_OFFSET;
    php_gobject_param_spec_handlers.dtor_obj = php_gobject_param_spec_dtor_object;
    php_gobject_param_spec_handlers.free_obj = php_gobject_param_spec_free_object;

    php_gobject_param_spec_handlers.read_property = php_gobject_param_spec_read_property;
    php_gobject_param_spec_handlers.write_property = php_gobject_param_spec_write_property;
    php_gobject_param_spec_handlers.get_property_ptr_ptr = php_gobject_param_spec_get_property_ptr_ptr;
    //php_gobject_param_spec_handlers.get_properties_for = php_gobject_param_spec_get_properties_for; // this replace debug_info ?
    //php_gobject_param_spec_handlers.get_properties = php_gobject_param_spec_get_properties;

    php_gobject_param_spec_handlers.get_debug_info = php_gobject_param_spec_get_debug_info;

    zend_register_long_constant("G_PARAM_READWRITE",      sizeof("G_PARAM_READWRITE")-1,      G_PARAM_READWRITE,      CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("G_PARAM_CONSTRUCT_ONLY", sizeof("G_PARAM_CONSTRUCT_ONLY")-1, G_PARAM_CONSTRUCT_ONLY, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("G_PARAM_CONSTRUCT",      sizeof("G_PARAM_CONSTRUCT")-1,      G_PARAM_CONSTRUCT,      CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);


    return &php_gobject_param_spec_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_gobject_param_spec_class_init */
zend_class_entry*
php_gobject_param_spec_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gobject_param_spec_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "GParamSpec", php_gobject_param_spec_methods);
    php_gobject_param_spec_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_gobject_param_spec_class_entry->create_object = php_gobject_param_spec_create_object;

    return php_gobject_param_spec_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/
zend_object *php_gobject_param_spec_new(GParamSpec *pspec) {
    zend_object *zparam_spec = php_gobject_param_spec_create_object(php_gobject_param_spec_class_entry);
    php_gobject_param_spec *param_spec = ZOBJ_TO_PHP_GOBJECT_PARAM_SPEC(zparam_spec);
    param_spec->ptr = pspec;// add ref
    return zparam_spec;
}

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

 /* {{{ g_param_spec::__construct() */
PHP_METHOD(g_param_spec, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_gobject_param_spec *self = ZOBJ_TO_PHP_GOBJECT_PARAM_SPEC(zobj);

}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
