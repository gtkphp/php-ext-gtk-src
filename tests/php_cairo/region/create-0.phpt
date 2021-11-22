--TEST--
05-0-0 : Check for cairo_rectangle_int
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$region = cairo_region_create();
var_dump($region);

$rectangle = new cairo_rectangle_int_t ();
$rectangle->width = 50;
$rectangle->height = 30;
$region = cairo_region_create_rectangle ($rectangle);

var_dump($region);


$rectangle_a = new cairo_rectangle_int_t ();
$rectangle_a->width = 50;
$rectangle_a->height = 30;
$rectangle_b = new cairo_rectangle_int_t ();
$rectangle_b->x = 50;
$rectangle_b->y = 30;
$rectangle_b->width = 50;
$rectangle_b->height = 30;
$rectangles = array($rectangle_a, $rectangle_b);

$region = cairo_region_create_rectangles ($rectangles);
var_dump($region);

$extents = new cairo_rectangle_int_t ();
cairo_region_get_extents ($region, $extents);
var_dump($extents);

$num = cairo_region_num_rectangles ($region);
var_dump($num);

$rectangle_c = new cairo_rectangle_int_t ();
cairo_region_get_rectangle ($region, 1, $rectangle_c);
var_dump($rectangle_c);

$bool = cairo_region_is_empty ($region);
var_dump($bool);

$bool = cairo_region_contains_point ($region, 10, 10);
var_dump($bool);
$bool = cairo_region_contains_point ($region, 200, 200);
var_dump($bool);

$rectangle_d = new cairo_rectangle_int_t();
$rectangle_d->width = 10;
$rectangle_d->height = 10;
$overlap = cairo_region_contains_rectangle ($region, $rectangle_d);
var_dump($overlap==CAIRO_REGION_OVERLAP_IN);

$rectangle_d->x = 200;
$rectangle_d->y = 200;
$overlap = cairo_region_contains_rectangle ($region, $rectangle_d);
var_dump($overlap==CAIRO_REGION_OVERLAP_OUT);

$rectangle_d->x = 95;
$rectangle_d->y = 55;
$overlap = cairo_region_contains_rectangle ($region, $rectangle_d);
var_dump($overlap==CAIRO_REGION_OVERLAP_PART);

?>
--EXPECT--
object(cairo_region_t)#1 (0) {
}
object(cairo_region_t)#3 (0) {
}
object(cairo_region_t)#5 (0) {
}
object(cairo_rectangle_int_t)#3 (4) {
  ["x"]=>
  int(0)
  ["y"]=>
  int(0)
  ["width"]=>
  int(100)
  ["height"]=>
  int(60)
}
int(2)
object(cairo_rectangle_int_t)#6 (4) {
  ["x"]=>
  int(50)
  ["y"]=>
  int(30)
  ["width"]=>
  int(50)
  ["height"]=>
  int(30)
}
bool(false)
bool(true)
bool(false)
bool(true)
bool(true)
bool(true)
