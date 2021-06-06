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
#include "php_cairo/path-data.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_path_data_t_class_entry;// union
zend_object_handlers  php_cairo_path_data_t_handlers;

extern zend_class_entry *zend_standard_class_def;

enum _php_cairo_path_data_t_properties {
    PHP_CAIRO_PATH_DATA_T_HEADER = 1,
    PHP_CAIRO_PATH_DATA_T_POINT = 2
};
//typedef enum php_cairo_path_data_t_properties php_cairo_path_data_t_properties;

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_path_data_t_methods[] = {
    PHP_ME(cairo_path_data_t, __construct, arginfo_cairo_path_data_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_path_data_t_create_object */
static zend_object*
php_cairo_path_data_t_create_object(zend_class_entry *class_type)
{
    php_cairo_path_data_t *intern = zend_object_alloc(sizeof(php_cairo_path_data_t), class_type);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->union_type = 0;//PHP_CAIRO_PATH_DATA_T_UNKNOWN
    ZVAL_NULL(&intern->header);
    ZVAL_NULL(&intern->point);


    intern->std.handlers = &php_cairo_path_data_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_path_data_t_create_object */


static void
php_cairo_path_data_t_dtor_object(zend_object *obj) {
    //php_cairo_path_data_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(obj);

}

/* {{{ php_cairo_path_data_t_free_object */
static void
php_cairo_path_data_t_free_object(zend_object *object)
{
    php_cairo_path_data_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(object);

    switch (intern->union_type) {
    case PHP_CAIRO_PATH_DATA_T_HEADER:
        zval_ptr_dtor(&intern->header);
        break;
    case PHP_CAIRO_PATH_DATA_T_POINT:
        zval_ptr_dtor(&intern->point);
        break;
    default:
        break;
    }

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_path_data_t_free_object */




/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_cairo_path_data_t_setter_anonymous_0(php_cairo_path_data_t *intern, zval *value, char *name, zval *dest) {
    switch (intern->union_type) {
        case PHP_CAIRO_PATH_DATA_T_HEADER:
            zval_delref_p(&intern->header);
            break;
        case PHP_CAIRO_PATH_DATA_T_POINT:
            zval_delref_p(&intern->point);
            break;
    }
    ZVAL_COPY(dest, value);//"@anonymous#0"
}




/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_cairo_path_data_t_setter_anonymous_1(php_cairo_path_data_t *intern, zval *value, char *name, zval *dest) {
    switch (intern->union_type) {
        case PHP_CAIRO_PATH_DATA_T_HEADER:
            zval_delref_p(&intern->header);
            break;
        case PHP_CAIRO_PATH_DATA_T_POINT:
            zval_delref_p(&intern->point);
            break;
    }
    ZVAL_COPY(dest, value);//"@anonymous#1"
}




struct PhpCairoPathDataTProperty {
  const char *name;
  int code;
  void (*setter) (php_cairo_path_data_t *intern, zval *rvalue, char *name, zval *dest);
};

static const struct PhpCairoPathDataTProperty php_cairo_path_data_t_properties[] = {
    {"header", PHP_CAIRO_PATH_DATA_T_HEADER, php_cairo_path_data_t_setter_anonymous_0},
    {"point", PHP_CAIRO_PATH_DATA_T_POINT, php_cairo_path_data_t_setter_anonymous_1}
};


const struct PhpCairoPathDataTProperty*
php_cairo_path_data_t_properties_lookup (const char *str, size_t len)
{
    if (len == 6) {
        if (str[0] == 'h' && str[1] == 'e' && str[2] == 'a' && str[3] == 'd'
         && str[4] == 'e' && str[5] == 'r') {
            return &php_cairo_path_data_t_properties[0];
        }
    } else if (len == 5) {
        if (str[0] == 'p' && str[1] == 'o' && str[2] == 'i' && str[3] == 'n'
         && str[4] == 't') {
            return &php_cairo_path_data_t_properties[1];
        }
    }
    return 0;
}

/* {{{ php_cairo_path_data_t_read_property */
static zval*
php_cairo_path_data_t_read_property(zend_object *object, zend_string *member_str, int type, void **cache_slot, zval *rv)
{
    php_cairo_path_data_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(object);

    const struct PhpCairoPathDataTProperty *cmd = php_cairo_path_data_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_PATH_DATA_T_HEADER:
            if(PHP_CAIRO_PATH_DATA_T_HEADER==intern->union_type) {
                ZVAL_COPY(rv, &intern->header);
                return rv;
            } else {
                php_printf("Type error : Expecting '%s' but you try to acces to '%s'\n",php_cairo_path_data_t_properties[intern->union_type-1].name, php_cairo_path_data_t_properties[PHP_CAIRO_PATH_DATA_T_HEADER-1].name);
            }
            break;
        case PHP_CAIRO_PATH_DATA_T_POINT:
            if(PHP_CAIRO_PATH_DATA_T_POINT==intern->union_type) {
                ZVAL_COPY(rv, &intern->point);
                return rv;
            } else {
                php_printf("Type error : Expecting '%s' but you try to acces to '%s'\n",php_cairo_path_data_t_properties[intern->union_type-1].name, php_cairo_path_data_t_properties[PHP_CAIRO_PATH_DATA_T_POINT-1].name);
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

/* {{{ php_cairo_path_data_t_write_property */
static zval*
php_cairo_path_data_t_write_property(zend_object *object, zend_string *member_str, zval *value, void **cache_slot)
{
    php_cairo_path_data_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(object);
    // union
    const struct PhpCairoPathDataTProperty *cmd = php_cairo_path_data_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_PATH_DATA_T_HEADER:
            cmd->setter(intern, value, member_str->val, &intern->header);
            intern->union_type = PHP_CAIRO_PATH_DATA_T_HEADER;
        break;
        case PHP_CAIRO_PATH_DATA_T_POINT:
            cmd->setter(intern, value, member_str->val, &intern->point);
            intern->union_type = PHP_CAIRO_PATH_DATA_T_POINT;
        break;
        }
    } else {
        // property not found
    }
    return value;
}
/* }}} */

/* {{{ php_cairo_path_data_t_get_property_ptr_ptr */
static zval*
php_cairo_path_data_t_get_property_ptr_ptr(zend_object *object, zend_string *member_str, int type, void **cache_slot)
{
    php_cairo_path_data_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(object);
    zval *retval = NULL;

    const struct PhpCairoPathDataTProperty *cmd = php_cairo_path_data_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_PATH_DATA_T_HEADER:
            if(PHP_CAIRO_PATH_DATA_T_HEADER==intern->union_type) {
                return &intern->header;
            } else {
                php_printf("Type error : Expecting '%s' but you try to acces to '%s'\n",php_cairo_path_data_t_properties[intern->union_type-1].name, php_cairo_path_data_t_properties[PHP_CAIRO_PATH_DATA_T_HEADER-1].name);
            }
        case PHP_CAIRO_PATH_DATA_T_POINT:
            if(PHP_CAIRO_PATH_DATA_T_POINT==intern->union_type) {
                return &intern->point;
            } else {
                php_printf("Type error : Expecting '%s' but you try to acces to '%s'\n",php_cairo_path_data_t_properties[intern->union_type-1].name, php_cairo_path_data_t_properties[PHP_CAIRO_PATH_DATA_T_POINT-1].name);
            }
        }
    } else {
        // Error
    }

    return retval;
}/* }}} */





/* {{{ php_cairo_path_data_t_get_debug_info */
static HashTable*
php_cairo_path_data_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_path_data_t  *intern = ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    switch (intern->union_type) {
    case PHP_CAIRO_PATH_DATA_T_HEADER:
    {
        zval zheader; ZVAL_COPY(&zheader, &intern->header);
        zend_hash_str_update(debug_info, "header", sizeof("header")-1, &zheader);
    }
    break;
    case PHP_CAIRO_PATH_DATA_T_POINT:
    {
        zval zpoint; ZVAL_COPY(&zpoint, &intern->point);
        zend_hash_str_update(debug_info, "point", sizeof("point")-1, &zpoint);
    }
    break;
    }

    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_path_data_t_get_handlers()
{
    memcpy(&php_cairo_path_data_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_path_data_t_handlers.offset = PHP_CAIRO_PATH_DATA_T_OFFSET;
    php_cairo_path_data_t_handlers.dtor_obj = php_cairo_path_data_t_dtor_object;
    php_cairo_path_data_t_handlers.free_obj = php_cairo_path_data_t_free_object;

    php_cairo_path_data_t_handlers.read_property = php_cairo_path_data_t_read_property;
    php_cairo_path_data_t_handlers.write_property = php_cairo_path_data_t_write_property;
    php_cairo_path_data_t_handlers.get_property_ptr_ptr = php_cairo_path_data_t_get_property_ptr_ptr;

    php_cairo_path_data_t_handlers.get_debug_info = php_cairo_path_data_t_get_debug_info;


    return &php_cairo_path_data_t_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_path_data_t_class_init */
zend_class_entry*
php_cairo_path_data_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_path_data_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_path_data_t", php_cairo_path_data_t_methods);
    php_cairo_path_data_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_path_data_t_class_entry->create_object = php_cairo_path_data_t_create_object;

    return php_cairo_path_data_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/
void
php_cairo_path_data_t_create_header(php_cairo_path_data_t*intern, cairo_path_data_t *data){
    zval *rv = &intern->header;
    //zend_object *object = php_cairo_path_data_t_create_object(php_cairo_path_data_t_class_entry);
    //cairo_path_data_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(object);
    zend_object *std_class;

    //intern->header
    intern->union_type = PHP_CAIRO_PATH_DATA_T_HEADER;


    zend_string *member_type_str = zend_string_init("type", sizeof("type")-1, 0);
    zend_string *member_length_str = zend_string_init("length", sizeof("length")-1, 0);
    zval member_type; ZVAL_STR(&member_type, member_type_str);
    zval member_length; ZVAL_STR(&member_length, member_length_str);

    zval ztype; ZVAL_LONG(&ztype, data->header.type);
    zval zlength; ZVAL_LONG(&zlength, data->header.length);


    std_class = zend_objects_new(zend_standard_class_def);
    ZVAL_OBJ(rv, std_class);

    zend_std_write_property(rv, &member_type, &ztype, NULL);
    zend_std_write_property(rv, &member_length, &zlength, NULL);

    zend_string_delref(member_type_str);
    zend_string_delref(member_length_str);

}

void
php_cairo_path_data_t_create_point(php_cairo_path_data_t *intern, cairo_path_data_t *data){
    zend_object *std_class;
    zval *rv = &intern->point;
    intern->union_type = PHP_CAIRO_PATH_DATA_T_POINT;

    zend_string *member_x_str = zend_string_init("x", sizeof("x")-1, 0);
    zend_string *member_y_str = zend_string_init("y", sizeof("y")-1, 0);
    zval member_x; ZVAL_STR(&member_x, member_x_str);
    zval member_y; ZVAL_STR(&member_y, member_y_str);

    zval zx; ZVAL_DOUBLE(&zx, data->point.x);
    zval zy; ZVAL_DOUBLE(&zy, data->point.y);


    std_class = zend_objects_new(zend_standard_class_def);
    ZVAL_OBJ(rv, std_class);


    zend_std_write_property(rv, &member_x, &zx, NULL);
    zend_std_write_property(rv, &member_y, &zy, NULL);

    zend_string_delref(member_x_str);
    zend_string_delref(member_y_str);
}

php_cairo_path_data_t *
php_cairo_path_data_t_new(){
    zend_object *object = php_cairo_path_data_t_create_object(php_cairo_path_data_t_class_entry);
    php_cairo_path_data_t *path_data = ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(object);
    return path_data;

}


/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

 /* {{{ cairo_path_data_t::__construct() */
PHP_METHOD(cairo_path_data_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_path_data_t *self = ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(zobj);


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
