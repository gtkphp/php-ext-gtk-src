<?php

//namespace Hello\World;

if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

confirm_gtk_compiled("");

//$allocation = new GdkRectangle();
//var_dump($allocation);

/*
class GlibObject extends GObject {
}

$obj = new GlibObject();
var_dump($obj);
*/
