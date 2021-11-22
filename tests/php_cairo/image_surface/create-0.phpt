--TEST--
05-0-0 : Check for cairo_image_surface_create
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$status = cairo_surface_status ($surface);
var_dump($status==CAIRO_STATUS_SUCCESS);


?>
--EXPECT--

bool(true)
