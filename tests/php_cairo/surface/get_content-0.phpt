--TEST--
05-0-0 : Check for cairo_surface_get_content
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$content = cairo_surface_get_content ($surface);
var_dump($content==CAIRO_CONTENT_COLOR_ALPHA);

?>
--EXPECT--
bool(true)
