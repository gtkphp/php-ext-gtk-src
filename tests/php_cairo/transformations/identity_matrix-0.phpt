--TEST--
05-0-0 : Check for cairo_rectangle_int
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

cairo_identity_matrix($cr);
$matrix = new cairo_matrix_t;
cairo_get_matrix($cr, $matrix);


var_dump($matrix);



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
  float(0)
  ["y0"]=>
  float(0)
}
