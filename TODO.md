# TODO

This file show all technical debt.
By continuously improving the design of code, we make it easier and easier to work with.

## Priority

Donner les liens
- musique quelque chose viens de tomber
- enfant de la lune( comic)

ext/gtk => ext/gtkml

+TODO(to GList): php_gtk/container.c => gtk_container_get_children():GList
 Implement GArray(Pair<GObject|Boxed, zend_object>) binarysearch
 When signal is emited, callback need to retrive the good (Object)#id
 associate zend_object with GObject, and so on
Quicksort algorithm:
https://code.woboq.org/userspace/glibc/stdlib/qsort.c.html
Binary search algorithm:
https://en.wikipedia.org/wiki/Binary_search_algorithm#Syntax_difficulties
GArray<zend_object, GObject>

+TODO: php_gobject/signal.c( each parametre type need to be implemented)


+TODO: php_g/g-hash-table.c => php_glib/hash-table.c (GHashTable)
+TODO:                         php_gio/application.c (GApplication)
+TODO:                         php_gmodule/module.c  (GModule)
+TODO: Implement unset($list[0]);


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

see /home/dev/Projects/php-ubuntu/ext/gtkml/php_gobject/signal.h

<?php
require_once("Gtk.php");// Wrapper get latest
// set_include_path "gtk+-4.0"
require_once("gtk+-4.0/Gtk/Widget.php");
require_once("gtk+-3.0/Gtk/Widget.php");
require_once("gtk+-2.0/Gtk/Widget.php");

use VendorGnome\Gtk\Grid;// Wrapper --with-gtk=VendorGnome,4
use Gtk\Window;// Wrapper --with-gtk=4


Implemente g_hash_table, g_hash_table_iter, g_hash_func/g_equal_func
Compatibility PHP5 -> PHP8


+ REFACTOR: ZOBJ_GET_PHP_G_LIST by Z_OBJ_PHP_G_LIST_P ?( preferable work with pointer)
+ REFACTOR: ZVAL_GET_PHP_G_LIST by Z_PHP_G_LIST_P ?


create config.nice


## Refactoring
- Readability
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

## Bugs
Potential bugs

## Vulnerabilities 
Potential hacks


## Testing
Add tests
- Unit
- Fonctional
- End-to-end




