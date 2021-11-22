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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "parameter.h"
#include "value.h"
#include "tag.h"
#include "comment.h"



#include "scanner.h"


typedef struct _php_doc_comment_t             php_doc_comment_t;
typedef struct _php_doc_content_t             php_doc_content_t;
typedef struct _php_doc_section_t             php_doc_section_t;
typedef struct _php_doc_description_t         php_doc_description_t;
typedef struct _php_doc_tag_t                 php_doc_tag_t;
typedef struct _php_doc_param_t               php_doc_param_t;
typedef enum     _php_doc_types                 php_doc_types;
typedef struct   _php_doc_type_t                php_doc_type_t;
typedef enum     _php_doc_values                php_doc_values;
typedef struct     _php_doc_value_t               php_doc_value_t;
typedef struct       _php_doc_filepath_t            php_doc_filepath_t;
typedef struct       _php_doc_object_t              php_doc_object_t;
typedef struct       _php_doc_dquoted_t             php_doc_dquoted_t;
typedef struct       _php_doc_squoted_t             php_doc_squoted_t;
typedef struct       _php_doc_callable_t            php_doc_callable_t;
typedef struct       _php_doc_array_t               php_doc_array_t;

// php_doc_pi_t | php_doc_tag_inline_t

enum _php_doc_values {
    PHP_DOC_VALUE_TYPE,
    PHP_DOC_VALUE_PARAM,
    PHP_DOC_VALUE_FILEPATH,
    // { ..., EMAIL, VERSION, COPYRIGHT, DATE}
};
struct _php_doc_value_t {
    php_doc_values type;
};
enum _php_doc_types {
    PHP_DOC_TYPE_UNKNOWN,

    PHP_DOC_TYPE_INT,
    PHP_DOC_TYPE_FLOAT,
    PHP_DOC_TYPE_STRING,
    PHP_DOC_TYPE_OBJECT,
    PHP_DOC_TYPE_ARRAY,

    PHP_DOC_TYPE_ID,
    PHP_DOC_TYPE_ITERABLE,
    PHP_DOC_TYPE_CALLABLE,
    PHP_DOC_TYPE_CLASS,
    PHP_DOC_TYPE_METHOD,
    PHP_DOC_TYPE_FUNCTION,//
    //PHP_DOC_TYPE_STATIC,
    //PHP_DOC_TYPE_CONST,
};
struct _php_doc_type_t {
    php_doc_value_t parent_instance;// remove this line ? Who use self struct
    php_doc_types type;
    char *string;// refactor by rename to "name"
};
struct _php_doc_param_t {
    php_doc_value_t parent_instance;
    php_doc_types type;//todo: refactor, use struct php_doc_type_t
    char *type_name;   //
    char  *named;
    size_t named_len;
    union {
        long tol;
        double tod;
        php_doc_object_t *too;
        php_doc_array_t *toa;
        php_doc_callable_t *toc;
        char *tos;
    } value;//zval
};
typedef struct _php_doc_list_t {
    //php_doc_section_t **data;// null-terminated
    //php_doc_param_t **data;// null-terminated
    void **data;// null-terminated
    int last;
    int length;
} php_doc_list_t;

struct _php_doc_filepath_t {
    php_doc_param_t parent_instance;
};
struct _php_doc_object_t {
    php_doc_value_t parent_instance;
};

struct _php_doc_callable_t {
    php_doc_param_t parent_instance;
    char *context_name;
    int   context_name_len;

    char *function_name;
    int   function_name_len;
};


//struct  email etc...
typedef enum _php_doc_sections {
    PHP_DOC_SECTION_NEWLINE,
    PHP_DOC_SECTION_TAG,
    PHP_DOC_SECTION_DESCRIPTION,
} php_doc_sections;
struct _php_doc_section_t {
    php_doc_sections type;
    size_t expect_len;// memory size allocation
    size_t len;// number of section
};
struct _php_doc_description_t {
    php_doc_section_t parent_instance;
    char *text;
    size_t text_len;
};
struct _php_doc_tag_t {
    php_doc_description_t parent_instance;
    php_doc_list_t *arguments;// of php_doc_data
    char *name;
    size_t name_len;
};
struct _php_doc_content_t {
    php_doc_list_t *sections;// null-terimnate
};
struct _php_doc_comment_t {
    int sha_bang;
    char *summary;
    char *description;
    php_doc_tag_t **tags;// null-terimnate
};

static php_doc_param_t  *php_doc_value_parse(char *str, char **end);
static php_doc_param_t  *php_doc_expression_parse(char *expression, char **end);

static php_doc_value_t*
php_doc_type_new(){
    php_doc_type_t *value = malloc(sizeof(php_doc_type_t));
    value->parent_instance.type = PHP_DOC_VALUE_TYPE;
    return (php_doc_value*)value;
}

static void
php_doc_type_free(php_doc_type_t *value){
    free(value);
}

static php_doc_value_t*
php_doc_data_new(){
    php_doc_param_t *value = malloc(sizeof(php_doc_param_t));
    value->parent_instance.type = PHP_DOC_VALUE_PARAM;
    value->named = 0;
    value->type_name = 0;
    return (php_doc_value_t*)value;
}

static void
php_doc_data_free(php_doc_type_t *value){
    free(value);
}

static php_doc_list_t*
php_doc_list_append(php_doc_list_t *arguments, void *argument) {
    if (0==arguments) {
        arguments = malloc(sizeof(php_doc_list_t));
        arguments->length = 10;
        arguments->data = malloc(sizeof(void*)*10);// of php_doc_param
        arguments->last=0;
    }
    if ((arguments->last+3)>arguments->length) {// null-terminated
        void **data = arguments->data;/// php_doc_param_t
        int length = arguments->length;
        arguments->length += 10;
        arguments->data = malloc(sizeof(void*)*arguments->length);
        memcpy(arguments->data, data, sizeof(void*)*length);
        free(data);
    }
    arguments->data[arguments->last] = argument;
    arguments->last++;
    arguments->data[arguments->last] = 0;

    return arguments;
}

static void php_doc_tag_t_free(php_doc_tag_t *tag);
static void php_doc_description_t_free(php_doc_description_t *description);

static void
php_doc_section_t_free(php_doc_section_t *section){

    switch(section->type) {
    case PHP_DOC_SECTION_TAG:
        php_doc_tag_t_free(section);
        break;
    case PHP_DOC_SECTION_NEWLINE:
        free(section);
        break;
    case PHP_DOC_SECTION_DESCRIPTION:
        php_doc_description_t_free(section);
        break;
    }
}

typedef void php_doc_section_destroy(php_doc_section_t *section);
php_doc_list_t_free(php_doc_list_t *sections, php_doc_section_destroy *destroy){
    for(int i=0; i<sections->last; i++) {
        destroy(sections->data[i]);
    }
    free(sections->data);
    free(sections);
}

/*abstract static php_doc_section*
php_doc_section_new(int type){
    php_doc_section *section = malloc(sizeof(php_doc_section));
    section->type = type;
    return section;
}*/



static void
php_doc_section_t_init(php_doc_section_t *section, php_doc_sections type){
    section->type = type;
    section->expect_len = 1;
    section->len = 1;
}
static void
php_doc_description_t_init(php_doc_description_t *description){
    description->text = 0;
    description->text_len = 0;
    description->parent_instance.expect_len = 0;
}
static php_doc_section_t*
php_doc_description_t_new(){
    php_doc_description_t *description = malloc(sizeof(php_doc_description_t));
    php_doc_section_t_init(description, PHP_DOC_SECTION_DESCRIPTION);
    php_doc_description_t_init(description);

    return (php_doc_section_t*)description;
}
static void
php_doc_description_t_free(php_doc_description_t *description){
    free(description);
}
static void
php_doc_description_t_set_text(php_doc_description_t *description, char *text, size_t len){
    //char *str = strndup(text, len+1 );
    //str[len] = '\0';
    //description->text = str;
    description->text = text;
    description->text_len = len;
}


static char *php_doc_newline = "\n";
static php_doc_section_t*
php_doc_newline_t_new() {
    php_doc_description_t *newline = malloc(sizeof(php_doc_description_t));
    php_doc_section_t_init(newline, PHP_DOC_SECTION_NEWLINE);
    php_doc_description_t_init(newline);
    newline->text = php_doc_newline;
    newline->text_len = 1;
    return (php_doc_section_t*)newline;
}

static void
php_doc_newline_t_free(php_doc_section_t *value){
    free(value);
}

static php_doc_section_t*
php_doc_tag_t_new(){
    php_doc_tag_t *tag = malloc(sizeof(php_doc_tag_t));
    php_doc_section_t_init(tag, PHP_DOC_SECTION_TAG);
    php_doc_description_t_init(tag);

    return (php_doc_section_t*)tag;
}

static void php_doc_callable_t_free(php_doc_callable_t *cb) {
    free(cb);
}

static void php_doc_param_t_free(php_doc_param_t *param) {
    //printf("php_doc_param_t_free: %p\n", param);
    switch(param->type) {
    case PHP_DOC_TYPE_ID:
    case PHP_DOC_TYPE_STRING:
        if (param->value.tos) {
            free(param->value.tos);
        }
        break;
    case PHP_DOC_TYPE_CALLABLE:
        if (param->value.toc) {
            php_doc_callable_t_free(param->value.toc);
        }
        break;
    default:
        break;
    }
    free(param);
}

static void
php_doc_tag_t_free(php_doc_tag_t *tag){
    if(tag->arguments)
        php_doc_list_t_free(tag->arguments, php_doc_param_t_free);
    free(tag);
}
static void
php_doc_tag_t_set_name(php_doc_tag_t *tag, char *name, size_t len) {
    // if (tag->name) free
    // if (len==0) strlen(name);
    //char *str = strndup(name, len );
    //str[len] = '\0';

    tag->name = name;
    tag->name_len = len;
    //printf("PHP_DOC_NAME='%s'\n", str);
}
static void
php_doc_tag_t_set_description(php_doc_tag_t *tag, char *text, size_t len) {
    //char *str = strndup(text, len );
    //str[len] = '\0';

    tag->parent_instance.text = text;
    tag->parent_instance.text_len = len;
}
static void
php_doc_tag_t_set_arguments(php_doc_tag_t *tag, php_doc_list_t *arguments) {
    tag->arguments = arguments;
}
/*
static void
php_doc_tag_append_description(php_doc_tag *tag, php_doc_section *description){
    switch(description->type) {
        case PHP_DOC_SECTION_NEWLINE:
            size_t len = strlen(tag->parent_instance.text);
            break;
        case PHP_DOC_SECTION_DESCRIPTION:
            size_t len = strlen(tag->parent_instance.text);
            size_t len_new = strlen(((php_doc_description*)description)->text);
            break;
        default:
            break;
    }
}
*/

static php_doc_comment_t*
php_doc_comment_t_new(){
    php_doc_comment_t *doc_comment = malloc(sizeof(php_doc_comment_t));
    return doc_comment;
}

static void
php_doc_comment_t_free(php_doc_comment_t *doc_comment){
    free(doc_comment);
}

static void
php_doc_comment_t_set_sha_bang(php_doc_comment_t *doc_comment, char *sha_bang, size_t sha_bang_len){
}
static void
php_doc_comment_t_set_summary(php_doc_comment_t *doc_comment, php_doc_description_t *summary){
}
static void
php_doc_comment_t_append_description(php_doc_comment_t *doc_comment, char *description){
}
static void
php_doc_comment_t_append_tag(php_doc_comment_t *doc_comment, php_doc_tag_t *tag){
}


#define PHP_DOC_IS_END()       (s.cursor[0]=='*' && s.cursor[1]=='/')
#define PHP_DOC_IS_DECORATOR() (s.cursor[0]=='*')
#define PHP_DOC_IS_NL()        (s.cursor[0]=='\n')
#define PHP_DOC_IS_WS()        (s.cursor[0]==' ' || s.cursor[0]=='\t')
#define PHP_DOC_IS_AT()        (s.cursor[0]=='@')
static int            php_doc_name_parse(char *str, char **end);
static int            php_doc_text_parse(char *str, char **end);
static php_doc_value_t *php_doc_type_parse(char *str, char **end);
static php_doc_param_t  *php_doc_data_parse(char *str, char **end);

#define PHP_DOC_IS_COMMA()     (s.cursor[0]==',')
#define PHP_DOC_IS_COLON()     (s.cursor[0]==':')
#define PHP_DOC_IS_LPARENTH()  (s.cursor[0]=='(')
#define PHP_DOC_IS_RPARENTH()  (s.cursor[0]==')')
#define PHP_DOC_IS_LCURLY()    (s.cursor[0]=='{')
#define PHP_DOC_IS_RCURLY()    (s.cursor[0]=='}')
#define PHP_DOC_IS_ALPHA()     ( ('a'<=s.cursor[0] && s.cursor[0]<='z') || ('A'<=s.cursor[0] && s.cursor[0]<='Z') )
#define PHP_DOC_IS_DIGITAL()   ( '0'<=s.cursor[0] && s.cursor[0]<='9' )

//PHP_DOC_IS_PRIVATE
//PHP_DOC_IS_PROTECTED
//PHP_DOC_IS_PUBLIC

//PHP_DOC_IS_ABSTRACT
//PHP_DOC_IS_FINAL
//PHP_DOC_IS_INTERFACE
//PHP_DOC_IS_FUNCTION
//PHP_DOC_IS_::$
//PHP_DOC_IS_::

#define PHP_DOC_T_BEGIN(code) \
    if (s.cursor[0]=='/' && s.cursor[1]=='*' && s.cursor[2]=='*') { \
        s.cursor+=3; \
        code \
    }
#define PHP_DOC_T_END(code) \
    if (PHP_DOC_IS_END()) { \
        s.cursor+=2; \
        code \
    }
#define PHP_DOC_T_WS(code) \
    if (PHP_DOC_IS_WS()) { \
        s.cursor++; \
        code \
    }
#define PHP_DOC_T_AT(code) \
    if (PHP_DOC_IS_AT()) { \
        s.cursor++; \
        code \
    }
#define PHP_DOC_T_LPARENTH(code) \
    if (PHP_DOC_IS_LPARENTH()) { \
        s.cursor++; \
        code \
    }
#define PHP_DOC_T_RPARENTH(code) \
    if (PHP_DOC_IS_RPARENTH()) { \
        s.cursor++; \
        code \
    }
#define PHP_DOC_T_LCURLY(code) \
    if (PHP_DOC_IS_LCURLY()) { \
        s.cursor++; \
        code \
    }
#define PHP_DOC_T_RCURLY(code) \
    if (PHP_DOC_IS_RCURLY()) { \
        s.cursor++; \
        code \
    }
#define PHP_DOC_T_LBRACE(code) \
    if (s.cursor[0]=='[') { \
        s.cursor++; \
        code \
    }
#define PHP_DOC_T_RBRACE(code) \
    if (s.cursor[0]==']') { \
        s.cursor++; \
        code \
    }
#define PHP_DOC_T_BACKSLASH(code) \
    if (s.cursor[0]=='\\') { \
        s.cursor++; \
        code \
    }


/** {{{ */

#define PHP_DOC_T_COLON(code) \
    if(PHP_DOC_IS_COLON()){ \
       ++s.cursor; \
       code \
    }

#define PHP_DOC_T_COMMA(code) \
    if(PHP_DOC_IS_COMMA()){ \
       ++s.cursor; \
       code \
    }

#define PHP_DOC_T_INT(code) \
    if( (s.cursor[0]=='i'||s.cursor[0]=='I') \
      &&(s.cursor[1]=='n'||s.cursor[1]=='N') \
      &&(s.cursor[2]=='t'||s.cursor[2]=='T') \
    ){ \
       s.cursor+=3; \
       code \
    }
#define PHP_DOC_T_FLOAT(code) \
    if( (s.cursor[0]=='f'||s.cursor[0]=='F') \
      &&(s.cursor[1]=='l'||s.cursor[1]=='L') \
      &&(s.cursor[2]=='o'||s.cursor[2]=='O') \
      &&(s.cursor[3]=='a'||s.cursor[3]=='A') \
      &&(s.cursor[4]=='t'||s.cursor[4]=='T') \
    ){ \
       s.cursor+=5; \
       code \
    }
#define PHP_DOC_T_STRING(code) \
    if( (s.cursor[0]=='s'||s.cursor[0]=='S') \
      &&(s.cursor[1]=='t'||s.cursor[1]=='T') \
      &&(s.cursor[2]=='r'||s.cursor[2]=='R') \
      &&(s.cursor[3]=='i'||s.cursor[3]=='I') \
      &&(s.cursor[4]=='n'||s.cursor[4]=='N') \
      &&(s.cursor[5]=='g'||s.cursor[5]=='G') \
    ){ \
       s.cursor+=6; \
       code \
    }
#define PHP_DOC_T_ARRAY(code) \
    if( (s.cursor[0]=='a'||s.cursor[0]=='A') \
      &&(s.cursor[1]=='r'||s.cursor[1]=='R') \
      &&(s.cursor[2]=='r'||s.cursor[2]=='R') \
      &&(s.cursor[3]=='a'||s.cursor[3]=='A') \
      &&(s.cursor[4]=='y'||s.cursor[5]=='Y') \
    ){ \
       s.cursor+=5; \
       code \
    }
/** }}} */


#define PHP_DOC_NAME(code) \
    s.token = s.cursor; \
    if (php_doc_name_parse(s.cursor, &s.next)) { \
        s.cursor = s.next; \
        code \
    }
#define PHP_DOC_TYPE(code) \
    s.token = s.cursor; \
    if (type=php_doc_type_parse(s.cursor, &s.next)) { \
        s.cursor = s.next; \
        code \
    }
#define PHP_DOC_DATA(code) \
    PHP_DOC_BREAK() \
    s.token = s.cursor; \
    if (data=php_doc_expression_parse(s.cursor, &s.next)) { \
        s.cursor = s.next; \
        code \
    }

#define PHP_DOC_TEXT(code) \
    s.token = s.cursor; \
    if (php_doc_text_parse(s.cursor, &s.next)) { \
        s.cursor = s.next; \
        code \
    }

#define PHP_DOC_OR(code) \
    if( *s.cursor=='|'){s.cursor++; code}

#define PHP_DOC_WSKIP(code) \
    PHP_DOC_T_WS( while(PHP_DOC_IS_WS()){s.cursor++;}; code)

#define PHP_DOC_EOL(code) \
    if(php_doc_newline_parse(s.cursor, &s.next)) { \
       s.cursor = s.next; \
        code \
    }
#define PHP_DOC_BREAK() \
    PHP_DOC_WSKIP(PHP_DOC_EOL(PHP_DOC_WSKIP()))else PHP_DOC_EOL(PHP_DOC_WSKIP())


static int
php_doc_newline_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};

    if (PHP_DOC_IS_NL()) {
        s.next = ++s.cursor;
        PHP_DOC_WSKIP()
        //FIXME
        if (PHP_DOC_IS_DECORATOR()) {
            if (s.cursor[1]!='/' && s.cursor[1]!=0) {
                s.cursor++;
            }
        } else {
            s.cursor=s.next;
        }
        if (end!=0)
            *end = s.cursor;
        return 1;
    }

    return 0;
}


static int
php_doc_name_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};

    if (PHP_DOC_IS_ALPHA() || PHP_DOC_IS_DIGITAL()) {
        s.cursor++;
    } else {
        return 0;// FALSE
    }

    while(PHP_DOC_IS_ALPHA() || PHP_DOC_IS_DIGITAL() || '_'==s.cursor[0]) {
        s.cursor++;
    }

    if (s.cursor-str>0) {
        *end = s.cursor;
        return s.cursor-str;
    }
    return 0;
}

static int
php_doc_text_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};

    while(!( PHP_DOC_IS_END() || php_doc_newline_parse(s.cursor, 0) )) {
        //printf("text: %c\n", s.cursor[0]);
        s.cursor++;
    }

    if (end!=0)
        *end = s.cursor;
    int ret = (s.cursor-str) > 0;
    return ret;// MAX(0, ptr-str)
}

static php_doc_value_t*
php_doc_type_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};

    php_doc_value_t *value = 0;

    do {
        PHP_DOC_T_INT(
            value=php_doc_type_new();
            ((php_doc_type_t*)value)->type = PHP_DOC_TYPE_INT;
            break;
        )
        PHP_DOC_T_FLOAT(
            value=php_doc_type_new();
            ((php_doc_type_t*)value)->type = PHP_DOC_TYPE_FLOAT;
            break;
        )
        PHP_DOC_T_STRING(
            value=php_doc_type_new();
            ((php_doc_type_t*)value)->type = PHP_DOC_TYPE_STRING;
            break;
        )
        PHP_DOC_T_ARRAY(
            value=php_doc_type_new();
            ((php_doc_type_t*)value)->type = PHP_DOC_TYPE_ARRAY;
            break;
        )
        // PHP_DOC_TYPE_CALLABLE

        //PHP_DOC_T_OBJECT(ptr, *end=ptr; return PHP_DOC_TYPE_OBJECT;)
        //PHP_DOC_T_FILEPATH(ptr, *end=ptr; return PHP_DOC_TYPE_FILEPATH;)
    }while(0);

    if (value && *end!=0) {
        *end=s.cursor;
    }
    return value;
}

static php_doc_object_t*
php_doc_object_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};

    php_doc_object_t *obj = 0;
    php_doc_param_t *data = 0;
    php_doc_param_t *root = 0;

    do {

        PHP_DOC_WSKIP()
        if (PHP_DOC_IS_LCURLY()) {
            ++s.cursor;

            PHP_DOC_DATA(
                do {
                    s.token = s.cursor;
                    PHP_DOC_WSKIP()
                    PHP_DOC_T_COMMA(
                        //printf("COMMA\n");
                        PHP_DOC_WSKIP()
                        PHP_DOC_DATA( 0; ) else {
                            s.cursor = s.token;
                            break;
                        }
                    ) else {
                        s.cursor = s.token;
                        break;
                    }
                }while(data);
            ) /** {{{else OPTIONAL }}} */

            PHP_DOC_WSKIP()
            if (PHP_DOC_IS_RCURLY()) {
                ++s.cursor;
                //printf("object{}\n");

                obj=1;
                break;// ACCEPT
            } else {/** {{{ ERROR }}} */}
        }
        // REJET
        //PHP_DOC_T_FILEPATH(ptr, *end=ptr; return PHP_DOC_TYPE_FILEPATH;)
    }while(0);

    if(obj && end!=0) {
        *end = s.cursor;
    }
    return obj;
}

static php_doc_array_t*
php_doc_array_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};

    php_doc_array_t *arr = 0;
    php_doc_param_t *data = 0;
    php_doc_param_t *root = 0;

    do {

        PHP_DOC_WSKIP()
        PHP_DOC_T_LBRACE(
            PHP_DOC_DATA(
                do {
                    s.token = s.cursor;
                    PHP_DOC_WSKIP()
                    PHP_DOC_T_COMMA(
                        //printf("COMMA\n");
                        PHP_DOC_WSKIP()
                        PHP_DOC_DATA(
                            0; //printf("DATA\n");
                        ) else {
                            s.cursor = s.token;
                            break;
                        }
                    ) else {
                        s.cursor = s.token;
                        break;
                    }
                }while(data);
            ) /** {{{else OPTIONAL }}} */

            PHP_DOC_WSKIP()
            PHP_DOC_T_RBRACE(
                //printf("array[]\n");
                arr=1;
            ) else {/** {{{ REJECT/ERROR }}} */}
        )
    }while(0);

    if(arr && end!=0) {
        *end = s.cursor;
    }
    return arr;
}

static char*
php_doc_string_simple_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};

    char *string = 0;

    PHP_DOC_WSKIP()
    s.token = s.cursor;
    if(s.cursor[0]=='\''){
        do {
            ++s.cursor;
        }while(*s.cursor && *s.cursor!='\'');
        if(s.cursor[0]=='\''){
            /// printf("string: %.*s\n", s.cursor-string, string);
            string = malloc(s.cursor-s.token+1);
            memcpy(string, s.token, s.cursor-s.token);
            string[s.cursor-s.token]=0;
            ++s.cursor;
        }
    }

    if(string && end!=0) {
        *end = s.cursor;
    }
    return string;
}


static char*
php_doc_string_double_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};

    char *string = 0;

    PHP_DOC_WSKIP()
    if(s.cursor[0]=='"'){
        s.token = ++s.cursor;
        while(*s.cursor && *s.cursor!='"') {
            ++s.cursor;
        };
        if(s.cursor[0]=='"'){
            //string = s.token;
            /// printf("string:: %.*s\n", s.cursor-string, string);
            string = malloc(s.cursor-s.token+1);
            memcpy(string, s.token, s.cursor-s.token);
            string[s.cursor-s.token]=0;
            ++s.cursor;
        }
    }

    if(string && end!=0) {
        *end = s.cursor;
    }
    return string;
}

static char*
php_doc_string_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};

    char *string = 0;

    PHP_DOC_WSKIP()

    s.token = s.cursor;
    if (string = php_doc_string_simple_parse(s.cursor, &s.next)) {
        s.cursor = s.next;
    } else if (string = php_doc_string_double_parse(s.cursor, &s.next)) {
        s.cursor = s.next;
    }

    if(string && end!=0) {
        *end = s.cursor;
    }
    return string;
}

static php_doc_callable_t*
php_doc_callable_t_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};

    php_doc_callable_t *cb = 0;
    int   is_global = 0;
    char *is_package = 0;
    char *name = 0;
    char *name_end = 0;
    char *function = 0;
    char *function_end = 0;

    PHP_DOC_WSKIP()
    name = s.cursor;
    PHP_DOC_T_BACKSLASH( is_global=1;)
    do {
        PHP_DOC_NAME(
            do {
                PHP_DOC_T_BACKSLASH(
                    PHP_DOC_NAME(
                        is_package = 1;
                        continue;
                    )
                )
                is_package = 0;
            }while(is_package);
            name_end = s.cursor;
            PHP_DOC_T_COLON(PHP_DOC_T_COLON(
                function = s.cursor;
                PHP_DOC_NAME(
                    function_end = s.cursor;
                    cb=malloc(sizeof(php_doc_callable_t));
                    ((php_doc_value_t*)cb)->type = PHP_DOC_VALUE_PARAM;
                    ((php_doc_param_t*)cb)->type = PHP_DOC_TYPE_CALLABLE;
                    ((php_doc_callable_t*)cb)->context_name = name;
                    ((php_doc_callable_t*)cb)->context_name_len = name_end-name;
                    ((php_doc_callable_t*)cb)->function_name = function;
                    ((php_doc_callable_t*)cb)->function_name_len = function_end-function;
                    break;
                )
            ))else {
                /*
                cb=malloc(sizeof(php_doc_callable_t));
                ((php_doc_value_t*)cb)->type = PHP_DOC_VALUE_PARAM;
                ((php_doc_param_t*)cb)->type = PHP_DOC_TYPE_CALLABLE;
                ((php_doc_callable_t*)cb)->context_name = 0;
                ((php_doc_callable_t*)cb)->context_name_len = 0;
                ((php_doc_callable_t*)cb)->function_name = name;
                ((php_doc_callable_t*)cb)->function_name_len = name_end-name;
                */
                break;
            }
        )
    } while(0);

    if(cb && end!=0) {
        *end = s.cursor;
    }
    return cb;
}

static char*
php_doc_id_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};

    char *id = 0;
    int   is_global = 0;
    char *package = 0;
    char *identifier = 0;

    PHP_DOC_WSKIP()
    identifier=s.cursor;
    PHP_DOC_T_BACKSLASH( is_global=1;)
    PHP_DOC_NAME(
        do {
            PHP_DOC_T_BACKSLASH(
                PHP_DOC_NAME(
                    package = 1;
                    continue;
                )
            )
            package = 0;
        }while(package);
        id=malloc(s.cursor-identifier+1);
        memcpy(id, identifier, s.cursor-identifier);
        id[s.cursor-identifier] = 0;
    )

    if(id && end!=0) {
        *end = s.cursor;
    }
    return id;
}


// TODO: rename by php_doc_parameter_parse
static php_doc_param_t *php_doc_data_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};

    php_doc_param_t *data = 0;
    char *name = 0;
    size_t name_len = 0;

    do {

        PHP_DOC_WSKIP()
        name = s.cursor;
        PHP_DOC_NAME(
            //name = s.token;
            PHP_DOC_WSKIP()
            PHP_DOC_T_COLON(
                PHP_DOC_T_COLON(
                    s.cursor = name;
                    name=0;
                ) else {
                    name_len = s.cursor-name-1;
                    //printf("name: '%.*s'\n", s.cursor-name-1, name);
                }
            ) else {
                s.cursor = name;
                name=0;
            }
        )

        PHP_DOC_BREAK()
        data = php_doc_value_parse(s.cursor, end);
        if (data) {
            s.cursor = *end;
        }

    }while(0);

    if (data && end!=0) {
        *end = s.cursor;
    }
    if (data && name_len) {
        data->named = name;
        data->named_len = name_len;
    }
    return data;
}

static long
php_doc_expression_contant_long(char *name)
{
    // if name is a constant of php, get it, else error
    // TODO zend_register_long_constant with value of G_TYPE_INT

    zend_constant *c = zend_get_constant_str(name, strlen(name));
    if (c && Z_TYPE(c->value)==IS_LONG) {
        return Z_LVAL(c->value);
    } else {
        // Unexpected value type of const
    }

    return 0;
}

static int
php_doc_expression_eval(char *expression)
{
    char *name = expression;
    int ret;
    ret = php_doc_expression_contant_long(name);
    return ret;
}

static php_doc_param_t *php_doc_expression_parse(char *expression, char **end)
{
    //char *exception=NULL;
    php_doc_scanner s={expression, 0, 0};
    php_doc_param_t *data;
    php_doc_param_t *tmp;
    int val = 0;

    PHP_DOC_BREAK()
    s.token = s.cursor;
    if (data=php_doc_data_parse(s.cursor, &s.next)) {
        s.cursor = s.next;
        if (data && data->type == PHP_DOC_TYPE_ID) {// bug if not a const( ex: user_function)
            tmp = (php_doc_param_t*)php_doc_data_new();
            tmp->type = PHP_DOC_TYPE_INT;
            tmp->value.tol = php_doc_expression_eval(data->value.tos);
            //php_printf("%s = %d\n", data->value.tos, tmp->value.tol);
            php_doc_param_t_free(data);
            data = tmp;
            // pause
            *end = s.cursor;
            /**/
            PHP_DOC_WSKIP( )
            PHP_DOC_OR(
                PHP_DOC_WSKIP( )
                s.token = s.cursor;
                if (tmp=php_doc_data_parse(s.cursor, &s.next)) {
                    s.cursor = s.next;
                    if (tmp && tmp->type == PHP_DOC_TYPE_ID) {
                        data->value.tol |= php_doc_expression_eval(tmp->value.tos);
                    } else if (tmp && tmp->type == PHP_DOC_TYPE_INT) {

                    }

                    php_doc_param_t_free(tmp);
                    *end = s.cursor;
                } else {
                    php_printf("Error: Expecting data\n");
                }
            )
            /**/
        } else {
            *end = s.cursor;
        }
    }

    return data;
}

//php_doc_value_t*
static php_doc_param_t*
php_doc_value_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};
    php_doc_param_t *data=NULL;

    do {
        long lval = strtol(s.cursor, &s.next, 10 );// TODO check for octal, ...
        if(s.next>s.cursor) {
            s.cursor=s.next;
            data = php_doc_data_new();//PHP_DOC_VALUE_DATA
            data->type = PHP_DOC_TYPE_INT;
            data->value.tol = lval;
            if (s.cursor[0]=='.') {
                double dval = strtod(s.cursor, &s.next);
                if(s.next>s.cursor) {
                    s.cursor=s.next;
                    data->type = PHP_DOC_TYPE_FLOAT;
                    data->value.tod = dval+lval;
                    //printf("float: %f(%.*s)\n", dval, s.cursor-str, str);
                    break;
                }
            } else {
                //printf("int: %d\n", lval);
                break;
            }
        }

        double dval = strtod(s.cursor, &s.next);
        if(s.next>s.cursor) {
            s.cursor=s.next;
            data = php_doc_data_new();
            data->type = PHP_DOC_TYPE_FLOAT;
            data->value.tod = dval;
            //printf("float: %f(%.*s)\n", dval+lval, s.cursor-str, str);
            break;
        }

        php_doc_object_t *oval;
        if (oval = php_doc_object_parse(s.cursor, &s.next)) {
            s.cursor = s.next;
            data = php_doc_data_new();
            data->type = PHP_DOC_TYPE_OBJECT;// or _TYPE_CLASS if has name
            data->value.too = oval;
            break;
        }

        php_doc_array_t *aval;
        if (aval = php_doc_array_parse(s.cursor, &s.next)) {
            s.cursor = s.next;
            data = php_doc_data_new();
            data->type = PHP_DOC_TYPE_ARRAY;// or _TYPE_ITERATOR if has name
            data->value.toa = aval;
            break;
        }

        php_doc_callable_t *cval;
        if (cval = php_doc_callable_t_parse(s.cursor, &s.next)) {
            //printf("callable: %.*s\n", s.next-s.cursor, s.cursor);
            s.cursor = s.next;
            data = php_doc_data_new();
            data->type = PHP_DOC_TYPE_CALLABLE;
            data->value.toc = cval;
            break;
        }

        char *ival;
        if (ival = php_doc_id_parse(s.cursor, &s.next)) {
            /// printf("identifier: %.*s\n", s.next-s.cursor, s.cursor);
            s.cursor = s.next;
            data = php_doc_data_new();
            data->type = PHP_DOC_TYPE_ID;
            data->value.tos = ival;
            //printf("php_doc_param_t_new: %p\n", data);
            break;
        }

        char *sval;
        if (sval = php_doc_string_parse(s.cursor, &s.next)) {
            /// printf("identifier: %.*s\n", s.next-s.cursor, s.cursor);
            s.cursor = s.next;
            data = php_doc_data_new();
            data->type = PHP_DOC_TYPE_STRING;
            data->value.tos = sval;
            //printf("php_doc_param_t_new: %p\n", data);
            break;
        }

        /*
        char *string = php_doc_string_parse(ptr, &token);// quote: simple, double, thick
        if(token>ptr) {
            ptr=token;
            break;
        }
        */

        //PHP_DOC_T_FILEPATH(ptr, *end=ptr; return PHP_DOC_TYPE_FILEPATH;)

    } while(0);

    if (data) {
        *end = s.cursor;
    }

    return data;
}

php_doc_section_t*
php_doc_section_t_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};


    php_doc_section_t *section = 0;

    /* @name [arguments] [argument] description */
    char *name = 0;
    char *name_end = 0;
    char *description=0;
    char *description_end=0;
    php_doc_list_t *arguments=0;// null-termined

    int type = 0;
    php_doc_value_t *value=0;//       int
    php_doc_param_t *data=0;
    php_doc_param_t *root=0;
    //size_t len = 0;
    // How to code alternative ?

tag_simple:
    s.token = s.cursor;
    do{
        PHP_DOC_WSKIP()
        PHP_DOC_T_AT(
            name = s.cursor;
            PHP_DOC_NAME(
                name_end = s.cursor;
                do {
                    char *reset = s.cursor;

                    PHP_DOC_WSKIP()
                    PHP_DOC_T_LPARENTH(
                        //php_printf("PHP_DOC_LARENTH %c\n", s.cursor[0]);
                        PHP_DOC_DATA(
                            //php_printf("... %c, %p\n", s.cursor[0], data);
                            //php_doc_expression_parse
                            arguments = php_doc_list_append(arguments, data);
                            do {
                                PHP_DOC_BREAK()
                                PHP_DOC_T_COMMA(
                                    //php_printf("PHP_DOC_COMMA\n");
                                    PHP_DOC_DATA(
                                        arguments = php_doc_list_append(arguments, data);
                                        // data list append
                                    ) else {
                                        /// {{{ MESSAGE ERROR }}}
                                    }
                                ) else if (*s.cursor==')') {
                                    // we consume ')' in next step
                                    break;
                                } else {
                                    s.cursor = reset;
                                    arguments = 0;//php_doc_list_free(arguments, cb);
                                    goto mon_label;
                                }
                            } while(data);
                        ) else {
                            php_printf("NO DATA PARAM\n");
                        }

                        PHP_DOC_BREAK( )
                        PHP_DOC_T_RPARENTH(
                            //php_printf("PHP_DOC_RPARENTH\n");
                        ) else {
                            s.cursor = reset;
                            // php_doc_list_free(php_doc_data_free);
                            php_printf("EXPECTED PHP_DOC_RPARENTH\n");
                        }
                    )/** {{{ OPTIONAL }}} */

                } while(0);

mon_label:

#if 0
                do {
                    char *reset = s.cursor;
                    char *type_literal;

                    PHP_DOC_WSKIP()

                    type_literal = s.cursor;
                    PHP_DOC_TYPE(
                        value = (php_doc_value_t*)type;
                        //((php_doc_type*)value)->type = type;
                        //printf("TYPE %d==%d\n", type, PHP_DOC_TYPE_INT);
                        //printf("TYPE %.*s\n", ptr-type_literal, type_literal);
                        break;
                    ) else PHP_DOC_DATA(
                            value = (php_doc_value_t*)data;
                            //value = php_doc_data_new();
                            //((php_doc_data*)value)->value = data;
                            //data;
                            //((php_doc_type*)value)->type = type;
                            break;
                    ) else {
                        s.cursor = reset;
                    }

                    //PHP_DOC_FILEPATH(break;)

                } while(0);
                // PHP_DOC_EXP()/** {{{ OPTIONAL }}} */
#endif

                {
                    description = s.cursor;
                    PHP_DOC_TEXT(
                        description_end = s.cursor;
                        //len = ptr-str;
                        /// printf("DESCRIPTION '%.*s'\n", s.cursor-description, description);
                        //php_doc_description_set_text(section, token, len);
                    )/** {{{ OPTIONAL }}} */
                }

                /** {{{ ACCEPT }}} */
                section = php_doc_tag_t_new();
                php_doc_tag_t_set_name((php_doc_tag_t*)section, name, name_end-name);
                php_doc_tag_t_set_arguments((php_doc_tag_t*)section, arguments);
                //php_doc_tag_set_type((php_doc_tag*)section, type);
                //php_doc_tag_set_var((php_doc_tag*)section, var);
                if (description_end)
                    php_doc_tag_t_set_description((php_doc_tag_t*)section, description, description_end-description);

            )
        )
    }while(0);

    if (section) {
        *end = s.cursor;
        return section;
    } else {
        // free
    }

newline:
    //printf("%c%c\n", s.cursor[0], s.cursor[1]);
    s.cursor = str;
    s.token = str;
    if(php_doc_newline_parse(s.cursor, &s.next)) {
        *end = s.next;
        section = php_doc_newline_t_new();
        return section;
    }

txt:
    s.cursor = str;
    s.token = str;
    do{
        PHP_DOC_TEXT(
            /** {{{ ACCEPT }}} */
            section = php_doc_description_t_new();
            php_doc_description_t_set_text((php_doc_description_t*)section, str, s.cursor-str);
            ///printf("TEXT '%.*s'\n", s.cursor-str, str);

            *end = s.cursor;
            return section;
        )
    }while(0);

    return section;

/*
process_instruction:
        PHP_DOC_LCURLY(
            PHP_DOC_AT(
                PHP_DOC_NAME(
                    PHP_DOC_WS( )
                            PHP_DOC_LPARENTH(
                                PHP_DOC_RPARENTH(
                                    //todo: *end = ptr
                                ) else {
                                    status=1;
                                    //break;
                                }
                            )
                            PHP_DOC_WS()
                            PHP_DOC_TEXT(
                                //do it
                            )

                    //PHP_DOC_URI()
                )
            )
        )
*/

//process_instruction:


    //   PHP_DOC_AT(ptr, PHP_DOC_NAME(ptr, PHP_DOC_WS(ptr, PHP_DOC_TEXT(ptr, ))))
    //else PHP_DOC_AT(ptr, PHP_DOC_NAME(ptr, ))

}

enum _php_doc_contexts {
    PHP_DOC_IS_COMMENT,
    PHP_DOC_IS_DESCRIPTION,
    PHP_DOC_IS_TAG,
};

//#define TRACE_DEBUG(msg) php_printf("%s\n", msg);
#define TRACE_DEBUG(msg)

php_doc_list_t*
php_doc_content_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};

    php_doc_list_t *sections = 0;
    php_doc_section_t *section = 0;
    php_doc_description_t *desc = 0;
    php_doc_tag_t *tag = 0;
    int is_tag=0;
    int context = PHP_DOC_IS_COMMENT;// 0 => Content.summary, 1=>  Content.description,  Content.tags

    TRACE_DEBUG("\e[1;32mcontent_parse\e[0;m()")
    while (section = php_doc_section_t_parse(s.cursor, &s.cursor)){
        TRACE_DEBUG("-> \e[1;31m section_t_parse\e[0;m()")
        //printf("   (%p) text_len: %d\n", section, ((php_doc_description_t*)section)->text_len);
        if (PHP_DOC_IS_COMMENT==context) {
            if(0==desc) {
                desc = (php_doc_description_t*)section;
                desc->parent_instance.len = 1;
                if(section->type==PHP_DOC_SECTION_NEWLINE) {
                    TRACE_DEBUG("  IN_COMMENT==0 PHP_DOC_SECTION_NEWLINE=")
                    section->expect_len = 1;
                } else if (section->type==PHP_DOC_SECTION_TAG) {
                    TRACE_DEBUG("  IN_COMMENT==0 PHP_DOC_SECTION_TAG+=")
                    desc->parent_instance.expect_len += ((php_doc_description_t*)section)->text_len;
                    desc->parent_instance.len = 1;
                    tag = (php_doc_tag_t*)section;
                    context=PHP_DOC_IS_TAG;
                } else {
                    TRACE_DEBUG("  IN_COMMENT==0 PHP_DOC_SECTION_DESCRIPTION=")
                    section->expect_len = ((php_doc_description_t*)section)->text_len;
                }
            } else {
                if(section->type==PHP_DOC_SECTION_NEWLINE) {
                    TRACE_DEBUG("  IN_COMMENT==1 PHP_DOC_SECTION_NEWLINE++")
                    desc->parent_instance.expect_len += 1;
                    desc->parent_instance.len += 1;// if strat by NEWLINE: push
                } else if (section->type==PHP_DOC_SECTION_TAG) {
                    TRACE_DEBUG("  IN_COMMENT==1 PHP_DOC_SECTION_TAG+=")
                    desc=0;
                    tag = (php_doc_tag_t*)section;
                    tag->parent_instance.parent_instance.expect_len += ((php_doc_description_t*)section)->text_len;
                    tag->parent_instance.parent_instance.len = 1;
                    context=PHP_DOC_IS_TAG;
                } else {
                    TRACE_DEBUG("  IN_COMMENT==1 PHP_DOC_SECTION_DESCRIPTION++")
                    desc->parent_instance.expect_len += ((php_doc_description_t*)section)->text_len;
                    desc->parent_instance.len += 1;
                }
            }
        } else if(PHP_DOC_IS_TAG==context) {//PHP_DOC_IS_TAG
            if (section->type==PHP_DOC_SECTION_NEWLINE) {
                TRACE_DEBUG("  IN_TAG   PHP_DOC_SECTION_NEWLINE");
                ((php_doc_section_t*)tag)->expect_len += 1;
                ((php_doc_section_t*)tag)->len += 1;
            } else if (section->type==PHP_DOC_SECTION_DESCRIPTION) {
                TRACE_DEBUG("  IN_TAG   PHP_DOC_SECTION_DESCRIPTION");
                ((php_doc_section_t*)tag)->expect_len += ((php_doc_description_t*)section)->text_len;
                ((php_doc_section_t*)tag)->len += 1;
                ///printf("   TAG::PHP_DOC_SECTION_DESCRIPTION(%d)\n", ((php_doc_description_t*)section)->text_len);
            } else {// PHP_DOC_SECTION_TAG
                TRACE_DEBUG("  IN_TAG   PHP_DOC_SECTION_TAG");
                ///printf("   TAG::PHP_DOC_SECTION_TAG(%d)\n", ((php_doc_description_t*)section)->text_len);
                tag = (php_doc_tag_t*)section;
                ((php_doc_section_t*)tag)->len = 1;
                ((php_doc_section_t*)tag)->expect_len = ((php_doc_description_t*)section)->text_len;
            }
            //tag->parent_instance.parent_instance.len += 1;

#if 0
            if (is_tag) {
                if (section->type==PHP_DOC_SECTION_NEWLINE) {
                    ((php_doc_section_t*)tag)->expect_len += 1;
                    printf("   TAG::PHP_DOC_SECTION_NEWLINE\n");
                } else {// PHP_DOC_SECTION_DESCRIPTION
                    ((php_doc_section_t*)tag)->expect_len += ((php_doc_description_t*)section)->text_len;
                    printf("   TAG::PHP_DOC_SECTION_DESCRIPTION\n");
                }
                tag->parent_instance.parent_instance.len += 1;
            } else if (section->type==PHP_DOC_SECTION_TAG) {
                is_tag = 1;
                tag = (php_doc_tag_t*)section;
                ((php_doc_section_t*)tag)->expect_len = ((php_doc_description_t*)section)->text_len;
                desc=0;// is_desc
                printf("   PHP_DOC_SECTION_TAG\n");
            }
#endif
        } else {
            TRACE_DEBUG("  IN_?")
        }

        sections=php_doc_list_append(sections, section);
    };

    if(sections && end!=0) {
        *end = s.cursor;
    }
    return sections;
}


//#define TRACE() printf("  (%p) expect_len: %d\n", section, ((php_doc_description_t*)section)->expect_len)
//#define TRACE() {}

#define TRACE() \
    switch (section->type) { \
    case PHP_DOC_SECTION_TAG: printf("  (%p) TAG expect_len: %d\n", section, ((php_doc_section_t*)section)->expect_len); \
        break; \
    case PHP_DOC_SECTION_DESCRIPTION: printf("  (%p) DESC expect_len: %d\n", \
        section, ((php_doc_section_t*)section)->expect_len); \
        break; \
    case PHP_DOC_SECTION_NEWLINE: printf("  (%p) NEWLINE %d %d\n", section, ((php_doc_section_t*)section)->expect_len, section->len); \
        break; \
    } \


static php_doc_parameter*
php_doc_parameter_new(php_doc_param_t *parameter, int position)
{
    php_doc_parameter *param = malloc(sizeof(php_doc_parameter));
    ///printf("parameter : %p\n", param);
    param->position = position;
    param->name = 0;
    param->type = 0;
    //param->value = 0;

    if (parameter->named) {
        param->name = zend_string_init(parameter->named, parameter->named_len, 0);
    }

    if (parameter->type_name) {
        param->type = zend_string_init(parameter->type_name, strlen(parameter->type_name), 0);
    }

    switch (parameter->type) {
    case PHP_DOC_TYPE_OBJECT:
        ZVAL_PTR(&param->value, parameter->value.too);
        break;
    case PHP_DOC_TYPE_INT:
        ZVAL_LONG(&param->value, parameter->value.tol);
        break;
    case PHP_DOC_TYPE_FLOAT:
        ZVAL_DOUBLE(&param->value, parameter->value.tod);
        break;
    case PHP_DOC_TYPE_ID:
    case PHP_DOC_TYPE_STRING:
        ZVAL_STRING(&param->value, parameter->value.tos);
        break;
    case PHP_DOC_TYPE_UNKNOWN:
    default:
        ZVAL_NULL(&param->value);
        break;
    }

    return param;
}

static php_doc_comment*
php_doc_comment_t_parse(char *str, char **end) {
    php_doc_scanner s={str, 0, 0};

    php_doc_comment *comment = php_doc_comment_new();
    php_doc_list_t *sections = 0;// of php_doc_section*
    php_doc_section_t *section;
    php_doc_section_t **data;
    php_doc_section_t *sec;
    int is_trim=1;// start by EOL*
    zend_string *summary=0;
    zend_string *description=0;

    //php_printf("\e[1;32mcomment_parse\e[0;m()\n");

    PHP_DOC_T_BEGIN() else {
        return 0;/** {{{ error message }}} */
    }

    PHP_DOC_WSKIP() else {/** {{{ ignore }}} */}

    int cursor;

    if (sections=php_doc_content_parse(s.cursor, &s.cursor)) {
        /** {{{ ACCEPT }}} */
        data=sections->data;

        // loop for summary/description
        cursor = 0;
        int i=0;
        for (; data[i]!=0
               && (data[i]->type==PHP_DOC_SECTION_NEWLINE
                || data[i]->type==PHP_DOC_SECTION_DESCRIPTION); i++) {
            section = data[i];
            if (0==description) {
                description = zend_string_alloc(section->expect_len+1, 0);
            }
            memcpy( description->val+cursor, ((php_doc_description_t*)section)->text, ((php_doc_description_t*)section)->text_len );
            cursor += ((php_doc_description_t*)section)->text_len;
            description->val[cursor] = '\0';
        }
        if (description) {
            comment->description = description;
        }

        //printf("\"%s\"\n", description->val);

        // loop for tags

        for (; data[i]!=0; i++) {
            section = data[i];
            cursor = 0;

            char *label[]={"EOL", "TAG", "TEXT"};
            //php_printf("\t%s( %d) - %d\n", label[section->type], section->len, ((php_doc_description_t*)section)->text_len/*, ((php_doc_description_t*)section)->text*/);


#if 1
            php_doc_tag *tag = NULL;

            if (section->type == PHP_DOC_SECTION_TAG) {
                php_doc_tag_t *section_tag = (php_doc_tag_t*)section;
                tag = php_doc_tag_new(section_tag->name, section_tag->name_len);
                ///printf("tag = %p\n", tag);

                ///printf("%s\n", tag->name->val);
                if(section_tag->arguments) {
                    zend_array *parameters = &tag->parameters;
                    //zend_hash_init(parameters, section_tag->arguments->last, NULL, php_doc_parameter_free, 0);

                    for (int x=0; x<section_tag->arguments->last; x++) {
                        php_doc_parameter *param = php_doc_parameter_new(section_tag->arguments->data[x], x);
                        //zend_hash_next_index_insert_mem(parameters, &param, sizeof(php_doc_parameter*));
                        //zend_hash_index_add_ptr(parameters, 1, param);
                        zend_hash_next_index_insert_ptr(parameters, param);
                    }
                }
            }
#endif

#if 1

            description = zend_string_alloc(section->expect_len+1, 0);
            /// once
            //php_printf("  => %d\n", section->expect_len);
            //php_printf("  => %d\n", ((php_doc_description_t*)section)->text_len);
            memcpy( description->val+cursor, ((php_doc_description_t*)section)->text, ((php_doc_description_t*)section)->text_len);
            cursor += ((php_doc_description_t*)section)->text_len;
            description->val[cursor] = '\0';

            //php_printf("section->expect_len %d\n", section->expect_len);
            //php_printf("         len %d\n", section->len);
            int len = section->len;
            for (int y=1; y<len; y++) {
                section=data[i+y];
                switch(section->type){
                    case PHP_DOC_SECTION_DESCRIPTION:
                        //php_printf("  : %d\n", ((php_doc_description_t*)section)->text_len);
                        memcpy( description->val+cursor, ((php_doc_description_t*)section)->text, ((php_doc_description_t*)section)->text_len );
                        cursor += ((php_doc_description_t*)section)->text_len;
                        break;
                    case PHP_DOC_SECTION_TAG:
                        break;
                    case PHP_DOC_SECTION_NEWLINE:
                        //php_printf("  -> %d\n", ((php_doc_description_t*)section)->text_len);
                        description->val[cursor] = '\n';
                        cursor += 1;
                        break;
                    default:
                        break;
                }
                description->val[cursor] = 0;
            }
            i += len-1;// because for ( ...; i++)
            //printf("\"%s\"\n", description->val);
            php_doc_tag_set_description(tag, description);

            zend_hash_next_index_insert_ptr(&comment->tags, tag);



#endif

        }
        php_doc_list_t_free(sections, php_doc_section_t_free);
    } else {
        /** {{{ IGNORE }}} */
    }

    PHP_DOC_T_END() else {
        //if(content)free(content);
        return 0;/** {{{ error message }}} */
    }


    if (comment && end!=0) {
        *end=s.cursor;
    }
    return comment;
}

/** {{{ */
php_doc_comment*
php_doc_comment_parse(char *str, char **end) {
    php_doc_comment *doc_comment=php_doc_comment_t_parse(str, end);
    return doc_comment;
}
void
php_doc_comment_free(zval *ptr) {
    php_doc_comment *doc_comment = Z_PTR_P(ptr);

    if (doc_comment->description) {
        zend_string_release(doc_comment->description);
        //zend_string_free(doc_comment->description);
    }

    zend_hash_destroy(&doc_comment->tags);

    efree(doc_comment);
}


php_doc_callable*
php_doc_callable_parse(char *str, char **end)
{
    php_doc_callable *cb = 0;
    php_doc_callable_t *t;
    char *context;
    char *name;
    char *ptr;
    if (t = php_doc_callable_t_parse(str, end)) {
        cb = php_doc_callable_new();
        if (t->context_name) {
            cb->context = zend_string_init(t->context_name, t->context_name_len, 0);
        }
        cb->name = zend_string_init(t->function_name, t->function_name_len, 0);

        php_doc_callable_t_free(t);
    } else if (context = php_doc_id_parse(str, &ptr)) {
        //todo:  assert((ptr-str) > 5); or prevent GLib error with : assert((ptr-str) > 7);
        if (ptr[-5]=='C' && ptr[-4]=='l' && ptr[-3]=='a' && ptr[-2]=='s' && ptr[-1]=='s') {
            context[ptr-str-5]='\0';
        }
        if (ptr[0]=='.') {
            ptr++;
            if (name = php_doc_id_parse(ptr, end)) {
                // name
                cb = php_doc_callable_new();
                cb->context = zend_string_init(context, strlen(context), 0);
                cb->name = zend_string_init(name, strlen(name), 0);

                free(name);
            }
        }
        free(context);
    }
    return cb;
}


/** }}} */
