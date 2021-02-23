# PHP bindings for GTK+
The GTK+PHP project provides php bindings for GTK+4,3,2.
It is intended for creating standalone GUI applications.

Partial binding support for the following libraries is currently implemented:

- GTK
- GLib
- Pango
- Cairo

Care has been taken for memory management to work seamlessly with php's
garbage collector without the need to use or understand GObject's
floating references.

For better understanding see
[package reference documation](https://gtk.php.net/gtk3?tab=doc)


## Sample Use

The following example can be found in [Examples](https://github.com/gtkphp/hello-world-examples/).

```
<?php

Gtk\Init($argc, $argv);

$window = new Gtk\Window;
G\Signal\Connect($window, "destroy", "Gtk\MainQuit", Null);
$window->showAll();

Gtk\Main();
```

## Documentation


## Requirements


## Installation

## Testing


## TODO

- Add bindings for all of GTK functions
- Add tests for each implemented binding

## License

GPL-3.0
