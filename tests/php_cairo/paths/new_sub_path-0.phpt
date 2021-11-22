--TEST--
05-0-0 : Check for cairo_path_destroy
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

cairo_move_to ($cr, 64.0, 25.6);
cairo_rectangle ($cr, 0.0, 0.0, 21.0, 29.7);

cairo_new_sub_path ($cr);
$path = cairo_copy_path_flat ($cr);


var_dump($path);


?>
--EXPECT--
object(cairo_path_t)#3 (3) {
  ["status"]=>
  int(0)
  ["data"]=>
  array(9) {
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
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [3]=>
    object(cairo_path_data_t)#10 (1) {
      ["point"]=>
      object(stdClass)#11 (2) {
        ["x"]=>
        float(21)
        ["y"]=>
        float(0)
      }
    }
    [4]=>
    object(cairo_path_data_t)#12 (1) {
      ["header"]=>
      object(stdClass)#13 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [5]=>
    object(cairo_path_data_t)#14 (1) {
      ["point"]=>
      object(stdClass)#15 (2) {
        ["x"]=>
        float(21)
        ["y"]=>
        float(29.69921875)
      }
    }
    [6]=>
    object(cairo_path_data_t)#16 (1) {
      ["header"]=>
      object(stdClass)#17 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [7]=>
    object(cairo_path_data_t)#18 (1) {
      ["point"]=>
      object(stdClass)#19 (2) {
        ["x"]=>
        float(0)
        ["y"]=>
        float(29.69921875)
      }
    }
    [8]=>
    object(cairo_path_data_t)#20 (1) {
      ["header"]=>
      object(stdClass)#21 (2) {
        ["type"]=>
        int(3)
        ["length"]=>
        int(1)
      }
    }
  }
  ["num_data"]=>
  int(9)
}
