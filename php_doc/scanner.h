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

#ifndef PHP_DOC_SCANNER_H
#define PHP_DOC_SCANNER_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


typedef struct _php_doc_scanner             php_doc_scanner;

struct _php_doc_scanner {
    char *cursor;
    char *token;
    char *next;
};

php_doc_comment  *php_doc_comment_parse(char *str, char **end);
php_doc_callable *php_doc_callable_parse(char *str, char **end);
void              php_doc_comment_free(zval *ptr);



#endif	/* PHP_DOC_SCANNER_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
