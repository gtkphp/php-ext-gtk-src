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

#ifndef PHP_CAIRO_FT_H
#define PHP_CAIRO_FT_H


#if CAIRO_VERSION >= 10000
#define PHP_CAIRO_FT_FE_10000()

#else
#define PHP_CAIRO_FT_FE_10000()
#endif


#if CAIRO_VERSION >= 11200
#define PHP_CAIRO_FT_FE_11200()

#else
#define PHP_CAIRO_FT_FE_11200()
#endif


#define PHP_CAIRO_FT_FE() \
    PHP_CAIRO_FT_FE_10000() \
    PHP_CAIRO_FT_FE_11200() \


#define PHP_CAIRO_FT_MINIT_FUNCTION(container_ce, parent_ce)

#define PHP_CAIRO_FT_MSHUTDOWN_FUNCTION() { \
}

#define PHP_CAIRO_FT_RSHUTDOWN_FUNCTION() {\
}




#endif	/* PHP_CAIRO_FT_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
