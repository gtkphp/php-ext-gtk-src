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

void
php_doc_parameter_free(zval *val)
{
    php_doc_parameter *parameter = Z_PTR_P(val);
    ///printf("    parameter : %p\n", parameter);

    if (parameter->name) {
        zend_string_release(parameter->name);
    }
    if (parameter->type) {
        zend_string_release(parameter->type);
    }

    if (Z_TYPE(parameter->value)==IS_STRING) {
        // FIXME: How to use Z_TRY_DELREF ?
        zend_string_release(Z_STR(parameter->value));
    }

    free(parameter);
}

