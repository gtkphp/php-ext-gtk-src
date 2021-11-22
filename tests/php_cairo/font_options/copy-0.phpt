--TEST--
05-0-0 : Check for cairo_font_options_create
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$font_options = cairo_font_options_create ();
$copy = cairo_font_options_copy($font_options);
var_dump($copy instanceof cairo_font_options_t);

?>
--EXPECT--
bool(true)
