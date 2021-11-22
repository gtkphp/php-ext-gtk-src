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

#ifndef PHP_DOC_TAG_H
#define PHP_DOC_TAG_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


typedef struct _php_doc_tag php_doc_tag;

struct _php_doc_tag {
    zend_string *name;
    zend_array   parameters;// of php_doc_parameter(type hint|var)
    zend_string *description;

    // zend_object std;
};

php_doc_tag       *php_doc_tag_new(char *name, size_t len);
void               php_doc_tag_set_description(php_doc_tag *tag, zend_string *description);
void               php_doc_tag_free(zval *val);
zend_array        *php_doc_tag_get_parameters_by_name(php_doc_tag *tag, char *name);
php_doc_parameter *php_doc_tag_get_parameter_at(php_doc_tag *tag, int index);
//char* php_doc_tag_get_name(php_doc_tag *tag);
//char* php_doc_tag_get_summary(php_doc_tag *tag);
//char* php_doc_tag_get_description(php_doc_tag *tag);
//php_doc_parameter** php_doc_tag_get_parameters(php_doc_tag *tag);
//php_doc_parameter*  php_doc_tag_get_parameter(php_doc_tag *tag, int pos);
//php_doc_parameter*  php_doc_tag_get_parameter_by_name(php_doc_tag *tag, const char *name);


#endif	/* PHP_DOC_TAG_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
