--TEST--
05-0-0 : Check for cairo_rectangle_int
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

cairo_translate ($cr, 10, 20);

$matrix = new cairo_matrix_t;
cairo_get_matrix($cr, $matrix);

$expected = new cairo_matrix_t;
cairo_matrix_init_translate($expected, 10, 20);

var_dump($matrix);
var_dump($expected);



?>
--EXPECT--
object(cairo_matrix_t)#3 (6) {
  ["xx"]=>
  float(1)
  ["yx"]=>
  float(0)
  ["xy"]=>
  float(0)
  ["yy"]=>
  float(1)
  ["x0"]=>
  float(10)
  ["y0"]=>
  float(20)
}
object(cairo_matrix_t)#4 (6) {
  ["xx"]=>
  float(1)
  ["yx"]=>
  float(0)
  ["xy"]=>
  float(0)
  ["yy"]=>
  float(1)
  ["x0"]=>
  float(10)
  ["y0"]=>
  float(20)
}
