# TODO

This file show all technical debt.
By continuously improving the design of code, we make it easier and easier to work with.

## Priority

+TODO: Rename ext/gtk => ext/gtkml


+TODO: fix g_propagate_error
+TODO: php_gobject/signal.c( each parametre type need to be implemented: GParam, GdkEvent)

+TODO: implement => php_glib/hash-table.c and g_hash_table_iter
+TODO:              php_gio/application.c (GApplication)
+TODO:              php_gmodule/module.c  (GModule)
+TODO: Implement unset($list[0]);
+TODO: Fix g_propagate_prefixed_error, g_propagate_error
       $src = zval{php_glib_error} has it's own ptr set to null,
       but not released so we can do $src->message="msg"; Or ptr is null


<?php
require_once("Gtk.php");// Wrapper get latest
// set_include_path "gtk+-4.0"
require_once("gtk+-4.0/Gtk/Widget.php");
require_once("gtk+-3.0/Gtk/Widget.php");
require_once("gtk+-2.0/Gtk/Widget.php");

use VendorGnome\Gtk\Grid;// Wrapper --with-gtk=VendorGnome,4
use Gtk\Window;// Wrapper --with-gtk=4

Compatibility PHP5 -> PHP8




create config.nice


## Refactoring
- Readability
  [ ] Rename ext/gtk by ext/gtkml
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
  [ ] Create ext/glib, ext/gtk, ext/cairo, ext/pango
  Find usage:
  ```
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




