<?php

//namespace Hello\World;

if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

class MyWidget extends \GtkWidget {
    /**
     * @override GtkWidget::draw
     */
    protected function draw(cairo_t $cr) {
    }
}

function my_callback($object, $param, $user_data){
}

function my_destroy($object, $param, $user_data){
}

\gtk_init($argc, $argv);

$widget = new MyWidget();
$container = new \GtkContainer();
$bin = new \GtkBin();
$window = new \GtkWindow();

\gtk_container_add($window, $widget);
\gtk_widget_show_all($window);


var_dump($widget);
var_dump($container);
var_dump($bin);
var_dump($window);

\g_signal_connect($window, "destroy", "\gtk_main_quit", NULL);

\gtk_main();
