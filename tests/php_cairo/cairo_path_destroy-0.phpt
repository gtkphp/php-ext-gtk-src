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

$path = cairo_copy_path ($cr);
cairo_path_destroy ($path);



?>
--EXPECT--
