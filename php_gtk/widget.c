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

#include "widget.h"

extern HashTable         classes;
extern zend_module_entry gtk_module_entry;

zend_class_entry     *php_gtk_widget_class_entry;
//HashTable             php_gtk_widget_prop_handlers;
zend_object_handlers  php_gtk_widget_handlers;

//#define TRACE(format, string, option) php_printf(format, string, option)
#define TRACE(format, string, option)

/*----------------------------------------------------------------------+
 | Internal                                                             |
 +----------------------------------------------------------------------*/

static const zend_function_entry php_gtk_widget_methods[] = {
    PHP_ME(gtk_widget, __construct, arginfo_gtk_widget___construct, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

/*----------------------------------------------------------------------+
 | Zend Handler                                                         |
 +----------------------------------------------------------------------*/
static void  php_gtk_widget_unset_property(zval *object, zval *member, void **cache_slot);
static void  php_gtk_widget_write_property(zval *object, zval *member, zval *value, void **cache_slot);
static zval* php_gtk_widget_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv);
static char* php_gtk_widget_dump(php_gtk_widget *list, int tab);

static void
php_gtk_widget_unset_dimension(zval *object, zval *offset) {
    //php_gobject *list = ZVAL_GET_PHP_GTK_WIDGET(object);
    void *cache;

    switch(Z_TYPE_P(offset)) {
    case IS_LONG:
        // @TODO
        //zend_hash_index_del(list->prop_handler, );
        // php_gobject
        break;
    case IS_STRING:
        php_gtk_widget_unset_property(object, offset, &cache);
        break;
    default:
        break;
    }
}

static void
php_gtk_widget_write_dimension(zval *object, zval *offset, zval *value)
{
    void *cache = NULL;
    zval member;
    ZVAL_COPY(&member, offset);
    php_gtk_widget_write_property(object, &member, value, &cache);
}

static zval*
php_gtk_widget_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
    if (!offset) {
        return NULL;
    }

    php_gtk_widget *intern = ZVAL_GET_PHP_GTK_WIDGET(object);
    php_gtk_widget *list;
    void *cache=NULL;

    if (Z_TYPE_P(offset)==IS_LONG) {
        ZVAL_NULL(rv);
        return rv;
    } else if (Z_TYPE_P(offset)==IS_STRING) {
        return php_gtk_widget_read_property(object, offset, type, &cache, rv);
    } else {
        // error
    }

    return rv;
} /* }}} end php_g_hash_table_read_dimension */

static int
php_gtk_widget_has_dimension(zval *object, zval *member, int check_empty) {
    //return FAILURE;
    return SUCCESS;
}

/* updates *count to hold the number of elements present and returns SUCCESS.
 * Returns FAILURE if the object does not have any sense of overloaded dimensions */
static int
php_gtk_widget_count_elements(zval *object, zend_long *count) {

    *count = 0;

    return SUCCESS;
}

static int
php_gtk_widget_cast_object(zval *readobj, zval *retval, int type)
{
    ZVAL_NULL(retval);

    return FAILURE;
}

static HashTable*
php_gtk_widget_get_properties(zval *object){
    php_gtk_widget  *self =  ZVAL_GET_PHP_GTK_WIDGET(object);
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(self);
    HashTable *props = gobject->properties;
    if (props==NULL) {
        ALLOC_HASHTABLE(gobject->properties);
        props = gobject->properties;
    } else {
        // TODO: rebuild the props( update)
        return props;// Else leaks : zend_hash_next_index_insert
    }

    /*
    zend_long length = php_gtk_widget_length(self);

    zend_hash_init(props, length, NULL, ZVAL_PTR_DTOR, 1);

    zval data;

    php_gtk_widget *it;
    for(it=php_gtk_widget_first(self); it; it = it->next){
        ZVAL_COPY(&data, &it->data);
        zend_hash_next_index_insert(props, &data);
    }
    */

    return props;
}

static HashTable*
php_gtk_widget_get_debug_info(zval *object, int *is_temp) /* {{{ */
{
    php_gtk_widget  *obj =  ZVAL_GET_PHP_GTK_WIDGET(object);
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(obj);
    HashTable   *debug_info,
                *std_props;
    zend_string *string_key = NULL;
    zval *value;

    *is_temp = 1;
    std_props = zend_std_get_properties(object);
    debug_info = zend_array_dup(std_props);


    ZEND_HASH_FOREACH_STR_KEY_VAL(gobject->std.properties, string_key, value) {
        zend_hash_add(debug_info, string_key, value);
    } ZEND_HASH_FOREACH_END();

    /*
    zval prev; ZVAL_SET_PHP_GTK_WIDGET(&prev, obj->prev);
    zend_hash_str_update(debug_info, "prev", sizeof("prev")-1, &prev);

    zval data; ZVAL_COPY(&data, &obj->data);
    zend_hash_str_update(debug_info, "data", sizeof("data")-1, &data);

    zval next; ZVAL_SET_PHP_GTK_WIDGET(&next, obj->next);
    zend_hash_str_update(debug_info, "next", sizeof("next")-1, &next);
    */

    return debug_info;
}
/* }}} */

static void
php_gtk_widget_unset_property(zval *object, zval *member, void **cache_slot) {
    php_gtk_widget *obj = ZVAL_GET_PHP_GTK_WIDGET(object);
    zend_string *member_str = zval_get_string(member);
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (zend_string_equals_literal(member->value.str, "next")
     || zend_string_equals_literal(member->value.str, "prev")
     || zend_string_equals_literal(member->value.str, "data") ) {
#if 0
        if (ZVAL_IS_PHP_GTK_WIDGET(value)) {
            // do unset(object->next) and php_gtk_widget_insert(object, value, 0);
        } else {
            zend_string *type = zend_zval_get_type(value);
            zend_error(E_USER_WARNING, "Cannot assign %s to property GObject::$next of type GObject", type->val);
        }
#else
        zend_error(E_USER_WARNING, "Readonly property GObject::$%s", member->value.str->val);
#endif
        return;
    }
    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->unset_property(object, member, cache_slot);

    zend_string_release(member_str);
}

/* {{{ php_gtk_widget_write_property */
static void
php_gtk_widget_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    php_gtk_widget *obj = ZVAL_GET_PHP_GTK_WIDGET(object);
    zend_string *member_str = zval_get_string(member);
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    if (zend_string_equals_literal(member->value.str, "next")
     || zend_string_equals_literal(member->value.str, "prev")
     || zend_string_equals_literal(member->value.str, "data") ) {
#if 0
        if (ZVAL_IS_PHP_GTK_WIDGET(value)) {
            // do unset(object->next) and php_gtk_widget_insert(object, value, 0);
        } else {
            zend_string *type = zend_zval_get_type(value);
            zend_error(E_USER_WARNING, "Cannot assign %s to property GObject::$next of type GObject", type->val);
        }
#else
        zend_error(E_USER_WARNING, "Readonly property GObject::$%s", member->value.str->val);
#endif
        return;
    }
    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    std_hnd->write_property(object, member, value, cache_slot);

    zend_string_release(member_str);
}
/* }}} */

static zval zval_ret;
/* {{{ gtk_read_property */
static zval*
php_gtk_widget_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    php_gtk_widget *obj = ZVAL_GET_PHP_GTK_WIDGET(object);
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    TRACE("%s(%s)\n", __FUNCTION__, member->value.str->val);

    /*
    if (zend_string_equals_literal(member_str, "next")) {
        if (NULL==obj->next) {
            ZVAL_NULL(&zval_ret);
            return &zval_ret;
        }
        ZVAL_OBJ(&zval_ret, &obj->next->std);
        return &zval_ret;
    }
    if (zend_string_equals_literal(member_str, "prev")) {
        if (NULL==obj->prev) {
            ZVAL_NULL(&zval_ret);
            return &zval_ret;
        }
        ZVAL_OBJ(&zval_ret, &obj->prev->std);
        return &zval_ret;
    }
    if (zend_string_equals_literal(member_str, "data")) {
        ZVAL_COPY(&zval_ret, &obj->data);
        return &zval_ret;
    }
    */

    zend_object_handlers *std_hnd = zend_get_std_object_handlers();
    retval = std_hnd->read_property(object, member, type, cache_slot, rv);

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ php_gtk_widget_free_object */
static void
php_gtk_widget_free_object(zend_object *object)
{
    php_gtk_widget *intern = ZOBJ_TO_PHP_GTK_WIDGET(object);
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(intern);
    TRACE("php_gtk_widget_free_object(\"%s\") / %d\n", intern->data.value.str->val, object->gc.refcount);

    if (gobject->ptr) {
        g_free(gobject->ptr);
        gobject->ptr = NULL;
    }

    if (gobject->properties!=NULL) {
        zend_hash_destroy(gobject->properties);
        efree(gobject->properties);
        gobject->properties=NULL;
    }

    zend_object_std_dtor(&gobject->std);
    //efree(intern);
}
/* }}} php_gtk_widget_free_object */

static void
php_gtk_widget_dtor_object(zend_object *obj) {
    php_gtk_widget *intern = ZOBJ_TO_PHP_GTK_WIDGET(obj);
    TRACE("php_gtk_widget_dtor_object(\"%s\") / %d\n", intern->data.value.str->val, obj->gc.refcount);

    /*
    if (!ZVAL_IS_NULL(&intern->data)) {
        Z_TRY_DELREF_P(&intern->data);
        //zval_ptr_dtor(&intern->data);
        //g_print("zend_string: %p\n", intern->data.value.str);
        //g_print("            (%d)\n", intern->data.value.str->gc.refcount);
        //zend_string_release(intern->data.value.str);
        ZVAL_NULL(&intern->data);
    }

    if (intern->next) {
        zend_object_release(&intern->next->std);
        intern->next=NULL;
    }

    if (intern->prev!=NULL) {
        zend_object_release(&intern->prev->std);
        intern->prev=NULL;
    }
    */

}


/* {{{ php_gtk_widget_create_object */
static zend_object*
php_gtk_widget_create_object(zend_class_entry *class_type)
{
    php_gtk_widget *intern = ecalloc(1, sizeof(php_gtk_widget) + zend_object_properties_size(class_type));
    php_gobject_object *gobject =  PHP_GOBJECT_OBJECT(intern);

    zend_object_std_init(&gobject->std, class_type);
    object_properties_init(&gobject->std, class_type);

    gobject->ptr = NULL;// new GObject ?
    gobject->properties = NULL;

    gobject->std.handlers = &php_gtk_widget_handlers;

    TRACE("php_gtk_widget_create_object(%p) / %d\n", &gobject->std, gobject->std.gc.refcount);
    return &gobject->std;
}
/* }}} php_gtk_widget_create_object */

/*
static void php_gtk_widget_dtor_prop_handler(zval *zv)
{
    free(Z_PTR_P(zv));
}
*/

static zend_object_handlers*
php_gtk_widget_get_handlers()
{
    memcpy(&php_gtk_widget_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_gtk_widget_handlers.offset = PHP_GTK_WIDGET_OFFSET;
    //php_gtk_widget_handlers.clone_obj;
    //php_gtk_widget_handlers.compare;
    //php_gtk_widget_handlers.compare_objects;
    //php_gtk_widget_handlers.get_constructor;
    php_gtk_widget_handlers.dtor_obj = php_gtk_widget_dtor_object;
    php_gtk_widget_handlers.free_obj = php_gtk_widget_free_object;
    php_gtk_widget_handlers.read_property = php_gtk_widget_read_property;
    php_gtk_widget_handlers.write_property = php_gtk_widget_write_property;
    php_gtk_widget_handlers.unset_property = php_gtk_widget_unset_property;
    //php_gtk_widget_handlers.get_property_ptr_ptr = php_gtk_widget_get_property_ptr_ptr;

    php_gtk_widget_handlers.get_debug_info = php_gtk_widget_get_debug_info;
    php_gtk_widget_handlers.get_properties = php_gtk_widget_get_properties;//get_properties_for TODO php 8.0
    //php_gtk_widget_handlers.set = php_gtk_widget_set;
    php_gtk_widget_handlers.cast_object = php_gtk_widget_cast_object;

    php_gtk_widget_handlers.count_elements = php_gtk_widget_count_elements;
    php_gtk_widget_handlers.has_dimension = php_gtk_widget_has_dimension;
    php_gtk_widget_handlers.read_dimension = php_gtk_widget_read_dimension;
    php_gtk_widget_handlers.unset_dimension = php_gtk_widget_unset_dimension;
    php_gtk_widget_handlers.write_dimension = php_gtk_widget_write_dimension;


    return &php_gtk_widget_handlers;
}



/*----------------------------------------------------------------------+
| PHP_MINIT                                                            |
+----------------------------------------------------------------------*/
/*{{{ php_gtk_widget_class_init */
zend_class_entry*
php_gtk_widget_class_init(zend_class_entry *container_ce, zend_class_entry *parent_ce) {
    php_gtk_widget_get_handlers();
    //INIT_NS_CLASS_ENTRY((*ce), "Gnome\\G", "Object", php_gtk_widget_methods);
    INIT_CLASS_ENTRY((*container_ce), "GtkWidget", php_gtk_widget_methods);
    php_gtk_widget_class_entry = zend_register_internal_class_ex(container_ce, parent_ce);
    php_gtk_widget_class_entry->create_object = php_gtk_widget_create_object;
    //ce->serialize;
    /*
    zend_hash_init(&php_gtk_widget_prop_handlers, 0, NULL, php_gtk_widget_dtor_prop_handler, 1);
    php_gtk_widget_register_prop_handler(&php_gtk_widget_prop_handlers, "prev", sizeof("prev")-1, php_gtk_widget_read_prev, php_gtk_widget_write_prev);
    php_gtk_widget_register_prop_handler(&php_gtk_widget_prop_handlers, "data", sizeof("data")-1, php_gtk_widget_read_data, php_gtk_widget_write_data);
    php_gtk_widget_register_prop_handler(&php_gtk_widget_prop_handlers, "next", sizeof("next")-1, php_gtk_widget_read_next, php_gtk_widget_write_next);
    zend_hash_add_ptr(&classes, ce->name, &php_gtk_widget_prop_handlers);
    */

#if 0
    char *comment = "/**"
                    " * Base class for all widgets"
                    " * @package Gtk"
                    " */";
    php_gtk_widget_class_entry->type == ZEND_USER_CLASS;
    php_gtk_widget_class_entry->info.user.doc_comment = zend_string_init(comment, strlen(comment), 1);
#endif
    php_gtk_widget_class_entry->info.user.doc_comment = NULL;

#if 0
    char *doc = "/**"
                    " * The constructor"
                    " * @package Gtk"
                    " */";
    php_gtk_widget_class_entry->constructor->op_array.doc_comment  = zend_string_init(doc, strlen(doc), 1);
#endif


    return php_gtk_widget_class_entry;
}/*}}} */

/*----------------------------------------------------------------------+
 | Zend-User utils                                                      |
 +----------------------------------------------------------------------*/


/*----------------------------------------------------------------------+
 | Zend-User API                                                        |
 +----------------------------------------------------------------------*/
void
php_gtk_widget_show_all(php_gtk_widget *list, zval *data) {
    zend_object *new_std = php_gtk_widget_create_object(php_gtk_widget_class_entry);
    php_gtk_widget *new_list = ZOBJ_TO_PHP_GTK_WIDGET(new_std);

}



/*----------------------------------------------------------------------+
| PHP_METHOD                                                           |
+----------------------------------------------------------------------*/

/* {{{ GObject::__construct() */
PHP_METHOD(gtk_widget, __construct)
{
    zval *data=NULL;


    /*
    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(data)
    ZEND_PARSE_PARAMETERS_END();
    */

    zend_object *zobj = Z_OBJ_P(getThis());
    php_gtk_widget *self = ZOBJ_TO_PHP_GTK_WIDGET(zobj);

}
/* }}} */


/*----------------------------------------------------------------------+
| PHP_FUNCTION                                                         |
+----------------------------------------------------------------------*/

/* {{{ proto GObject gtk_widget_show_all(GObject list, mixed data) */
PHP_FUNCTION(gtk_widget_show_all)
{
    zval *zwidget = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zwidget)
    ZEND_PARSE_PARAMETERS_END();


    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget) ? ZVAL_GET_PHP_GTK_WIDGET(zwidget) : NULL;
    php_gobject_object *gwidget = PHP_GOBJECT_OBJECT(widget);
    GtkWidget *gtk_widget = GTK_WIDGET(gwidget->ptr);

    gtk_widget_show_all(gtk_widget);

}/* }}} */

/* {{{ proto GObject gtk_widget_show_all(GObject list, mixed data) */
PHP_FUNCTION(gtk_widget_show)
{
    zval *zwidget = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(zwidget)
    ZEND_PARSE_PARAMETERS_END();


    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget) ? ZVAL_GET_PHP_GTK_WIDGET(zwidget) : NULL;
    php_gobject_object *gwidget = PHP_GOBJECT_OBJECT(widget);
    GtkWidget *gtk_widget = GTK_WIDGET(gwidget->ptr);

    gtk_widget_show(gtk_widget);

}/* }}} */


#   if 0

#include "ext/reflection/php_reflection.h"

enum _DocCommentToken{
    DOC_START,
    DOC_SECTION,
    DOC_DESCRIPTION,
    DOC_MARGIN,
    DOC_TAG,
    DOC_END,
};

typedef struct _php_doc_tag php_doc_tag;
struct _php_doc_tag {
    char *name;
    char *value;
    char *description;
};

typedef struct _php_doc_block php_doc_block;
struct _php_doc_block {
    char *section;
    char *description;
    php_doc_tag **tags;// null-termineted
};

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
    char *buffer = g_strdup("");
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

        buf = g_strdup_printf("%s%.*s\n", buffer, ptr-tmp, tmp);
        g_free(buffer);
        buffer = buf;

        // jump
        SKIP_WS(ptr, end);
    }

    if (buffer[0]!='\0') {
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
static char
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
#   endif

#include "php_doc/tag.h";
#include "php_doc/comment.h";
#include "php_doc/parser.h";

static php_doc_tag*
php_reflection_doc_comment_find_tag_by_name(php_doc_block *doc_block, char *tag_name) {
    php_doc_tag *tag = NULL;
    int i = 0;
    if (doc_block && doc_block->tags)
    while (doc_block->tags[i]) {
        tag = doc_block->tags[i];
        if (0==g_strcmp0(tag->name, tag_name)) {
            break;
        }
        tag = NULL;
        i++;
    }

    return tag;
}

#if 0
// php_doc_tag_override
typedef struct _php_doc_tag_method php_doc_tag_method;
struct _php_doc_tag_method {
    char *klass;
    char *name;
};

// TODO fixme
static char
php_reflection_method(char *tag_value, php_doc_tag_method *method) {
    char *pos = strrchr(tag_value, ':');
    if(tag_value<pos) {
        method->klass = g_strndup(tag_value, pos-tag_value-1);
        method->name = g_strdup(pos+1);
    }
    return SUCCESS;
}

// php_doc_tag_value_is_identical(php_doc_tag *a, php_doc_tag*b)
static zend_bool
php_doc_tag_override_is_identical(php_doc_tag_method *a, php_doc_tag_method *b) {
    if(!a || !a->klass || !a->name)
        return FALSE;
    if(!b|| !b->klass || !b->name)
        return FALSE;
    if(0==g_strcmp0(a->klass, b->klass) && 0==g_strcmp0(a->name, b->name))
        return TRUE;
    return FALSE;
}
#endif

#if 0
typedef struct {
    zval dummy; /* holder for the second property */
    zval obj;
    void *ptr;
    zend_class_entry *ce;
    int foo;// hacking
} reflection_object;
#endif

/*
static php_doc_tag_method php_doc_tag_gtk_widget_get_preferred_width = {
    "GtkWidget", "get_preferred_width"
};
static php_doc_tag php_doc_tag_override_gtk_widget_get_preferred_width = {
    "override", "GtkWidget::get_preferred_width", NULL
};*/

zend_function*
php_gtk_get_override_function(zend_object *zobject, char *name) {

    /**
    zend_bool is_recusive = FALSE;
    zend_function *func = execute_data->func;
    zend_execute_data *curr = execute_data->prev_execute_data;
    while(curr){
        zend_function *f = curr->func;
        if (func==f) {
            is_recusive = TRUE;
            break;
        }
        curr = curr->prev_execute_data;
    }
    g_print("is_recursive: %d\n", is_recusive);
    */

#if 1

    // cash: overrides = Map<zend_class_entry, Array<zend_function>>
    // cash: overrides_zend_class_entry = Array<zend_class_entry>
    //php_doc_block doc_block;
    //php_doc_tag_method method;
    php_doc_block *doc_comment;

    zend_object *zobj = zobject;//&widget->parent_instance.std;
    zend_class_entry *top = zobj->ce;
    zend_class_entry *base = php_gtk_widget_class_entry;
    while (top) {
        g_print("             : %s\n", top->name->val);
#if 1
        zend_function *func;
        zend_string *key;
        ZEND_HASH_FOREACH_STR_KEY_PTR(&top->function_table, key, func) {
            if (func->type == ZEND_USER_FUNCTION) {
                //g_print("%s\n", func->op_array.doc_comment->val);
                //g_print("function %s - %s\n", key->val, func->common.function_name->val);
                char *str = func->op_array.doc_comment->val;
                doc_comment = php_doc_comment_create(str/*, &error*/);
                php_doc_tag *tag = php_reflection_doc_comment_find_tag_by_name(doc_comment, "override");
                if (tag && 0==g_strcmp0(tag->value, name)) {
                    return func;
                }
                php_doc_comment_free(doc_comment);

#if 0
                char status = parseDocBlock(&str, &doc_block);
                if (status==SUCCESS) {
                    php_doc_tag *tag = php_reflection_doc_comment_find_tag_by_name(&doc_block, "override");
                    //php_reflection_method(tag->value, &method);
                    //g_print("%s @%s %s\n", name.value.str->val, tag->name, tag->value);
                    //if (php_doc_tag_override_is_identical(&method, &php_doc_tag_gtk_widget_get_preferred_width)) {
                    //g_print("tag %s - %s\n", tag->value, name);
                    if (0==g_strcmp0(tag->value, name)) {
                        return func;
                    } else {
                        //g_print("Continue...\n");
                    }
                } else {
                    g_print("Failled to parse doc comment in %s\n", func->common.function_name->val);
                }
#endif
            }
        } ZEND_HASH_FOREACH_END();
#else

        zval class_reflector;
        zend_reflection_class_factory(top, &class_reflector);

        //memset(&execute_data, 0, sizeof(zend_execute_data));
        //EG(current_execute_data) = &execute_data;


        zval retval;
        zend_call_method_with_0_params(&class_reflector, NULL, NULL, "getMethods", &retval);
        //g_print("  -> %d/%d\n", Z_TYPE(retval), IS_ARRAY);
        zval *reflector_method;
        zval name;
        zval comment;
        char *ptr;
        char status;
        ZEND_HASH_FOREACH_VAL(retval.value.arr, reflector_method) {
            zend_call_method_with_0_params(reflector_method, NULL, NULL, "getName", &name);

            zend_call_method_with_0_params(reflector_method, NULL, NULL, "getDocComment", &comment);
            if (Z_TYPE(comment)==IS_STRING) {
                ptr = comment.value.str->val;
                //g_print("    %s\n", ptr);
                status = parseDocBlock(&ptr, &doc_block);
                //g_print("parsed:%d\n", status);
                php_doc_tag *tag = php_reflection_doc_comment_find_tag_by_name(&doc_block, "override");
                php_reflection_method(tag->value, &method);
                //g_print("%s @%s %s\n", name.value.str->val, tag->name, tag->value);
                if (php_doc_tag_override_is_identical(&method, &php_doc_tag_gtk_widget_get_preferred_width)) {
                    g_print("%s %s@%s\n", name.value.str->val, method.klass, method.name);
                    zend_object *ref = reflector_method->value.obj;
                    reflection_object *intern = (char*)ref - ref->handlers->offset;
                    return intern->ptr;

#if 0
// Btn::get_prefered_width
// gtk_widget_get_prefered_width
                    zend_object *ref = reflector_method->value.obj;
                    reflection_object *intern = (char*)ref - ref->handlers->offset;
                    zend_function *fptr = intern->ptr;
                    g_print("%s\n", fptr->common.function_name->val);
                    //g_print("%s\n", fptr->op_array.filename->val);
                    zend_function *my_self = execute_data->func;
                    g_print("%s\n", my_self->common.function_name->val);
                    g_print("%p\n", my_self);
                    g_print("%p\n", fptr);
#endif

                }

                // TODO free

            }
            //g_print("    function %s(){}\n", name.value.str->val);
        } ZEND_HASH_FOREACH_END();

        //zend_string *lc_method_name = zend_string_init("getDocComment", strlen("getDocComment"), 0);
//        zend_string *lc_method_name = zend_string_init("getMethod", strlen("getMethod"), 0);
//        zend_function *fbc;
//        fbc = zend_hash_find_ptr(&ref->function_table, lc_method_name);
//$reflector->getMethod('get_preferred_width')->getDocComment();
#endif
        break;
        top = top->parent;
        if (top==base)
            break;
    }

    // search if php class override get_preferred_width/getPreferredWidth
    // See in * @override, or in #[Override('', class: 'GtkWidget')]
    // for each parent... until GtkWidget
    /*
    */
    //zobj->ce->function_table;

    /*
    char *klass_name = "GtkWidget";
    char *funct_name = "get_preferred_width";
    GtkButton *button = GTK_BUTTON(self->parent_instance.parent_instance.parent_instance.ptr);
    GtkWidget *widget = GTK_WIDGET(button);

    GtkButtonClass *btn_klass = g_type_class_peek((GType)button);
    GtkWidgetClass *wdg_klass = &btn_klass->parent_class.parent_class.parent_class;
    */

#endif

    return NULL;
}



static GList *php_gtk_widget_get_preferred_width_caller_recursive = NULL;
/* {{{ proto GObject gtk_widget_show_all(GObject list, mixed data) */
PHP_FUNCTION(gtk_widget_get_preferred_width)
{
    zval *zwidget = NULL;
    zval *zminimum_width = NULL;
    zval *znatural_width = NULL;

    //Z_PARAM_OBJECT_OF_CLASS_EX(zwidget, php_gtk_widget_class_entry, 1, 0)
    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(zwidget)
        Z_PARAM_ZVAL_DEREF(zminimum_width)
        Z_PARAM_ZVAL_DEREF(znatural_width)
    ZEND_PARSE_PARAMETERS_END();

    php_gtk_widget *widget = ZVAL_IS_PHP_GTK_WIDGET(zwidget) ? ZVAL_GET_PHP_GTK_WIDGET(zwidget) : NULL;
    if (NULL==widget) {
        //zend_error( TypeError);
        return;
    }

#if 1
    GtkWidget *__widget = PHP_GOBJECT_OBJECT(widget)->ptr;
    int __minimum_width;
    int __natural_width;
    gtk_widget_get_preferred_width(__widget, &__minimum_width, &__natural_width);

    ZVAL_DOUBLE(zminimum_width, __minimum_width);
    ZVAL_DOUBLE(znatural_width, __natural_width);

#else

    zend_function *func = NULL;
    zend_bool is_override = FALSE;
    zend_bool is_recursive = NULL!=
    g_list_find(php_gtk_widget_get_preferred_width_caller_recursive, widget);

    if (!is_recursive) {
        // try to find override user_function
        func = php_gtk_get_override_function(&widget->parent_instance.std, "GtkWidget::get_preferred_width");
        if (func) {
            is_override = TRUE;
            zend_execute_data *execute = execute_data->prev_execute_data;
            g_print("Same object ? %d\n", zwidget->value.obj == execute->This.value.obj);// func<-common
            if (0==g_strcmp0(execute->func->common.function_name->val, func->common.function_name->val)) {
                if (ZVAL_IS_PHP_GTK_WIDGET(&execute->This)) {
                    is_override = FALSE;
                }
            }
        }
        g_print("Call is not recusive\n");
    } else {
        g_print("Call is recusive\n");
    }

    if (is_override) {
        g_print("  call override function\n");
        php_gtk_widget_get_preferred_width_caller_recursive =
        g_list_append(php_gtk_widget_get_preferred_width_caller_recursive, widget);

        zval retval;
        char *function_name = func->common.function_name->val;
        //int result = zend_call_method(zwidget, NULL, NULL, function_name, strlen(function_name), &retval, 2, zminimum_width, znatural_width);
        int result;
        zend_fcall_info fci;
        //zval retval;
        zval params[2];
            ZVAL_COPY_VALUE(&params[0], zminimum_width);// ?
            ZVAL_COPY_VALUE(&params[1], znatural_width);// ?

        fci.size = sizeof(fci);
        fci.object = Z_OBJ_P(zwidget);
        fci.retval = &retval;
        fci.param_count = 2;
        fci.params = params;
        fci.no_separation = 0;
            ZVAL_STRINGL(&fci.function_name, function_name, strlen(function_name));
            result = zend_call_function(&fci, NULL);

        if (FAILURE != result) {
            double __minimum_width = 0;
            double __natural_width = 0;
            if (Z_TYPE(params[0])==IS_REFERENCE) {
                if (Z_TYPE(params[0].value.ref->val)==IS_DOUBLE) {
                    __minimum_width = params[0].value.ref->val.value.dval;
                    __natural_width = params[1].value.ref->val.value.dval;
                } else if (Z_TYPE(params[0].value.ref->val)==IS_LONG) {
                    __minimum_width = params[0].value.ref->val.value.lval;
                    __natural_width = params[1].value.ref->val.value.lval;
                }
            }
            ZVAL_DOUBLE(zminimum_width, __minimum_width);
            ZVAL_DOUBLE(znatural_width, __natural_width);
        } else {
            g_print("zend_call_method_ Failure\n");
        }

        php_gtk_widget_get_preferred_width_caller_recursive =
        g_list_remove(php_gtk_widget_get_preferred_width_caller_recursive, widget);
    } else {
        GtkWidget *__widget = PHP_GOBJECT_OBJECT(widget)->ptr;
        int __minimum_width;
        int __natural_width;
        gtk_widget_get_preferred_width(__widget, &__minimum_width, &__natural_width);

        ZVAL_DOUBLE(zminimum_width, __minimum_width);
        ZVAL_DOUBLE(znatural_width, __natural_width);
    }
#endif


}/* }}} */

