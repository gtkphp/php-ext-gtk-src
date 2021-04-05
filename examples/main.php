<?php


if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);



/*
require_once("Window.php");
//include "Gtkmm.php";


//use Gtk\Orientation{const HORIZONTAL};
use Gtk\{function Init, function Main, const ORIENTATION_HORIZONTAL};
use Gtk\Window;
use Gtk\Box;
use Gtk\Button;


class MyWin extends Window {
    #[Signal('accept', run: 'LAST', slot:function(int, string):bool{})]
    const SIGNAL_ACCEPT=0;
    function __construct() {
        parent::__construct();
        $box = new Box(ORIENTATION_HORIZONTAL, 0);

        $btnAccept = new Button("Valide");
        $btnCancel = new Button("Cancel");

        $box->add($btnAccept);
        $box->add($btnCancel);

        $this->add($box);

        $this->showAll();
    }

    #[Override('GtkWidget::draw')]
    function draw() {
    }

    #[Action('do')]
    function close() {
    }
}

Init($argc, $argv);
$win = new MyWin();
//$win->connect('accept', function($win){echo "Thank you\n";});
//$win->emit('accept');
Main();


*//*


Init($argc, $argv);

$window = new Window();

//G\Signal\Connect($window, "destroy", "on_quit", Null);
//g_signal_connect($window, "destroy", "on_quit", Null);

$box = new Box(ORIENTATION_HORIZONTAL, 0);

$button_a = new Button("Valide");
$button_b = new Button("Cancel");

$box->add($button_a);
$box->add($button_b);


$window->add($box);

$window->showAll();

Main();
*/




function on_add(GtkContainer $container, GtkWidget $widget, $user_data) {
    echo "on_add(".$widget->label.")\n";

    $children = gtk_container_get_children($container);

    //g_list_dump($children);
    //print_r((array)$children);
    for($it=$children; $it!=null; $it=$it->next) {
        $button = $it->data;
        var_dump($button->label);
    }

    g_list_free($children);// unset($children)
    // unset do zend_object_release();
    // but we whant to call dtor_object() wich call release
}

function on_quit(GtkWidget $object, $user_data) {
    gtk_main_quit();
}


gtk_init($argc, $argv);

$window = gtk_window_new();
g_signal_connect($window, "destroy", "on_quit", Null);

$box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
g_signal_connect($box, "add", "on_add", new StdClass());

$button_a = gtk_button_new_with_label("Valide");
$button_b = gtk_button_new_with_label("Cancel");
$button_c = gtk_button_new_with_label("Pause");

gtk_container_add($box, $button_a);
gtk_container_add($box, $button_b);
gtk_container_add($box, $button_c);

gtk_container_add($window, $box);

gtk_widget_show_all($window);



gtk_main();

