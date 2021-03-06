# TODO

This file show all technical debt.
By continuously improving the design of code, we make it easier and easier to work with.

## Priority

--with-gtk=all
--with-gtk=4,3
--with-gtk=3
--with-gtk=2
<?php
require_once("Gtk.php");// get latest
// set_include_path "gtk+-4.0"
require_once("gtk+-4.0/Gtk/Widget.php");
require_once("gtk+-3.0/Gtk/Widget.php");
require_once("gtk+-2.0/Gtk/Widget.php");

use VendorGnome\Gtk\Grid;// Wrapper --with-gtk=VendorGnome,4
use Gtk\Window;// Wrapper --with-gtk=4


Implemente g_hash_table, g_hash_table_iter, g_hash_func/g_equal_func
Compatibility PHP5 -> PHP8

// maybe is better to Z_ADDREF_P();
zval *val = emalloc(sizeof(zval));
ZVAL_COPY(val, data);
// efree();

+ REFACTOR: ZOBJ_GET_PHP_G_LIST by Z_OBJ_PHP_G_LIST_P ?( preferable work with pointer)


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




