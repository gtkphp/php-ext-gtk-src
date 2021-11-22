--TEST--
05-0-0 : Check for cairo_matrix_init
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

$pattern = cairo_pattern_create_mesh ();
cairo_mesh_pattern_begin_patch ($pattern);
cairo_mesh_pattern_move_to($pattern, 0.0, 0.0);
cairo_mesh_pattern_line_to($pattern, 50.0, 0.0);
cairo_mesh_pattern_line_to($pattern, 50.0, 50.0);
cairo_mesh_pattern_line_to($pattern,  0.0, 50.0);
//cairo_mesh_pattern_line_to($pattern, 0.0, 0.0);
cairo_mesh_pattern_curve_to ($pattern, 25.0, 20.0, 25.0, 10.0, 0.0, 0.0);
cairo_mesh_pattern_set_control_point ($pattern, 0, 10.0, 0.0);
cairo_mesh_pattern_set_corner_color_rgb($pattern, 0, 1.0, 0.0, 0.0);
cairo_mesh_pattern_set_corner_color_rgb($pattern, 1, 0.0, 1.0, 0.0);
cairo_mesh_pattern_set_corner_color_rgb($pattern, 2, 0.0, 0.0, 1.0);
cairo_mesh_pattern_set_corner_color_rgb($pattern, 3, 1.0, 1.0, 1.0);
cairo_mesh_pattern_end_patch($pattern);

$path = cairo_mesh_pattern_get_path ($pattern, 0);
cairo_mesh_pattern_get_control_point ($pattern, 0, 1, $x, $y);
cairo_mesh_pattern_get_corner_color_rgba ($pattern, 0, 1, $red, $green, $blue, $alpha);

$status = cairo_pattern_status($pattern);
var_dump($status==CAIRO_STATUS_SUCCESS);

cairo_rectangle($cr, 0.0, 0.0, 50.0, 50.0);
cairo_set_source($cr, $pattern);
cairo_fill($cr);


//$status = cairo_surface_write_to_png($surface, "/home/dev/Projects/gtkphp/hello.png");

$status = cairo_status($cr);
var_dump($status==CAIRO_STATUS_SUCCESS);


var_dump($x, $y);
var_dump($red, $green, $blue, $alpha);

var_dump($path);


?>
--EXPECT--
bool(true)
bool(true)
float(41.666666666666664)
float(14.444444444444443)
float(0)
float(1)
float(0)
float(1)
object(cairo_path_t)#4 (3) {
  ["status"]=>
  int(0)
  ["data"]=>
  array(18) {
    [0]=>
    object(cairo_path_data_t)#5 (1) {
      ["header"]=>
      object(stdClass)#6 (2) {
        ["type"]=>
        int(0)
        ["length"]=>
        int(2)
      }
    }
    [1]=>
    object(cairo_path_data_t)#7 (1) {
      ["point"]=>
      object(stdClass)#8 (2) {
        ["x"]=>
        float(0)
        ["y"]=>
        float(0)
      }
    }
    [2]=>
    object(cairo_path_data_t)#9 (1) {
      ["header"]=>
      object(stdClass)#10 (2) {
        ["type"]=>
        int(2)
        ["length"]=>
        int(4)
      }
    }
    [3]=>
    object(cairo_path_data_t)#11 (1) {
      ["point"]=>
      object(stdClass)#12 (2) {
        ["x"]=>
        float(16.666666666666664)
        ["y"]=>
        float(0)
      }
    }
    [4]=>
    object(cairo_path_data_t)#13 (1) {
      ["point"]=>
      object(stdClass)#14 (2) {
        ["x"]=>
        float(33.33333333333333)
        ["y"]=>
        float(0)
      }
    }
    [5]=>
    object(cairo_path_data_t)#15 (1) {
      ["point"]=>
      object(stdClass)#16 (2) {
        ["x"]=>
        float(50)
        ["y"]=>
        float(0)
      }
    }
    [6]=>
    object(cairo_path_data_t)#17 (1) {
      ["header"]=>
      object(stdClass)#18 (2) {
        ["type"]=>
        int(2)
        ["length"]=>
        int(4)
      }
    }
    [7]=>
    object(cairo_path_data_t)#19 (1) {
      ["point"]=>
      object(stdClass)#20 (2) {
        ["x"]=>
        float(50)
        ["y"]=>
        float(16.666666666666664)
      }
    }
    [8]=>
    object(cairo_path_data_t)#21 (1) {
      ["point"]=>
      object(stdClass)#22 (2) {
        ["x"]=>
        float(50)
        ["y"]=>
        float(33.33333333333333)
      }
    }
    [9]=>
    object(cairo_path_data_t)#23 (1) {
      ["point"]=>
      object(stdClass)#24 (2) {
        ["x"]=>
        float(50)
        ["y"]=>
        float(50)
      }
    }
    [10]=>
    object(cairo_path_data_t)#25 (1) {
      ["header"]=>
      object(stdClass)#26 (2) {
        ["type"]=>
        int(2)
        ["length"]=>
        int(4)
      }
    }
    [11]=>
    object(cairo_path_data_t)#27 (1) {
      ["point"]=>
      object(stdClass)#28 (2) {
        ["x"]=>
        float(33.33333333333333)
        ["y"]=>
        float(50)
      }
    }
    [12]=>
    object(cairo_path_data_t)#29 (1) {
      ["point"]=>
      object(stdClass)#30 (2) {
        ["x"]=>
        float(16.666666666666664)
        ["y"]=>
        float(50)
      }
    }
    [13]=>
    object(cairo_path_data_t)#31 (1) {
      ["point"]=>
      object(stdClass)#32 (2) {
        ["x"]=>
        float(0)
        ["y"]=>
        float(50)
      }
    }
    [14]=>
    object(cairo_path_data_t)#33 (1) {
      ["header"]=>
      object(stdClass)#34 (2) {
        ["type"]=>
        int(2)
        ["length"]=>
        int(4)
      }
    }
    [15]=>
    object(cairo_path_data_t)#35 (1) {
      ["point"]=>
      object(stdClass)#36 (2) {
        ["x"]=>
        float(25)
        ["y"]=>
        float(20)
      }
    }
    [16]=>
    object(cairo_path_data_t)#37 (1) {
      ["point"]=>
      object(stdClass)#38 (2) {
        ["x"]=>
        float(25)
        ["y"]=>
        float(10)
      }
    }
    [17]=>
    object(cairo_path_data_t)#39 (1) {
      ["point"]=>
      object(stdClass)#40 (2) {
        ["x"]=>
        float(0)
        ["y"]=>
        float(0)
      }
    }
  }
  ["num_data"]=>
  int(18)
}
