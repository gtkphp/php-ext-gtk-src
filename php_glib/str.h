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

#ifndef PHP_G_STR_H
#define PHP_G_STR_H


#define PHP_G_STR_FE() \
    PHP_GTK_FE(g_str_hash,  arginfo_g_str_hash)   \
    PHP_GTK_FE(g_str_equal, arginfo_g_str_equal)

#define PHP_G_STR_MINIT_FUNCTION(container_ce, parent_ce)

#define PHP_G_STR_MSHUTDOWN_FUNCTION() { \
}

#define PHP_G_STR_RSHUTDOWN_FUNCTION() {\
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_g_str_hash, 0, 0, 0)
    ZEND_ARG_INFO(0, v)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_str_hash);
ZEND_BEGIN_ARG_INFO_EX(arginfo_g_str_equal, 0, 0, 0)
    ZEND_ARG_INFO(0, v1)
    ZEND_ARG_INFO(0, v2)
ZEND_END_ARG_INFO()
PHP_FUNCTION(g_str_equal);



#endif	/* PHP_G_STR_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
