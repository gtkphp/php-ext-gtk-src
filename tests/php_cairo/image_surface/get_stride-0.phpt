--TEST--
05-0-0 : Check for cairo_image_surface_get_stride
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$stride = cairo_image_surface_get_stride ($surface);
var_dump($stride==(250*4));

?>
--EXPECT--
bool(true)
