--TEST--
05-0-0 : Check for cairo_image_surface_get_width
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
cairo_surface_set_device_scale ($surface, 10, 20);
cairo_surface_get_device_scale ($surface, $x, $y);
var_dump($x==10);
var_dump($y==20);

?>
--EXPECT--
bool(true)
bool(true)
