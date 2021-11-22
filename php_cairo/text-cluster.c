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

#include <cairo/cairo.h>

#include "php_gtk.h"

#include "php_cairo/text-cluster.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_text_cluster_t_class_entry;// struct
zend_object_handlers  php_cairo_text_cluster_t_handlers;




enum _php_cairo_text_cluster_t_properties {
    PHP_CAIRO_TEXT_CLUSTER_T_NUM_BYTES = 1,
    PHP_CAIRO_TEXT_CLUSTER_T_NUM_GLYPHS = 2
};
//typedef enum php_cairo_text_cluster_t_properties php_cairo_text_cluster_t_properties;



/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_text_cluster_t_methods[] = {
    PHP_ME(cairo_text_cluster_t, __construct, arginfo_cairo_text_cluster_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_text_cluster_t_create_object */
static zend_object*
php_cairo_text_cluster_t_create_object(zend_class_entry *class_type)
{
    php_cairo_text_cluster_t *intern = zend_object_alloc(sizeof(php_cairo_text_cluster_t), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);


    ZVAL_LONG(&intern->num_bytes, 0);
    ZVAL_LONG(&intern->num_glyphs, 0);

    intern->std.handlers = &php_cairo_text_cluster_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_text_cluster_t_create_object */


static void
php_cairo_text_cluster_t_dtor_object(zend_object *obj) {
    //php_cairo_text_cluster_t *intern = ZOBJ_TO_PHP_CAIRO_TEXT_CLUSTER_T(obj);

}

/* {{{ php_cairo_text_cluster_t_free_object */
static void
php_cairo_text_cluster_t_free_object(zend_object *object)
{
    php_cairo_text_cluster_t *intern = ZOBJ_TO_PHP_CAIRO_TEXT_CLUSTER_T(object);

    Z_TRY_DELREF(intern->num_bytes);
    Z_TRY_DELREF(intern->num_glyphs);

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_text_cluster_t_free_object */




/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_cairo_text_cluster_t_setter_int(php_cairo_text_cluster_t *intern, zval *value, char *name, zval *dest) {
    if (Z_TYPE_P(value)==IS_LONG) {
        ZVAL_SET_LONG(dest, value->value.lval);
    } else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        const char *type_name = zend_zval_type_name(value);
        if (strict_types) {
            zend_error(E_USER_NOTICE, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\cairo_text_cluster_t::$%s of type float,", type_name, name);
        } else {
            int allow_errors = -1;
            zend_long lval=0;
            double dval=0;
            if (Z_TYPE_P(value)==IS_STRING) {
                zend_uchar z_type = is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), &lval, &dval, allow_errors);
                if (z_type==IS_LONG) {
                    ZVAL_SET_LONG(dest, lval);
                    zend_error(E_USER_NOTICE, "Implicite %s(%s) to int(%d) convertion,", type_name, value->value.str->val, lval);
                    return;
                } else if(z_type==IS_DOUBLE) {
                    ZVAL_SET_LONG(dest, (int)dval);
                    zend_error(E_USER_NOTICE, "Implicite %s(%s) to int(%d) convertion,", type_name, value->value.str->val, (int)dval);
                    return;
                }
            }
            if (Z_TYPE_P(value)==IS_DOUBLE) {
                ZVAL_SET_LONG(dest, (int)value->value.dval);
                zend_error(E_USER_WARNING, "Implicite float(%f) to int(%d) convertion,", value->value.dval, (int)value->value.dval);
                return;
            }
            zend_error(E_USER_NOTICE, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\cairo_text_cluster_t::$%s of type int,", type_name, name);
        }
    }
}




struct PhpCairoTextClusterTProperty {
  const char *name;
  int code;
  void (*setter) (php_cairo_text_cluster_t *intern, zval *rvalue, char *name, zval *dest);
};

static const struct PhpCairoTextClusterTProperty php_cairo_text_cluster_t_properties[] = {
    {"num_bytes", PHP_CAIRO_TEXT_CLUSTER_T_NUM_BYTES, php_cairo_text_cluster_t_setter_int},
    {"num_glyphs", PHP_CAIRO_TEXT_CLUSTER_T_NUM_GLYPHS, php_cairo_text_cluster_t_setter_int}
};


const struct PhpCairoTextClusterTProperty*
php_cairo_text_cluster_t_properties_lookup (const char *str, size_t len)
{
    if (len == 9) {
        if (str[0] == 'n' && str[1] == 'u' && str[2] == 'm' && str[3] == '_'
         && str[4] == 'b' && str[5] == 'y' && str[6] == 't' && str[7] == 'e'
         && str[8] == 's') {
            return &php_cairo_text_cluster_t_properties[0];
        }
    } else if (len == 10) {
        if (str[0] == 'n' && str[1] == 'u' && str[2] == 'm' && str[3] == '_'
         && str[4] == 'g' && str[5] == 'l' && str[6] == 'y' && str[7] == 'p'
         && str[8] == 'h' && str[9] == 's') {
            return &php_cairo_text_cluster_t_properties[1];
        }
    }
    return 0;
}

/* {{{ php_cairo_text_cluster_t_read_property */
static zval*
php_cairo_text_cluster_t_read_property(zend_object *object, zend_string *member_str, int type, void **cache_slot, zval *rv)
{
    php_cairo_text_cluster_t *intern = ZOBJ_TO_PHP_CAIRO_TEXT_CLUSTER_T(object);

    const struct PhpCairoTextClusterTProperty *cmd = php_cairo_text_cluster_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_TEXT_CLUSTER_T_NUM_BYTES:
            ZVAL_COPY(rv, &intern->num_bytes);
            return rv;
            break;
        case PHP_CAIRO_TEXT_CLUSTER_T_NUM_GLYPHS:
            ZVAL_COPY(rv, &intern->num_glyphs);
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

/* {{{ php_cairo_text_cluster_t_write_property */
static zval*
php_cairo_text_cluster_t_write_property(zend_object *object, zend_string *member_str, zval *value, void **cache_slot)
{
    php_cairo_text_cluster_t *intern = ZOBJ_TO_PHP_CAIRO_TEXT_CLUSTER_T(object);
    // struct
    const struct PhpCairoTextClusterTProperty *cmd = php_cairo_text_cluster_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_TEXT_CLUSTER_T_NUM_BYTES:
            cmd->setter(intern, value, member_str->val, &intern->num_bytes);
        break;
        case PHP_CAIRO_TEXT_CLUSTER_T_NUM_GLYPHS:
            cmd->setter(intern, value, member_str->val, &intern->num_glyphs);
        break;
        }
    } else {
        // property not found
    }
    return value;
}
/* }}} */

/* {{{ php_cairo_text_cluster_t_get_property_ptr_ptr */
static zval*
php_cairo_text_cluster_t_get_property_ptr_ptr(zend_object *object, zend_string *member_str, int type, void **cache_slot)
{
    php_cairo_text_cluster_t *intern = ZOBJ_TO_PHP_CAIRO_TEXT_CLUSTER_T(object);
    zval *retval = NULL;

    const struct PhpCairoTextClusterTProperty *cmd = php_cairo_text_cluster_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_TEXT_CLUSTER_T_NUM_BYTES:
            return &intern->num_bytes;
        case PHP_CAIRO_TEXT_CLUSTER_T_NUM_GLYPHS:
            return &intern->num_glyphs;
        }
    } else {
        // Error
    }

    return retval;
}/* }}} */





/* {{{ php_cairo_text_cluster_t_get_debug_info */
static HashTable*
php_cairo_text_cluster_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_text_cluster_t  *intern = ZOBJ_TO_PHP_CAIRO_TEXT_CLUSTER_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    zval znum_bytes; ZVAL_COPY(&znum_bytes, &intern->num_bytes);
    zend_hash_str_update(debug_info, "num_bytes", sizeof("num_bytes")-1, &znum_bytes);
    zval znum_glyphs; ZVAL_COPY(&znum_glyphs, &intern->num_glyphs);
    zend_hash_str_update(debug_info, "num_glyphs", sizeof("num_glyphs")-1, &znum_glyphs);

    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_text_cluster_t_get_handlers()
{
    memcpy(&php_cairo_text_cluster_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_text_cluster_t_handlers.offset = PHP_CAIRO_TEXT_CLUSTER_T_OFFSET;
    php_cairo_text_cluster_t_handlers.dtor_obj = php_cairo_text_cluster_t_dtor_object;
    php_cairo_text_cluster_t_handlers.free_obj = php_cairo_text_cluster_t_free_object;

    php_cairo_text_cluster_t_handlers.read_property = php_cairo_text_cluster_t_read_property;
    php_cairo_text_cluster_t_handlers.write_property = php_cairo_text_cluster_t_write_property;
    php_cairo_text_cluster_t_handlers.get_property_ptr_ptr = php_cairo_text_cluster_t_get_property_ptr_ptr;

    php_cairo_text_cluster_t_handlers.get_debug_info = php_cairo_text_cluster_t_get_debug_info;


    return &php_cairo_text_cluster_t_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_text_cluster_t_class_init */
zend_class_entry*
php_cairo_text_cluster_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_text_cluster_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_text_cluster_t", php_cairo_text_cluster_t_methods);
    php_cairo_text_cluster_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_text_cluster_t_class_entry->create_object = php_cairo_text_cluster_t_create_object;

    return php_cairo_text_cluster_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
php_cairo_text_cluster_t*
php_cairo_text_cluster_t_new() {
    zend_object *zobj = php_cairo_text_cluster_t_create_object(php_cairo_text_cluster_t_class_entry);
    return ZOBJ_TO_PHP_CAIRO_TEXT_CLUSTER_T(zobj);
}

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

 /* {{{ cairo_text_cluster_t::__construct() */
PHP_METHOD(cairo_text_cluster_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_text_cluster_t *self = ZOBJ_TO_PHP_CAIRO_TEXT_CLUSTER_T(zobj);


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
