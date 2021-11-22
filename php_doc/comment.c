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

#include <string.h>

#include "parameter.h"
#include "tag.h"
#include "comment.h"
//#include "parser.h"
#include "scanner.h"

php_doc_comment*
php_doc_comment_new()
{
    php_doc_comment *intern = ecalloc(1, sizeof(php_doc_comment));
    zend_hash_init(&intern->tags, 1, NULL, php_doc_tag_free, 0);//php_doc_tag_free
    return intern;
}
zend_array*
php_doc_comment_get_tags_by_name(php_doc_comment *comment, char *name)
{
    zend_array *tags;// = emalloc(sizeof(zend_array));
    ALLOC_HASHTABLE(tags);
    zend_hash_init(tags, 1, NULL, NULL, 1);

    php_doc_tag *tag;
    ZEND_HASH_FOREACH_PTR(&comment->tags, tag) {
        if (0==strcmp(tag->name->val, name)) {
            zend_hash_next_index_insert_ptr(tags, tag);
        }
    } ZEND_HASH_FOREACH_END();

    return tags;
}
zend_array*
php_doc_comment_get_tags_by_names(php_doc_comment *comment, const char *names[])
{
    zend_array *tags;// = malloc(sizeof(zend_array));
    ALLOC_HASHTABLE(tags);
    zend_hash_init(tags, 1, NULL, NULL, 1);

    php_doc_tag *tag;
    ZEND_HASH_FOREACH_PTR(&comment->tags, tag) {
        for(int index=0; names[index]!=NULL; index++){
            if (0==strcmp(tag->name->val, names[index])) {
                zend_hash_next_index_insert_ptr(tags, tag);
            }
        }
    } ZEND_HASH_FOREACH_END();

    return tags;
}

php_doc_callable*
php_doc_callable_new() {
    php_doc_callable *cb = emalloc(sizeof(php_doc_callable));
    return cb;
}
void php_doc_callable_free(php_doc_callable *cb)
{
    if (cb->context) {
        zend_string_release(cb->context);
    }
    if (cb->name) {
        zend_string_release(cb->name);
    }
    efree(cb);
}

int php_doc_comment_tests_suite() {

#if 1


    const char *dataset[] = {
        /// 0...9
        "/***/",
        "/** */",
        "/** \n * */",
        "/** \n **/",
        "/** \n* */",
        "/** \n**/",
        "/** \n*/",
        "/**@poi*/",
        "/**@poi */",
        "/** @poi*/",
        /// 10...19
        "/** @poi */",
        "/** @My\\Ns\\Poi */",
        "/** @poi() */",
        "/** @poi(123) */",
        "/** @poi(1, 2, 3) */",
        "/** @My\\Ns\\Poi(1, 2) */",
        "/** @poi Ma description*/",
        "/** @poi(123) Ma description\n*/",
        "/** @poi(123) Ma description\n */",
        "/** @poi(123) Ma description\n * */",
        /// 20...29
        "/** @poi(123) Ma description\n*****/",
        "/** @poi(123) Ma description\n* *** */",
        "/** @poi(123) Ma description\n * multi line\n * extra.\n * @aze*/",
        "/** @poi(123) Ma description\n * multilines\n * \n * Hello World\n * @aze\n * @qer*/",
        "/** @poi({}) */",
        "/** @poi ( { } ) */",
        "/** @poi({a:1,b:{c:2}}) Description*/",
        "/** @poi(1, {a:2,b:{c:3}}) Description */",
        "/** @poi ( 1 , { a : 2 , b : { c : 3 } } ) Description */",
        "/** @poi(named: 1, 2, xav: 3) */",

        /// 30...39
        "/** {@example /} */",
        "/** {@example filename     } */",
        "/** {@example filename.txt} */",
        "/** {@example path/file.txt} */",
        "/** {@example #idname} */",
        "/** {@example http://127.0.0.1/path/file.txt} */",
        "/** {@example http://user:pws@www.example.com/path/file.txt?foo=bar#idname} */",
        "/** @poi(named: 'Hello world !\\n') */",
        "/** @poi( \"Hello world !\" ) */",
        "/** @poi( [1, 2, 3] ) */",

        /// 40...49
        "/** @poi( {a: [1, 2, .4]} ) */",
        "/** @poi( {a: []} ) */",
        "/** @poi( {a: [ ] } ) */",

        "/** \n * Hello \n * World !\n * @style Ma description */",

        NULL
    };
    const char *error[] = {
        "/** {@example } */",/// Error: Empty URI. {@example URI}

        "/** @poi(named: \" \\x0010 \\n \") */",
        "/**!re2c Rule: A | B; */",
        "/**!phpunit */",
        "/**!php-unit */",
        "/**!php-doc */",
        "/**TODO: varnish */",
        "/**TODO: zval/php_doc_node */",
        NULL
    };
    const char *dataset__[] = {
        ///"/** @poi(1, {a:2,b:{c:3}}) Description */",

        "/** @param(7) hello wordl*/",
        "/** @param(7, G_PARAM_CONSTRUCT) hello wordl*/",
        "/** @param(7, G_PARAM_CONSTRUCT | G_PARAM_READWRITE) */",

        ///"/** @g_override GObjectClass.set_property */",
        ///"/** @override GObject::set_property */",

        ///"/** @dataProvider provider */",
        ///"/** @dataProvider My::provider(1)*/",
        ///"/** @dataProvider [1, 'a']\n *                 [2, 'b'] [3, 'c'] */",
        NULL
    };
    // Phpdoc\Tag::registry("dataProvider", "Array");

    char **data = dataset__;
    //const char *str = "/** @poi({a:321}) Xy\n * \n * My desc\n * multi line\n * @aze\n */";
    for (int i=0; data[i]!=NULL; i++) {
        const char *str = data[i];

        char *end = NULL;
        php_doc_comment *doc_comment;
        if (doc_comment = php_doc_comment_parse(str, &end)) {
            //php_printf("description = %s\n", doc_comment->description->val);
            php_doc_tag *tag;
            ZEND_HASH_FOREACH_PTR(&doc_comment->tags, tag) {
                //php_printf("@%s %s\n", tag->name->val, tag->description->val);
                if (0==strcmp(tag->name->val, "g_override")) {
                    //php_printf("@%s %s\n", tag->name->val, tag->description->val);
                    //php_printf("%s\n", tag->description->val);
                }
            } ZEND_HASH_FOREACH_END();
            //printf("OK = %p, ", doc_comment);

            zval ptr; ZVAL_PTR(&ptr, doc_comment);
            php_doc_comment_free(&ptr);
        } else {
            php_printf("Error %d\n", i);
        }
    }
    //printf("\n");



#endif

    return SUCCESS;// FAILURE
}
