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

//$error=new GError();// Must be null


g_set_error($error, my_quark(), 404, "'%s' invalid", "Application", null);
g_prefix_error($error, "GTK:", null);
g_prefix_error($error, "GNOME:", null);

var_dump($error);


//confirm_gtk_compiled("");
