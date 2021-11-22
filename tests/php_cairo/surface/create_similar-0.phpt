--TEST--
05-0-0 : Check for cairo_image_surface_get_width
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$target = cairo_surface_create_similar ($surface, CAIRO_CONTENT_COLOR_ALPHA, 500, 500);
var_dump($target instanceof cairo_surface_t);

?>
--EXPECT--
bool(true)
