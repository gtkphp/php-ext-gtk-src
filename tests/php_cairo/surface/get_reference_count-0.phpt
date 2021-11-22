--TEST--
05-0-0 : Check for cairo_surface_get_reference_count
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$reference = cairo_surface_get_reference_count ($surface);
var_dump($reference==1);

?>
--EXPECT--
bool(true)
