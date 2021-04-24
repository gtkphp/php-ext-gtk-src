--TEST--
05-0-0 : Check for cairo_copy_path
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

cairo_move_to ($cr, 64.0, 25.6);
cairo_rectangle ($cr, 0.0, 0.0, 21.0, 29.7);

$path = cairo_copy_path ($cr);

var_dump($path);

?>
--EXPECT--
object(cairo_path_t)#3 (3) {
  ["status"]=>
  int(0)
  ["num_data"]=>
  int(11)
  ["data"]=>
  array(11) {
    [0]=>
    object(stdClass)#5 (1) {
      ["header"]=>
      object(cairo_path_data_t)#4 (2) {
        ["type"]=>
        int(0)
        ["length"]=>
        int(2)
      }
    }
    [1]=>
    object(stdClass)#7 (1) {
      ["point"]=>
      object(cairo_path_data_t)#6 (2) {
        ["x"]=>
        float(0)
        ["y"]=>
        float(0)
      }
    }
    [2]=>
    object(stdClass)#9 (1) {
      ["header"]=>
      object(cairo_path_data_t)#8 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [3]=>
    object(stdClass)#11 (1) {
      ["point"]=>
      object(cairo_path_data_t)#10 (2) {
        ["x"]=>
        float(21)
        ["y"]=>
        float(0)
      }
    }
    [4]=>
    object(stdClass)#13 (1) {
      ["header"]=>
      object(cairo_path_data_t)#12 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [5]=>
    object(stdClass)#15 (1) {
      ["point"]=>
      object(cairo_path_data_t)#14 (2) {
        ["x"]=>
        float(21)
        ["y"]=>
        float(29.69921875)
      }
    }
    [6]=>
    object(stdClass)#17 (1) {
      ["header"]=>
      object(cairo_path_data_t)#16 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [7]=>
    object(stdClass)#19 (1) {
      ["point"]=>
      object(cairo_path_data_t)#18 (2) {
        ["x"]=>
        float(0)
        ["y"]=>
        float(29.69921875)
      }
    }
    [8]=>
    object(stdClass)#21 (1) {
      ["header"]=>
      object(cairo_path_data_t)#20 (2) {
        ["type"]=>
        int(3)
        ["length"]=>
        int(1)
      }
    }
    [9]=>
    object(stdClass)#23 (1) {
      ["header"]=>
      object(cairo_path_data_t)#22 (2) {
        ["type"]=>
        int(0)
        ["length"]=>
        int(2)
      }
    }
    [10]=>
    object(stdClass)#25 (1) {
      ["point"]=>
      object(cairo_path_data_t)#24 (2) {
        ["x"]=>
        float(0)
        ["y"]=>
        float(0)
      }
    }
  }
}
