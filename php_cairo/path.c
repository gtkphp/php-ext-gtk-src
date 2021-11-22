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
#include "php_cairo/cairo.h"
#include "php_cairo/glyph.h"
#include "php_cairo/path-data.h"
#include "php_cairo/path-data-type.h"

#include "php_cairo/path.h"


extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_path_t_class_entry;// struct
zend_object_handlers  php_cairo_path_t_handlers;




enum _php_cairo_path_t_properties {
    PHP_CAIRO_PATH_T_STATUS = 1,
    PHP_CAIRO_PATH_T_DATA = 2,
    PHP_CAIRO_PATH_T_NUM_DATA = 3
};
//typedef enum php_cairo_path_t_properties php_cairo_path_t_properties;



/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry
php_cairo_path_t_methods[] = {
    PHP_ME(cairo_path_t, __construct, arginfo_cairo_path_t___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/

/* {{{ php_cairo_path_t_create_object */
static zend_object*
php_cairo_path_t_create_object(zend_class_entry *class_type)
{
    php_cairo_path_t *intern = zend_object_alloc(sizeof(php_cairo_path_t), class_type);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    zend_array *zdata;
    ALLOC_HASHTABLE(zdata);
    zend_hash_init(zdata, 1, NULL, ZVAL_PTR_DTOR, 1);

    ZVAL_LONG(&intern->status, 0);
    ZVAL_ARR(&intern->data, zdata);
    ZVAL_LONG(&intern->num_data, 0);

    intern->std.handlers = &php_cairo_path_t_handlers;

    return &intern->std;
}
/* }}} php_cairo_path_t_create_object */


static void
php_cairo_path_t_dtor_object(zend_object *obj) {
    //php_cairo_path_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_T(obj);

}

/* {{{ php_cairo_path_t_free_object */
static void
php_cairo_path_t_free_object(zend_object *object)
{
    php_cairo_path_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_T(object);

    Z_TRY_DELREF(intern->status);
    Z_DELREF_P(&intern->data);
    if (intern->data.value.arr->gc.refcount==0) {
        zend_hash_destroy(intern->data.value.arr);
        FREE_HASHTABLE(intern->data.value.arr);
    }
    Z_TRY_DELREF(intern->num_data);

    zend_object_std_dtor(&intern->std);
}
/* }}} php_cairo_path_t_free_object */




/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_cairo_path_t_setter_int(php_cairo_path_t *intern, zval *value, char *name, zval *dest) {
    if (Z_TYPE_P(value)==IS_LONG) {
        ZVAL_SET_LONG(dest, value->value.lval);
    } else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        const char *type_name = zend_zval_type_name(value);
        if (strict_types) {
            zend_error(E_USER_NOTICE, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\cairo_path_t::$%s of type float,", type_name, name);
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
            zend_error(E_USER_NOTICE, "Cannot assign %s to property "GTK_NS_QUOTE(GTK_NS)"\\cairo_path_t::$%s of type int,", type_name, name);
        }
    }
}




/** TODO: implement all the types */
/** rename it by : php_gtkml_setter_[double|long|string] */
static void
php_cairo_path_t_setter_php_cairo_path_data_t(php_cairo_path_t *intern, zval *value, char *name, zval *dest) {
    if(IS_ARRAY==Z_TYPE_P(value)) {
        Z_DELREF_P(dest);
        if (dest->value.arr->gc.refcount==0) {
            zend_hash_destroy(dest->value.arr);
            FREE_HASHTABLE(dest->value.arr);
        }
    }
    ZVAL_COPY(dest, value);//"php_cairo_path_data_t"
}




struct PhpCairoPathTProperty {
  const char *name;
  int code;
  void (*setter) (php_cairo_path_t *intern, zval *rvalue, char *name, zval *dest);
};

static const struct PhpCairoPathTProperty php_cairo_path_t_properties[] = {
    {"status", PHP_CAIRO_PATH_T_STATUS, php_cairo_path_t_setter_int},
    {"data", PHP_CAIRO_PATH_T_DATA, php_cairo_path_t_setter_php_cairo_path_data_t},
    {"num_data", PHP_CAIRO_PATH_T_NUM_DATA, php_cairo_path_t_setter_int}
};


const struct PhpCairoPathTProperty*
php_cairo_path_t_properties_lookup (const char *str, size_t len)
{
    if (len == 6) {
        if (str[0] == 's' && str[1] == 't' && str[2] == 'a' && str[3] == 't'
         && str[4] == 'u' && str[5] == 's') {
            return &php_cairo_path_t_properties[0];
        }
    } else if (len == 4) {
        if (str[0] == 'd' && str[1] == 'a' && str[2] == 't' && str[3] == 'a') {
            return &php_cairo_path_t_properties[1];
        }
    } else if (len == 8) {
        if (str[0] == 'n' && str[1] == 'u' && str[2] == 'm' && str[3] == '_'
         && str[4] == 'd' && str[5] == 'a' && str[6] == 't' && str[7] == 'a') {
            return &php_cairo_path_t_properties[2];
        }
    }
    return 0;
}

/* {{{ php_cairo_path_t_read_property */
static zval*
php_cairo_path_t_read_property(zend_object *object, zend_string *member_str, int type, void **cache_slot, zval *rv)
{
    php_cairo_path_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_T(object);

    const struct PhpCairoPathTProperty *cmd = php_cairo_path_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_PATH_T_STATUS:
            ZVAL_COPY(rv, &intern->status);
            return rv;
            break;
        case PHP_CAIRO_PATH_T_DATA:
            ZVAL_COPY(rv, &intern->data);
            return rv;
            break;
        case PHP_CAIRO_PATH_T_NUM_DATA:
            php_cairo_path_t_update_num_data(intern);
            ZVAL_COPY(rv, &intern->num_data);
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

/* {{{ php_cairo_path_t_write_property */
static zval*
php_cairo_path_t_write_property(zend_object *object, zend_string *member_str, zval *value, void **cache_slot)
{
    php_cairo_path_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_T(object);
    // struct
    const struct PhpCairoPathTProperty *cmd = php_cairo_path_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_PATH_T_STATUS:
            cmd->setter(intern, value, member_str->val, &intern->status);
        break;
        case PHP_CAIRO_PATH_T_DATA:
            cmd->setter(intern, value, member_str->val, &intern->data);
        break;
        case PHP_CAIRO_PATH_T_NUM_DATA:
            cmd->setter(intern, value, member_str->val, &intern->num_data);
        break;
        }
    } else {
        // property not found
    }
    return value;
}
/* }}} */

/* {{{ php_cairo_path_t_get_property_ptr_ptr */
static zval*
php_cairo_path_t_get_property_ptr_ptr(zend_object *object, zend_string *member_str, int type, void **cache_slot)
{
    php_cairo_path_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_T(object);
    zval *retval = NULL;

    const struct PhpCairoPathTProperty *cmd = php_cairo_path_t_properties_lookup(member_str->val, member_str->len);
    if (cmd) {
        switch(cmd->code) {
        case PHP_CAIRO_PATH_T_STATUS:
            return &intern->status;// forbiden
        case PHP_CAIRO_PATH_T_DATA:
            return &intern->data;
        case PHP_CAIRO_PATH_T_NUM_DATA:
            php_cairo_path_t_update_num_data(intern);
            return &intern->num_data;// forbiden
        }
    } else {
        // Error
    }

    return retval;
}/* }}} */





/* {{{ php_cairo_path_t_get_debug_info */
static HashTable*
php_cairo_path_t_get_debug_info(zend_object *object, int *is_temp)
{
    php_cairo_path_t  *intern = ZOBJ_TO_PHP_CAIRO_PATH_T(object);
    HashTable   *debug_info,
    *std_props;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);

    zval zstatus; ZVAL_COPY(&zstatus, &intern->status);
    zend_hash_str_update(debug_info, "status", sizeof("status")-1, &zstatus);
    zval zdata; ZVAL_COPY(&zdata, &intern->data);
    zend_hash_str_update(debug_info, "data", sizeof("data")-1, &zdata);
            php_cairo_path_t_update_num_data(intern);
    zval znum_data; ZVAL_COPY(&znum_data, &intern->num_data);
    zend_hash_str_update(debug_info, "num_data", sizeof("num_data")-1, &znum_data);

    return debug_info;
}
/* }}} */





static zend_object_handlers*
php_cairo_path_t_get_handlers()
{
    memcpy(&php_cairo_path_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_path_t_handlers.offset = PHP_CAIRO_PATH_T_OFFSET;
    php_cairo_path_t_handlers.dtor_obj = php_cairo_path_t_dtor_object;
    php_cairo_path_t_handlers.free_obj = php_cairo_path_t_free_object;

    php_cairo_path_t_handlers.read_property = php_cairo_path_t_read_property;
    php_cairo_path_t_handlers.write_property = php_cairo_path_t_write_property;
    php_cairo_path_t_handlers.get_property_ptr_ptr = php_cairo_path_t_get_property_ptr_ptr;

    php_cairo_path_t_handlers.get_debug_info = php_cairo_path_t_get_debug_info;


    return &php_cairo_path_t_handlers;
}

/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/

 /*{{{ php_cairo_path_t_class_init */
zend_class_entry*
php_cairo_path_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_path_t_get_handlers();
    PHP_GTK_INIT_CLASS_ENTRY((*container_ce), "cairo_path_t", php_cairo_path_t_methods);
    php_cairo_path_t_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_path_t_class_entry->create_object = php_cairo_path_t_create_object;

    return php_cairo_path_t_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/
php_cairo_path_t*
php_cairo_path_t_new(cairo_path_t *path){

    zend_object *zpath = php_cairo_path_t_create_object(php_cairo_path_t_class_entry);
    php_cairo_path_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_T(zpath);

    zend_array *zarray = intern->data.value.arr;

    zval zheader;
    zval zpoint;
    php_cairo_path_data_t *intern_data;

    int i, j;
    cairo_path_data_t *data = path->data;
    for (i=0; i < path->num_data; i += path->data[i].header.length) {
        intern_data = php_cairo_path_data_t_new();

        php_cairo_path_data_t_create_header(intern_data, &path->data[i]);
        ZVAL_OBJ(&zheader, &intern_data->std);
        zend_hash_next_index_insert(zarray, &zheader);

        for(j=1; j<path->data[i].header.length; j++) {
            intern_data = php_cairo_path_data_t_new();
            php_cairo_path_data_t_create_point(intern_data, &path->data[i+j]);
            ZVAL_OBJ(&zpoint, &intern_data->std);
            zend_hash_next_index_insert(zarray, &zpoint);
        }

    }
    ZVAL_ARR(&intern->data, zarray);
    ZVAL_LONG(&intern->num_data, path->num_data);
    ZVAL_LONG(&intern->status, path->status);

    return intern;
}

cairo_path_t *
php_cairo_path_t_get_ptr(php_cairo_path_t *php_path){
    cairo_path_t *path;

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
    cairo_t *cr = cairo_create (surface);

    zend_string *member_header_str = zend_string_init("header", sizeof("header")-1, 0);
    zend_string *member_point_str = zend_string_init("point", sizeof("point")-1, 0);
    zend_string *member_x_str = zend_string_init("x", sizeof("x")-1, 0);
    zend_string *member_y_str = zend_string_init("y", sizeof("y")-1, 0);
    zend_string *member_type_str = zend_string_init("type", sizeof("type")-1, 0);
    zend_string *member_length_str = zend_string_init("length", sizeof("length")-1, 0);

    zval member_point; ZVAL_STR(&member_point, member_point_str);
    zval member_header; ZVAL_STR(&member_header, member_header_str);
    zval member_x; ZVAL_STR(&member_x, member_x_str);
    zval member_y; ZVAL_STR(&member_y, member_y_str);
    zval member_type; ZVAL_STR(&member_type, member_type_str);
    zval member_length; ZVAL_STR(&member_length, member_length_str);

    void *cache_slot = NULL;
    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    zval *ztype;
    zval *zlength;
    zval *zx;
    zval *zy;
    zval rv;
    zval *value;
    zval *data = &php_path->data;

    cairo_path_data_type_t type;
    int length;
    int count;
    double points[3][2];
    //g_print("php_cairo_path_t_get_path: %d\n", data->value.arr->nNumOfElements);
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(data), value) {
        //g_print("  value: %d\n", Z_TYPE_P(value));

        if  (ZVAL_IS_PHP_CAIRO_PATH_DATA_T(value)) {
            php_cairo_path_data_t *path_data = ZVAL_GET_PHP_CAIRO_PATH_DATA_T(value);
            // isset header|point
            //zval *ret = std_hnd->read_property(value, &member_point, IS_OBJECT, &cache_slot, &rv);
            if (path_data->union_type==1/*PHP_CAIRO_PATH_DATA_T_HEADER*/) {
                zval *zheader = &path_data->header;
                ztype = std_hnd->read_property(zheader->value.obj, member_type_str, IS_LONG, NULL, NULL);
                zlength = std_hnd->read_property(zheader->value.obj, member_length_str, IS_LONG, NULL, NULL);
                type = ztype->value.lval;
                length = zlength->value.lval;
                count = 0;
            } else {
                zval *zpoint;
                zpoint = &path_data->point;
                zx = std_hnd->read_property(zpoint->value.obj, member_x_str, IS_DOUBLE, NULL, NULL);
                zy = std_hnd->read_property(zpoint->value.obj, member_y_str, IS_DOUBLE, NULL, NULL);
                points[0+count][0] = zx->value.dval;
                points[0+count][1] = zy->value.dval;
                count++;
            }
            switch (type) {
            case CAIRO_PATH_MOVE_TO:
                if (count==1) cairo_move_to(cr, points[0][0], points[0][1]);
                break;
            case CAIRO_PATH_LINE_TO:
                if (count==1) cairo_line_to(cr, points[0][0], points[0][1]);
                break;
            case CAIRO_PATH_CLOSE_PATH:
                if (count==0) cairo_close_path(cr);
                break;
            case CAIRO_PATH_CURVE_TO:
                if (count==3) cairo_curve_to(cr, points[0][0], points[0][1], points[1][0], points[1][1], points[2][0], points[2][1]);
                break;
            default:
                break;
            }
        } else {
            g_print("Unexpected zval, isn't cairo_path_data_t");
        }
    } ZEND_HASH_FOREACH_END();


    zend_string_release(member_header_str);
    zend_string_release(member_point_str);
    zend_string_release(member_x_str);
    zend_string_release(member_y_str);
    zend_string_release(member_type_str);
    zend_string_release(member_length_str);

    path = cairo_copy_path(cr);

    cairo_surface_destroy (surface);
    cairo_destroy (cr);

    return path;
}
void
php_cairo_path_t_update_num_data(php_cairo_path_t *intern){
    if (IS_ARRAY==Z_TYPE(intern->data)) {
        ZVAL_SET_LONG(&intern->num_data, zend_array_count(intern->data.value.arr));
    } else if (IS_REFERENCE==Z_TYPE(intern->data)) {
        if (IS_ARRAY==Z_TYPE(intern->data.value.ref->val)) {
            ZVAL_SET_LONG(&intern->num_data, zend_array_count(intern->data.value.ref->val.value.arr));
        } else {
            g_print("Expecting array for data\n");
        }
    } else {
        g_print("Expecting array for data\n");
    }
}

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | PHP_METHOD                                                           |
 +----------------------------------------------------------------------*/

 /* {{{ cairo_path_t::__construct() */
PHP_METHOD(cairo_path_t, __construct)
{
    //zend_object *zobj = Z_OBJ_P(getThis());
    //php_cairo_path_t *self = ZOBJ_TO_PHP_CAIRO_PATH_T(zobj);


}
/* }}} */

/*----------------------------------------------------------------------+
 | PHP_FUNCTION                                                         |
 +----------------------------------------------------------------------*/

#if CAIRO_VERSION >= 10000
/* {{{ proto php_cairo_path_t cairo_copy_path(php_cairo_t cr)
   Creates a copy of the current path and returns it to the user as a ca... */
PHP_FUNCTION(cairo_copy_path)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_path_t *ret = cairo_copy_path(cr);
    php_cairo_path_t *php_ret = php_cairo_path_t_new(ret);
    zend_object *z_ret = &php_ret->std;
    cairo_path_destroy(ret);

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto php_cairo_path_t cairo_copy_path_flat(php_cairo_t cr)
   Gets a flattened copy of the current path and returns it to the user ... */
PHP_FUNCTION(cairo_copy_path_flat)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_path_t *ret = cairo_copy_path_flat(cr);
    php_cairo_path_t *php_ret = php_cairo_path_t_new(ret);
    zend_object *z_ret = &php_ret->std;
    cairo_path_destroy(ret);

    RETURN_OBJ(z_ret);
}/* }}} */
/* {{{ proto void cairo_path_destroy(php_cairo_path_t path)
   Immediately releases all memory associated with path . */
PHP_FUNCTION(cairo_path_destroy)
{
    zval *zpath;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpath, php_cairo_path_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_path_t *php_path = ZVAL_IS_PHP_CAIRO_PATH_T(zpath)? ZVAL_GET_PHP_CAIRO_PATH_T(zpath): NULL;
    DECL_PHP_CAIRO_PATH_T(path);

    cairo_path_destroy(path);

    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_append_path(php_cairo_t cr, php_cairo_path_t path)
   Append the path onto the current path. */
PHP_FUNCTION(cairo_append_path)
{
    zval *zcr;
    zval *zpath;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_OBJECT_OF_CLASS_EX(zpath, php_cairo_path_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    php_cairo_path_t *php_path = ZVAL_IS_PHP_CAIRO_PATH_T(zpath)? ZVAL_GET_PHP_CAIRO_PATH_T(zpath): NULL;
    DECL_PHP_CAIRO_PATH_T(path);

    cairo_append_path(cr, path);
    cairo_path_destroy(path);

    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10600
/* {{{ proto cairo_bool_t cairo_has_current_point(php_cairo_t cr)
   Returns whether a current point is defined on the current path. */
PHP_FUNCTION(cairo_has_current_point)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_bool_t ret = cairo_has_current_point(cr);

    if (ret) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}/* }}} */
#endif
#if CAIRO_VERSION >= 10000
/* {{{ proto void cairo_get_current_point(php_cairo_t cr, double x, double y)
   Gets the current point of the current path, which is conceptually the... */
PHP_FUNCTION(cairo_get_current_point)
{
    zval *zcr;
    zval *zx;
    zval *zy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zx, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zy, 0, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    double x = zx->value.dval;
    double y = zy->value.dval;

    cairo_get_current_point(cr, &x, &y);
    ZVAL_DOUBLE(zx, x);
    ZVAL_DOUBLE(zy, y);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_new_path(php_cairo_t cr)
   Clears the current path. */
PHP_FUNCTION(cairo_new_path)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_new_path(cr);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10200
/* {{{ proto void cairo_new_sub_path(php_cairo_t cr)
   Begin a new sub-path. */
PHP_FUNCTION(cairo_new_sub_path)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_new_sub_path(cr);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10000
/* {{{ proto void cairo_close_path(php_cairo_t cr)
   Adds a line segment to the path from the current point to the beginni... */
PHP_FUNCTION(cairo_close_path)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_close_path(cr);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_arc(php_cairo_t cr, double xc, double yc, double radius, double angle1, double angle2)
   Adds a circular arc of the given radius to the current path. */
PHP_FUNCTION(cairo_arc)
{
    zval *zcr;
    double xc;
    double yc;
    double radius;
    double angle1;
    double angle2;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(xc);
        Z_PARAM_DOUBLE(yc);
        Z_PARAM_DOUBLE(radius);
        Z_PARAM_DOUBLE(angle1);
        Z_PARAM_DOUBLE(angle2);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_arc(cr, xc, yc, radius, angle1, angle2);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_arc_negative(php_cairo_t cr, double xc, double yc, double radius, double angle1, double angle2)
   Adds a circular arc of the given radius to the current path. */
PHP_FUNCTION(cairo_arc_negative)
{
    zval *zcr;
    double xc;
    double yc;
    double radius;
    double angle1;
    double angle2;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(xc);
        Z_PARAM_DOUBLE(yc);
        Z_PARAM_DOUBLE(radius);
        Z_PARAM_DOUBLE(angle1);
        Z_PARAM_DOUBLE(angle2);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_arc_negative(cr, xc, yc, radius, angle1, angle2);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_curve_to(php_cairo_t cr, double x1, double y1, double x2, double y2, double x3, double y3)
   Adds a cubic Bézier spline to the path from the current point to pos... */
PHP_FUNCTION(cairo_curve_to)
{
    zval *zcr;
    double x1;
    double y1;
    double x2;
    double y2;
    double x3;
    double y3;

    ZEND_PARSE_PARAMETERS_START(7, 7)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x1);
        Z_PARAM_DOUBLE(y1);
        Z_PARAM_DOUBLE(x2);
        Z_PARAM_DOUBLE(y2);
        Z_PARAM_DOUBLE(x3);
        Z_PARAM_DOUBLE(y3);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_curve_to(cr, x1, y1, x2, y2, x3, y3);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_line_to(php_cairo_t cr, double x, double y)
   Adds a line to the path from the current point to position (x , y ) i... */
PHP_FUNCTION(cairo_line_to)
{
    zval *zcr;
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x);
        Z_PARAM_DOUBLE(y);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_line_to(cr, x, y);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_move_to(php_cairo_t cr, double x, double y)
   Begin a new sub-path. After this call the current point will be (x , y ). */
PHP_FUNCTION(cairo_move_to)
{
    zval *zcr;
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x);
        Z_PARAM_DOUBLE(y);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_move_to(cr, x, y);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_rectangle(php_cairo_t cr, double x, double y, double width, double height)
   Adds a closed sub-path rectangle of the given size to the current pat... */
PHP_FUNCTION(cairo_rectangle)
{
    zval *zcr;
    double x;
    double y;
    double width;
    double height;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(x);
        Z_PARAM_DOUBLE(y);
        Z_PARAM_DOUBLE(width);
        Z_PARAM_DOUBLE(height);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_rectangle(cr, x, y, width, height);
    RETURN_NULL();
}/* }}} */

static size_t
php_cairo_glyph_path_get_glyphs_array (zend_array *arr, cairo_glyph_t **glyphs) {

    uint32_t size = zend_array_count(arr);
    cairo_glyph_t *array = emalloc(sizeof(cairo_glyph_t)*size);
    php_cairo_glyph_t *php_glyph;
    int i=0;
    int j=0;
    zval *value;
    ZEND_HASH_FOREACH_VAL(arr, value) {
        if (Z_TYPE_P(value)==IS_OBJECT) {
            if (instanceof_function(value->value.obj, php_cairo_glyph_t_class_entry)) {
                php_glyph = ZOBJ_TO_PHP_CAIRO_GLYPH_T(value->value.obj);
                PHP_CAIRO_GLYPH_T_COPY(php_glyph, &array[i]);
                i++;
            } else {
                php_printf("Error type: array[%d] is not glyph\n", j);
            }
        } else {
            php_printf("Error type: array[%d] is not glyph\n", j);
        }
        j++;
    } ZEND_HASH_FOREACH_END();

    *glyphs = array;
    return i;
}

/* {{{ proto void cairo_glyph_path(php_cairo_t cr, php_cairo_glyph_t glyphs, int num_glyphs)
   Adds closed paths for the glyphs to the current path. */
PHP_FUNCTION(cairo_glyph_path)
{
    zval *zcr;
    zval *zglyphs;
    cairo_glyph_t *glyphs;
    size_t num_glyphs;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_ARRAY(zglyphs);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    num_glyphs = php_cairo_glyph_path_get_glyphs_array (zglyphs->value.arr, &glyphs);


    cairo_glyph_path(cr, glyphs, num_glyphs);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_text_path(php_cairo_t cr, char utf8)
   Adds closed paths for text to the current path. */
PHP_FUNCTION(cairo_text_path)
{
    zval *zcr;
    char *utf8;
    size_t utf8_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_STRING(utf8, utf8_len);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_text_path(cr, utf8);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_rel_curve_to(php_cairo_t cr, double dx1, double dy1, double dx2, double dy2, double dx3, double dy3)
   Relative-coordinate version of cairo_curve_to(). */
PHP_FUNCTION(cairo_rel_curve_to)
{
    zval *zcr;
    double dx1;
    double dy1;
    double dx2;
    double dy2;
    double dx3;
    double dy3;

    ZEND_PARSE_PARAMETERS_START(7, 7)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(dx1);
        Z_PARAM_DOUBLE(dy1);
        Z_PARAM_DOUBLE(dx2);
        Z_PARAM_DOUBLE(dy2);
        Z_PARAM_DOUBLE(dx3);
        Z_PARAM_DOUBLE(dy3);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_rel_curve_to(cr, dx1, dy1, dx2, dy2, dx3, dy3);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_rel_line_to(php_cairo_t cr, double dx, double dy)
   Relative-coordinate version of cairo_line_to(). */
PHP_FUNCTION(cairo_rel_line_to)
{
    zval *zcr;
    double dx;
    double dy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(dx);
        Z_PARAM_DOUBLE(dy);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_rel_line_to(cr, dx, dy);
    RETURN_NULL();
}/* }}} */
/* {{{ proto void cairo_rel_move_to(php_cairo_t cr, double dx, double dy)
   Begin a new sub-path. */
PHP_FUNCTION(cairo_rel_move_to)
{
    zval *zcr;
    double dx;
    double dy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_DOUBLE(dx);
        Z_PARAM_DOUBLE(dy);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);

    cairo_rel_move_to(cr, dx, dy);
    RETURN_NULL();
}/* }}} */
#endif
#if CAIRO_VERSION >= 10600
/* {{{ proto void cairo_path_extents(php_cairo_t cr, double x1, double y1, double x2, double y2)
   Computes a bounding box in user-space coordinates covering the points... */
PHP_FUNCTION(cairo_path_extents)
{
    zval *zcr;
    zval *zx1;
    zval *zy1;
    zval *zx2;
    zval *zy2;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0);
        Z_PARAM_ZVAL_EX2(zx1, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zy1, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zx2, 0, 1, 0);
        Z_PARAM_ZVAL_EX2(zy2, 0, 1, 0);
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *php_cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    DECL_PHP_CAIRO_T(cr);
    double x1 = zx1->value.dval;
    double y1 = zy1->value.dval;
    double x2 = zx2->value.dval;
    double y2 = zy2->value.dval;

    cairo_path_extents(cr, &x1, &y1, &x2, &y2);
    ZVAL_DOUBLE(zx1, x1);
    ZVAL_DOUBLE(zy1, y1);
    ZVAL_DOUBLE(zx2, x2);
    ZVAL_DOUBLE(zy2, y2);
    RETURN_NULL();
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
