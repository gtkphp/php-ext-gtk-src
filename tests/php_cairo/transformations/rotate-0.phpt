--TEST--
05-0-0 : Check for cairo_rectangle_int
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

cairo_rotate ($cr, 10);

$matrix = new cairo_matrix_t;
cairo_get_matrix($cr, $matrix);

$expected = new cairo_matrix_t;
cairo_matrix_init_rotate($expected, 10);

var_dump($matrix);
var_dump($expected);



?>
--EXPECT--
object(cairo_matrix_t)#3 (6) {
  ["xx"]=>
  float(-0.8390715290764524)
  ["yx"]=>
  float(-0.5440211108893698)
  ["xy"]=>
  float(0.5440211108893698)
  ["yy"]=>
  float(-0.8390715290764524)
  ["x0"]=>
  float(0)
  ["y0"]=>
  float(0)
}
object(cairo_matrix_t)#4 (6) {
  ["xx"]=>
  float(-0.8390715290764524)
  ["yx"]=>
  float(-0.5440211108893698)
  ["xy"]=>
  float(0.5440211108893698)
  ["yy"]=>
  float(-0.8390715290764524)
  ["x0"]=>
  float(0)
  ["y0"]=>
  float(0)
}
