--TEST--
05-0-0 : Check for cairo_path_destroy
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

cairo_move_to ($cr, 0.0, 0.0);
cairo_arc ($cr, 0.0, 0.0, 90.0, 180.0, 212.0);

$path = cairo_copy_path ($cr);



var_dump($path->num_data);



?>
--EXPECT--
int(132)
