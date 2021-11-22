--TEST--
05-0-0 : Check for cairo_font_options_create
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$font_options = cairo_font_options_create ();
var_dump($font_options instanceof cairo_font_options_t);

?>
--EXPECT--
bool(true)
