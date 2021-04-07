<?php

namespace Gtk;

//define('Gtk\ORIENTATION_HORIZONTAL', \GTK_ORIENTATION_HORIZONTAL);
const ORIENTATION_HORIZONTAL = \GTK_ORIENTATION_HORIZONTAL;

function Init($argc, $argv) {
    \gtk_init();
}

trait __Widget {
    public function showAll() {
        \gtk_widget_show_all($this);
    }
}
class Widget extends \GtkWidget {use __Widget;}

trait __Container {
    use __Widget;
    public function add($widget) {
        \gtk_container_add($this, $widget);
    }
}
class Container extends \GtkContainer {use __Container;}

trait __Bin {
    use __Container;
}
class Bin extends \GtkBin {use __Bin;}

trait __Button {
    use __Bin;
    public function setLabel(string $label) {
        \gtk_button_set_label($this, $widget);
    }
}
class Button extends \GtkButton {
    use __Button;
}

trait __Box {
    use __Container;
}
class Box extends \GtkBox {use __Box;}

trait __Window {
    use __Bin;
}
class Window extends \GtkWindow {
    use __Window;
    public function __construct() {
        parent::__construct();
        g_signal_connect($this, "destroy", "gtk_main_quit", Null);
    }
}


function Main() {
    \gtk_main();
}

function MainQuit() {
    \gtk_main_quit();
}
