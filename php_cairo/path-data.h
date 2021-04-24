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

#ifndef PHP_CAIRO_PATH_DATA_T_H
#define PHP_CAIRO_PATH_DATA_T_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif



#define PHP_CAIRO_PATH_DATA_T(ptr)           ((php_cairo_path_data_t*)(ptr))
#define PHP_CAIRO_PATH_DATA_T_CLASS          php_cairo_path_data_t_class_entry
#define PHP_CAIRO_PATH_DATA_T_OFFSET         (sizeof(php_cairo_path_data_t) - sizeof(zend_object))

#define ZOBJ_IS_PHP_CAIRO_PATH_DATA_T(obj)   ((obj)!=NULL && obj->ce == php_cairo_path_data_t_class_entry)
#define ZOBJ_TO_PHP_CAIRO_PATH_DATA_T(std)   PHP_CAIRO_PATH_DATA_T( ((void*)(std))-PHP_CAIRO_PATH_DATA_T_OFFSET )

#define ZVAL_IS_PHP_CAIRO_PATH_DATA_T(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_CAIRO_PATH_DATA_T((val)->value.obj))
#define ZVAL_GET_PHP_CAIRO_PATH_DATA_T(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_CAIRO_PATH_DATA_T((val)->value.obj))


typedef struct _php_cairo_path_data_t php_cairo_path_data_t;
struct _php_cairo_path_data_t {
    cairo_path_data_t *ptr;
    zend_bool is_header;
    zend_bool is_owner;
    //cairo_path_t *path;

    zend_object std;
};

void php_cairo_path_data_t_create_header(cairo_path_data_t *data, zval *rv);
void php_cairo_path_data_t_create_point(cairo_path_data_t *data, zval *rv);
zend_class_entry *php_cairo_path_data_t_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce);

ZEND_BEGIN_ARG_INFO_EX(arginfo_cairo_path_data_t___construct, 0, 0, 1)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, x)
    ZEND_ARG_INFO(ZEND_SEND_BY_VAL, y)
ZEND_END_ARG_INFO()
PHP_METHOD(cairo_path_data_t, __construct);

#endif	/* PHP_CAIRO_PATH_DATA_T_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
