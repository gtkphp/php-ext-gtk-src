--TEST--
05-0-0 : Check for cairo_matrix_init
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

$pattern = cairo_pattern_create_rgba (1.0, 0.0, 0.0, 0.5);// red
cairo_rectangle($cr, 0.0, 0.0, 50.0, 30.0);
cairo_set_source($cr, $pattern);
cairo_fill($cr);

$status = cairo_status($cr);

var_dump($status==CAIRO_STATUS_SUCCESS);

cairo_pattern_get_rgba ($pattern, $red, $green, $blue, $alpha);
var_dump($red, $green, $blue, $alpha);

?>
--EXPECT--
bool(true)
float(1)
float(0)
float(0)
float(0.5)
