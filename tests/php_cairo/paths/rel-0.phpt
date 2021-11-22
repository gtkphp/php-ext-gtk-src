--TEST--
05-0-0 : Check for cairo_path_destroy
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php



$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 270, 50);
$cr = cairo_create($surface);

cairo_rectangle ($cr, 0.0, 0.0, 270.0, 50.0);
cairo_set_source_rgb ($cr, 1.0, 1.0, 1.0);
cairo_fill ($cr);

cairo_move_to($cr, 10.0, 10.0);
cairo_rel_curve_to ($cr, 50.0, 50.0, 100.0, 50.0, 150.0, 0.0);
cairo_rel_line_to ($cr, 150.0, 50.0);
cairo_rel_move_to ($cr, 10.0, 10.0);

cairo_set_source_rgb ($cr, 0.0, 0.0, 0.0);
cairo_fill ($cr);

//$status = cairo_surface_write_to_png($surface, "/home/dev/Projects/gtkphp/hello.png");
$status = cairo_status($cr);

var_dump($status==CAIRO_STATUS_SUCCESS);


?>
--EXPECT--
bool(true)
