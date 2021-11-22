--TEST--
05-0-0 : Check for cairo_path_destroy
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

cairo_move_to ($cr, 0.0, 0.0);
cairo_curve_to ($cr, 50.0, 50.0, 100.0, 50.0, 150.0, 0.0);

$path = cairo_copy_path ($cr);



var_dump($path);



?>
--EXPECT--
object(cairo_path_t)#3 (3) {
  ["status"]=>
  int(0)
  ["data"]=>
  array(6) {
    [0]=>
    object(cairo_path_data_t)#4 (1) {
      ["header"]=>
      object(stdClass)#5 (2) {
        ["type"]=>
        int(0)
        ["length"]=>
        int(2)
      }
    }
    [1]=>
    object(cairo_path_data_t)#6 (1) {
      ["point"]=>
      object(stdClass)#7 (2) {
        ["x"]=>
        float(0)
        ["y"]=>
        float(0)
      }
    }
    [2]=>
    object(cairo_path_data_t)#8 (1) {
      ["header"]=>
      object(stdClass)#9 (2) {
        ["type"]=>
        int(2)
        ["length"]=>
        int(4)
      }
    }
    [3]=>
    object(cairo_path_data_t)#10 (1) {
      ["point"]=>
      object(stdClass)#11 (2) {
        ["x"]=>
        float(50)
        ["y"]=>
        float(50)
      }
    }
    [4]=>
    object(cairo_path_data_t)#12 (1) {
      ["point"]=>
      object(stdClass)#13 (2) {
        ["x"]=>
        float(100)
        ["y"]=>
        float(50)
      }
    }
    [5]=>
    object(cairo_path_data_t)#14 (1) {
      ["point"]=>
      object(stdClass)#15 (2) {
        ["x"]=>
        float(150)
        ["y"]=>
        float(0)
      }
    }
  }
  ["num_data"]=>
  int(6)
}
