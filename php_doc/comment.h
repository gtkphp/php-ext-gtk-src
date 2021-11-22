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

#ifndef PHP_DOC_COMMENT_H
#define PHP_DOC_COMMENT_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


typedef struct _php_doc_callable            php_doc_callable;
struct _php_doc_callable {
    zend_string *name;
    zend_string *context;
};
php_doc_callable   *php_doc_callable_new();
void                php_doc_callable_free(php_doc_callable *cb);

typedef struct _php_doc_comment             php_doc_comment;

struct _php_doc_comment {
    //int sha_bang;
    zend_string *summary;
    zend_string *description;
    zend_array   tags;// of php_doc_tag
};

php_doc_comment   *php_doc_comment_new();
//void             php_doc_comment_set_summary(php_doc_comment *comment, zend_string *summary);
//void             php_doc_comment_set_description(php_doc_comment *comment, zend_string *description);
//void             php_doc_comment_set_tags(php_doc_comment *comment, void *tags);
zend_array        *php_doc_comment_get_tags_by_name(php_doc_comment *comment, char *name);
zend_array        *php_doc_comment_get_tags_by_names(php_doc_comment *comment, const char *names[]);

// speed up php tests
int php_doc_comment_tests_suite(void);


#endif	/* PHP_DOC_COMMENT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
