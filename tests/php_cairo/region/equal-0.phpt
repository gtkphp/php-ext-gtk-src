--TEST--
05-0-0 : Check for cairo_rectangle_int
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php



$rectangle_a = new cairo_rectangle_int_t ();
$rectangle_a->width = 50;
$rectangle_a->height = 30;
$rectangle_b = new cairo_rectangle_int_t ();
$rectangle_b->width = 50;
$rectangle_b->height = 30;

$region_a = cairo_region_create_rectangle ($rectangle_a);
$region_b = cairo_region_create_rectangle ($rectangle_b);

$bool = cairo_region_equal ($region_a, $region_b);
var_dump($bool==true);

cairo_region_translate ($region_a, 10, 10);
$bool = cairo_region_equal ($region_a, $region_b);
var_dump($bool==false);

cairo_region_intersect ($region_a, $region_b);
$rectangle = new cairo_rectangle_int_t;
cairo_region_get_rectangle ($region_a, 0, $rectangle);
var_dump($rectangle);


$rectangle_e = new cairo_rectangle_int_t;
$rectangle_e->x = 20;
$rectangle_e->y = 20;
$rectangle_e->width = 60;
$rectangle_e->height = 10;
cairo_region_intersect_rectangle ($region_a, $rectangle_e);
cairo_region_get_rectangle ($region_a, 0, $rectangle);
var_dump($rectangle);


$rectangle_d = new cairo_rectangle_int_t ();
$rectangle_d->width = 30;
$rectangle_d->height = 50;
$region_d = cairo_region_create_rectangle ($rectangle_d);
cairo_region_subtract ($region_a, $region_d);
cairo_region_get_rectangle ($region_a, 0, $rectangle);
var_dump($rectangle);


$rectangle_f = new cairo_rectangle_int_t ();
$rectangle_f->width = 40;
$rectangle_f->height = 50;
cairo_region_subtract_rectangle ($region_a, $rectangle_f);
cairo_region_get_rectangle ($region_a, 0, $rectangle);
var_dump($rectangle);


$rectangle_d = new cairo_rectangle_int_t ();
$rectangle_d->width = 30;
$rectangle_d->height = 50;
$other = cairo_region_create_rectangle ($rectangle_d);
cairo_region_union ($region_a, $other);
cairo_region_get_extents ($region_a, $rectangle);
var_dump($rectangle);

$rectangle_g = new cairo_rectangle_int_t ();
$rectangle_g->width = 60;
$rectangle_g->height = 50;
cairo_region_union_rectangle ($region_a, $rectangle_g);
cairo_region_get_extents ($region_a, $rectangle);
var_dump($rectangle);


$rectangle_h = new cairo_rectangle_int_t ();
$rectangle_h->width = 30;
$rectangle_h->height = 50;
$other = cairo_region_create_rectangle ($rectangle_h);
cairo_region_xor ($region_a, $other);
cairo_region_get_extents ($region_a, $rectangle);
var_dump($rectangle);



$rectangle_g = new cairo_rectangle_int_t ();
$rectangle_g->width = 60;
$rectangle_g->height = 50;
cairo_region_xor_rectangle ($region_a, $rectangle_g);
cairo_region_get_extents ($region_a, $rectangle);
var_dump($rectangle);



?>
--EXPECT--
bool(true)
bool(true)
object(cairo_rectangle_int_t)#5 (4) {
  ["x"]=>
  int(10)
  ["y"]=>
  int(10)
  ["width"]=>
  int(40)
  ["height"]=>
  int(20)
}
object(cairo_rectangle_int_t)#5 (4) {
  ["x"]=>
  int(20)
  ["y"]=>
  int(20)
  ["width"]=>
  int(30)
  ["height"]=>
  int(10)
}
object(cairo_rectangle_int_t)#5 (4) {
  ["x"]=>
  int(30)
  ["y"]=>
  int(20)
  ["width"]=>
  int(20)
  ["height"]=>
  int(10)
}
object(cairo_rectangle_int_t)#5 (4) {
  ["x"]=>
  int(40)
  ["y"]=>
  int(20)
  ["width"]=>
  int(10)
  ["height"]=>
  int(10)
}
object(cairo_rectangle_int_t)#5 (4) {
  ["x"]=>
  int(0)
  ["y"]=>
  int(0)
  ["width"]=>
  int(50)
  ["height"]=>
  int(50)
}
object(cairo_rectangle_int_t)#5 (4) {
  ["x"]=>
  int(0)
  ["y"]=>
  int(0)
  ["width"]=>
  int(60)
  ["height"]=>
  int(50)
}
object(cairo_rectangle_int_t)#5 (4) {
  ["x"]=>
  int(30)
  ["y"]=>
  int(0)
  ["width"]=>
  int(30)
  ["height"]=>
  int(50)
}
object(cairo_rectangle_int_t)#5 (4) {
  ["x"]=>
  int(0)
  ["y"]=>
  int(0)
  ["width"]=>
  int(30)
  ["height"]=>
  int(50)
}
