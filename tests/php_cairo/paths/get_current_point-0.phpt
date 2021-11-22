--TEST--
05-0-0 : Check for cairo_get_current_point
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

cairo_rectangle ($cr, 0.0, 0.0, 21.0, 29.7);
cairo_move_to ($cr, 2.0, 2.0);

var_dump(cairo_has_current_point($cr));
cairo_get_current_point($cr, $x, $y);
var_dump($x, $y);

?>
--EXPECT--
bool(true)
float(2)
float(2)
