# TODO

This file show all technical debt.
By continuously improving the design of code, we make it easier and easier to work with.

## Priority

Donner les liens
- musique quelque chose viens de tomber
- enfant de la lune( comic)


+TODO: refactor ghashtable, certenly leaks
+TODO: gtk.c PHP_MINIT_FUNCTION_G_LIST
+TODO: Implement unset($list[0]);


--with-gtk=shared
--with-gtk=static
--with-gtk=Gnome,4,shared => libgtk-4.so
--with-gtk=Gtk3,3,shared
--with-gtk=2,shared

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




