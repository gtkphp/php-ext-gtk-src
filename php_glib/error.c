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

#include <glib.h>

#include "php_gtk.h"



#include "php_glib/error.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_g_error_class_entry;// struct
zend_object_handlers  php_g_error_handlers;




enum _php_g_error_properties {
    PHP_G_ERROR_DOMAIN = 1,
    PHP_G_ERROR_CODE = 2,
    PHP_G_ERROR_MESSAGE = 3
};
//typedef enum php_g_error_properties php_g_error_properties;



/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_g_error_methods[] = {
    PHP_ME(g_error, __construct, arginfo_g_error___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_g_error_create_object */
static zend_object*
php_g_error_create_object(zend_class_entry *class_type)
{
    php_g_error *intern = zend_object_alloc(sizeof(php_g_error), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);


    ZVAL_LONG(&intern->domain, 0);
    ZVAL_LONG(&intern->code, 0);
    ZVAL_NULL(&intern->message);

    intern->std.handlers = &php_g_error_handlers;

    return &intern->std;
}
/* }}} php_g_error_create_object */


static void
php_g_error_dtor_object(zend_object *obj) {
    //php_g_error *intern = ZOBJ_TO_PHP_G_ERROR(obj);

}

/* {{{ php_g_error_free_object */
static void
php_g_error_free_object(zend_object *object)
{
    php_g_error *intern = ZOBJ_TO_PHP_G_ERROR(object);

    //php_printf("str = %d\n", intern->message.value.str->gc.refcount);

    Z_TRY_DELREF(intern->domain);
    Z_TRY_DELREF(intern->code);
    zval_ptr_dtor(&intern->message);

    zend_object_std_dtor(&intern->std);
}
/* }}} php_g_error_free_object */




/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_g_error_setter_gquark(php_g_error *intern, zval *value, char *name, zval *dest) {
    ZVAL_COPY(dest, value);//"GQuark"
}




/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_g_error_setter_int(php_g_error *intern, zval *value, char *name, zval *dest) {
    if (Z_TYPE_P(value)==IS_LONG) {
        ZVAL_SET_LONG(dest, value->value.lval);
    } else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        const char *type_name = zend_zval_type_name(value);
        if (strict_types) {
            zend_error(E_USER_NOTICE, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\GError::$%s of type float,", type_name, name);
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
            zend_error(E_USER_NOTICE, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\GError::$%s of type int,", type_name, name);
        }
    }
}




/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_g_error_setter_char(php_g_error *intern, zval *value, char *name, zval *dest) {
    ZVAL_COPY(dest, value);//"char"
}




struct PhpGErrorProperty {
  const char *name;
  int code;
  void (*setter) (php_g_error *intern, zval *rvalue, char *name, zval *dest);
};

static const struct PhpGErrorProperty php_g_error_properties[] = {
    {"domain", PHP_G_ERROR_DOMAIN, php_g_error_setter_gquark},
    {"code", PHP_G_ERROR_CODE, php_g_error_setter_int},
    {"message", PHP_G_ERROR_MESSAGE, php_g_error_setter_char}
};


const struct PhpGErrorProperty*
php_g_error_properties_lookup (const char *str, size_t len)
{
    if (len == 6) {
        if (str[0] == 'd' && str[1] == 'o' && str[2] == 'm' && str[3] == 'a'
         && str[4] == 'i' && str[5] == 'n') {
            return &php_g_error_properties[0];
        }
    } else if (len == 4) {
        if (str[0] == 'c' && str[1] == 'o' && str[2] == 'd' && str[3] == 'e') {
            return &php_g_error_properties[1];
        }
    } else if (len == 7) {
        if (str[0] == 'm' && str[1] == 'e' && str[2] == 's' && str[3] == 's'
         && str[4] == 'a' && str[5] == 'g' && str[6] == 'e') {
            return &php_g_error_properties[2];
        }
    }
    return 0;
}

/* {{{ php_g_error_read_property */
static zval*
php_g_error_read_property(zend_object *object, zend_string *member_str, int type, void **cache_slot, zval *rv)
{
    php_g_error *intern = ZOBJ_TO_PHP_G_ERROR(object);

    const struct PhpGErrorProperty *cmd = php_g_error_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_G_ERROR_DOMAIN:
            ZVAL_COPY(rv, &intern->domain);
            return rv;
            break;
        case PHP_G_ERROR_CODE:
            ZVAL_COPY(rv, &intern->code);
            return rv;
            break;
        case PHP_G_ERROR_MESSAGE:
            ZVAL_COPY(rv, &intern->message);
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

/* {{{ php_g_error_write_property */
static zval*
php_g_error_write_property(zend_object *object, zend_string *member_str, zval *value, void **cache_slot)
{
    php_g_error *intern = ZOBJ_TO_PHP_G_ERROR(object);
    // struct
    const struct PhpGErrorProperty *cmd = php_g_error_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_G_ERROR_DOMAIN:
            cmd->setter(intern, value, member_str->val, &intern->domain);
        break;
        case PHP_G_ERROR_CODE:
            cmd->setter(intern, value, member_str->val, &intern->code);
        break;
        case PHP_G_ERROR_MESSAGE:
            cmd->setter(intern, value, member_str->val, &intern->message);
        break;
        }
    } else {
        // property not found
    }
    return value;
}
/* }}} */

/* {{{ php_g_error_get_property_ptr_ptr */
static zval*
php_g_error_get_property_ptr_ptr(zend_object *object, zend_string *member_str, int type, void **cache_slot)
{
    php_g_error *intern = ZOBJ_TO_PHP_G_ERROR(object);
    zval *retval = NULL;

    const struct PhpGErrorProperty *cmd = php_g_error_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_G_ERROR_DOMAIN:
            return &intern->domain;
        case PHP_G_ERROR_CODE:
            return &intern->code;
        case PHP_G_ERROR_MESSAGE:
            return &intern->message;
        }
    } else {
        // Error
    }

    return retval;
}/* }}} */





/* {{{ php_g_error_get_debug_info */
static HashTable*
php_g_error_get_debug_info(zend_object *object, int *is_temp)
{
    php_g_error  *intern = ZOBJ_TO_PHP_G_ERROR(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    zval zdomain; ZVAL_COPY(&zdomain, &intern->domain);
    zend_hash_str_update(debug_info, "domain", sizeof("domain")-1, &zdomain);
    zval zcode; ZVAL_COPY(&zcode, &intern->code);
    zend_hash_str_update(debug_info, "code", sizeof("code")-1, &zcode);
    zval zmessage; ZVAL_COPY(&zmessage, &intern->message);
    zend_hash_str_update(debug_info, "message", sizeof("message")-1, &zmessage);

    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_g_error_get_handlers()
{
    memcpy(&php_g_error_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_g_error_handlers.offset = PHP_G_ERROR_OFFSET;
    php_g_error_handlers.dtor_obj = php_g_error_dtor_object;
    php_g_error_handlers.free_obj = php_g_error_free_object;

    php_g_error_handlers.read_property = php_g_error_read_property;
    php_g_error_handlers.write_property = php_g_error_write_property;
    php_g_error_handlers.get_property_ptr_ptr = php_g_error_get_property_ptr_ptr;

    php_g_error_handlers.get_debug_info = php_g_error_get_debug_info;


    return &php_g_error_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_g_error_class_init */
zend_class_entry*
php_g_error_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_g_error_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "GError", php_g_error_methods);
    php_g_error_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_g_error_class_entry->create_object = php_g_error_create_object;

    return php_g_error_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
php_g_error*
php_g_error_new(GError *gerror) {
    zend_object *zerror = php_g_error_create_object(php_g_error_class_entry);
    php_g_error *error = ZOBJ_TO_PHP_G_ERROR(zerror);

    PHP_G_ERROR_SET(error, gerror);

    return error;
}

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

 /* {{{ g_error::__construct() */
PHP_METHOD(g_error, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_g_error *self = ZOBJ_TO_PHP_G_ERROR(zobj);


}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

/* {{{ proto php_GError g_error_new(GQuark domain, int code, char format)
   Creates a new GError with the given domain and code , and a message f... */
PHP_FUNCTION(g_error_new)
{
    zend_long domain;
    zend_long code;
    char *format;
    size_t format_len;
    int argc;
    zval *args = NULL;

    ZEND_PARSE_PARAMETERS_START(3, -1)
        Z_PARAM_LONG(domain);
        Z_PARAM_LONG(code);
        Z_PARAM_STRING(format, format_len);
        Z_PARAM_VARIADIC('*', args, argc);
    ZEND_PARSE_PARAMETERS_END();

    //GError *ret = g_error_new(domain, code, format);
    zend_object *z_ret = php_g_error_create_object(php_g_error_class_entry);
    php_g_error *php_ret = ZOBJ_TO_PHP_G_ERROR(z_ret);

    ZVAL_LONG(&php_ret->domain, domain);
    ZVAL_LONG(&php_ret->code, code);


    zval *params = emalloc(sizeof(zval)*(argc+1));
    zval retval;
    zend_fcall_info fci;
    zend_fcall_info_cache fcc;
    fci.object = NULL;
    fci.size = sizeof(zend_fcall_info);
    ZVAL_STRING(&fci.function_name, "sprintf");
    fci.param_count = argc+1;
    ZVAL_STRING(&params[0], format);
    int i;
    for (i=0; i<argc; i++) {
        ZVAL_COPY(&params[i+1], &args[i]);
    }
    fci.retval = &retval;
    fci.params = params;
    fci.named_params = NULL;
    if (zend_call_function(&fci, NULL)==SUCCESS ) {
        ZVAL_COPY(&php_ret->message, &retval);
    }

    zend_string_delref(retval.value.str);
    zend_string_efree(fci.params[0].value.str);
    zend_string_efree(fci.function_name.value.str);
    efree(params);



    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto php_GError g_error_new_literal(GQuark domain, int code, char message)
   Creates a new GError; unlike g_error_new(), message is not a printf()... */
PHP_FUNCTION(g_error_new_literal)
{
    zend_long domain;
    zend_long code;
    char *message;
    size_t message_len;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_LONG(domain);
        Z_PARAM_LONG(code);
        Z_PARAM_STRING(message, message_len);
    ZEND_PARSE_PARAMETERS_END();

    zend_object *z_ret = php_g_error_create_object(php_g_error_class_entry);
    php_g_error *php_ret = ZOBJ_TO_PHP_G_ERROR(z_ret);

    ZVAL_LONG(&php_ret->domain, domain);
    ZVAL_LONG(&php_ret->code, code);
    ZVAL_STRING(&php_ret->message, message);

    RETURN_OBJ(z_ret);
}/* }}} */
#if GLIB_VERSION >= GLIB_VERSION_2_22
/* {{{ proto php_GError g_error_new_valist(GQuark domain, int code, char format, va_list args)
   Creates a new GError with the given domain and code , and a message f... */
PHP_FUNCTION(g_error_new_valist)
{
    zend_long domain;
    zend_long code;
    char *format;
    size_t format_len;
    zval *zargs;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_LONG(domain);
        Z_PARAM_LONG(code);
        Z_PARAM_STRING(format, format_len);
        Z_PARAM_ARRAY(zargs);
    ZEND_PARSE_PARAMETERS_END();

    zend_object *z_ret = php_g_error_create_object(php_g_error_class_entry);
    php_g_error *php_ret = ZOBJ_TO_PHP_G_ERROR(z_ret);

    ZVAL_LONG(&php_ret->domain, domain);
    ZVAL_LONG(&php_ret->code, code);


    int argc = zend_array_count(zargs->value.arr);
    zval *params = emalloc(sizeof(zval)*(argc+1));
    zval retval;
    zend_fcall_info fci;
    fci.object = NULL;
    fci.size = sizeof(zend_fcall_info);
    ZVAL_STRING(&fci.function_name, "sprintf");
    fci.param_count = argc+1;
    ZVAL_STRING(&params[0], format);

    int i=0;
    zval *value;
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(zargs), value) {
        ZVAL_COPY(&params[i+1], value);
        i++;
    } ZEND_HASH_FOREACH_END();

    fci.retval = &retval;
    fci.params = params;
    fci.named_params = NULL;
    if (zend_call_function(&fci, NULL)==SUCCESS ) {
        ZVAL_STR(&php_ret->message, retval.value.str);
    }

    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(zargs), value) {
        Z_TRY_DELREF_P(value);
    } ZEND_HASH_FOREACH_END();

    zend_string_delref(retval.value.str);
    //zend_string_efree(retval.value.str);
    zend_string_efree(fci.params[0].value.str);
    zend_string_efree(fci.function_name.value.str);
    efree(params);

    RETURN_OBJ(z_ret);
}/* }}} */
#endif

/* {{{ proto bool g_error_matches(php_GError error, GQuark domain, int code)
   Returns TRUE if error matches domain and code , FALSE otherwise. */
PHP_FUNCTION(g_error_matches)
{
    zval *zerror;
    zend_long domain;
    zend_long code;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zerror, php_g_error_class_entry, 0, 0);
        Z_PARAM_LONG(domain);
        Z_PARAM_LONG(code);
    ZEND_PARSE_PARAMETERS_END();

    php_g_error *php_error = ZVAL_IS_PHP_G_ERROR(zerror)? ZVAL_GET_PHP_G_ERROR(zerror): NULL;
    DECL_PHP_G_ERROR(error);

    gboolean ret = g_error_matches(error, domain, code);

    if (ret) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}/* }}} */
/* {{{ proto void g_set_error(php_GError err, GQuark domain, int code, char format)
   Does nothing if err is NULL; if err is non-NULL, then *err must be NULL. */
PHP_FUNCTION(g_set_error)
{
    zval *zerr;
    zend_long domain;
    zend_long code;
    char *format;
    size_t format_len;
    int argc;
    zval *args = NULL;

    ZEND_PARSE_PARAMETERS_START(4, -1)
        Z_PARAM_ZVAL_EX2(zerr, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_LONG(domain);
        Z_PARAM_LONG(code);
        Z_PARAM_STRING(format, format_len);
        Z_PARAM_VARIADIC('+', args, argc);
    ZEND_PARSE_PARAMETERS_END();

    php_g_error *php_err = ZVAL_IS_PHP_G_ERROR(zerr)? ZVAL_GET_PHP_G_ERROR(zerr): NULL;

    if (NULL==php_err) {
        return;
    }

    ZVAL_SET_LONG(&php_err->domain, domain);
    ZVAL_SET_LONG(&php_err->code, code);

    zval *params = emalloc(sizeof(zval)*(argc+1));
    zval retval;
    zend_fcall_info fci;
    zend_fcall_info_cache fcc;
    fci.object = NULL;
    fci.size = sizeof(zend_fcall_info);
    ZVAL_STRING(&fci.function_name, "sprintf");
    fci.param_count = argc+1;
    ZVAL_STRING(&params[0], format);
    int i;
    for (i=0; i<argc; i++) {
        ZVAL_COPY(&params[i+1], &args[i]);
    }
    fci.retval = &retval;
    fci.params = params;
    fci.named_params = NULL;
    if (zend_call_function(&fci, NULL)==SUCCESS ) {
        ZVAL_STR(&php_err->message, retval.value.str);
    }

    //zend_string_delref(retval.value.str);
    zend_string_efree(fci.params[0].value.str);
    zend_string_efree(fci.function_name.value.str);
    efree(params);

}/* }}} */
#if GLIB_VERSION >= GLIB_VERSION_2_18
/* {{{ proto void g_set_error_literal(php_GError err, GQuark domain, int code, char message)
   Does nothing if err is NULL; if err is non-NULL, then *err must be NULL. */
PHP_FUNCTION(g_set_error_literal)
{
    zval *zerr;
    zend_long domain;
    zend_long code;
    char *message;
    size_t message_len;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_ZVAL_EX2(zerr, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_LONG(domain);
        Z_PARAM_LONG(code);
        Z_PARAM_STRING(message, message_len);
    ZEND_PARSE_PARAMETERS_END();

    php_g_error *php_err = ZVAL_IS_PHP_G_ERROR(zerr)? ZVAL_GET_PHP_G_ERROR(zerr): NULL;
    DECL_PHP_G_ERROR(err);

    ZVAL_SET_LONG(&php_err->domain, domain);
    ZVAL_SET_LONG(&php_err->code, code);
    ZVAL_STRING(&php_err->message, message);

}/* }}} */
#endif
/* {{{ proto void g_propagate_error(php_GError dest, php_GError src)
   If dest is NULL, free src ; otherwise, moves src into *dest . */
PHP_FUNCTION(g_propagate_error)
{
    zval *zdest;
    zval *zsrc;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        //Z_PARAM_OBJECT_OF_CLASS_EX2(zdest, php_g_error_class_entry, 1, ZEND_SEND_BY_REF, 1);
        Z_PARAM_ZVAL_EX2(zdest, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zsrc, php_g_error_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    // dest is NULL free src
    php_g_error *php_dest = ZVAL_IS_PHP_G_ERROR(zdest)? ZVAL_GET_PHP_G_ERROR(zdest): NULL;
    php_g_error *php_src = ZVAL_IS_PHP_G_ERROR(zsrc)? ZVAL_GET_PHP_G_ERROR(zsrc): NULL;

    if (NULL==php_dest) {
        zend_object *z_error = php_g_error_create_object(php_g_error_class_entry);
        php_dest = ZOBJ_TO_PHP_G_ERROR(z_error);
    }
    if (php_src) {
        ZVAL_COPY(&php_dest->domain, &php_src->domain);
        ZVAL_COPY(&php_dest->code, &php_src->code);
        ZVAL_COPY(&php_dest->message, &php_src->message);

        ZVAL_OBJ(zdest, &php_dest->std);
    }

}/* }}} */
/* {{{ proto php_GError g_error_copy(php_GError error)
   Makes a copy of error . */
PHP_FUNCTION(g_error_copy)
{
    zval *zerror;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zerror, php_g_error_class_entry, 0, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_g_error *php_error = ZVAL_IS_PHP_G_ERROR(zerror)? ZVAL_GET_PHP_G_ERROR(zerror): NULL;
    DECL_PHP_G_ERROR(error);

    GError *ret = g_error_copy(error);
    zend_object *z_ret = php_g_error_create_object(php_g_error_class_entry);
    php_g_error *php_ret = ZOBJ_TO_PHP_G_ERROR(z_ret);
    PHP_G_ERROR_SET(php_ret, error);

    RETURN_OBJ(&php_ret->std);
}/* }}} */
/* {{{ proto void g_clear_error(php_GError err)
   If err or *err is NULL, does nothing. */
PHP_FUNCTION(g_clear_error)
{
    zval *zerr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX2(zerr, php_g_error_class_entry, 0, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_g_error *php_err = ZVAL_IS_PHP_G_ERROR(zerr)? ZVAL_GET_PHP_G_ERROR(zerr): NULL;

    if (php_err) {
        zend_object_release(&php_err->std);
        ZVAL_NULL(zerr);
    }

    RETURN_NULL();
}/* }}} */
#if GLIB_VERSION >= GLIB_VERSION_2_16
/* {{{ proto void g_prefix_error(php_GError err, char format)
   Formats a string according to format and prefix it to an existing err... */
PHP_FUNCTION(g_prefix_error)
{
    zval *zerr;
    char *format;
    size_t format_len;
    int argc;
    zval *args = NULL;

    ZEND_PARSE_PARAMETERS_START(2, -1)
        Z_PARAM_ZVAL_EX2(zerr, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_STRING(format, format_len);
        Z_PARAM_VARIADIC('*', args, argc);
    ZEND_PARSE_PARAMETERS_END();

    php_g_error *php_err = ZVAL_IS_PHP_G_ERROR(zerr)? ZVAL_GET_PHP_G_ERROR(zerr): NULL;
    if (NULL==php_err) {
        return;
    }

    zval *params = emalloc(sizeof(zval)*(argc+1));
    zval retval;
    zend_fcall_info fci;
    zend_fcall_info_cache fcc;
    fci.object = NULL;
    fci.size = sizeof(zend_fcall_info);
    ZVAL_STRING(&fci.function_name, "sprintf");
    fci.param_count = argc+1;
    ZVAL_STRING(&params[0], format);
    int i;
    for (i=0; i<argc; i++) {
        ZVAL_COPY(&params[i+1], &args[i]);
    }
    fci.retval = &retval;
    fci.params = params;
    fci.named_params = NULL;
    if (zend_call_function(&fci, NULL)==SUCCESS ) {
        zend_string * str = zend_string_concat2(retval.value.str->val, retval.value.str->len, php_err->message.value.str->val, php_err->message.value.str->len);
        zend_string_efree(php_err->message.value.str);
        ZVAL_STR(&php_err->message, str);
    }

    //zend_string_delref(retval.value.str);
    zend_string_efree(retval.value.str);
    zend_string_efree(fci.params[0].value.str);
    zend_string_efree(fci.function_name.value.str);
    efree(params);

    RETURN_NULL();
}/* }}} */

/* {{{ proto void g_propagate_prefixed_error(php_GError dest, php_GError src, char format)
   If dest is NULL, free src ; otherwise, moves src into *dest . */
PHP_FUNCTION(g_propagate_prefixed_error)
{
    zval *zdest;
    zval *zsrc;
    char *format;
    size_t format_len;
    int argc;
    zval *args = NULL;

    zend_string * str;

    ZEND_PARSE_PARAMETERS_START(3, -1)
        //Z_PARAM_OBJECT_OF_CLASS_EX(zdest, php_g_error_class_entry, 0, 0);
        Z_PARAM_ZVAL_EX2(zdest, 0, ZEND_SEND_BY_REF, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zsrc, php_g_error_class_entry, 0, 0);
        Z_PARAM_STRING(format, format_len);
        Z_PARAM_VARIADIC('+', args, argc);
    ZEND_PARSE_PARAMETERS_END();

    php_g_error *php_dest = ZVAL_IS_PHP_G_ERROR(zdest)? ZVAL_GET_PHP_G_ERROR(zdest): NULL;
    php_g_error *php_src = ZVAL_IS_PHP_G_ERROR(zsrc)? ZVAL_GET_PHP_G_ERROR(zsrc): NULL;

    zval *params = emalloc(sizeof(zval)*(argc+1));
    zval retval;
    zend_fcall_info fci;
    zend_fcall_info_cache fcc;
    fci.object = NULL;
    fci.size = sizeof(zend_fcall_info);
    ZVAL_STRING(&fci.function_name, "sprintf");
    fci.param_count = argc+1;
    ZVAL_STRING(&params[0], format);
    int i;
    for (i=0; i<argc; i++) {
        ZVAL_COPY(&params[i+1], &args[i]);
    }
    fci.retval = &retval;
    fci.params = params;
    fci.named_params = NULL;
    if (zend_call_function(&fci, NULL)==SUCCESS ) {
        str = zend_string_concat2(retval.value.str->val, retval.value.str->len, php_src->message.value.str->val, php_src->message.value.str->len);
        //zend_string_efree(php_dest->message.value.str);
    }

    //zend_string_delref(retval.value.str);
    zend_string_efree(retval.value.str);
    zend_string_efree(fci.params[0].value.str);
    zend_string_efree(fci.function_name.value.str);
    efree(params);

    if (NULL==php_dest) {
        zend_object *z_error = php_g_error_create_object(php_g_error_class_entry);
        php_dest = ZOBJ_TO_PHP_G_ERROR(z_error);
    }
    if (php_src) {
        ZVAL_COPY(&php_dest->domain, &php_src->domain);
        ZVAL_COPY(&php_dest->code, &php_src->code);
        //ZVAL_COPY(&php_dest->message, &php_src->message);
        ZVAL_STR(&php_dest->message, str);

        ZVAL_OBJ(zdest, &php_dest->std);
    }

}/* }}} */
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
