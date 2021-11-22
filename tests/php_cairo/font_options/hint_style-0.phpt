--TEST--
05-0-0 : Check for cairo_font_options_status
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$options = cairo_font_options_create ();
$status = cairo_font_options_status($options);
var_dump($status==CAIRO_STATUS_SUCCESS);

cairo_font_options_set_hint_style($options, CAIRO_HINT_STYLE_MEDIUM);
$hint_style = cairo_font_options_get_hint_style($options);
var_dump($hint_style==CAIRO_HINT_STYLE_MEDIUM);


?>
--EXPECT--
bool(true)
bool(true)
