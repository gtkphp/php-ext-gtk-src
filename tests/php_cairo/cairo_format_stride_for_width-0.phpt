--TEST--
05-0-0 : Check for cairo_image_surface_get_width
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$stride = cairo_format_stride_for_width (CAIRO_FORMAT_ARGB32, 1);
var_dump($stride==4);

?>
--EXPECT--
bool(true)
