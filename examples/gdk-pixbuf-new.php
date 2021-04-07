<?php

if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

$error = null;
$pixbuf = gdk_pixbuf_new_from_file("/home/dev/Images/logo-6.png", $error);
var_dump($pixbuf);
