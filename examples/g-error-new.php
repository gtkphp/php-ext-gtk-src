<?php

if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);


function my_quark():int {
    static $q=null;
    if (!$q)
        $q = g_quark_from_static_string ("MY");
    return $q;
}

//$error = new GError();
$error = g_error_new (my_quark(), 404, "'%s' not found near line %d", "Application", 23, NULL);

var_dump($error);





/*
$quark = g_quark_from_static_string ("string");
var_dump($quark);
$string = g_quark_to_string ($quark);
var_dump($string);
*/
