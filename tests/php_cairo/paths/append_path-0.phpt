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
object(cairo_path_t)#28 (3) {
  ["status"]=>
  int(0)
  ["data"]=>
  array(20) {
    [0]=>
    object(cairo_path_data_t)#29 (1) {
      ["header"]=>
      object(stdClass)#30 (2) {
        ["type"]=>
        int(0)
        ["length"]=>
        int(2)
      }
    }
    [1]=>
    object(cairo_path_data_t)#31 (1) {
      ["point"]=>
      object(stdClass)#32 (2) {
        ["x"]=>
        float(0)
        ["y"]=>
        float(0)
      }
    }
    [2]=>
    object(cairo_path_data_t)#33 (1) {
      ["header"]=>
      object(stdClass)#34 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [3]=>
    object(cairo_path_data_t)#35 (1) {
      ["point"]=>
      object(stdClass)#36 (2) {
        ["x"]=>
        float(21)
        ["y"]=>
        float(0)
      }
    }
    [4]=>
    object(cairo_path_data_t)#37 (1) {
      ["header"]=>
      object(stdClass)#38 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [5]=>
    object(cairo_path_data_t)#39 (1) {
      ["point"]=>
      object(stdClass)#40 (2) {
        ["x"]=>
        float(21)
        ["y"]=>
        float(29.69921875)
      }
    }
    [6]=>
    object(cairo_path_data_t)#41 (1) {
      ["header"]=>
      object(stdClass)#42 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [7]=>
    object(cairo_path_data_t)#43 (1) {
      ["point"]=>
      object(stdClass)#44 (2) {
        ["x"]=>
        float(0)
        ["y"]=>
        float(29.69921875)
      }
    }
    [8]=>
    object(cairo_path_data_t)#45 (1) {
      ["header"]=>
      object(stdClass)#46 (2) {
        ["type"]=>
        int(3)
        ["length"]=>
        int(1)
      }
    }
    [9]=>
    object(cairo_path_data_t)#47 (1) {
      ["header"]=>
      object(stdClass)#48 (2) {
        ["type"]=>
        int(0)
        ["length"]=>
        int(2)
      }
    }
    [10]=>
    object(cairo_path_data_t)#49 (1) {
      ["point"]=>
      object(stdClass)#50 (2) {
        ["x"]=>
        float(10)
        ["y"]=>
        float(10)
      }
    }
    [11]=>
    object(cairo_path_data_t)#51 (1) {
      ["header"]=>
      object(stdClass)#52 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [12]=>
    object(cairo_path_data_t)#53 (1) {
      ["point"]=>
      object(stdClass)#54 (2) {
        ["x"]=>
        float(31)
        ["y"]=>
        float(10)
      }
    }
    [13]=>
    object(cairo_path_data_t)#55 (1) {
      ["header"]=>
      object(stdClass)#56 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [14]=>
    object(cairo_path_data_t)#57 (1) {
      ["point"]=>
      object(stdClass)#58 (2) {
        ["x"]=>
        float(31)
        ["y"]=>
        float(39.69921875)
      }
    }
    [15]=>
    object(cairo_path_data_t)#59 (1) {
      ["header"]=>
      object(stdClass)#60 (2) {
        ["type"]=>
        int(1)
        ["length"]=>
        int(2)
      }
    }
    [16]=>
    object(cairo_path_data_t)#61 (1) {
      ["point"]=>
      object(stdClass)#62 (2) {
        ["x"]=>
        float(10)
        ["y"]=>
        float(39.69921875)
      }
    }
    [17]=>
    object(cairo_path_data_t)#63 (1) {
      ["header"]=>
      object(stdClass)#64 (2) {
        ["type"]=>
        int(3)
        ["length"]=>
        int(1)
      }
    }
    [18]=>
    object(cairo_path_data_t)#65 (1) {
      ["header"]=>
      object(stdClass)#66 (2) {
        ["type"]=>
        int(0)
        ["length"]=>
        int(2)
      }
    }
    [19]=>
    object(cairo_path_data_t)#67 (1) {
      ["point"]=>
      object(stdClass)#68 (2) {
        ["x"]=>
        float(10)
        ["y"]=>
        float(10)
      }
    }
  }
  ["num_data"]=>
  int(20)
}
