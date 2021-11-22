--TEST--
05-0-0 : Check for cairo_image_surface_get_height
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$height = cairo_image_surface_get_height ($surface);
var_dump($height==80);

?>
--EXPECT--
bool(true)
