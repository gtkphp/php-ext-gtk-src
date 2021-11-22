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

#include "parameter.h"
#include "tag.h"

php_doc_tag*
php_doc_tag_new(char *name, size_t len)
{
    php_doc_tag *intern = ecalloc(1, sizeof(php_doc_tag));
    intern->name = zend_string_init(name, len, 0);
    zend_hash_init(&intern->parameters, 10, NULL, php_doc_parameter_free, 0);
    return intern;
}

void
php_doc_tag_free(zval *val)
{
    php_doc_tag *tag = Z_PTR_P(val);
    ///printf("tag : %p\n", tag);

    if (tag->name) {
        zend_string_free(tag->name);
    }
    if (tag->description) {
        zend_string_free(tag->description);
    }

    zend_hash_destroy(&tag->parameters);



    efree(tag);
}


void php_doc_tag_set_description(php_doc_tag *tag, zend_string *description)
{
    tag->description = description;
}

zend_array*
php_doc_tag_get_parameters_by_name(php_doc_tag *tag, char *name)
{
    zend_array *parameters = malloc(sizeof(zend_array));
    zend_hash_init(parameters, 1, NULL, NULL, 1);// php_doc_parameter_free

    php_doc_parameter *parameter;
    ZEND_HASH_FOREACH_PTR(&tag->parameters, parameter) {
        if (parameter->name && 0==strcmp(parameter->name->val, name)) {
            zend_hash_next_index_insert_ptr(parameters, parameter);
        }
    } ZEND_HASH_FOREACH_END();

    return parameters;
}

php_doc_parameter*
php_doc_tag_get_parameter_at(php_doc_tag *tag, int index)
{
    php_doc_parameter *parameter;
    ZEND_HASH_FOREACH_PTR(&tag->parameters, parameter) {
        if (parameter->position == index) {
            return parameter;
        }
    } ZEND_HASH_FOREACH_END();

    return 0;
}
