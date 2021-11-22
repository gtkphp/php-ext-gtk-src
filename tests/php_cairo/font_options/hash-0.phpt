--TEST--
05-0-0 : Check for cairo_font_options_status
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$options = cairo_font_options_create ();
$status = cairo_font_options_status($options);
var_dump($status==CAIRO_STATUS_SUCCESS);

$hash = cairo_font_options_hash($options);
var_dump($hash==0);

cairo_font_options_set_antialias ($options, CAIRO_ANTIALIAS_GRAY);
$hash = cairo_font_options_hash($options);
var_dump($hash==2);


?>
--EXPECT--
bool(true)
bool(true)
bool(true)
