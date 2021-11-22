--TEST--
05-0-0 : Check for cairo_matrix_init
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

$pattern = cairo_pattern_create_rgb (1.0, 0.0, 0.0);// red
cairo_rectangle($cr, 0.0, 0.0, 50.0, 30.0);
cairo_set_source($cr, $pattern);
cairo_fill($cr);

$status = cairo_status($cr);

var_dump($status==CAIRO_STATUS_SUCCESS);

?>
--EXPECT--
bool(true)
