# TODO

This file show all technical debt.
By continuously improving the design of code, we make it easier and easier to work with.
Service : Support, consulting, training, certification

## Priority

TODO: do not use zend_objects_new, use php_object_new instead

cairo_text_path use utf-8 ; what need to do ?


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




