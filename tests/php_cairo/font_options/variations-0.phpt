--TEST--
05-0-0 : Check for cairo_font_options_status
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip";
if (CAIRO_VERSION < 11600) print "skip";
?>
--FILE--
<?php

$options = cairo_font_options_create ();
$status = cairo_font_options_status($options);
var_dump($status==CAIRO_STATUS_SUCCESS);

cairo_font_options_set_variations($options, "abc");
$font_variations = cairo_font_options_get_variations($options);
var_dump($font_variations);


?>
--EXPECT--
bool(true)
bool(true)
