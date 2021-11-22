# TODO

This file show all technical debt.
By continuously improving the design of code, we make it easier and easier to work with.
Service : Support, consulting, training, certification

## Notice for Generator
gtk_cairo_transform_to_window is part of GtkWidget( make a strategy to clean object method/function)

## Documentation
https://github.com/ToshioCP/Gobject-tutorial/blob/main/gfm/sec4.md


## Priority

TODO: safe-thread PHP_GOBJECT_DEFINE_TYPE do wait while(!g_array_find())
TODO: PHP_FUNCTION(g_signal_emit_by_name)
TODO: php_gobject_signal_connect utilise g_cclosure_new au lieu de g_cclosure_new_swap
Pourquoi le callback est appelé deux fois ? ( la derniere sans paramètre)

TODO: php_gtk_widget_free_object( ref_sink vs ref_counted)
TODO: php_gtk_widget_class_init( use user_function)

NB: Two strategy for implementing G Structurs
    - Use ptr to GStructure
    - Use own ZendObject Structure to reflet implementation of G and create/copy/free function

TODO: remove php_gobject_signal{property_name}
TODO: remove occurence zend_internal_type_error
TODO: php_gobject_get_user_method
TODO: check #define ZOBJ_IS_PHP_G***(obj) use instanceof_function( see php_gtk/widget.h)
TODO: fix -Warning, memory leaks

TODO: signal
+ modifier php_gobject_object_marshaler_INT__POINTER


+ tester le retour du callback( g_signal_emit(..., &ret)

+ g_signal_new

+ g_object_connect
   -> php_g_signal_connect_object
   normalize_signal_detail "signal::notify::property"

+ php_doc_expression_t and eval
+ php_doc_string_t, php_doc_array_t and php_doc_json_t

+ simple php_doc_tag_t + description = bug
+ FIXME : @style "Ma description" generate corruption memory

+ TODO : php_gobject/paramspecs.h make all types
+ TODO : php_gobject/value.h make all types

TODO: test
 - scaled_font

TODO: cairo_raster_source_pattern_set_finish, probleme avec le callback qui est efree(intern->callback); dans php_cairo_pattern_t_free_object avant que set_finish soit appelé
TODO: dans les fonction cairo_surface, si : undefinied variable $surface: Le programme s'est terminé subitement.

TODO: in php_cairo/path ::properties_ptr_ptr => get status|num_data forbiden / readonly

TODO: do not use zend_objects_new, use php_my_object_new instead or ce->create_object(ce)

cairo_text_path use utf-8 ; what need to do ?

TODO: Fix Zend
$x = 5.0;// bug if $x=5
$y = 3.0;
cairo_user_to_device_distance($cr, $x, $y);


In php_glist use Z_SET_REFCOUNT/Z_DELREF_P/Z_ADDREF_P/Z_REFCOUNT_P

- **TODO**: php_gtk/widget.c : php_gtk_widget_register
- **TODO**: add signal destroy on each widget to know if wee need to free widget in php_gtk_**_free_object
- **TODO**: php_cairo/path.c : #if IS_IMPLEMENTED (cairo_glyph_path)

- **TODO**: Implement php_cairo/cairo.c : let override GtkWidgetClass.draw
- **TODO**: gtkml/ zend extension ? register_class('<element>', class_name);
- **TODO**: gtkml/ parser remove double ws, implemente signals attr; end_element() => top of the tree

- **TODO**: use ZEND_PARSE_PARAMETERS_START insteanof zend_parse
            see PHP_FUNCTION(cairo_matrix_init)

- **TODO**: implement => php_glib/hash-table.c and g_hash_table_iter
- **TODO**:               php_gio/application.c (GApplication)
- **TODO**:               php_gmodule/module.c  (GModule)
- **TODO**:               php_gdk/window.c
- **TODO**:               php_doc/scanner.c ( EXPORT_API fonction for php user?)
- **TODO**: php_gobject/signal.c( each parametre type need to be implemented: GParam, GdkEvent)
- **TODO**: php_glib/list => Implement unset($list[0]);
- **TODO**:                  continue g_list_copy
- **TODO**: improve hineritance( see php_gtk/button, php_gobject/object)
- **TODO**: CairoMatrix => binarysearch(8 max) / perfect hash for G properties

- **TODO**: Rename ext/gtk => ext/gtkml


- **TODO**: fix g_propagate_error
- **TODO**: Fix g_propagate_prefixed_error, g_propagate_error
>       $src = zval{php_glib_error} has it's own ptr set to null,
>       but not released so we can do $src->message="msg"; Or ptr is null


- **TODO**: add zend_module_dep

```
<?php
require_once("Gtk.php");// Wrapper get latest
// set_include_path "gtk+-4.0"
require_once("gtk+-4.0/Gtk/Widget.php");
require_once("gtk+-3.0/Gtk/Widget.php");
require_once("gtk+-2.0/Gtk/Widget.php");

use VendorGnome\Gtk\Grid;// Wrapper --with-gtk=VendorGnome,4
use Gtk\Window;// Wrapper --with-gtk=4
```

Compatibility PHP5 -> PHP8




create config.nice


## Refactoring
- Readability
> Create php API files
> Create php wrapper( Gtkmm)
- Code smell
- Code pooling
- Reduced complexity
- Performance
- Algoritme
- Less memory

## Design Pattern
- SOLID
- GANG4
- Injection

## Namaing
- standardized
- concise, well-named, single-purpose methods.

## Architecture 

- Server-Cache
- Client-Cache
- Seperate responsability
  - [ ] Rename ext/gtk by ext/gtkml
  - [ ] ext/glib( gobject, gio, g)
  - [ ] ext/gtk( gdk, gsk, atk)
  - [ ] ext/cairo( cairo-gobject)
  - [ ] ext/pango
  - [ ] Find usage

```
php-src/
  + ext/
    + gui/
    + gui-ui/
    + gui-gtk-2/
    + gui-gtk-3/
       + --with-gtk-3=Gnome,shared
    + gui-gtk-4/

  --enable-gui --with-gtk=yes|no|3,Gnome,static

  --with-glib=static
      --with-gobject=static
      --with-gio=static

  --with-pango=static
      --with-pango-gobject=static
      --with-cairo=static

  --with-gtk=static
      --with-atk=static
      --with-gdk-pixbuf=static
      --with-gdk=static


  --with-gtk=Gnome,3,shared


  --with-gtk=shared
  --with-gtk=static
  --with-gtk=Gnome,4,shared => libgtk-4.so
  --with-gtk=Gtk3,3,shared
  --with-gtk=2,shared
```
## Bugs
Potential bugs

## Vulnerabilities 
Potential hacks


## Testing
Add tests
- Unit
- Fonctional
- End-to-end




