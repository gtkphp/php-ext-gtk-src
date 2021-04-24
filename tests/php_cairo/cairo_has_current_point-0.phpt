--TEST--
05-0-0 : Check for cairo_has_current_point
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

var_dump(cairo_has_current_point($cr));

cairo_rectangle ($cr, 0.0, 0.0, 21.0, 29.7);

var_dump(cairo_has_current_point($cr));

?>
--EXPECT--
bool(false)
bool(true)
