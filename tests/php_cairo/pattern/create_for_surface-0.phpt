--TEST--
05-0-0 : Check for cairo_matrix_init
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

//$surface = cairo_image_surface_create_from_png("../sqaure.png");
/**/
$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 40, 40);
$cr = cairo_create ($surface);

$pattern = cairo_pattern_create_rgba (1.0, 0.0, 0.0, 0.5);// red
cairo_rectangle($cr, 0.0, 0.0, 20.0, 20.0);
cairo_set_source($cr, $pattern);
cairo_fill($cr);

$pattern = cairo_pattern_create_rgba (0.0, 0.0, 1.0, 0.5);// blue
cairo_rectangle($cr, 20.0, 20.0, 20.0, 20.0);
cairo_set_source($cr, $pattern);
cairo_fill($cr);
/**/

$target = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$context = cairo_create ($target);
$source = cairo_pattern_create_for_surface ($surface);
cairo_pattern_set_extend($source, CAIRO_EXTEND_REPEAT);
cairo_set_source($context, $source);
cairo_rectangle($context, 0.0, 0.0, 160.0, 80.0);
cairo_fill($context);

$status = cairo_status($cr);

var_dump($status==CAIRO_STATUS_SUCCESS);

//$status = cairo_surface_write_to_png($target, "/home/dev/Projects/gtkphp/hello.png");

cairo_pattern_get_surface($source, $surf);
$status = cairo_surface_status($surf);
var_dump($status==CAIRO_STATUS_SUCCESS);


?>
--EXPECT--
bool(true)
bool(true)
