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

g_set_error($error, my_quark(), 403, "'%s' do not exist", "Application", null);

g_propagate_prefixed_error($err, $error, "GTKML:%s:", "GLIB", null);

var_dump($err);


//confirm_gtk_compiled("");
