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

#include "tag.h"
#include "comment.h"

#include "parser.h"

#include <glib.h>

#define SKIP_WS(ptr, end) while(ptr<end && (*ptr==' ' || *ptr=='\t' || *ptr=='\n' || *ptr=='\r')) { ptr++;}
#define IS_WS(ptr, end) (*ptr==' ' || *ptr=='\t')
#define IS_EOL(ptr, end) (*ptr=='\n' || *ptr=='\r')
#define IS_EOF(ptr, end) (end<=ptr)
#define IS_WORD(ptr, end) (('a'<=*ptr && *ptr<='z')||('A'<=*ptr && *ptr<='Z'))

static char
parseDocBlockStart(char **str, char *end) {
    char *ptr = *str;

    SKIP_WS(ptr, end);
    if ((ptr+3)>=end) {
        return FAILURE;
    }
    if (ptr[0]=='/') {
        if (ptr[1]=='*') {
            if (ptr[2]=='*') {
                *str = ptr+3;
                return SUCCESS;
            }
            *str = ptr+2;
            return ptr[2];
        }
        *str = ptr+1;
        return ptr[1];
    }
    return ptr[0];
}

// parseDocName
// parseDocIdentifier
static char
parseIdentifier(char **str, char *end, char **section) {
    char *ptr = *str;
    char *tmp = ptr;

    while(ptr<end && (('a'<=*ptr && *ptr<='z')||('A'<=*ptr && *ptr<='Z')||*ptr=='-'||*ptr=='_'||*ptr==':'||*ptr=='/'||*ptr=='\\')) { ptr++;}

    if (tmp<ptr) {
        *section = g_strndup(tmp, ptr-tmp);
        *str = ptr;
        return SUCCESS;
    }

    return ptr[0];
}

static char
parseDocBlockMargin(char **str, char *end) {
    char *ptr = *str;

    SKIP_WS(ptr, end);

    if ((ptr+1)<end && ptr[0]=='*' && ptr[1]!='/') {
        ptr++;
        /*SKIP_WS(ptr, end);
        if (ptr[0]=='*')
            parseDocBlockMargin(&ptr, end);
        */
        *str = ptr;
        return SUCCESS;
    }

    return ptr[0];
}

static char
parseDocBlockDescriptionLine(char **str, char *end) {
    char *ptr = *str;
    char *tmp = ptr;
    char *last_printable = NULL;

    while(ptr<end && (
                ('a'<=*ptr && *ptr<='z')||('A'<=*ptr && *ptr<='Z')||('0'<=*ptr && *ptr<='9')
                 ||*ptr=='-'||*ptr=='_'||*ptr==':'||*ptr=='/'||*ptr=='\\'||*ptr==','
                 ||*ptr=='$'||*ptr=='#'
                 ||*ptr=='('||*ptr==')'||*ptr=='['||*ptr==']'||*ptr=='\''||*ptr=='"'
                 ||*ptr==' '||*ptr=='\t'
    )) {
        if(ptr[0]!=' '&&ptr[0]!='\t')
            last_printable = ptr;
        ptr++;
    }
    if (tmp<=last_printable && last_printable!=NULL) {
        *str = last_printable+1;
        return SUCCESS;
    }
    return ptr[0];
}

static char
parseDocBlockDescription(char **str, char *end, php_doc_block *doc_block) {
    char *ptr = *str;
    char *tmp;
    char *last_line = ptr;
    char *token;
    char *buffer = NULL;
    char *buf = NULL;

    SKIP_WS(ptr, end);

    //if ((ptr+1)<end && ptr[0]=='@') {
    //    return ptr[0];
    //}

    while (ptr<end) {
        tmp = ptr;
        /*
        token = parseDocBlockMargin(&ptr, end);
        if (SUCCESS!=token) {
            break;
        }

        if(ptr[0]=='\n') {
            SKIP_WS(ptr, end);
            continue;
        }*/
        tmp = ptr;
        while(SUCCESS==parseDocBlockMargin(&ptr, end)) tmp = ptr;

        SKIP_WS(ptr, end);
        if(ptr[0]=='@') {
            last_line = ptr;
            break;
        }

        tmp = ptr;
        token = parseDocBlockDescriptionLine(&ptr, end);
        if (SUCCESS!=token) {
            break;
        }
        last_line = ptr;

        if (NULL==buffer) {
            buffer = g_strdup("");
        }
        buf = g_strdup_printf("%s%.*s\n", buffer, ptr-tmp, tmp);
        g_free(buffer);
        buffer = buf;

        // jump
        SKIP_WS(ptr, end);
    }

    if (NULL!=buffer && buffer[0]!='\0') {
        //buffer[strlen(buffer)-1]='\0';// remove laste EOL
        doc_block->description = buffer;
        *str = last_line;
        return SUCCESS;
    }

    return ptr[0];
}

// parseDocTag
static char
parseDocBlockTag(char **str, char *end, php_doc_tag *doc_tag) {
    char *ptr = *str;
    char *tmp;
    char *token;
    char *section;
    php_doc_block tag_name={NULL, NULL, NULL};

    SKIP_WS(ptr, end);

    if((ptr+1)<end && ptr[0]!='@') {
        return ptr[0];
    }
    ptr++;

    tmp = ptr;
    while(IS_WORD(ptr, end)) {ptr++;}
    if (tmp<ptr) {
        doc_tag->name = g_strndup(tmp, ptr-tmp);

        SKIP_WS(ptr, end);

        tmp = ptr;
        token = parseIdentifier(&ptr, end, &section);
        if (SUCCESS==token) doc_tag->value = section;
        else return ptr[0];

        SKIP_WS(ptr, end);

        tmp = ptr;
        token = parseDocBlockDescription(&ptr, end, &tag_name);
        if (SUCCESS==token) doc_tag->description = tag_name.description;

    }

    *str = ptr;

    return SUCCESS;
}
static char
parseDocBlockTags(char **str, char *end, php_doc_block *doc_block) {
    char *ptr = *str;
    char *tmp;
    char *token = SUCCESS;
    php_doc_tag doc_tag = {NULL, NULL, NULL};
    int num_tags = 0;
    php_doc_tag *tags[100];
    php_doc_tag *tag;

    while (SUCCESS==token) {
        tmp = ptr;
        while(SUCCESS==parseDocBlockMargin(&ptr, end)) tmp = ptr;
        token = parseDocBlockTag(&ptr, end, &doc_tag);
        if (SUCCESS==token) {
            *str = ptr;
            tag = g_new(php_doc_tag, 1);
            tag->name = doc_tag.name;
            tag->value = doc_tag.value;
            tag->description = doc_tag.description;
            tags[num_tags] = tag;

            //g_free();
            doc_tag.name = NULL;
            doc_tag.value = NULL;
            doc_tag.description = NULL;
            num_tags++;
        }
    }
    if (num_tags>0) {
        doc_block->tags = g_new(php_doc_tag*, num_tags+1);
        memcpy(doc_block->tags, tags, sizeof(php_doc_tag*)*num_tags);
        doc_block->tags[num_tags] = NULL;
    } else {
        doc_block->tags = NULL;
    }

    return SUCCESS;
}

static char
parseDocBlockEnd(char **str, char *end) {
    char *ptr = *str;

    //while(SUCCESS==parseDocBlockMargin(&ptr, end));
    // bug if not the last line

    if ((ptr+2)<=end && ptr[0]=='*' && ptr[1]=='/') {
        *str = ptr+2;
        return SUCCESS;
    }

    return ptr[0];
}



/**
 * A brief description. A more elaborate class description
 * @param bool somebool a boolean argument.
 * @see Test()
 * @return The test results
 */
char
parseDocBlock(char **str, php_doc_block *doc_block) {
    char *tmp = NULL;
    char *ptr = *str;
    char *end = ptr + strlen(ptr);
    char *token;
    char *section;

    tmp = ptr;
    token = parseDocBlockStart(&ptr, end); if (SUCCESS!=token) return token;

    SKIP_WS(ptr, end);

    tmp = ptr;
    token = parseIdentifier(&ptr, end, &section);
    if (SUCCESS==token) {
        doc_block->section = section;
        //g_print("Section: \"%s\"\n", section);
    }

    SKIP_WS(ptr, end);

    tmp = ptr;
    token = parseDocBlockDescription(&ptr, end, doc_block);
    //if (SUCCESS==token) g_print("Description: \"%s\"\n", doc_block->description);

    SKIP_WS(ptr, end);

    tmp = ptr;
    token = parseDocBlockTags(&ptr, end, doc_block);
    if (SUCCESS!=token) ptr = tmp;

    tmp = ptr;
    token = parseDocBlockEnd(&ptr, end);
    if (SUCCESS!=token) return ptr[0];

    *str = ptr;

    return SUCCESS;
}

