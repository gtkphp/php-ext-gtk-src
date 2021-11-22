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

#include <glib-object.h>

#include "php_doc/parameter.h"
#include "php_doc/tag.h"
#include "php_doc/comment.h"
#include "php_doc/scanner.h"

#include "object.h"
#include "value.h"
#include "paramspecs.h"
#include "type.h"
#include "object-extends.h"

static void php_gobject_object_get_property (GObject    *object,
                                             guint       prop_id,
                                             GValue     *value,
                                             GParamSpec *pspec);
static void php_gobject_object_set_property (GObject      *object,
                                             guint         prop_id,
                                             const GValue *value,
                                             GParamSpec   *pspec);

PHP_GOBJECT_DEFINE_TYPE(PhpGObjectObject, php_gobject_object, G_TYPE_OBJECT)

void
php_gobject_object_init(PhpGObjectObject *self) {
}

void
php_gobject_object_class_init(PhpGObjectObjectClass *klass) {
    GObjectClass *gobject_class = klass;

    //TODO get/set property
    gobject_class->set_property = php_gobject_object_set_property;
    gobject_class->get_property = php_gobject_object_get_property;
}

//-----------------------------------------------------------------------------

static int php_gobject_object_install_property(GObjectClass *type, php_doc_tag *tag) {

    static guint property_id=0;
    GParamSpec *pspec;

    php_doc_parameter *param_property_name = php_doc_tag_get_parameter_at(tag, 0);
    php_doc_parameter *param_property_nick = php_doc_tag_get_parameter_at(tag, 1);
    php_doc_parameter *param_property_blurb = php_doc_tag_get_parameter_at(tag, 2);
    char *name = Z_STR(param_property_name->value)->val;
    char *nick = Z_STR(param_property_nick->value)->val;
    char *blurb= Z_STR(param_property_blurb->value)->val;

    if(0==strcmp(tag->name->val, "g_param_spec_uint")) {
        php_doc_parameter *param_minimum = php_doc_tag_get_parameter_at(tag, 3);
        php_doc_parameter *param_maximum = php_doc_tag_get_parameter_at(tag, 4);
        php_doc_parameter *param_default_value = php_doc_tag_get_parameter_at(tag, 5);
        php_doc_parameter *param_flags = php_doc_tag_get_parameter_at(tag, 6);

        gint minimum=Z_LVAL(param_minimum->value);
        gint maximum=Z_LVAL(param_maximum->value);
        gint default_value=Z_LVAL(param_default_value->value);
        GParamFlags flags=Z_LVAL(param_flags->value);
        pspec = g_param_spec_uint(name, nick, blurb, minimum, maximum, default_value, flags);
    }
    else if(0==strcmp(tag->name->val, "g_param_spec_string")) {
        php_doc_parameter *param_default_value = php_doc_tag_get_parameter_at(tag, 3);
        php_doc_parameter *param_flags = php_doc_tag_get_parameter_at(tag, 4);

        gchar *default_value=Z_STR(param_default_value->value)->val;
        GParamFlags flags=Z_LVAL(param_flags->value);
        pspec = g_param_spec_string(name, nick, blurb, default_value, flags);
    }

    // TODO if pspec
    property_id++;
    g_object_class_install_property(type, property_id, pspec);

    return property_id;
}

int php_gobject_object_changed(gpointer object, gpointer param, gpointer user_data) {
    php_printf("closure::php_gobject_object_changed(%s, %p, %p)\n", g_type_name_from_instance(object), param, user_data);
    return 0;
}

//php_gobject_object_marshaler_MIXED__ARRAY
//php_gobject_object_marshaler_ZVAL__ZVAL
//php_gobject_object_marshaler_BOXED__BOXED

#define g_marshal_value_peek_pointer(v)  (v)->data[0].v_pointer

/* POINTER:POINTER (marshal.list:3) */
static void
php_gobject__POINTER__POINTER (GClosure     *closure,
                               GValue       *return_value,
                               guint         n_param_values,
                               const GValue *param_values,
                               gpointer      invocation_hint G_GNUC_UNUSED,
                               gpointer      marshal_data)
{
  typedef gpointer (*GMarshalFunc_POINTER__POINTER) (gpointer data1,
                                                     gpointer arg1,
                                                     gpointer data2);
  GCClosure *cc = (GCClosure *) closure;
  gpointer data1, data2;
  GMarshalFunc_POINTER__POINTER callback;
  gpointer v_return;

  g_return_if_fail (return_value != NULL);
  //g_return_if_fail (n_param_values == 2);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
      php_printf("----\n");
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
      php_printf("....\n");
    }
  callback = (GMarshalFunc_POINTER__POINTER) (marshal_data ? marshal_data : cc->callback);

  php_printf("php_gobject__POINTER__POINTER(%d: %s, %s, user_data)%s\n", n_param_values, g_type_name(param_values[0].g_type), g_type_name(param_values[1].g_type), g_type_name(return_value->g_type));
  php_printf("   %d\n", return_value->g_type);
  v_return = callback (data1,
                       g_marshal_value_peek_pointer (param_values + 1),
                       data2);

  if (G_TYPE_INT == return_value->g_type) {
      g_value_set_int(return_value, v_return);
  }
  else if (G_TYPE_POINTER == return_value->g_type) {
      g_value_set_pointer (return_value, v_return);
  }

}

void
php_gobject_object_marshaler_INT__POINTER (GClosure     *closure,
                                           GValue       *return_value G_GNUC_UNUSED,
                                           guint         n_param_values,
                                           const GValue *param_values,
                                           gpointer      invocation_hint G_GNUC_UNUSED,
                                           gpointer      marshal_data)
{
  typedef gint (*GMarshalFunc_INT__POINTER) (gpointer     data1,
                                             gpointer     arg_1,
                                             gpointer     data2);

  GMarshalFunc_INT__POINTER callback;
  GCClosure *cc = (GCClosure*) closure;
  gpointer data1, data2;
  gint v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 2);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_INT__POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_pointer (param_values + 1),
                       data2);

  g_value_set_int (return_value, v_return);
}

static unsigned int php_gobject_object_install_signal(GType type, php_doc_tag *tag) {
    //PhpGObjectObjectClass *klass = g_type_class_peek(G_TYPE_FROM_INSTANCE(widget));

    size_t size = zend_array_count(&tag->parameters);

    php_doc_parameter *param_signal_name = php_doc_tag_get_parameter_at(tag, 0);
    //php_doc_parameter *param_itype = php_doc_tag_get_parameter_at(tag, 1);
    php_doc_parameter *param_signal_run = php_doc_tag_get_parameter_at(tag, 2);
    ///php_doc_parameter *param_accumulator = php_doc_tag_get_parameter_at(tag, 3);
    php_doc_parameter *param_accu = php_doc_tag_get_parameter_at(tag, 4);
    php_doc_parameter *param_accu_data = php_doc_tag_get_parameter_at(tag, 5);
    php_doc_parameter *param_return_type = php_doc_tag_get_parameter_at(tag, 6);
    php_doc_parameter *param_n_param = php_doc_tag_get_parameter_at(tag, 7);

    char *signal_name  = Z_STR(param_signal_name->value)->val;
    //param_itype = php_doc_expression_eval("MyObject::class") | intval();
    GSignalFlags signal_run = Z_LVAL(param_signal_run->value);//G_SIGNAL_RUN_LAST
    GSignalAccumulator accu = NULL;//php_doc_parameter_eval(Z_STR(param_accu->value)->val);
    gpointer accu_data = NULL;//php_doc_parameter_eval(Z_STR(param_accu_data->value)->val);
    zend_long  return_type  = Z_LVAL(param_return_type->value);//G_TYPE_INT
    zend_long  n_param      = Z_LVAL(param_n_param->value);
    //php_printf("assert(%d == %d)\n", size-8, n_param);
    GType *param_types      = malloc(sizeof(GType)*(n_param+1));
    for (zend_long  n = 0; n<n_param; n++) {
        php_doc_parameter *param = php_doc_tag_get_parameter_at(tag, 8+n);
        param_types[n] = Z_LVAL(param->value);
    }
    param_types[n_param] = G_TYPE_INVALID;//null-terminated
    //php_printf("assert(%d == %d)\n", param_types[0], G_TYPE_POINTER);
    //php_printf("assert(%d == %d)\n", param_types[1], G_TYPE_INVALID);

/*
   zend_array *parameters = php_doc_tag_get_parameters_by_name(tag, "signal_name");
   //Bucket *buck = parameters->arData[0];
   ZEND_HASH_FOREACH_PTR(parameters, param) {
       signal_name = param->value.value.str->val;
   } ZEND_HASH_FOREACH_END();

   zend_hash_destroy(parameters);
   FREE_HASHTABLE(parameters);
*/

   //GClosure closure = G_STRUCT_OFFSET (PhpGObjectObjectClass, changed);
   GClosure *closure = NULL; //g_cclosure_new (G_CALLBACK (php_gobject_object_changed),//default_write_signal_handler
                             //          (gpointer)0x0000003 /* user_data */,
                             //          NULL /* destroy_data */);
   // php_gobject_signal_new();
   //klass->signals
   GType               w_return_type = G_TYPE_POINTER;
   guint               w_n_params = 1;
   GType               w_param_types[1] = {G_TYPE_POINTER};

   php_printf("ICI est le bug: %d, %d, %d==111\n", return_type==G_TYPE_INT, n_param==1, param_types[0]==G_TYPE_INT);

   unsigned int signal_id =
       g_signal_newv (signal_name,// "changed"
                     type,// "MyObject::class", G_OBJECT_CLASS_TYPE (klass),
                     signal_run,// G_SIGNAL_RUN_LAST, //G_SIGNAL_RUN_FIRST | G_SIGNAL_RUN_LAST,
                     closure,// G_STRUCT_OFFSET (PhpGObjectObjectClass, changed)
                     accu, accu_data,
                     php_gobject__POINTER__POINTER,
                     return_type, n_param,
                     param_types);

   free(param_types);
   return signal_id;// php_gobject_object_ext_signals[0];

}

void
php_gobject_object_class_override (GType type, zend_object *zobject)
{
    /*
    GObject *inst = g_object_new(type, NULL);
    if (g_object_is_floating(inst)) {
        inst = g_object_ref_sink(inst);// fix: if(NULL==klass)
    }
    //g_object_unref(inst);// fix: if(NULL==klass)
    //g_clear_object(&inst);
    */
    GTypeClass *klass = g_type_class_peek(type);
    if (NULL==klass) {
        //klass = g_type_class_ref(type);// need g_type_class_unref(klass)
        //return G_TYPE_INVALID;
    }

    zend_class_entry *class_type = zobject->ce;

    //ZEND_HASH_FOREACH_PTR(&class_type->attributes, c) {} ZEND_HASH_FOREACH_END();

    zend_property_info *prop_info;
    zend_string *key;
    zval *prop;
    ZEND_HASH_FOREACH_STR_KEY_PTR(&class_type->properties_info, key, prop_info) {
        prop = &class_type->default_properties_table[OBJ_PROP_TO_NUM(prop_info->offset)];
        if (NULL!=prop_info->doc_comment) {
            //if not static => prop_info->flags & ZEND_ACC_STATIC == 0
            php_doc_comment *comment;
            if (comment = php_doc_comment_parse(prop_info->doc_comment->val, 0)) {
                ///printf("properties_table parser SUCCES\n");

                php_doc_tag *tag;
                zend_array *tags = &comment->tags;
                char *names[] = {
                    "g_param_spec_boolean",
                    "g_param_spec_char",
                    "g_param_spec_uchar",
                    "g_param_spec_int",
                    "g_param_spec_uint",
                    "g_param_spec_long",
                    "g_param_spec_ulong",
                    "g_param_spec_int64u",
                    "g_param_spec_int64",
                    "g_param_spec_float",
                    "g_param_spec_double",
                    "g_param_spec_enum",
                    "g_param_spec_flags",
                    "g_param_spec_string",
                    "g_param_spec_param",
                    "g_param_spec_boxed",
                    "g_param_spec_pointer",
                    "g_param_spec_object",
                    "g_param_spec_unichar",
                    "g_param_spec_value_array",
                    "g_param_spec_override",
                    "g_param_spec_gtype",
                    "g_param_spec_variant",
                    NULL
                };
                tags = php_doc_comment_get_tags_by_names(comment, names);
                if(zend_array_count(tags)>1) {
                    php_printf("TODO: Error, multiple definition of @g_param_spec_[type] in file ...\n");
                } else {
                    ZEND_HASH_FOREACH_PTR(tags, tag) {
                        //php_printf("TODO: ...@%s%s\n", tag->name->val, tag->description->val);
                        int id = php_gobject_object_install_property(klass, tag);
                    } ZEND_HASH_FOREACH_END();
                }
                zend_hash_destroy(tags);
                FREE_HASHTABLE(tags);


                zval val; ZVAL_PTR(&val, comment);// coz zend_hash_init(, pDestroy, )
                php_doc_comment_free(&val);
            }

        }
    } ZEND_HASH_FOREACH_END();



    zend_class_constant *c;

    unsigned int i = 0;

    ZEND_HASH_FOREACH_PTR(&class_type->constants_table, c) {
        // switch c->attributs
        if(c->doc_comment) {
            // @g_signal_new

            php_doc_comment *comment;
            if (comment= php_doc_comment_parse(c->doc_comment->val, 0)) {
                zend_array *tags = &comment->tags;
                php_doc_tag *tag;

                tags = php_doc_comment_get_tags_by_name(comment, "g_signal_new");
                ZEND_HASH_FOREACH_PTR(tags, tag) {
                    i=php_gobject_object_install_signal(type, tag);
                } ZEND_HASH_FOREACH_END();


                zend_hash_destroy(tags);
                FREE_HASHTABLE(tags);


                zval val; ZVAL_PTR(&val, comment);// coz zend_hash_init(, pDestroy, )
                php_doc_comment_free(&val);

                ///printf("constants_table parser SUCCES\n");
            } else {
                printf("constants_table parser FAILLED\n");
            }

        }
        if(i) ZVAL_LONG(&c->value, i);// const CHANGED = g_signal_unique_id;

    } ZEND_HASH_FOREACH_END();

#if 0
    /*
    for(int i=0; i<class_type->default_properties_count; i++) {
        zval *v = &class_type->default_properties_table[i];
        //printf("var %d\n", );//Z_TYPE(v->value) IS_LONG
    };
    */

    zend_function *f=0;
    ZEND_HASH_FOREACH_PTR(&class_type->function_table, f) {
        if (f->type == ZEND_USER_FUNCTION & NULL!=f->op_array.doc_comment) {
            /**/
            php_doc_comment *comment;
            if (comment = php_doc_comment_parse(f->op_array.doc_comment->val, 0)) {
                printf("function_table parser SUCCES\n");
                php_doc_tag *tag;
                zend_array *tags = &comment->tags;
                ZEND_HASH_FOREACH_PTR(tags, tag) {
                    if (0==strcmp(tag->name->val, "g_override")) {
                        char *end;
                        php_doc_callable *cb = 0;
                        if(cb = php_doc_callable_parse(tag->description->val, &end)) {
                            php_gobject_object_install_override(f, klass, cb->context, cb->name);
                            php_doc_callable_free(cb);
                        }
                    }
                } ZEND_HASH_FOREACH_END();

                zval val; ZVAL_PTR(&val, comment);// coz zend_hash_init(, pDestroy, )
                php_doc_comment_free(&val);
            }

            /**/
        }
    } ZEND_HASH_FOREACH_END();



    zend_class_constant *c;

    unsigned int i = 0;

    ZEND_HASH_FOREACH_PTR(&class_type->constants_table, c) {
        // switch c->attributs
        if(c->doc_comment) {
            ///php_printf("    %s\n", c->doc_comment->val);

            // @extends GtkWidgetClass.draw
            // @override GtkWidget::draw
            // @g_signal_new

            php_doc_comment *comment;
            if (comment= php_doc_comment_parse(c->doc_comment->val, 0)) {
                /// zend_array *tags = php_doc_comment_get_tags_by_name(comment, "g_param_spec_uint");
                /// ZEND_HASH_FOREACH_PTR(tags, tag) {
                /// } ZEND_HASH_FOREACH_END();

                php_doc_tag *tag;
                zend_array *tags = &comment->tags;
                /*
                ZEND_HASH_FOREACH_PTR(tags, tag) {
                    php_printf("@%s\n", tag->name->val);
                } ZEND_HASH_FOREACH_END();
                */


                tags = php_doc_comment_get_tags_by_name(comment, "g_signal_new");
                ZEND_HASH_FOREACH_PTR(tags, tag) {
                    i=php_gobject_object_install_signal(type, tag);
                } ZEND_HASH_FOREACH_END();


                zend_hash_destroy(tags);
                FREE_HASHTABLE(tags);

                // else

                char *names[] = {
                    "g_param_spec_boolean",
                    "g_param_spec_char",
                    "g_param_spec_uchar",
                    "g_param_spec_int",
                    "g_param_spec_uint",
                    "g_param_spec_long",
                    "g_param_spec_ulong",
                    "g_param_spec_int64u",
                    "g_param_spec_int64",
                    "g_param_spec_float",
                    "g_param_spec_double",
                    "g_param_spec_enum",
                    "g_param_spec_flags",
                    "g_param_spec_string",
                    "g_param_spec_param",
                    "g_param_spec_boxed",
                    "g_param_spec_pointer",
                    "g_param_spec_object",
                    "g_param_spec_unichar",
                    "g_param_spec_value_array",
                    "g_param_spec_override",
                    "g_param_spec_gtype",
                    "g_param_spec_variant",
                    NULL
                };
                tags = php_doc_comment_get_tags_by_names(comment, names);
                if(zend_array_count(tags)>1) {
                    php_printf("TODO: Error, multiple definition of @g_param_spec_[type] in file ...\n");
                } else {
                    ZEND_HASH_FOREACH_PTR(tags, tag) {
                        i=php_gobject_object_install_property(klass, tag);
                    } ZEND_HASH_FOREACH_END();
                }
                zend_hash_destroy(tags);
                FREE_HASHTABLE(tags);


                char *style_properties[] = {
                    "g_param_spec_boolean",
                    "g_param_spec_gtype",
                    "g_param_spec_variant",
                    NULL
                };
                //tags = php_doc_comment_get_tags_by_names(comment, ['@style']);
                //tags = php_doc_comment_get_tags_by_names(comment, style_properties);
                ///ZEND_HASH_FOREACH_PTR(tags, tag) {
                //    i=php_gobject_object_install_style_property(type, tag);
                ///} ZEND_HASH_FOREACH_END();

                zval val; ZVAL_PTR(&val, comment);// coz zend_hash_init(, pDestroy, )
                php_doc_comment_free(&val);

                ///printf("constants_table parser SUCCES\n");
            } else {
                printf("constants_table parser FAILLED\n");
            }

        } else {
            ///printf("No doc_comment for constants_table\n");
        }
        //php_printf("%p: %p\n", c->ce, class_type);
        //php_printf("%d\n", c->value.value.lval);
        if(i) ZVAL_LONG(&c->value, i);// const CHANGED = g_signal_unique_id;

        //ZVAL_LONG(&c->value, 5);
        /*
        if (c->ce == ce) {
            zval_ptr_dtor_nogc(&c->value);
            if (c->doc_comment) {
                zend_string_release_ex(c->doc_comment, 0);
            }
            if (c->attributes) {
                zend_hash_release(c->attributes);
            }
        }
        */
    } ZEND_HASH_FOREACH_END();
#endif

    return type;
}


#if 1

static void
php_gobject_object_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
  PhpGObjectObject *obj = (PhpGObjectObject*)object;
  zend_object *zobject = g_object_get_data(obj, "zend_object");
  zend_object *zobj = zobject ? zobject : pop_zend();// G_PARAM_CONSTRUCT
  ///php_printf("php_gobject_object_set_property\n");

  if (zobj) {
      zend_string *prop_name = zend_string_init(pspec->name, strlen(pspec->name), 0);

      zval zvalue; ZVAL_LONG(&zvalue, g_value_get_uint(value));
      zend_std_write_property(zobj, prop_name, &zvalue, NULL);

      zend_string_release(prop_name);
  }
  //G_OBJECT_CLASS(php_gobject_object_parent_class)->set_property(object, prop_id, value, pspec);
}

static void
php_gobject_object_get_property (GObject    *object,
                                 guint       prop_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
  PhpGObjectObject *obj = (PhpGObjectObject*)object;
  zend_object *zobject = g_object_get_data(obj, "zend_object");

  if (zobject) {
      zend_string *prop_name = zend_string_init(pspec->name, strlen(pspec->name), 0);

      zval zvalue;
      zend_std_read_property(zobject, prop_name, 0, NULL, &zvalue);// todo find type ...
      g_value_set_uint(value, Z_LVAL(zvalue));

      zend_string_release(prop_name);
  } else {
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
  }

  //G_OBJECT_CLASS(php_gobject_object_parent_class)->set_property(object, prop_id, value, pspec);
}


#else

GHashTable *php_gobject_object_classes=NULL;
PhpGObjectObject php_gobject_object_instance;
PhpGObjectObjectClass php_gobject_object_classe;


#define g_marshal_value_peek_pointer(v)  (v)->data[0].v_pointer
void
php_gobject_object_marshaler_INT__POINTER (GClosure     *closure,
                                           GValue       *return_value G_GNUC_UNUSED,
                                           guint         n_param_values,
                                           const GValue *param_values,
                                           gpointer      invocation_hint G_GNUC_UNUSED,
                                           gpointer      marshal_data)
{
  typedef gint (*GMarshalFunc_INT__POINTER) (gpointer     data1,
                                             gpointer     arg_1,
                                             gpointer     data2);
  GMarshalFunc_INT__POINTER callback;
  GCClosure *cc = (GCClosure*) closure;
  gpointer data1, data2;
  gint v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 2);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_INT__POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_pointer (param_values + 1),
                       data2);

  g_value_set_int (return_value, v_return);
}

int php_gobject_object_changed(gpointer user_data) {
    php_printf("class::php_gobject_object_changed(%p)\n", user_data);
    return 0;
}

static GSignalFlags
g_signal_flags(char *name)
{
  if (0==strcmp(name, "G_SIGNAL_RUN_FIRST")) return G_SIGNAL_RUN_FIRST;
  if (0==strcmp(name, "G_SIGNAL_RUN_LAST")) return G_SIGNAL_RUN_LAST;
  if (0==strcmp(name, "G_SIGNAL_RUN_CLEANUP")) return G_SIGNAL_RUN_CLEANUP;
  if (0==strcmp(name, "G_SIGNAL_NO_RECURSE")) return G_SIGNAL_NO_RECURSE;
  if (0==strcmp(name, "G_SIGNAL_DETAILED")) return G_SIGNAL_DETAILED;
  if (0==strcmp(name, "G_SIGNAL_ACTION")) return G_SIGNAL_ACTION;
  if (0==strcmp(name, "G_SIGNAL_NO_HOOKS")) return G_SIGNAL_NO_HOOKS;
  if (0==strcmp(name, "G_SIGNAL_MUST_COLLECT")) return G_SIGNAL_MUST_COLLECT;
  if (0==strcmp(name, "G_SIGNAL_DEPRECATED")) return G_SIGNAL_DEPRECATED;
  return 0;
}

static long
g_types(char *name)
{
    // if name is a constant of php, get it, else error
    // TODO zend_register_long_constant with value of G_TYPE_INT

    if (0==strcmp(name, "G_TYPE_INT")) return G_TYPE_INT;
    if (0==strcmp(name, "G_TYPE_POINTER")) return G_TYPE_POINTER;
    if (0==strcmp(name, "G_TYPE_OBJECT")) return G_TYPE_OBJECT;
    return 0;
}

static long
g_contants(char *name)
{
    // if name is a constant of php, get it, else error
    // TODO zend_register_long_constant with value of G_TYPE_INT

    if (0==strcmp(name, "NULL")) return NULL;
    if (0==strcmp(name, "G_PARAM_READWRITE")) return G_PARAM_READWRITE;
    if (0==strcmp(name, "G_PARAM_CONSTRUCT_ONLY")) return G_PARAM_CONSTRUCT_ONLY;

    return 0;
}

//TODO: rename by php_doc_expression_eval
static int
php_doc_parameter_eval(char *expression)
{
    char *name = expression;
    int ret;

    // What appen if expression is Json ?
    ret = g_signal_flags(name);// G_SIGNAL_RUN_FIRST | G_SIGNAL_RUN_LAST
    if (0==ret) {
        ret = g_types(name);// G_TYPE_OBJECT
        if (0==ret) {
            ret = g_contants(name);// NULL
        }
    }

    return ret;
}

/**
 * multiple class from one struct definition
 */
static guint php_gobject_object_ext_signals[1] = { 0 };
static unsigned int php_gobject_object_install_signal(GType type, php_doc_tag *tag) {
    //PhpGObjectObjectClass *klass = g_type_class_peek(G_TYPE_FROM_INSTANCE(widget));

    size_t size = zend_array_count(&tag->parameters);

    php_doc_parameter *param_signal_name = php_doc_tag_get_parameter_at(tag, 0);
    //php_doc_parameter *param_itype = php_doc_tag_get_parameter_at(tag, 1);
    php_doc_parameter *param_signal_run = php_doc_tag_get_parameter_at(tag, 2);
    ///php_doc_parameter *param_accumulator = php_doc_tag_get_parameter_at(tag, 3);
    php_doc_parameter *param_accu = php_doc_tag_get_parameter_at(tag, 4);
    php_doc_parameter *param_accu_data = php_doc_tag_get_parameter_at(tag, 5);
    php_doc_parameter *param_return_type = php_doc_tag_get_parameter_at(tag, 6);
    php_doc_parameter *param_n_param = php_doc_tag_get_parameter_at(tag, 7);

    char *signal_name  = Z_STR(param_signal_name->value)->val;
    //param_itype = php_doc_expression_eval("MyObject::class") | intval();
    GSignalFlags signal_run = php_doc_parameter_eval(Z_STR(param_signal_run->value)->val);//G_SIGNAL_RUN_LAST
    GSignalAccumulator accu = php_doc_parameter_eval(Z_STR(param_accu->value)->val);
    gpointer accu_data = php_doc_parameter_eval(Z_STR(param_accu_data->value)->val);
    zend_long  return_type  = php_doc_parameter_eval(Z_STR(param_return_type->value)->val);//G_TYPE_INT
    zend_long  n_param      = Z_LVAL(param_n_param->value);
    //php_printf("assert(%d == %d)\n", size-8, n_param);
    GType *param_types      = malloc(sizeof(GType)*(n_param+1));
    for (zend_long  n = 0; n<n_param; n++) {
        php_doc_parameter *param = php_doc_tag_get_parameter_at(tag, 8+n);
        param_types[n] = php_doc_parameter_eval(Z_STR(param->value)->val);
    }
    param_types[n_param] = G_TYPE_INVALID;//null-terminated
    //php_printf("assert(%d == %d)\n", param_types[0], G_TYPE_POINTER);
    //php_printf("assert(%d == %d)\n", param_types[1], G_TYPE_INVALID);

/*
   zend_array *parameters = php_doc_tag_get_parameters_by_name(tag, "signal_name");
   //Bucket *buck = parameters->arData[0];
   ZEND_HASH_FOREACH_PTR(parameters, param) {
       signal_name = param->value.value.str->val;
   } ZEND_HASH_FOREACH_END();

   zend_hash_destroy(parameters);
   FREE_HASHTABLE(parameters);
*/

   //GClosure closure = G_STRUCT_OFFSET (PhpGObjectObjectClass, changed);
   GClosure *closure = g_cclosure_new (G_CALLBACK (php_gobject_object_changed),//default_write_signal_handler
                                       (gpointer)0xdeadbeaf /* user_data */,
                                       NULL /* destroy_data */);
   // php_gobject_signal_new();
   //klass->signals
   //php_gobject_object_ext_signals[0] =
   unsigned int signal_id =
       g_signal_newv (signal_name,// "changed"
                     type,// "MyObject::class", G_OBJECT_CLASS_TYPE (klass),
                     signal_run,// G_SIGNAL_RUN_LAST, //G_SIGNAL_RUN_FIRST | G_SIGNAL_RUN_LAST,
                     closure,// G_STRUCT_OFFSET (PhpGObjectObjectClass, changed)
                     accu, accu_data,
                     php_gobject_object_marshaler_INT__POINTER,
                     return_type, n_param,
                     param_types);

   free(param_types);
   return signal_id;// php_gobject_object_ext_signals[0];

}

static int php_gobject_object_install_property(GObjectClass *type, php_doc_tag *tag) {

    static guint property_id=0;
    GParamSpec *pspec;

    php_doc_parameter *param_property_name = php_doc_tag_get_parameter_at(tag, 0);
    php_doc_parameter *param_property_nick = php_doc_tag_get_parameter_at(tag, 1);
    php_doc_parameter *param_property_blurb = php_doc_tag_get_parameter_at(tag, 2);
    char *name = Z_STR(param_property_name->value)->val;
    char *nick = Z_STR(param_property_nick->value)->val;
    char *blurb= Z_STR(param_property_blurb->value)->val;

    if(0==strcmp(tag->name->val, "g_param_spec_uint")) {
        php_doc_parameter *param_minimum = php_doc_tag_get_parameter_at(tag, 3);
        php_doc_parameter *param_maximum = php_doc_tag_get_parameter_at(tag, 4);
        php_doc_parameter *param_default_value = php_doc_tag_get_parameter_at(tag, 5);
        php_doc_parameter *param_flags = php_doc_tag_get_parameter_at(tag, 6);

        gint minimum=Z_LVAL(param_minimum->value);
        gint maximum=Z_LVAL(param_maximum->value);
        gint default_value=Z_LVAL(param_default_value->value);
        GParamFlags flags=G_PARAM_CONSTRUCT | G_PARAM_READWRITE;
        pspec = g_param_spec_uint(name, nick, blurb, minimum, maximum, default_value, flags);
    }
    else if(0==strcmp(tag->name->val, "g_param_spec_string")) {
        php_doc_parameter *param_default_value = php_doc_tag_get_parameter_at(tag, 3);
        php_doc_parameter *param_flags = php_doc_tag_get_parameter_at(tag, 4);

        gchar *default_value=Z_STR(param_default_value->value)->val;
        GParamFlags flags=G_PARAM_CONSTRUCT | G_PARAM_READWRITE;//php_doc_parameter_eval(Z_STR(param_flags->value)->val);
        pspec = g_param_spec_string(name, nick, blurb, default_value, flags);
        /**
         * @g_param_spec_string("zoomed",
         *                      "Maman construct prop",
         *                      "Set maman's name",
         *                      "no-name-set",
         *                      G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE)
         */
    }


    // TODO if pspec
    property_id++;
    g_object_class_install_property(type, property_id, pspec);

    return property_id;
}

static php_gobject_object_override_get_property(GObject        *object,
                                                guint           property_id,
                                                GValue         *value,
                                                GParamSpec     *pspec) {

    // call user_function
    php_printf("php_gobject_object_override_get_property\n");
}





static PhpGObjectObjectClass php_gobject_object_class = {G_TYPE_INVALID};
//static PhpGObjectObjectClass php_gobject_object_user_methods = {NULL};
extern zend_object *php_gobject_hack_dirty_bad_smel;

static void
php_gobject_object_override_set_property(GObject        *object,
                                         guint           property_id,
                                         const GValue   *value,
                                         GParamSpec     *pspec) {
    php_printf("php_gobject_object_override_set_property(%s)%d\n", pspec->name, pspec->param_id);

    static GList *recursive_object = NULL;
    zend_object *zobject = g_object_get_data(G_OBJECT(object), "zend_object");

    zend_function *func = NULL;
    zend_bool is_override = FALSE;
    zend_bool is_recursive = FALSE;

    if (NULL==zobject) {
        zobject = pop_zend();// because g_object_new() call set_property when param is G_PARAM_CONSTRUCT alors que g_object_get_data(, "zend_object") n'a pas encore ete appelé
        ZOBJ_TO_PHP_GOBJECT_OBJECT(zobject)->ptr = object;
    }

    is_recursive = NULL != g_list_find(recursive_object, object);

    if (!is_recursive) {
        // try to find override user_function
        func = php_gobject_object_get_user_method(zobject, "GObjectClass.set_property");//<-------------
        if (func) {
            is_override = TRUE;
        }
        zend_execute_data *current_execute = EG(current_execute_data);
        zend_execute_data *execute = NULL;
        if (NULL!=current_execute) {
            execute = current_execute->prev_execute_data;
        }// else on est mode GTKML

        if (func && execute && execute->func->common.function_name) {
            g_print("... %s\n", current_execute->func->common.function_name->val);// TODO
            g_print("Same object ? %d\n", zobject == execute->This.value.obj);// TODO
            if (0==g_strcmp0(execute->func->common.function_name->val, func->common.function_name->val)) {
                if (ZVAL_IS_PHP_GOBJECT_OBJECT(&execute->This)) {
                    is_override = FALSE;
                }
            }
        }
        //g_print("Call is not recusive\n");
    } else {
        //g_print("Call is recusive\n");
    }

    if (is_override) {
        //g_print("  call override function\n");
        recursive_object =
        g_list_append(recursive_object, object);

        zval retval;
        char *function_name = func->common.function_name->val;
        size_t function_name_len = func->common.function_name->len;
#if 1
/*
cannot access protected/private method MyObject::setProperty()
 */

        // call function with context

        zend_object *zgval = php_gobject_value_class_entry->create_object(php_gobject_value_class_entry);
        php_gobject_value *gval = ZOBJ_TO_PHP_GOBJECT_VALUE(zgval);
        memcpy(&gval->gvalue, value, sizeof(GValue));

        zend_object *zgspec = php_gobject_param_spec_class_entry->create_object(php_gobject_param_spec_class_entry);
        php_gobject_param_spec *gspec = ZOBJ_TO_PHP_GOBJECT_PARAM_SPEC(zgspec);
        //gspec->.. = spec

        zend_fcall_info_cache fci_cache;
        fci_cache.function_handler = func;
        fci_cache.object = zobject;
        fci_cache.called_scope = zobject->ce;

        int result;
        zend_fcall_info fci;
        zval zprop_id;
        zval zvalue;
        zval zpspec;
        ZVAL_LONG(&zprop_id, property_id);
        ZVAL_OBJ(&zvalue, zgval);
        ZVAL_OBJ(&zpspec, zgspec);

        zval params[3];
            ZVAL_COPY_VALUE(&params[0], &zprop_id);
            ZVAL_COPY_VALUE(&params[1], &zvalue);
            ZVAL_COPY_VALUE(&params[2], &zpspec);

        fci.size = sizeof(fci);
        fci.object = zobject;//Z_OBJ_P(zwidget);
        fci.retval = &retval;
        fci.param_count = 3;
        fci.params = params;
        fci.named_params = 0;
        ZVAL_STRINGL(&fci.function_name, function_name, function_name_len);
            result = zend_call_function(&fci, &fci_cache);
        zval_ptr_dtor(&fci.function_name);

#elif 0
        zval zwidget; ZVAL_OBJ(&zwidget, zobject);
        zval zminimum_width;
        zval znatural_width;
        ZVAL_NEW_REF(&zminimum_width, &zminimum_width);//<------------------------------------------------------
        ZVAL_NEW_REF(&znatural_width, &znatural_width);
        int result = zend_call_method(&zwidget, NULL, NULL, function_name, strlen(function_name), &retval, 2, &zminimum_width, &znatural_width);
        if (FAILURE != result) {
            if (Z_TYPE(zminimum_width)==IS_REFERENCE) {
                if (Z_TYPE(zminimum_width.value.ref->val)==IS_DOUBLE) {
                    ///*minimum_width = zminimum_width.value.ref->val.value.dval;
                    ///*natural_width = znatural_width.value.ref->val.value.dval;
                } else if (Z_TYPE(zminimum_width.value.ref->val)==IS_LONG) {
                    //TODO check define(strict_types=1)
                    //zend_bool strict_types = ZEND_CALL_USES_STRICT_TYPES(EG(current_execute_data));
                    ///*minimum_width = zminimum_width.value.ref->val.value.lval;
                    ///*natural_width = znatural_width.value.ref->val.value.lval;
                }
            }
        } else {
            g_print("zend_call_method_ Failure\n");
        }
        zval_ptr_dtor(&zminimum_width);
        zval_ptr_dtor(&znatural_width);

#else
        int result;
        zend_fcall_info fci;
        //zval retval;
        zval zminimum; ZVAL_DOUBLE(&zminimum, *minimum_width);
        zval znatural; ZVAL_DOUBLE(&znatural, *natural_width);
        //zval zminimum_width;
        //zval znatural_width;
        //ZVAL_NEW_REF(&zminimum_width, &zminimum);
        //ZVAL_NEW_REF(&znatural_width, &znatural);
        zval params[2];
            //ZVAL_COPY_VALUE(&params[0], &zminimum_width);// ?
            //ZVAL_COPY_VALUE(&params[1], &znatural_width);// ?
            ZVAL_COPY_VALUE(&params[0], &zminimum);// ?
            ZVAL_COPY_VALUE(&params[1], &znatural);// ?

        ///zend_call_method()
        fci.size = sizeof(fci);
        fci.object = zobject;//Z_OBJ_P(zwidget);
        fci.retval = &retval;
        fci.param_count = 2;
        fci.params = params;
        fci.no_separation = 0;
            ZVAL_STRINGL(&fci.function_name, function_name, strlen(function_name));
            result = zend_call_function(&fci, NULL);
        zval_ptr_dtor(&fci.function_name);

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
            //ZVAL_DOUBLE(zminimum_width, __minimum_width);
            //ZVAL_DOUBLE(znatural_width, __natural_width);
            *minimum_width = __minimum_width;
            *natural_width = __natural_width;
        } else {
            g_print("zend_call_method_ Failure\n");
        }
#endif

        recursive_object =
        g_list_remove(recursive_object, object);
    } else {
        php_printf("-> %s\n", g_type_name_from_instance(object));
        GObjectClass *object_klass = g_type_class_ref(object->g_type_instance.g_class->g_type);
        guint n_properties;
        GParamSpec **specs = g_object_class_list_properties(object_klass, &n_properties);
        for(int i = 0; i < n_properties; i++) {
            GParamSpec *spec = specs[i];
            php_printf("   + %s(%d)\n", spec->name, spec->param_id);
        }
        g_type_class_unref(object_klass);

        GObjectClass *gobject_klass = g_type_class_peek(G_TYPE_OBJECT);
        gobject_klass->set_property(object, property_id, value, pspec);
        if (gobject_klass->set_property) {
        }
        /*
        GObjectClass *klass = G_OBJECT_CLASS(&php_gobject_object_class);
        klass->set_property(object, property_id, value, pspec);
        //g_print(" %d; %d\n", *minimum_width, *natural_width);
        */
    }

}


static void
php_gobject_object_install_override(zend_function *f, GTypeClass *klass, zend_string *context, zend_string *name)
{

    if(0==strcmp(name->val, "set_property")) {
        G_OBJECT_CLASS(klass)->set_property = php_gobject_object_override_set_property;
        //G_OBJECT_CLASS(&php_gobject_object_user_methods)->set_property = f;
    } else if(0==strcmp(name->val, "get_property")) {
        G_OBJECT_CLASS(klass)->get_property = php_gobject_object_override_get_property;
        //G_OBJECT_CLASS(&php_gobject_object_user_methods)->get_property = f;
    }
    //printf("  %s\n", g_type_name(klass->g_type));
    //printf("  %s\n", context->val);
    //printf("  %s\n", name->val);

    //GObjectClass *gobject_klass = g_type_class_peek(G_TYPE_OBJECT);
    //printf("  %s\n", g_type_name(k->g_type));
    /*
    GTypeClass *parent = klass;
    while(parent = g_type_class_peek_parent(parent)) {
        if (G_TYPE_FROM_CLASS(parent) != G_TYPE_OBJECT) {
            continue;
        }
        if(0==strcmp(name->val, "set_property")) {
            G_OBJECT_CLASS(klass)->set_property = php_gobject_class_set_property;
            printf("  '%s'\n", name->val);
        } else if(0==strcmp(name->val, "get_property")) {
            G_OBJECT_CLASS(klass)->get_property = php_gobject_class_get_property;
            printf("  %s\n", name->val);
        }
    }
    */


    // switch context
    // case GObject
    // case MyObject
         // switch name
         // case get_property
    // case GApplication
    // case GtkBox
    // case GtkWidget
    // case GtkWindow
}

static void php_gobject_object_intern_init(PhpGObjectObject *widget) {
}

static void
php_gobject_object_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
  PhpGObjectObject *obj = (PhpGObjectObject*)object;
  zend_object *zobject = g_object_get_data(obj, "zend_object");
  zend_object *zobj = zobject ? zobject : pop_zend();// G_PARAM_CONSTRUCT

  if (zobj) {
      zend_string *prop_name = zend_string_init(pspec->name, strlen(pspec->name), 0);

      zval zvalue; ZVAL_LONG(&zvalue, g_value_get_uint(value));
      zend_std_write_property(zobj, prop_name, &zvalue, NULL);

      zend_string_release(prop_name);
  }
  //G_OBJECT_CLASS(&php_gobject_object_class)->set_property(object, prop_id, value, pspec);
}

static void
php_gobject_object_get_property (GObject    *object,
                          guint       prop_id,
                          GValue     *value,
                          GParamSpec *pspec)
{
    PhpGObjectObject *obj = (PhpGObjectObject*)object;

  switch (prop_id)
    {
    case 1:
      g_value_set_double (value, 1.1/*file->autosave_frequency*/);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void php_gobject_object_intern_class_init(PhpGObjectObjectClass *klass) {

   GObjectClass *gobject_class;
   //GtkWidgetClass *w_class;

   gobject_class = G_OBJECT_CLASS(klass);
   //w_class = GTK_WIDGET_CLASS(klass);

   /* Override widget class methods */
   //w_class->realize = my_widget_realize;
   //w_class->size_allocate = my_widget_size_allocate;
   //w_class->draw = my_widget_draw;


   ///memcpy(g_class, &php_gobject_object_class, sizeof(PhpGObjectObjectClass));
   // mem copy GObjectClass => PhpGObjectObjectClass *klass
   //g_class->set_property = php_gobject_object_set_property;// if @override
   //g_class->get_property = php_gobject_object_get_property;

   // For further use
   PhpGObjectObjectClass *override_klass = &php_gobject_object_class;
   GObjectClass *gobject_klass = g_type_class_peek(G_TYPE_OBJECT);
   if (override_klass->parent_class.g_type_class.g_type==G_TYPE_INVALID) {
       memcpy(override_klass, gobject_klass, sizeof(GObjectClass));
   }

   klass->changed = php_gobject_object_changed;// pour les callback

   gobject_class->set_property = php_gobject_object_set_property;
   gobject_class->get_property = php_gobject_object_get_property;
   /* Install property */

   //g_object_class_install_property(g_class, P_PERCENT, pspec);

   /* Add private data */
   //g_type_class_add_private(g_class, sizeof(MyCpuPrivate));
}



static GType
php_gobject_object_get_type (const char *qname, GType parent_type)
{
    /*
    gpointer type_id = g_hash_table_lookup(php_gobject_object_classes, key);
    //gsize g_define_type_id__volatile = GPOINTER_TO_SIZE(type_id);
    if (type_id!=NULL) {
        g_print("Error: unexpected case\n");
    }
    */

    gsize id = 0;

  if (g_once_init_enter (&id))
    {
#if 1
      GType g_define_type_id =
        g_type_register_static_simple (parent_type,
                                       g_intern_static_string (qname),
                                       sizeof (PhpGObjectObjectClass),
                                       (GClassInitFunc)(void (*)(void)) php_gobject_object_intern_class_init,
                                       sizeof (PhpGObjectObject),
                                       (GInstanceInitFunc)(void (*)(void)) php_gobject_object_intern_init,
                                       (GTypeFlags) 0);
#else
      GType g_define_type_id =
        g_type_register_dynamic		(parent,
                           g_intern_static_string (key),
                           /*GTypePlugin		    *plugin*/0,
                           (GTypeFlags) 0);
#endif
        {
          /* custom code follows */
          /* following custom code */
        }
        g_once_init_leave (&id, g_define_type_id);
    }

    /*
     * g_hash_table_insert(php_gobject_object_classes, key, GSIZE_TO_POINTER(id));
     */
    return id;
}

static GTypeClass *klasses[] = {};

GType
php_gobject_object_create_type (zend_class_entry *class_type, GType parent)
{
    //char *name = "All-MyObject";
    const char *name = class_type->name->val;
    GType type = php_gobject_object_get_type(name, parent);


    GObject *inst = g_object_new(type, NULL);g_object_unref(inst);// fix: if(NULL==klass)
    GTypeClass *klass = g_type_class_peek(type);
    if (NULL==klass) {
        klass = g_type_class_ref(type);// need g_type_class_unref(klass)
        printf("Warning : memory leaks\n");
        //return G_TYPE_INVALID;
    }

    //ZEND_HASH_FOREACH_PTR(&class_type->attributes, c) {} ZEND_HASH_FOREACH_END();

    zend_property_info *prop_info;
    zend_string *key;
    zval *prop;
    ZEND_HASH_FOREACH_STR_KEY_PTR(&class_type->properties_info, key, prop_info) {
        prop = &class_type->default_properties_table[OBJ_PROP_TO_NUM(prop_info->offset)];
        if (NULL!=prop_info->doc_comment) {
            //if not static => prop_info->flags & ZEND_ACC_STATIC == 0
            php_doc_comment *comment;
            if (comment = php_doc_comment_parse(prop_info->doc_comment->val, 0)) {
                ///printf("properties_table parser SUCCES\n");

                php_doc_tag *tag;
                zend_array *tags = &comment->tags;
                char *names[] = {
                    "g_param_spec_boolean",
                    "g_param_spec_char",
                    "g_param_spec_uchar",
                    "g_param_spec_int",
                    "g_param_spec_uint",
                    "g_param_spec_long",
                    "g_param_spec_ulong",
                    "g_param_spec_int64u",
                    "g_param_spec_int64",
                    "g_param_spec_float",
                    "g_param_spec_double",
                    "g_param_spec_enum",
                    "g_param_spec_flags",
                    "g_param_spec_string",
                    "g_param_spec_param",
                    "g_param_spec_boxed",
                    "g_param_spec_pointer",
                    "g_param_spec_object",
                    "g_param_spec_unichar",
                    "g_param_spec_value_array",
                    "g_param_spec_override",
                    "g_param_spec_gtype",
                    "g_param_spec_variant",
                    NULL
                };
                tags = php_doc_comment_get_tags_by_names(comment, names);
                if(zend_array_count(tags)>1) {
                    php_printf("TODO: Error, multiple definition of @g_param_spec_[type] in file ...\n");
                } else {
                    ZEND_HASH_FOREACH_PTR(tags, tag) {
                        int id = php_gobject_object_install_property(klass, tag);
                    } ZEND_HASH_FOREACH_END();
                }
                zend_hash_destroy(tags);
                FREE_HASHTABLE(tags);


                zval val; ZVAL_PTR(&val, comment);// coz zend_hash_init(, pDestroy, )
                php_doc_comment_free(&val);
            }

        }
    } ZEND_HASH_FOREACH_END();

    /*
    for(int i=0; i<class_type->default_properties_count; i++) {
        zval *v = &class_type->default_properties_table[i];
        //printf("var %d\n", );//Z_TYPE(v->value) IS_LONG
    };
    */

    zend_function *f=0;
    ZEND_HASH_FOREACH_PTR(&class_type->function_table, f) {
        if (f->type == ZEND_USER_FUNCTION & NULL!=f->op_array.doc_comment) {
            /**/
            php_doc_comment *comment;
            if (comment = php_doc_comment_parse(f->op_array.doc_comment->val, 0)) {
                printf("function_table parser SUCCES\n");
                php_doc_tag *tag;
                zend_array *tags = &comment->tags;
                ZEND_HASH_FOREACH_PTR(tags, tag) {
                    if (0==strcmp(tag->name->val, "g_override")) {
                        char *end;
                        php_doc_callable *cb = 0;
                        if(cb = php_doc_callable_parse(tag->description->val, &end)) {
                            php_gobject_object_install_override(f, klass, cb->context, cb->name);
                            php_doc_callable_free(cb);
                        }
                    }
                } ZEND_HASH_FOREACH_END();

                zval val; ZVAL_PTR(&val, comment);// coz zend_hash_init(, pDestroy, )
                php_doc_comment_free(&val);
            }

            /**/
        }
    } ZEND_HASH_FOREACH_END();



    zend_class_constant *c;

    unsigned int i = 0;

    ZEND_HASH_FOREACH_PTR(&class_type->constants_table, c) {
        // switch c->attributs
        if(c->doc_comment) {
            ///php_printf("    %s\n", c->doc_comment->val);

            // @extends GtkWidgetClass.draw
            // @override GtkWidget::draw
            // @g_signal_new

            php_doc_comment *comment;
            if (comment= php_doc_comment_parse(c->doc_comment->val, 0)) {
                /// zend_array *tags = php_doc_comment_get_tags_by_name(comment, "g_param_spec_uint");
                /// ZEND_HASH_FOREACH_PTR(tags, tag) {
                /// } ZEND_HASH_FOREACH_END();

                php_doc_tag *tag;
                zend_array *tags = &comment->tags;
                /*
                ZEND_HASH_FOREACH_PTR(tags, tag) {
                    php_printf("@%s\n", tag->name->val);
                } ZEND_HASH_FOREACH_END();
                */


                tags = php_doc_comment_get_tags_by_name(comment, "g_signal_new");
                ZEND_HASH_FOREACH_PTR(tags, tag) {
                    i=php_gobject_object_install_signal(type, tag);
                } ZEND_HASH_FOREACH_END();


                zend_hash_destroy(tags);
                FREE_HASHTABLE(tags);

                // else

                char *names[] = {
                    "g_param_spec_boolean",
                    "g_param_spec_char",
                    "g_param_spec_uchar",
                    "g_param_spec_int",
                    "g_param_spec_uint",
                    "g_param_spec_long",
                    "g_param_spec_ulong",
                    "g_param_spec_int64u",
                    "g_param_spec_int64",
                    "g_param_spec_float",
                    "g_param_spec_double",
                    "g_param_spec_enum",
                    "g_param_spec_flags",
                    "g_param_spec_string",
                    "g_param_spec_param",
                    "g_param_spec_boxed",
                    "g_param_spec_pointer",
                    "g_param_spec_object",
                    "g_param_spec_unichar",
                    "g_param_spec_value_array",
                    "g_param_spec_override",
                    "g_param_spec_gtype",
                    "g_param_spec_variant",
                    NULL
                };
                tags = php_doc_comment_get_tags_by_names(comment, names);
                if(zend_array_count(tags)>1) {
                    php_printf("TODO: Error, multiple definition of @g_param_spec_[type] in file ...\n");
                } else {
                    ZEND_HASH_FOREACH_PTR(tags, tag) {
                        i=php_gobject_object_install_property(klass, tag);
                    } ZEND_HASH_FOREACH_END();
                }
                zend_hash_destroy(tags);
                FREE_HASHTABLE(tags);


                char *style_properties[] = {
                    "g_param_spec_boolean",
                    "g_param_spec_gtype",
                    "g_param_spec_variant",
                    NULL
                };
                //tags = php_doc_comment_get_tags_by_names(comment, ['@style']);
                //tags = php_doc_comment_get_tags_by_names(comment, style_properties);
                ///ZEND_HASH_FOREACH_PTR(tags, tag) {
                //    i=php_gobject_object_install_style_property(type, tag);
                ///} ZEND_HASH_FOREACH_END();

                zval val; ZVAL_PTR(&val, comment);// coz zend_hash_init(, pDestroy, )
                php_doc_comment_free(&val);

                ///printf("constants_table parser SUCCES\n");
            } else {
                printf("constants_table parser FAILLED\n");
            }

        } else {
            ///printf("No doc_comment for constants_table\n");
        }
        //php_printf("%p: %p\n", c->ce, class_type);
        //php_printf("%d\n", c->value.value.lval);
        if(i) ZVAL_LONG(&c->value, i);// const CHANGED = g_signal_unique_id;

        //ZVAL_LONG(&c->value, 5);
        /*
        if (c->ce == ce) {
            zval_ptr_dtor_nogc(&c->value);
            if (c->doc_comment) {
                zend_string_release_ex(c->doc_comment, 0);
            }
            if (c->attributes) {
                zend_hash_release(c->attributes);
            }
        }
        */
    } ZEND_HASH_FOREACH_END();


    return type;
}

#endif

zend_function*
php_gobject_object_get_user_method(zend_object *zobject, char *name)// "GObjectClass.get_property"
{
    //zend_get_user_call_function(object->ce, function_name);

    zval ptr;
    php_doc_comment *doc_comment;
    php_doc_callable *cb_name = php_doc_callable_parse(name, NULL);
    php_doc_callable *cb = 0;
    zend_function *override_func=NULL;

    zend_class_entry *top = zobject->ce;//MyObject
    zend_class_entry *base = php_gobject_object_class_entry;//GObject
    while (top) {
        zend_function *func;
        zend_string *key;
        ZEND_HASH_FOREACH_STR_KEY_PTR(&top->function_table, key, func) {
            if (func->type == ZEND_USER_FUNCTION & NULL!=func->op_array.doc_comment) {
                //g_print("%s\n", func->op_array.doc_comment->val);
                //g_print("function %s - %s\n", key->val, func->common.function_name->val);
                char *str = func->op_array.doc_comment->val;
                doc_comment = php_doc_comment_parse(str, NULL);
                ZVAL_PTR(&ptr, doc_comment);
                zend_array *tags = php_doc_comment_get_tags_by_name(doc_comment, "g_override");
                php_doc_tag *tag;
                ZEND_HASH_FOREACH_PTR(tags, tag) {
                    cb = 0;
                    if(cb = php_doc_callable_parse(tag->description->val, NULL)) {// @override GObjectClass.get_property
                        //printf("\t>%s\n", cb->context->val);// "GObjectClass"
                        //printf("\t>%s\n", cb->name->val);// "get_property"
                        if (0==g_strcmp0(cb->context->val, cb_name->context->val)
                         && 0==g_strcmp0(cb->name->val, cb_name->name->val)
                        ) {
                            override_func = func;
                        }
                        php_doc_callable_free(cb);
                    }

                    if (override_func) {
                        break;
                    }
                } ZEND_HASH_FOREACH_END();
                php_doc_comment_free(&ptr);

                zend_hash_destroy(tags);
                FREE_HASHTABLE(tags);

                if (override_func) {
                    break;
                }

            }
        } ZEND_HASH_FOREACH_END();

        break;
        top = top->parent;
        if (top==base)
            break;
    }
    if (cb_name) {
        php_doc_callable_free(cb_name);
    }
    return override_func;
}
