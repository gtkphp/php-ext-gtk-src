<?php

if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

function my_callback($object, $param, $user_data){
}

function my_destroy($object, $param, $user_data){
}

$object = new GObject();
g_object_connect($object,
                 "notify::title", "my_callback", NULL,
                 NULL);

$id = g_signal_connect_data($object, "notify::title", "my_callback", NULL, "my_destroy", 0);

var_dump($object);

//g_object_unref($object);

var_dump($object);
