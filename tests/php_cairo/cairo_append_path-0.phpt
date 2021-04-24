--TEST--
05-0-0 : Check for cairo_append_path
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface1 = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr1 = cairo_create ($surface1);
cairo_rectangle ($cr1, 10.0, 10.0, 21.0, 29.7);
$path1 = cairo_copy_path ($cr1);


$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

cairo_rectangle ($cr, 0.0, 0.0, 21.0, 29.7);
cairo_append_path ($cr, $path1);

$path = cairo_copy_path ($cr);
var_dump($path);


?>
--EXPECT--
object(cairo_path_t)#6 (3) {
  ["status"]=>
  int(0)
  ["num_data"]=>
  int(20)
  ["data"]=>
  array(20) {
    [0]=>
    object(stdClass)#8 (1) {
      ["header"]=>
      object(cairo_path_data_t)#7 (2) {
        ["type"]=>
        int(0)
        ["length"]=>
        int(2)
      }
    }
    [1]=>
    object(stdClass)#10 (1) {
      ["point"]=>
      object(cairo_path_data_t)#9 (2) {
        ["x"]=>
        float(0)
        ["y"]=>
        float(0)
      }
    }
    [2]=>
    object(stdClass)#12 (1) {
      ["header"]=>
      object(cairo_path_data_t)#11 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [3]=>
    object(stdClass)#14 (1) {
      ["point"]=>
      object(cairo_path_data_t)#13 (2) {
        ["x"]=>
        float(21)
        ["y"]=>
        float(0)
      }
    }
    [4]=>
    object(stdClass)#16 (1) {
      ["header"]=>
      object(cairo_path_data_t)#15 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [5]=>
    object(stdClass)#18 (1) {
      ["point"]=>
      object(cairo_path_data_t)#17 (2) {
        ["x"]=>
        float(21)
        ["y"]=>
        float(29.69921875)
      }
    }
    [6]=>
    object(stdClass)#20 (1) {
      ["header"]=>
      object(cairo_path_data_t)#19 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [7]=>
    object(stdClass)#22 (1) {
      ["point"]=>
      object(cairo_path_data_t)#21 (2) {
        ["x"]=>
        float(0)
        ["y"]=>
        float(29.69921875)
      }
    }
    [8]=>
    object(stdClass)#24 (1) {
      ["header"]=>
      object(cairo_path_data_t)#23 (2) {
        ["type"]=>
        int(3)
        ["length"]=>
        int(1)
      }
    }
    [9]=>
    object(stdClass)#26 (1) {
      ["header"]=>
      object(cairo_path_data_t)#25 (2) {
        ["type"]=>
        int(0)
        ["length"]=>
        int(2)
      }
    }
    [10]=>
    object(stdClass)#28 (1) {
      ["point"]=>
      object(cairo_path_data_t)#27 (2) {
        ["x"]=>
        float(10)
        ["y"]=>
        float(10)
      }
    }
    [11]=>
    object(stdClass)#30 (1) {
      ["header"]=>
      object(cairo_path_data_t)#29 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [12]=>
    object(stdClass)#32 (1) {
      ["point"]=>
      object(cairo_path_data_t)#31 (2) {
        ["x"]=>
        float(31)
        ["y"]=>
        float(10)
      }
    }
    [13]=>
    object(stdClass)#34 (1) {
      ["header"]=>
      object(cairo_path_data_t)#33 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [14]=>
    object(stdClass)#36 (1) {
      ["point"]=>
      object(cairo_path_data_t)#35 (2) {
        ["x"]=>
        float(31)
        ["y"]=>
        float(39.69921875)
      }
    }
    [15]=>
    object(stdClass)#38 (1) {
      ["header"]=>
      object(cairo_path_data_t)#37 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [16]=>
    object(stdClass)#40 (1) {
      ["point"]=>
      object(cairo_path_data_t)#39 (2) {
        ["x"]=>
        float(10)
        ["y"]=>
        float(39.69921875)
      }
    }
    [17]=>
    object(stdClass)#42 (1) {
      ["header"]=>
      object(cairo_path_data_t)#41 (2) {
        ["type"]=>
        int(3)
        ["length"]=>
        int(1)
      }
    }
    [18]=>
    object(stdClass)#44 (1) {
      ["header"]=>
      object(cairo_path_data_t)#43 (2) {
        ["type"]=>
        int(0)
        ["length"]=>
        int(2)
      }
    }
    [19]=>
    object(stdClass)#46 (1) {
      ["point"]=>
      object(cairo_path_data_t)#45 (2) {
        ["x"]=>
        float(10)
        ["y"]=>
        float(10)
      }
    }
  }
}
