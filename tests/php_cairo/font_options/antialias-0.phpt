--TEST--
05-0-0 : Check for cairo_font_options_status
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$options = cairo_font_options_create ();
$status = cairo_font_options_status($options);
var_dump($status==CAIRO_STATUS_SUCCESS);

cairo_font_options_set_antialias ($options, CAIRO_ANTIALIAS_GRAY);
$antialias = cairo_font_options_get_antialias ($options);
var_dump($antialias==CAIRO_ANTIALIAS_GRAY);


?>
--EXPECT--
bool(true)
bool(true)
