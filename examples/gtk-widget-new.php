<?php

if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

function my_callback($object, $param, $user_data){
}

function my_destroy($object, $param, $user_data){
}

$widget = new GtkWidget();
$container = new GtkContainer();
$bin = new GtkBin();
$window = new GtkWindow();

gtk_container_add($window, $widget);
gtk_widget_show_all($window);


var_dump($widget);
var_dump($container);
var_dump($bin);
var_dump($window);

g_object_connect($window,
                 "notify::title", "my_callback", NULL,
                 NULL);
