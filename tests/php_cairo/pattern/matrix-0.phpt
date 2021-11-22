--TEST--
05-0-0 : Check for cairo_font_options_status
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

$pattern = cairo_pattern_create_linear (0.0, 0.0, 100, 100.0);
cairo_pattern_add_color_stop_rgb ($pattern, 0.0, 1.0, 0.0, 0.0);
cairo_pattern_add_color_stop_rgba ($pattern, 1.0, 0.0, 0.0, 1.0, 1.0);

$matrix = new cairo_matrix_t;
cairo_matrix_init_identity($matrix);
cairo_pattern_set_matrix ($pattern, $matrix);

$expected;
cairo_pattern_get_matrix ($pattern, $expected);

var_dump($matrix==$expected);

?>
--EXPECT--
bool(true)
