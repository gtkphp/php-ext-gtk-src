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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <php_ini.h>
#include <zend_interfaces.h>
//#include <zend_globals.h>
//#include <zend_globals_macros.h>
#include <ext/standard/info.h>

#include "matrix.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_matrix_class_entry;
zend_object_handlers  php_cairo_matrix_handlers;


static const zend_function_entry php_cairo_matrix_methods[] = {
    PHP_ME(cairo_matrix, __construct, arginfo_cairo_matrix___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static void
php_cairo_matrix_set_xx(php_cairo_matrix *matrix, zval *value) {
    if (Z_TYPE_P(value)==IS_DOUBLE)
        matrix->ptr->xx = value->value.dval;
    else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        int allow_errors = -1;
        double dval;
        if (!strict_types && Z_TYPE_P(value)==IS_STRING
         && is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), NULL, &dval, allow_errors) ) {
            matrix->ptr->xx = dval;
            return;
        }
        zend_string *type = zend_zval_get_type(value);
        zend_internal_type_error(1, "Cannot assign %s to property \\cairo_matrix_t::$xx of type float,", type->val);
    }
}

static void
php_cairo_matrix_set_yx(php_cairo_matrix *matrix, zval *value) {
    if (Z_TYPE_P(value)==IS_DOUBLE)
        matrix->ptr->yx = value->value.dval;
    else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        int allow_errors = -1;
        double dval;
        if (!strict_types && Z_TYPE_P(value)==IS_STRING
         && is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), NULL, &dval, allow_errors) ) {
            matrix->ptr->yx = dval;
            return;
        }
        zend_string *type = zend_zval_get_type(value);
        zend_internal_type_error(1, "Cannot assign %s to property \\cairo_matrix_t::$yx of type float,", type->val);
    }
}

static void
php_cairo_matrix_set_xy(php_cairo_matrix *matrix, zval *value) {
    if (Z_TYPE_P(value)==IS_DOUBLE)
        matrix->ptr->xy = value->value.dval;
    else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        int allow_errors = -1;
        double dval;
        if (!strict_types && Z_TYPE_P(value)==IS_STRING
         && is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), NULL, &dval, allow_errors) ) {
            matrix->ptr->xy = dval;
            return;
        }
        zend_string *type = zend_zval_get_type(value);
        zend_internal_type_error(1, "Cannot assign %s to property \\cairo_matrix_t::$xy of type float,", type->val);
    }
}

static void
php_cairo_matrix_set_yy(php_cairo_matrix *matrix, zval *value) {
    if (Z_TYPE_P(value)==IS_DOUBLE)
        matrix->ptr->yy = value->value.dval;
    else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        int allow_errors = -1;
        double dval;
        if (!strict_types && Z_TYPE_P(value)==IS_STRING
         && is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), NULL, &dval, allow_errors) ) {
            matrix->ptr->yy = dval;
            return;
        }
        zend_string *type = zend_zval_get_type(value);
        zend_internal_type_error(1, "Cannot assign %s to property \\cairo_matrix_t::$yy of type float,", type->val);
    }
}

static void
php_cairo_matrix_set_x0(php_cairo_matrix *matrix, zval *value) {
    if (Z_TYPE_P(value)==IS_DOUBLE)
        matrix->ptr->x0 = value->value.dval;
    else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        int allow_errors = -1;
        double dval;
        if (!strict_types && Z_TYPE_P(value)==IS_STRING
         && is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), NULL, &dval, allow_errors) ) {
            matrix->ptr->x0 = dval;
            return;
        }
        zend_string *type = zend_zval_get_type(value);
        zend_internal_type_error(1, "Cannot assign %s to property \\cairo_matrix_t::$x0 of type float,", type->val);
    }
}

static void
php_cairo_matrix_set_y0(php_cairo_matrix *matrix, zval *value) {
    if (Z_TYPE_P(value)==IS_DOUBLE)
        matrix->ptr->y0 = value->value.dval;
    else {
        zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
        int allow_errors = -1;
        double dval;
        if (!strict_types && Z_TYPE_P(value)==IS_STRING
         && is_numeric_string(Z_STRVAL_P(value), Z_STRLEN_P(value), NULL, &dval, allow_errors) ) {
            matrix->ptr->y0 = dval;
            return;
        }
        zend_string *type = zend_zval_get_type(value);
        zend_internal_type_error(1, "Cannot assign %s to property \\cairo_matrix_t::$y0 of type float,", type->val);
    }
}

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/
static void
php_cairo_matrix_unset_dimension(zval *object, zval *offset) {
    //php_g_list *list = ZVAL_GET_PHP_G_LIST(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
        // @TODO
        //zend_hash_index_del(list->prop_handler, );
        // php_g_list
        break;
    case IS_STRING:
        //php_cairo_matrix_unset_property(object, offset, &cache);
        break;
    default:
        break;
    }
}

static void
php_cairo_matrix_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    //php_cairo_matrix_write_property(object, &member, value, &cache);
    if (IS_STRING==Z_TYPE_P(offset)) {
        zend_string *member_str = offset->value.str;
        php_cairo_matrix *obj = ZVAL_GET_PHP_CAIRO_MATRIX(object);
        if (zend_string_equals_literal(member_str, "xx")) {
            php_cairo_matrix_set_xx(obj, value);
            return;
        }
        if (zend_string_equals_literal(member_str, "yx")) {
            php_cairo_matrix_set_yx(obj, value);
            return;
        }

        if (zend_string_equals_literal(member_str, "xy")) {
            php_cairo_matrix_set_xy(obj, value);
            return;
        }
        if (zend_string_equals_literal(member_str, "yy")) {
            php_cairo_matrix_set_yy(obj, value);
            return;
        }

        if (zend_string_equals_literal(member_str, "x0")) {
            php_cairo_matrix_set_x0(obj, value);
            return;
        }
        if (zend_string_equals_literal(member_str, "y0")) {
            php_cairo_matrix_set_y0(obj, value);
            return;
        }
    } else {

    }
}

static zval*
php_cairo_matrix_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
        return NULL;
    }

    php_cairo_matrix *intern = ZVAL_GET_PHP_CAIRO_MATRIX(object);
    php_cairo_matrix *list;
    void *cache=NULL;

    if (Z_TYPE_P(offset)==IS_LONG) {
        /*list = php_cairo_matrix_nth(intern, offset->value.lval);
        if (list) {
            ZVAL_COPY(rv, &list->data);
        } else*/ {
            ZVAL_NULL(rv);
            zend_error(E_USER_WARNING, "Undefined offset: %d", offset->value.lval);
        }
        return rv;
    } else if (Z_TYPE_P(offset)==IS_STRING) {
        //return php_cairo_matrix_read_property(object, offset, type, &cache, rv);
    } else {
        // error
    }

    return rv;
} /* }}} end php_g_hash_table_read_dimension */

static int
php_cairo_matrix_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

/* updates *count to hold the number of elements present and returns SUCCESS.
 * Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_cairo_matrix_count_elements(zval *object, zend_long *count) {

    *count = 6;//php_cairo_matrix_length(ZVAL_GET_PHP_CAIRO_MATRIX(object));

    return SUCCESS;
}

static int
php_cairo_matrix_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}

static HashTable*
php_cairo_matrix_get_properties(zval *object){
    php_cairo_matrix  *self =  ZVAL_GET_PHP_CAIRO_MATRIX(object);

    HashTable *props = self->std.properties;
/*
    if (props==NULL) {
        ALLOC_HASHTABLE(props);//self->properties);
        //props = self->properties;
    } else {
        // TODO: rebuild the props( update)
        return props;// Else leaks : zend_hash_next_index_insert
    }

    zend_long length = 6;

    zend_hash_init(props, length, NULL, ZVAL_PTR_DTOR, 1);

    zval data;

    */

    return props;
}

static HashTable*
php_cairo_matrix_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_cairo_matrix  *obj =  ZVAL_GET_PHP_CAIRO_MATRIX(object);
    HashTable   *debug_info,
                *std_props;
    zend_string *string_key = NULL;
    zval *value;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    cairo_matrix_t *m = obj->ptr;

    zval xx; ZVAL_DOUBLE(&xx, m->xx);
    zend_hash_str_update(debug_info, "xx", sizeof("xx")-1, &xx);
    zval yx; ZVAL_DOUBLE(&yx, m->yx);
    zend_hash_str_update(debug_info, "yx", sizeof("yx")-1, &yx);

    zval xy; ZVAL_DOUBLE(&xy, m->xy);
    zend_hash_str_update(debug_info, "xy", sizeof("xy")-1, &xy);
    zval yy; ZVAL_DOUBLE(&yy, m->yy);
    zend_hash_str_update(debug_info, "yy", sizeof("yy")-1, &yy);

    zval x0; ZVAL_DOUBLE(&x0, m->x0);
    zend_hash_str_update(debug_info, "x0", sizeof("x0")-1, &x0);
    zval y0; ZVAL_DOUBLE(&y0, m->y0);
    zend_hash_str_update(debug_info, "y0", sizeof("y0")-1, &y0);

    ZEND_HASH_FOREACH_STR_KEY_VAL(obj->std.properties, string_key, value) {
        zend_hash_add(debug_info, string_key, value);
    } ZEND_HASH_FOREACH_END();


    return debug_info;
}
/* }}} */

static void
php_cairo_matrix_unset_property(zval *object, zval *member, void **cache_slot) {
    php_cairo_matrix *obj = ZVAL_GET_PHP_CAIRO_MATRIX(object);
    zend_string *member_str = zval_get_string(member);

    if (zend_string_equals_literal(member->value.str, "xx")
     || zend_string_equals_literal(member->value.str, "yx")
     || zend_string_equals_literal(member->value.str, "xy")
     || zend_string_equals_literal(member->value.str, "yy")
     || zend_string_equals_literal(member->value.str, "x0")
     || zend_string_equals_literal(member->value.str, "y0") ) {
        zend_error(E_USER_WARNING, "Unsetable property \\cairo_matrix_t::$%s", member->value.str->val);
        return;
    }
    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}

/* {{{ php_cairo_matrix_write_property */
static void
php_cairo_matrix_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_cairo_matrix *obj = ZVAL_GET_PHP_CAIRO_MATRIX(object);
    zend_string *member_str = zval_get_string(member);
    //php_printf("%s(%s)", __FUNCTION__, member->value.str->val);

    cairo_matrix_t *m = obj->ptr;

    if (zend_string_equals_literal(member_str, "xx")) {
        php_cairo_matrix_set_xx(obj, value);
        return;
    }
    if (zend_string_equals_literal(member_str, "yx")) {
        php_cairo_matrix_set_yx(obj, value);
        return;
    }

    if (zend_string_equals_literal(member_str, "xy")) {
        php_cairo_matrix_set_xy(obj, value);
        return;
    }
    if (zend_string_equals_literal(member_str, "yy")) {
        php_cairo_matrix_set_yy(obj, value);
        return;
    }

    if (zend_string_equals_literal(member_str, "x0")) {
        php_cairo_matrix_set_x0(obj, value);
        return;
    }
    if (zend_string_equals_literal(member_str, "y0")) {
        php_cairo_matrix_set_y0(obj, value);
        return;
    }

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->write_property(object, member, value, cache_slot);

    zend_string_release(member_str);
}
/* }}} */

static zval zval_ret;
/* {{{ gtk_read_property */
static zval*
php_cairo_matrix_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_cairo_matrix *obj = ZVAL_GET_PHP_CAIRO_MATRIX(object);
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    //php_printf("%s(%s)", __FUNCTION__, member->value.str->val);

    cairo_matrix_t *m = obj->ptr;

    if (zend_string_equals_literal(member_str, "xx")) {
        ZVAL_DOUBLE(&zval_ret, m->xx)
        return &zval_ret;
    }
    if (zend_string_equals_literal(member_str, "yx")) {
        ZVAL_DOUBLE(&zval_ret, m->yx)
        return &zval_ret;
    }

    if (zend_string_equals_literal(member_str, "xy")) {
        ZVAL_DOUBLE(&zval_ret, m->xy)
        return &zval_ret;
    }
    if (zend_string_equals_literal(member_str, "yy")) {
        ZVAL_DOUBLE(&zval_ret, m->yy)
        return &zval_ret;
    }

    if (zend_string_equals_literal(member_str, "x0")) {
        ZVAL_DOUBLE(&zval_ret, m->x0)
        return &zval_ret;
    }
    if (zend_string_equals_literal(member_str, "y0")) {
        ZVAL_DOUBLE(&zval_ret, m->y0)
        return &zval_ret;
    }

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    retval = std_hnd->read_property(object, member, type, cache_slot, rv);

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ php_cairo_matrix_free_object */
static void
php_cairo_matrix_free_object(zend_object *object)
{
    php_cairo_matrix *intern = ZOBJ_TO_PHP_CAIRO_MATRIX(object);

    zend_object_std_dtor(&intern->std);
    //efree(intern);
}
/* }}} php_cairo_matrix_free_object */

static void
php_cairo_matrix_dtor_object(zend_object *obj) {
    php_cairo_matrix *intern = ZOBJ_TO_PHP_CAIRO_MATRIX(obj);

    if (intern->ptr) {
        efree(intern->ptr);
        intern->ptr = NULL;
    }

}

/* {{{ php_cairo_matrix_create_object */
static zend_object*
php_cairo_matrix_create_object(zend_class_entry *class_type)
{
    php_cairo_matrix *intern = ecalloc(1, sizeof(php_cairo_matrix) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    //php_cairo_matrix_properties_init(intern);
    intern->ptr = ecalloc(1, sizeof(cairo_matrix_t));
    cairo_matrix_init_identity(intern->ptr);

    intern->std.handlers = &php_cairo_matrix_handlers;

    return &intern->std;
}
/* }}} php_cairo_matrix_create_object */



static zend_object_handlers*
php_cairo_matrix_get_handlers()
{
    memcpy(&php_cairo_matrix_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_matrix_handlers.offset = PHP_CAIRO_MATRIX_OFFSET;
    //php_cairo_matrix_handlers.clone_obj;
    //php_cairo_matrix_handlers.compare;
    //php_cairo_matrix_handlers.compare_objects;
    //php_cairo_matrix_handlers.get_constructor;
    php_cairo_matrix_handlers.dtor_obj = php_cairo_matrix_dtor_object;
    php_cairo_matrix_handlers.free_obj = php_cairo_matrix_free_object;
    php_cairo_matrix_handlers.read_property = php_cairo_matrix_read_property;
    php_cairo_matrix_handlers.write_property = php_cairo_matrix_write_property;
    php_cairo_matrix_handlers.unset_property = php_cairo_matrix_unset_property;
    //php_cairo_matrix_handlers.get_property_ptr_ptr = php_cairo_matrix_get_property_ptr_ptr;

    php_cairo_matrix_handlers.get_debug_info = php_cairo_matrix_get_debug_info;
    php_cairo_matrix_handlers.get_properties = php_cairo_matrix_get_properties;//get_properties_for TODO php 8.0
    //php_cairo_matrix_handlers.set = php_cairo_matrix_set;
    php_cairo_matrix_handlers.cast_object = php_cairo_matrix_cast_object;

    php_cairo_matrix_handlers.count_elements = php_cairo_matrix_count_elements;
    php_cairo_matrix_handlers.has_dimension = php_cairo_matrix_has_dimension;
    php_cairo_matrix_handlers.read_dimension = php_cairo_matrix_read_dimension;
    php_cairo_matrix_handlers.unset_dimension = php_cairo_matrix_unset_dimension;
    php_cairo_matrix_handlers.write_dimension = php_cairo_matrix_write_dimension;


    return &php_cairo_matrix_handlers;
}



/*----------------------------------------------------------------------+
 | PHP_MINIT                                                            |
 +----------------------------------------------------------------------*/
#if 0
typedef enum _php_my_type {
    PHP_MY_CAIRO_TYPE,
} php_my_type;

typedef struct _php_my_object php_my_object;
struct _php_my_object {
    php_my_type type;
    void *ptr;
    zend_object std;
};

typedef int (*php_my_property_read)(php_my_object *obj, zval *retval);
typedef int (*php_my_property_write)(php_my_object *obj, zval *newval);

typedef struct _php_my_property {
    php_my_property_read read_func;
    php_my_property_write write_func;
} php_my_property;

/* {{{ dom_register_prop_handler */
static void php_my_register_property(HashTable *prop_handler, char *name, size_t name_len, php_my_property_read read_func, php_my_property_write write_func)
{
    php_my_property hnd;

    hnd.read_func = read_func ? read_func : dom_read_na;
    hnd.write_func = write_func ? write_func : dom_write_na;
    //hnd.unset_func = write_func ? write_func : dom_write_na; clear
    zend_hash_str_add_mem(prop_handler, name, name_len, &hnd, sizeof(php_my_property));
}
/* }}} */
#endif

/*{{{ php_cairo_matrix_class_init */
zend_class_entry*
php_cairo_matrix_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_cairo_matrix_get_handlers();
    //INIT_NS_CLASS_ENTRY((*ce), "Gnome\\G", "List", php_cairo_matrix_methods);
    INIT_CLASS_ENTRY((*container_ce), "cairo_matrix_t", php_cairo_matrix_methods);// Keep CairoMatrix for cairo-gobject
    php_cairo_matrix_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_cairo_matrix_class_entry->create_object = php_cairo_matrix_create_object;
    //ce->serialize;



    //php_my_register_property(&php_cairo_node_prop_handlers, "nodeName", sizeof("nodeName")-1, dom_node_node_name_read, NULL);
    /*
    zend_hash_init(&php_cairo_matrix_prop_handlers, 0, NULL, php_cairo_matrix_dtor_prop_handler, 1);
    php_cairo_matrix_register_prop_handler(&php_cairo_matrix_prop_handlers, "prev", sizeof("prev")-1, php_cairo_matrix_read_prev, php_cairo_matrix_write_prev);
    php_cairo_matrix_register_prop_handler(&php_cairo_matrix_prop_handlers, "data", sizeof("data")-1, php_cairo_matrix_read_data, php_cairo_matrix_write_data);
    php_cairo_matrix_register_prop_handler(&php_cairo_matrix_prop_handlers, "next", sizeof("next")-1, php_cairo_matrix_read_next, php_cairo_matrix_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_cairo_matrix_prop_handlers);
    */

    return php_cairo_matrix_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
void
php_cairo_matrix_init(php_cairo_matrix *matrix, double xx, double yx, double xy, double yy, double x0, double y0) {
    // TODO: implementation
}

void
php_cairo_matrix_init_identity(php_cairo_matrix *matrix) {
    // TODO: implementation
}

void
php_cairo_matrix_init_translate(php_cairo_matrix *matrix, double tx, double ty) {
    // TODO: implementation
}

void
php_cairo_matrix_init_scale(php_cairo_matrix *matrix, double sx, double sy) {
    // TODO: implementation
}

void
php_cairo_matrix_init_rotate(php_cairo_matrix *matrix, double radians) {
    // TODO: implementation
}

void
php_cairo_matrix_translate(php_cairo_matrix *matrix, double tx, double ty) {
    // TODO: implementation
}

void
php_cairo_matrix_scale(php_cairo_matrix *matrix, double sx, double sy) {
    // TODO: implementation
}

void
php_cairo_matrix_rotate(php_cairo_matrix *matrix, double radians) {
    // TODO: implementation
}

php_cairo_matrix*
php_cairo_matrix_invert(php_cairo_matrix *matrix) {
    // TODO: implementation
}

void
php_cairo_matrix_multiply(php_cairo_matrix *result, php_cairo_matrix *a, php_cairo_matrix *b) {
    // TODO: implementation
}

void
php_cairo_matrix_transform_distance(php_cairo_matrix *matrix, double dx, double dy) {
    // TODO: implementation
}

void
php_cairo_matrix_transform_point(php_cairo_matrix *matrix, double x, double y) {
    // TODO: implementation
}




/*----------------------------------------------------------------------+
| PHP_METHOD                                                           |
+----------------------------------------------------------------------*/

/* {{{ cairo_matrix_t::__construct() */
PHP_METHOD(cairo_matrix, __construct)
{

    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();

    zend_object *zobj = Z_OBJ_P(getThis());
    php_cairo_matrix *self = ZOBJ_TO_PHP_CAIRO_MATRIX(zobj);
}
/* }}} */

/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/

/* {{{ proto void cairo_matrix_init(cairo_matrix_t matrix, mixed xx, mixed yx, mixed xy, mixed yy, mixed x0, mixed y0) */
PHP_FUNCTION(cairo_matrix_init)
{
    zval *zmatrix = NULL;
    double __xx = 0.0;
    double __yx = 0.0;
    double __xy = 0.0;
    double __yy = 0.0;
    double __x0 = 0.0;
    double __y0 = 0.0;

    ZEND_PARSE_PARAMETERS_START(7, 7)
        Z_PARAM_OBJECT_OF_CLASS_EX(zmatrix, php_cairo_matrix_class_entry, 1, 0)
        Z_PARAM_DOUBLE(__xx)
        Z_PARAM_DOUBLE(__yx)
        Z_PARAM_DOUBLE(__xy)
        Z_PARAM_DOUBLE(__yy)
        Z_PARAM_DOUBLE(__x0)
        Z_PARAM_DOUBLE(__y0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix *__matrix = ZVAL_IS_PHP_CAIRO_MATRIX(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX(zmatrix): NULL;
    cairo_matrix_init(__matrix->ptr, __xx, __yx, __xy, __yy, __x0, __y0);


}/* }}} */

/* {{{ proto void cairo_matrix_init_identity(cairo_matrix_t matrix) */
PHP_FUNCTION(cairo_matrix_init_identity)
{
    zval *zmatrix = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zmatrix)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix *__matrix = ZVAL_IS_PHP_CAIRO_MATRIX(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX(zmatrix): NULL;
    php_cairo_matrix_init_identity(__matrix);

}/* }}} */

/* {{{ proto void cairo_matrix_init_translate(cairo_matrix_t matrix, mixed tx, mixed ty) */
PHP_FUNCTION(cairo_matrix_init_translate)
{
    zval *zmatrix = NULL;
    zval *ztx = NULL;
    zval *zty = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zmatrix)
        Z_PARAM_ZVAL(ztx)
        Z_PARAM_ZVAL(zty)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix *__matrix = ZVAL_IS_PHP_CAIRO_MATRIX(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX(zmatrix): NULL;
    double __tx = Z_TYPE_P(ztx)==IS_DOUBLE? ztx->value.dval: 0;
    double __ty = Z_TYPE_P(zty)==IS_DOUBLE? zty->value.dval: 0;
    php_cairo_matrix_init_translate(__matrix, __tx, __ty);

}/* }}} */

/* {{{ proto void cairo_matrix_init_scale(cairo_matrix_t matrix, mixed sx, mixed sy) */
PHP_FUNCTION(cairo_matrix_init_scale)
{
    zval *zmatrix = NULL;
    zval *zsx = NULL;
    zval *zsy = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zmatrix)
        Z_PARAM_ZVAL(zsx)
        Z_PARAM_ZVAL(zsy)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix *__matrix = ZVAL_IS_PHP_CAIRO_MATRIX(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX(zmatrix): NULL;
    double __sx = Z_TYPE_P(zsx)==IS_DOUBLE? zsx->value.dval: 0;
    double __sy = Z_TYPE_P(zsy)==IS_DOUBLE? zsy->value.dval: 0;
    php_cairo_matrix_init_scale(__matrix, __sx, __sy);

}/* }}} */

/* {{{ proto void cairo_matrix_init_rotate(cairo_matrix_t matrix, mixed radians) */
PHP_FUNCTION(cairo_matrix_init_rotate)
{
    zval *zmatrix = NULL;
    zval *zradians = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zmatrix)
        Z_PARAM_ZVAL(zradians)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix *__matrix = ZVAL_IS_PHP_CAIRO_MATRIX(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX(zmatrix): NULL;
    double __radians = Z_TYPE_P(zradians)==IS_DOUBLE? zradians->value.dval: 0;
    php_cairo_matrix_init_rotate(__matrix, __radians);

}/* }}} */

/* {{{ proto void cairo_matrix_translate(cairo_matrix_t matrix, mixed tx, mixed ty) */
PHP_FUNCTION(cairo_matrix_translate)
{
    zval *zmatrix = NULL;
    zval *ztx = NULL;
    zval *zty = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zmatrix)
        Z_PARAM_ZVAL(ztx)
        Z_PARAM_ZVAL(zty)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix *__matrix = ZVAL_IS_PHP_CAIRO_MATRIX(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX(zmatrix): NULL;
    double __tx = Z_TYPE_P(ztx)==IS_DOUBLE? ztx->value.dval: 0.0;
    double __ty = Z_TYPE_P(zty)==IS_DOUBLE? zty->value.dval: 0.0;
    php_cairo_matrix_translate(__matrix, __tx, __ty);

}/* }}} */

/* {{{ proto void cairo_matrix_scale(cairo_matrix_t matrix, mixed sx, mixed sy) */
PHP_FUNCTION(cairo_matrix_scale)
{
    zval *zmatrix = NULL;
    zval *zsx = NULL;
    zval *zsy = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zmatrix)
        Z_PARAM_ZVAL(zsx)
        Z_PARAM_ZVAL(zsy)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix *__matrix = ZVAL_IS_PHP_CAIRO_MATRIX(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX(zmatrix): NULL;
    double __sx = Z_TYPE_P(zsx)==IS_DOUBLE? zsx->value.dval: 0.0;
    double __sy = Z_TYPE_P(zsy)==IS_DOUBLE? zsy->value.dval: 0.0;
    php_cairo_matrix_scale(__matrix, __sx, __sy);

}/* }}} */

/* {{{ proto void cairo_matrix_rotate(cairo_matrix_t matrix, mixed radians) */
PHP_FUNCTION(cairo_matrix_rotate)
{
    zval *zmatrix = NULL;
    zval *zradians = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ZVAL(zmatrix)
        Z_PARAM_ZVAL(zradians)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix *__matrix = ZVAL_IS_PHP_CAIRO_MATRIX(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX(zmatrix): NULL;
    double __radians = Z_TYPE_P(zradians)==IS_DOUBLE? zradians->value.dval: 0;
    php_cairo_matrix_rotate(__matrix, __radians);

}/* }}} */

/* {{{ proto mixed cairo_matrix_invert(cairo_matrix_t matrix) */
PHP_FUNCTION(cairo_matrix_invert)
{
    zval *zmatrix = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zmatrix)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix *__matrix = ZVAL_IS_PHP_CAIRO_MATRIX(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX(zmatrix): NULL;
    php_cairo_matrix *__ret = php_cairo_matrix_invert(__matrix);

    RETURN_OBJ(&__ret->std);
}/* }}} */

/* {{{ proto void cairo_matrix_multiply(cairo_matrix_t result, cairo_matrix_t a, cairo_matrix_t b) */
PHP_FUNCTION(cairo_matrix_multiply)
{
    zval *zresult = NULL;
    zval *za = NULL;
    zval *zb = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zresult)
        Z_PARAM_ZVAL(za)
        Z_PARAM_ZVAL(zb)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix *__result = /*ZVAL_IS_PHP_CAIRO_MATRIX(zresult)? ZVAL_GET_PHP_CAIRO_MATRIX(zresult): */NULL;
    php_cairo_matrix *__a = ZVAL_IS_PHP_CAIRO_MATRIX(za)? ZVAL_GET_PHP_CAIRO_MATRIX(za): NULL;
    php_cairo_matrix *__b = ZVAL_IS_PHP_CAIRO_MATRIX(zb)? ZVAL_GET_PHP_CAIRO_MATRIX(zb): NULL;
    php_cairo_matrix_multiply(__result, __a, __b);

    ZVAL_OBJ(zresult, &__result->std);
}/* }}} */

/* {{{ proto void cairo_matrix_transform_distance(cairo_matrix_t matrix, mixed dx, mixed dy) */
PHP_FUNCTION(cairo_matrix_transform_distance)
{
    zval *zmatrix = NULL;
    zval *zdx = NULL;
    zval *zdy = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zmatrix)
        Z_PARAM_ZVAL(zdx)
        Z_PARAM_ZVAL(zdy)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix *__matrix = ZVAL_IS_PHP_CAIRO_MATRIX(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX(zmatrix): NULL;
    double __dx = Z_TYPE_P(zdx)==IS_DOUBLE? zdx->value.dval: 0.0;
    double __dy = Z_TYPE_P(zdy)==IS_DOUBLE? zdy->value.dval: 0.0;
    php_cairo_matrix_transform_distance(__matrix, __dx, __dy);

}/* }}} */

/* {{{ proto void cairo_matrix_transform_point(cairo_matrix_t matrix, mixed x, mixed y) */
PHP_FUNCTION(cairo_matrix_transform_point)
{
    zval *zmatrix = NULL;
    zval *zx = NULL;
    zval *zy = NULL;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zmatrix)
        Z_PARAM_ZVAL(zx)
        Z_PARAM_ZVAL(zy)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_matrix *__matrix = ZVAL_IS_PHP_CAIRO_MATRIX(zmatrix)? ZVAL_GET_PHP_CAIRO_MATRIX(zmatrix): NULL;
    double __zx = Z_TYPE_P(zx)==IS_DOUBLE? zx->value.dval: 0.0;
    double __zy = Z_TYPE_P(zy)==IS_DOUBLE? zy->value.dval: 0.0;
    php_cairo_matrix_transform_point(__matrix, __zx, __zy);

}/* }}} */

