--TEST--
05-0-0 : Check for cairo_font_options_status
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$options = cairo_font_options_create ();
$status = cairo_font_options_status($options);
var_dump($status==CAIRO_STATUS_SUCCESS);

$other = cairo_font_options_create ();
$status = cairo_font_options_status($other);
var_dump($status==CAIRO_STATUS_SUCCESS);

$equal = cairo_font_options_equal($options, $other);
var_dump($equal);

cairo_font_options_set_antialias ($options, CAIRO_ANTIALIAS_GRAY);
$equal = cairo_font_options_equal($options, $other);
var_dump($equal==false);


?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
