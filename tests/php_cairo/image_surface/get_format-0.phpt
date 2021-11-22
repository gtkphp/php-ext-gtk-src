--TEST--
05-0-0 : Check for cairo_image_surface_get_format
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$format = cairo_image_surface_get_format ($surface);
var_dump($format==CAIRO_FORMAT_ARGB32);

?>
--EXPECT--
bool(true)
