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

#ifndef PHP_GTK_H
#define PHP_GTK_H

#include <php.h>
#include <php_ini.h>
#include <zend_interfaces.h>
#include <ext/standard/info.h>

extern zend_module_entry gtk_module_entry;
#define phpext_gtk_ptr &gtk_module_entry

#define PHP_GTK_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_GTK_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_GTK_API __attribute__ ((visibility("default")))
#else
#	define PHP_GTK_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif



#define GTK_NS_STRING(name) #name
#define GTK_NS_QUOTE(name) GTK_NS_STRING(name)

#define GTK_NS_EXPAND(VAL)  VAL ## 1
#define GTK_NS_IS_EMPTY(name)  GTK_NS_EXPAND(name)

#if defined(GTK_NS) && GTK_NS_IS_EMPTY(GTK_NS)!=1
#define PHP_GTK_INIT_CLASS_ENTRY(ce, name, methods) INIT_NS_CLASS_ENTRY(ce, GTK_NS_QUOTE(GTK_NS), name, methods)
#define PHP_GTK_FE(name, arg_info) ZEND_NS_FE(GTK_NS_QUOTE(GTK_NS), name, arg_info)
#else
#define PHP_GTK_FE(name, arg_info) ZEND_FE(name, arg_info)
#define PHP_GTK_INIT_CLASS_ENTRY(ce, name, methods) INIT_CLASS_ENTRY(ce, name, methods)
#endif

#define ZVAL_SET_LONG(z, lval) \
    if (IS_REFERENCE==Z_TYPE_P(z)) { \
        ZVAL_LONG(&(z)->value.ref->val, lval); \
    } else { \
        ZVAL_LONG((z), lval); \
    }

#define ZVAL_GET_LONG(src, dest) \
    if (IS_LONG==Z_TYPE_P(src)) {\
        dest = Z_LVAL_P(src);\
    } else if(IS_REFERENCE==Z_TYPE_P(src)) {\
        if(IS_LONG==Z_TYPE((src)->value.ref->val)) {\
            dest = Z_LVAL((src)->value.ref->val);\
        } \
    }

#define ZVAL_SET_DOUBLE(z, dval) \
    if (IS_REFERENCE==Z_TYPE_P(z)) { \
        ZVAL_DOUBLE(&(z)->value.ref->val, dval); \
    } else { \
        ZVAL_DOUBLE((z), dval); \
    }

#define ZVAL_GET_DOUBLE(src, dest) \
    if (IS_DOUBLE==Z_TYPE_P(src)) {\
        dest = Z_DVAL_P(src);\
    } else if(IS_REFERENCE==Z_TYPE_P(src)) {\
        if(IS_DOUBLE==Z_TYPE((src)->value.ref->val)) {\
            dest = Z_DVAL((src)->value.ref->val);\
        } \
    }

/*
ZEND_VERSION "3.2.0"
ZEND_ENGINE_3
*/


/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:

ZEND_BEGIN_MODULE_GLOBALS(gtk)
	zend_long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(gtk)
*/

/* Always refer to the globals in your function as GTK_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define GTK_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(gtk, v)

#if defined(ZTS) && defined(COMPILE_DL_GTK)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif	/* PHP_GTK_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

