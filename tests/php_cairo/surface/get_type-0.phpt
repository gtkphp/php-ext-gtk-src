--TEST--
05-0-0 : Check for cairo_image_surface_get_width
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$type = cairo_surface_get_type ($surface);
var_dump($type==CAIRO_SURFACE_TYPE_IMAGE);

?>
--EXPECT--
bool(true)
