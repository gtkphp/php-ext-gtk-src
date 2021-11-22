--TEST--
05-0-0 : Check for cairo_rectangle_int
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

cairo_translate ($cr, 10, 20);

$x=5.0;
$y=3.0;
cairo_device_to_user_distance($cr, $x, $y);

var_dump($x, $y);



?>
--EXPECT--
float(5)
float(3)
