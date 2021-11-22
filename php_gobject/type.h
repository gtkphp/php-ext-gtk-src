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

#ifndef PHP_GOBJECT_TYPE_H
#define PHP_GOBJECT_TYPE_H


#define PHP_GOBJECT_DEFINE_TYPE(TN, t_n, T_P)			             PHP_GOBJECT_DEFINE_TYPE_EXTENDED (TN, t_n, T_P, 0, {})
#define PHP_GOBJECT_DEFINE_TYPE_EXTENDED(TN, t_n, T_P, _f_, _C_)	_PHP_GOBJECT_DEFINE_TYPE_EXTENDED_BEGIN (TN, t_n, T_P, _f_) {_C_;} _PHP_GOBJECT_DEFINE_TYPE_EXTENDED_END(t_n)

#define canonical_replace(name, search, replace) for(unsigned int i=0; name[i]!='\0'; i++){if (name[i]==search) name[i]=replace; }

#define _PHP_GOBJECT_DEFINE_TYPE_EXTENDED_ZTS(TypeName, type_name, TYPE_PARENT) \
\
typedef struct _pair_type_name_t { \
    GType type; \
    gchar *name; \
} pair_type_name_t; \
 \
static void type_name##_clear_func(gpointer       data) { \
    pair_type_name_t *elt = data; \
    if (elt && elt->name) { \
        g_free(elt->name); \
    } \
} \
 \
static GMutex  type_name##_once_mutex; \
static GCond   type_name##_once_cond; \
GArray *type_name##_once_init_array = NULL;/* Array of pair_type_name_t( Store a stack of GType==G_TYPE_INVALID)*/ \
 \
gboolean \
type_name##_once_init_enter (const char *name, GType *type) \
{ \
  pair_type_name_t pair = {G_TYPE_INVALID, NULL}; \
  gboolean need_init = TRUE; \
  g_mutex_lock (&type_name##_once_mutex); \
 \
  if (type_name##_once_init_array==NULL) { \
      type_name##_once_init_array = g_array_sized_new(FALSE, FALSE, sizeof(pair_type_name_t), 60); \
      g_array_set_clear_func(type_name##_once_init_array, type_name##_clear_func); \
      type_name##_once_init_array = g_array_append_val(type_name##_once_init_array, pair); \
      g_array_index(type_name##_once_init_array, pair_type_name_t, type_name##_once_init_array->len-1).type = G_TYPE_INVALID; \
      g_array_index(type_name##_once_init_array, pair_type_name_t, type_name##_once_init_array->len-1).name = g_strdup(name); \
      pair_type_name_t *elt = &g_array_index(type_name##_once_init_array, pair_type_name_t, type_name##_once_init_array->len-1); \
      need_init = TRUE; \
  } else { \
      for (int i=0; i<type_name##_once_init_array->len; i++) { \
          pair_type_name_t *pair = &g_array_index(type_name##_once_init_array, pair_type_name_t, i); \
          if (0==g_strcmp0(pair->name, name)) { \
              need_init = FALSE; /* occurence found */ \
              /*value_location = &pair->type;*/ \
              if (G_TYPE_INVALID!=type) { \
                  *type = pair->type; \
                  break; \
              } \
              do \
                g_cond_wait (&type_name##_once_cond, &type_name##_once_mutex);/* <<----- concurrent */ \
              while (G_TYPE_INVALID!=pair->type);/* if array realloc( append_val) pair poiter is out-of-memory */ \
              *type = pair->type;                /* todo: fix => redo the search                               */ \
 \
              break; \
          } \
      } \
      /* not found */ \
      if (need_init) { \
          /*if realloc( ex: 3 types remaind waiting)*/  \
          /*<<----------------------------------- $->data concurrent*/ \
          type_name##_once_init_array = g_array_append_val(type_name##_once_init_array, pair); \
          g_array_index(type_name##_once_init_array, pair_type_name_t, type_name##_once_init_array->len-1).type = G_TYPE_INVALID; \
          g_array_index(type_name##_once_init_array, pair_type_name_t, type_name##_once_init_array->len-1).name = g_strdup(name); \
          need_init = TRUE; \
      } \
 \
  } \
 \
  g_mutex_unlock (&type_name##_once_mutex); \
  return need_init; \
} \
 \
void \
type_name##_once_init_leave (const gchar *name, \
                                gsize result) \
{ \
  /* g_return_if_fail (value_location); */ \
  g_return_if_fail (result != G_TYPE_INVALID); \
 \
  for (int i=0; i<type_name##_once_init_array->len; i++) { \
      pair_type_name_t *pair = &g_array_index(type_name##_once_init_array, pair_type_name_t, i); \
      if (0==g_strcmp0(pair->name, name)) { \
          /* occurence found*/ \
          pair->type = result; \
          break; \
      } \
  } /* else error*/ \
 \
  g_mutex_lock (&type_name##_once_mutex); \
  /*g_return_if_fail (type_name##_once_init_array != NULL);*/ \
  /* type_name##_once_init_array = g_slist_remove (type_name##_once_init_array, (void*) value_location); */ \
  g_cond_broadcast (&type_name##_once_cond); \
  g_mutex_unlock (&type_name##_once_mutex); \
} \
\
GObject *type_name##_extends(type_name *zobject) \
{ \
    if (0==strcmp(g_type_name(TYPE_PARENT), zobject->std.ce->name->val)) { \
        push_zend(&zobject->std); \
        zobject->ptr = g_object_new(TYPE_PARENT, NULL); \
        g_object_set_data(G_OBJECT(zobject->ptr), "zend_object", &zobject->std); \
        return zobject->ptr; \
    } \
    char *name = g_strdup(zobject->std.ce->name->val); \
    canonical_replace(name, '\\', '_') \
 \
    GType type = g_type_from_name(name); \
    if (type==G_TYPE_INVALID) { \
 \
        push_zend(&zobject->std);/* used in get_property when G_PARAM_CONSTRUCT*/ \
        type = type_name##_get_type(name); \
        php_gobject_object_class_override(type, &zobject->std); \
        zobject->ptr = g_object_new(type, NULL); /*use gtk_widget_new() */ \
    } else { \
        push_zend(&zobject->std); \
        zobject->ptr = g_object_new(type, NULL); /*use like php_gtk_widget_new */ \
    } \
    g_object_set_data(G_OBJECT(zobject->ptr), "zend_object", &zobject->std); \
 \
    g_free(name); \
    return zobject->ptr; \
}



/* we need to have this macro under conditional expansion, as it references
 * a function that has been added in 2.38. see bug:
 * https://bugzilla.gnome.org/show_bug.cgi?id=703191
 */
#if GLIB_VERSION_MAX_ALLOWED >= GLIB_VERSION_2_38
#define _PHP_GOBJECT_DEFINE_TYPE_EXTENDED_CLASS_INIT(TypeName, type_name) \
static void     type_name##_class_intern_init (gpointer klass) \
{ \
  type_name##_parent_class = g_type_class_peek_parent (klass); \
  if (TypeName##_private_offset != 0) \
    g_type_class_adjust_private_offset (klass, &TypeName##_private_offset); \
  type_name##_class_init ((TypeName##Class*) klass); \
}

#else
#define _PHP_GOBJECT_DEFINE_TYPE_EXTENDED_CLASS_INIT(TypeName, type_name) \
static void     type_name##_class_intern_init (gpointer klass) \
{ \
  type_name##_parent_class = g_type_class_peek_parent (klass); \
  type_name##_class_init ((TypeName##Class*) klass); \
}
#endif /* GLIB_VERSION_MAX_ALLOWED >= GLIB_VERSION_2_38 */

/* Added for _PHP_GOBJECT_DEFINE_TYPE_EXTENDED_WITH_PRELUDE */
#define _PHP_GOBJECT_DEFINE_TYPE_EXTENDED_BEGIN_PRE(TypeName, type_name, TYPE_PARENT) \
\
static gpointer type_name##_parent_class = NULL; \
static gint     TypeName##_private_offset; \
 \
_PHP_GOBJECT_DEFINE_TYPE_EXTENDED_ZTS(TypeName, type_name, TYPE_PARENT) \
 \
_PHP_GOBJECT_DEFINE_TYPE_EXTENDED_CLASS_INIT(TypeName, type_name) \
\
G_GNUC_UNUSED \
static inline gpointer \
type_name##_get_instance_private (TypeName *self) \
{ \
  return (G_STRUCT_MEMBER_P (self, TypeName##_private_offset)); \
} \
\
GType \
type_name##_get_type (const char *name) \
{ \
  GType g_define_type_id = G_TYPE_INVALID; \
  /* Prelude goes here */

/* Added for _G_DEFINE_TYPE_EXTENDED_WITH_PRELUDE */
#define _PHP_GOBJECT_DEFINE_TYPE_EXTENDED_BEGIN_REGISTER(TypeName, type_name, TYPE_PARENT, flags) \
  if (type_name##_once_init_enter (name, &g_define_type_id))  \
    { \
      g_define_type_id = \
        g_type_register_static_simple (TYPE_PARENT, \
                                       g_intern_string (name), \
                                       sizeof (TypeName##Class), \
                                       (GClassInitFunc)(void (*)(void)) type_name##_class_intern_init, \
                                       sizeof (TypeName), \
                                       (GInstanceInitFunc)(void (*)(void)) type_name##_init, \
                                       (GTypeFlags) flags); \
      { /* custom code follows */

#define _PHP_GOBJECT_DEFINE_TYPE_EXTENDED_END(type_name)	\
        /* following custom code */	\
      } \
      type_name##_once_init_leave (name, g_define_type_id); \
    } \
  return g_define_type_id;	\
} /* closes type_name##_get_type() */


/* This was defined before we had G_DEFINE_TYPE_WITH_CODE_AND_PRELUDE, it's simplest
 * to keep it.
 */
#define _PHP_GOBJECT_DEFINE_TYPE_EXTENDED_BEGIN(TypeName, type_name, TYPE_PARENT, flags) \
  _PHP_GOBJECT_DEFINE_TYPE_EXTENDED_BEGIN_PRE(TypeName, type_name, TYPE_PARENT) \
  _PHP_GOBJECT_DEFINE_TYPE_EXTENDED_BEGIN_REGISTER(TypeName, type_name, TYPE_PARENT, flags) \


#endif	/* PHP_GOBJECT_TYPE_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
