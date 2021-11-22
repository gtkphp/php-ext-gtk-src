--TEST--
05-0-0 : Check for cairo_matrix_init
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

$pattern = cairo_pattern_create_linear (0.0, 0.0, 100, 100.0);
cairo_pattern_add_color_stop_rgb ($pattern, 0.0, 1.0, 0.0, 0.0);
cairo_pattern_add_color_stop_rgba ($pattern, 1.0, 0.0, 0.0, 1.0, 1.0);


cairo_rectangle($cr, 0.0, 0.0, 50.0, 30.0);
cairo_set_source($cr, $pattern);
cairo_fill($cr);

$status = cairo_status($cr);

var_dump($status==CAIRO_STATUS_SUCCESS);

$count=0;
cairo_pattern_get_color_stop_count ($pattern, $count);
var_dump($count==2);

cairo_pattern_get_linear_points ($pattern, $x0, $y0, $x1, $y1);
var_dump($x0, $y0, $x1, $y1);

?>
--EXPECT--
bool(true)
bool(true)
float(0)
float(0)
float(100)
float(100)
