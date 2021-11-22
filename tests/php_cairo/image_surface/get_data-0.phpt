--TEST--
05-0-0 : Check for cairo_image_surface_get_data
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$input = __DIR__."/../sqaure.png";
$surface = cairo_image_surface_create_from_png ($input);

$image = cairo_image_surface_get_data ($surface);
var_dump($image);



?>
--EXPECT--
object(cairo_image_data_t)#2 (16) {
  [0]=>
  string(4) "\x00"
  [1]=>
  string(4) "\x00"
  [2]=>
  string(4) "\xFF"
  [3]=>
  string(4) "\xFF"
  [4]=>
  string(4) "\x00"
  [5]=>
  string(4) "\xFF"
  [6]=>
  string(4) "\x00"
  [7]=>
  string(4) "\xFF"
  [8]=>
  string(4) "\xFF"
  [9]=>
  string(4) "\x00"
  [10]=>
  string(4) "\x00"
  [11]=>
  string(4) "\xFF"
  [12]=>
  string(4) "\x00"
  [13]=>
  string(4) "\x00"
  [14]=>
  string(4) "\x00"
  [15]=>
  string(4) "\x00"
}
