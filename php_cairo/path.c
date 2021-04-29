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
#include <ext/standard/info.h>

#include <cairo/cairo.h>
#include "php_gtk.h"

#include "php_cairo/cairo.h"
#include "path-data.h"
#include "path.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;


zend_class_entry     *php_cairo_path_t_class_entry;
zend_object_handlers  php_cairo_path_t_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
| Internal                                                             |
+----------------------------------------------------------------------*/

static const zend_function_entry php_cairo_path_t_methods[] = {
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
    php_cairo_path_t *intern = ecalloc(1, sizeof(php_cairo_path_t) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->ptr = NULL;

    intern->std.handlers = &php_cairo_path_t_handlers;

    TRACE("php_cairo_path_t_create_object(%p) / %d\n", &intern->std, intern->std.gc.refcount);
    return &intern->std;
}
/* }}} php_cairo_path_t_create_object */


static void
php_cairo_path_t_dtor_object(zend_object *obj) {
    php_cairo_path_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_T(obj);
    TRACE("php_cairo_path_t_dtor_object(\e[1;31m\"%s\"\e[0;m) / %d\n", intern->data.value.str->val, obj->gc.refcount);


}

/* {{{ php_cairo_path_t_free_object */
static void
php_cairo_path_t_free_object(zend_object *object)
{
    php_cairo_path_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_T(object);
    TRACE("php_cairo_path_t_free_object(\e[1;31m\"%s\"\e[0;m) / %d\n", intern->data.value.str->val, object->gc.refcount);

    if (intern->ptr!=NULL) {
        cairo_path_destroy(intern->ptr);
    }

    zend_object_std_dtor(&intern->std);
    //efree(intern);
}
/* }}} php_cairo_path_t_free_object */


/* {{{ gtk_read_property */
static zval*
php_cairo_path_t_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_cairo_path_t *obj = ZVAL_GET_PHP_CAIRO_PATH_T(object);
    zend_string *member_str = zval_get_string(member);
    char *str = member_str->val;
    zval *retval;
    //php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (member_str->len==4 && str[0]=='d' && str[1]=='a' && str[2]=='t' && str[3]=='a' ) {
        zend_array *zarray; ALLOC_HASHTABLE(zarray);
        zend_hash_init(zarray, 1, NULL, ZVAL_PTR_DTOR, 1);

        zval member_point; ZVAL_STRING(&member_point, "point");
        zval member_header; ZVAL_STRING(&member_header, "header");
        zval zheader;
        zval zpoint;
        zend_object *std_class;
        zval val;
        int i, j;
        cairo_path_t *path = obj->ptr;
        cairo_path_data_t *data = path->data;
        for (i=0; i < path->num_data; i += path->data[i].header.length) {

            php_cairo_path_data_t_create_header(&path->data[i], &zheader);

            std_class = zend_objects_new(zend_standard_class_def);
            ZVAL_OBJ(&val, std_class);
            zend_std_write_property(&val, &member_header, &zheader, cache_slot);


            zend_hash_next_index_insert(zarray, &val);
            Z_TRY_DELREF(zheader);

            for(j=1; j<path->data[i].header.length; j++) {
                php_cairo_path_data_t_create_point(&path->data[i+j], &zpoint);

                std_class = zend_objects_new(zend_standard_class_def);
                ZVAL_OBJ(&val, std_class);
                zend_std_write_property(&val, &member_point, &zpoint, cache_slot);

                zend_hash_next_index_insert(zarray, &val);
                Z_TRY_DELREF(zpoint);
            }
        }


        ZVAL_ARR(rv, zarray);

        Z_TRY_DELREF(member_point);
        Z_TRY_DELREF(member_header);

        zend_string_release(member_str);
        return rv;
    }

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    retval = std_hnd->read_property(object, member, type, cache_slot, rv);

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ php_cairo_path_t_write_property */
static void
php_cairo_path_t_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_cairo_path_t *obj = ZVAL_GET_PHP_CAIRO_PATH_T(object);
    zend_string *member_str = zval_get_string(member);
    //php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (zend_string_equals_literal(member->value.str, "child")
     || zend_string_equals_literal(member->value.str, "parent") ) {
#if 1
        zend_error(E_USER_WARNING, "Readonly property Node::$%s", member->value.str->val);
#else
        if (ZVAL_IS_PHP_SAMPLE_NODE(value)) {
            // do unset(object->child) and php_cairo_path_t_insert(object, value, 0);
        } else {
            zend_string *type = zend_zval_get_type(value);
            zend_error(E_USER_WARNING, "Cannot assign %s to property Node::$child of type Node", type->val);
        }
#endif
        return;
    }
    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->write_property(object, member, value, cache_slot);

    zend_string_release(member_str);
}
/* }}} */

static void
php_cairo_path_t_unset_property(zval *object, zval *member, void **cache_slot) {
    php_cairo_path_t *obj = ZVAL_GET_PHP_CAIRO_PATH_T(object);
    zend_string *member_str = zval_get_string(member);
    //php_printf("%s(%s)\n", __FUNCTION__, member->value.str->val);


    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}

extern zend_class_entry *zend_standard_class_def;

static HashTable*
php_cairo_path_t_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_cairo_path_t  *obj =  ZVAL_GET_PHP_CAIRO_PATH_T(object);
    HashTable   *debug_info,
    *std_props;
    zend_string *string_key = NULL;
    zval *value;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    ZEND_HASH_FOREACH_STR_KEY_VAL(obj->std.properties, string_key, value) {
        zend_hash_add(debug_info, string_key, value);
    } ZEND_HASH_FOREACH_END();


    cairo_path_t *path = obj->ptr;

    if (NULL!=path) {
        zval status; ZVAL_LONG(&status, path->status);
        zend_hash_str_update(debug_info, "status", sizeof("status")-1, &status);

        zval num_data; ZVAL_LONG(&num_data, path->num_data);
        zend_hash_str_update(debug_info, "num_data", sizeof("num_data")-1, &num_data);

        zval data;
        zval member; ZVAL_STRING(&member, "data");
        php_cairo_path_t_read_property(object, &member, IS_ARRAY, NULL, &data);
        zend_hash_str_update(debug_info, "data", sizeof("data")-1, &data);

        zend_string_release(member.value.str);

    }

    return debug_info;
}
/* }}} */


static HashTable*
php_cairo_path_t_get_properties(zval *object){
    php_cairo_path_t  *self =  ZVAL_GET_PHP_CAIRO_PATH_T(object);


    return NULL;
}


static int
php_cairo_path_t_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}


/* updates *count to hold the number of elements present and returns SUCCESS.
* Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_cairo_path_t_count_elements(zval *object, zend_long *count) {

    *count = 0;//php_cairo_path_t_length(ZVAL_GET_PHP_CAIRO_PATH_T(object));

    return SUCCESS;
}

static int
php_cairo_path_t_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

static zval*
php_cairo_path_t_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
    return NULL;
    }

    ZVAL_NULL(rv);

    return rv;
} /* }}} end php_g_hash_table_read_dimension */


static void
php_cairo_path_t_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_cairo_path_t_write_property(object, &member, value, &cache);
}

static void
php_cairo_path_t_unset_dimension(zval *object, zval *offset) {
    //php_g_list *list = ZVAL_GET_PHP_G_LIST(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
    // @TODO
    //zend_hash_index_del(list->prop_handler, );
    // php_g_list
    break;
    case IS_STRING:
        php_cairo_path_t_unset_property(object, offset, &cache);
    break;
    default:
    break;
    }
}

static zend_object_handlers*
php_cairo_path_t_get_handlers()
{
    memcpy(&php_cairo_path_t_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_cairo_path_t_handlers.offset = PHP_CAIRO_PATH_T_OFFSET;
    //php_cairo_path_t_handlers.clone_obj;
    //php_cairo_path_t_handlers.compare;
    //php_cairo_path_t_handlers.compare_objects;
    //php_cairo_path_t_handlers.get_constructor;
    php_cairo_path_t_handlers.dtor_obj = php_cairo_path_t_dtor_object;
    php_cairo_path_t_handlers.free_obj = php_cairo_path_t_free_object;
    php_cairo_path_t_handlers.read_property = php_cairo_path_t_read_property;
    php_cairo_path_t_handlers.write_property = php_cairo_path_t_write_property;
    php_cairo_path_t_handlers.unset_property = php_cairo_path_t_unset_property;
    //php_cairo_path_t_handlers.get_property_ptr_ptr = php_cairo_path_t_get_property_ptr_ptr;

    php_cairo_path_t_handlers.get_debug_info = php_cairo_path_t_get_debug_info;
    php_cairo_path_t_handlers.get_properties = php_cairo_path_t_get_properties;//get_properties_for TODO php 8.0
    //php_cairo_path_t_handlers.set = php_cairo_path_t_set;
    php_cairo_path_t_handlers.cast_object = php_cairo_path_t_cast_object;

    php_cairo_path_t_handlers.count_elements = php_cairo_path_t_count_elements;
    php_cairo_path_t_handlers.has_dimension = php_cairo_path_t_has_dimension;
    php_cairo_path_t_handlers.read_dimension = php_cairo_path_t_read_dimension;
    php_cairo_path_t_handlers.unset_dimension = php_cairo_path_t_unset_dimension;
    php_cairo_path_t_handlers.write_dimension = php_cairo_path_t_write_dimension;


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
    //ce->serialize;
    /*
    zend_hash_init(&php_cairo_path_t_prop_handlers, 0, NULL, php_cairo_path_t_dtor_prop_handler, 1);
    php_cairo_path_t_register_prop_handler(&php_cairo_path_t_prop_handlers, "prev", sizeof("prev")-1, php_cairo_path_t_read_prev, php_cairo_path_t_write_prev);
    php_cairo_path_t_register_prop_handler(&php_cairo_path_t_prop_handlers, "data", sizeof("data")-1, php_cairo_path_t_read_data, php_cairo_path_t_write_data);
    php_cairo_path_t_register_prop_handler(&php_cairo_path_t_prop_handlers, "next", sizeof("next")-1, php_cairo_path_t_read_next, php_cairo_path_t_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_cairo_path_t_prop_handlers);
    */

    zend_register_long_constant("CAIRO_PATH_MOVE_TO", sizeof("CAIRO_PATH_MOVE_TO")-1,
                                CAIRO_PATH_MOVE_TO, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_PATH_LINE_TO", sizeof("CAIRO_PATH_LINE_TO")-1,
                                CAIRO_PATH_LINE_TO, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_PATH_CURVE_TO", sizeof("CAIRO_PATH_CURVE_TO")-1,
                                CAIRO_PATH_CURVE_TO, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);
    zend_register_long_constant("CAIRO_PATH_CLOSE_PATH", sizeof("CAIRO_PATH_CLOSE_PATH")-1,
                                CAIRO_PATH_CLOSE_PATH, CONST_CS | CONST_PERSISTENT, gtk_module_entry.module_number);

    return php_cairo_path_t_class_entry;
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

/* {{{ cairo_path_t::__construct() */
PHP_METHOD(cairo_path_t, __construct)
{
    zend_object *zobj = Z_OBJ_P(getThis());
    php_cairo_path_t *self = ZOBJ_TO_PHP_CAIRO_PATH_T(zobj);
}
/* }}} */

/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/
#define IS_IMPLEMENTED 0

/* {{{ proto cairo_path_t cairo_copy_path(cairo_t cr) */
PHP_FUNCTION(cairo_copy_path)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_path_t *path = cairo_copy_path(cr->ptr);
    if (NULL==path) {
        RETURN_NULL();
    }

    zend_object *zpath = php_cairo_path_t_create_object(php_cairo_path_t_class_entry);
    php_cairo_path_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_T(zpath);
    intern->ptr = path;


    RETURN_OBJ(zpath);
}/* }}} */

/* {{{ proto cairo_path_t cairo_copy_path_flat(cairo_t cr) */
PHP_FUNCTION(cairo_copy_path_flat)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_path_t *path = cairo_copy_path_flat(cr->ptr);

    if (NULL==path) {
        RETURN_NULL();
    }

    zend_object *zpath = php_cairo_path_t_create_object(php_cairo_path_t_class_entry);
    php_cairo_path_t *intern = ZOBJ_TO_PHP_CAIRO_PATH_T(zpath);
    intern->ptr = path;

    RETURN_OBJ(zpath);
}/* }}} */

/* {{{ proto void cairo_path_destroy(cairo_path_t path) */
PHP_FUNCTION(cairo_path_destroy)
{
    zval *zpath;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpath, php_cairo_path_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_path_t *intern = ZVAL_IS_PHP_CAIRO_PATH_T(zpath)? ZVAL_GET_PHP_CAIRO_PATH_T(zpath): NULL;

    if (intern->ptr) {
        cairo_path_destroy(intern->ptr);
        intern->ptr = NULL;
   }

}/* }}} */

/* {{{ proto void cairo_append_path(cairo_t cr, cairo_path_t path) */
PHP_FUNCTION(cairo_append_path)
{
    zval *zcr;
    zval *zpath;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zpath, php_cairo_path_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    php_cairo_path_t *path = ZVAL_IS_PHP_CAIRO_PATH_T(zpath)? ZVAL_GET_PHP_CAIRO_PATH_T(zpath): NULL;

    cairo_append_path(cr->ptr, path->ptr);


}/* }}} */

/* {{{ proto mixed cairo_has_current_point(cairo_t cr) */
PHP_FUNCTION(cairo_has_current_point)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_bool_t has = cairo_has_current_point(cr->ptr);

    if (has) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }

}/* }}} */

/* {{{ proto void cairo_get_current_point(cairo_t cr, int x, int y) */
PHP_FUNCTION(cairo_get_current_point)
{
    zval *zcr;
    zval *zx;
    zval *zy;
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_ZVAL_DEREF(zx)
        Z_PARAM_ZVAL_DEREF(zy)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_get_current_point(cr->ptr, &x, &y);

    ZVAL_DOUBLE(zx, x);
    ZVAL_DOUBLE(zy, y);

}/* }}} */

/* {{{ proto void cairo_new_path(cairo_t cr) */
PHP_FUNCTION(cairo_new_path)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_new_path(cr->ptr);


}/* }}} */

/* {{{ proto void cairo_new_sub_path(cairo_t cr) */
PHP_FUNCTION(cairo_new_sub_path)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_new_sub_path(cr->ptr);


}/* }}} */

/* {{{ proto void cairo_close_path(cairo_t cr) */
PHP_FUNCTION(cairo_close_path)
{
    zval *zcr;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_close_path(cr->ptr);


}/* }}} */

/* {{{ proto void cairo_arc(cairo_t cr, int xc, int yc, int radius, int angle1, int angle2) */
PHP_FUNCTION(cairo_arc)
{
    zval *zcr;
    double xc;
    double yc;
    double radius;
    double angle1;
    double angle2;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(xc)
        Z_PARAM_DOUBLE(yc)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_DOUBLE(angle1)
        Z_PARAM_DOUBLE(angle2)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_arc(cr->ptr, xc, yc, radius, angle1, angle2);


}/* }}} */

/* {{{ proto void cairo_arc_negative(cairo_t cr, int xc, int yc, int radius, int angle1, int angle2) */
PHP_FUNCTION(cairo_arc_negative)
{
    zval *zcr;
    double xc;
    double yc;
    double radius;
    double angle1;
    double angle2;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(xc)
        Z_PARAM_DOUBLE(yc)
        Z_PARAM_DOUBLE(radius)
        Z_PARAM_DOUBLE(angle1)
        Z_PARAM_DOUBLE(angle2)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_arc_negative(cr->ptr, xc, yc, radius, angle1, angle2);


}/* }}} */

/* {{{ proto void cairo_curve_to(cairo_t cr, int x1, int y1, int x2, int y2, int x3, int y3) */
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
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(x1)
        Z_PARAM_DOUBLE(y1)
        Z_PARAM_DOUBLE(x2)
        Z_PARAM_DOUBLE(y2)
        Z_PARAM_DOUBLE(x3)
        Z_PARAM_DOUBLE(y3)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_curve_to(cr->ptr, x1, y1, x2, y2, x3, y3);


}/* }}} */

/* {{{ proto void cairo_line_to(cairo_t cr, int x, int y) */
PHP_FUNCTION(cairo_line_to)
{
    zval *zcr;
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_line_to(cr->ptr, x, y);


}/* }}} */

/* {{{ proto void cairo_move_to(cairo_t cr, int x, int y) */
PHP_FUNCTION(cairo_move_to)
{
    zval *zcr;
    double x;
    double y;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_move_to(cr->ptr, x, y);


}/* }}} */

/* {{{ proto void cairo_rectangle(cairo_t cr, int x, int y, int width, int height) */
PHP_FUNCTION(cairo_rectangle)
{
    zval *zcr;
    double x;
    double y;
    double width;
    double height;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(x)
        Z_PARAM_DOUBLE(y)
        Z_PARAM_DOUBLE(width)
        Z_PARAM_DOUBLE(height)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_rectangle(cr->ptr, x, y, width, height);


}/* }}} */

/* {{{ proto void cairo_glyph_path(cairo_t cr, mixed glyphs, int num_glyphs) */
PHP_FUNCTION(cairo_glyph_path)
{
    zval *zcr;
    zval *zglyphs;
    zend_long num_glyphs;

#if IS_IMPLEMENTED
    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_OBJECT_OF_CLASS_EX(zglyphs, php_cairo_glyph_t_class_entry, 1, 0)
        Z_PARAM_LONG(num_glyphs)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_glyph_path(cr->ptr, glyphs, num_glyphs);
#endif

}/* }}} */

/* {{{ proto void cairo_text_path(cairo_t cr, string utf8) */
PHP_FUNCTION(cairo_text_path)
{
    zval *zcr;
    char *utf8;
    int utf8_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_STRING(utf8, utf8_len)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_text_path(cr->ptr, utf8);


}/* }}} */

/* {{{ proto void cairo_rel_curve_to(cairo_t cr, int dx1, int dy1, int dx2, int dy2, int dx3, int dy3) */
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
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(dx1)
        Z_PARAM_DOUBLE(dy1)
        Z_PARAM_DOUBLE(dx2)
        Z_PARAM_DOUBLE(dy2)
        Z_PARAM_DOUBLE(dx3)
        Z_PARAM_DOUBLE(dy3)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_rel_curve_to(cr->ptr, dx1, dy1, dx2, dy2, dx3, dy3);


}/* }}} */

/* {{{ proto void cairo_rel_line_to(cairo_t cr, int dx, int dy) */
PHP_FUNCTION(cairo_rel_line_to)
{
    zval *zcr;
    double dx;
    double dy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(dx)
        Z_PARAM_DOUBLE(dy)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_rel_line_to(cr->ptr, dx, dy);


}/* }}} */

/* {{{ proto void cairo_rel_move_to(cairo_t cr, int dx, int dy) */
PHP_FUNCTION(cairo_rel_move_to)
{
    zval *zcr;
    double dx;
    double dy;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_DOUBLE(dx)
        Z_PARAM_DOUBLE(dy)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;

    cairo_rel_move_to(cr->ptr, dx, dy);


}/* }}} */

/* {{{ proto void cairo_path_extents(cairo_t cr, int x1, int y1, int x2, int y2) */
PHP_FUNCTION(cairo_path_extents)
{
    zval *zcr;
    zval *zx1;
    zval *zy1;
    zval *zx2;
    zval *zy2;

    double x1;
    double y1;
    double x2;
    double y2;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_OBJECT_OF_CLASS_EX(zcr, php_cairo_t_class_entry, 1, 0)
        Z_PARAM_ZVAL_DEREF(zx1)
        Z_PARAM_ZVAL_DEREF(zy1)
        Z_PARAM_ZVAL_DEREF(zx2)
        Z_PARAM_ZVAL_DEREF(zy2)
    ZEND_PARSE_PARAMETERS_END();

    php_cairo_t *cr = ZVAL_IS_PHP_CAIRO_T(zcr)? ZVAL_GET_PHP_CAIRO_T(zcr): NULL;
    cairo_path_extents(cr->ptr, &x1, &y1, &x2, &y2);

    ZVAL_DOUBLE(zx1, x1);
    ZVAL_DOUBLE(zy1, y1);
    ZVAL_DOUBLE(zx2, x2);
    ZVAL_DOUBLE(zy2, y2);

}/* }}} */
