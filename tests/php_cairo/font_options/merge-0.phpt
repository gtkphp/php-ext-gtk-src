--TEST--
05-0-0 : Check for cairo_font_options_status
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$options = cairo_font_options_create ();
$other = cairo_font_options_copy($options);
var_dump($options);
var_dump($other);
$status = cairo_font_options_status($options);
var_dump($status==CAIRO_STATUS_SUCCESS);
$status = cairo_font_options_status($other);
var_dump($status==CAIRO_STATUS_SUCCESS);

cairo_font_options_merge($options, $other);


?>
--EXPECT--
object(cairo_font_options_t)#1 (0) {
}
object(cairo_font_options_t)#2 (0) {
}
bool(true)
bool(true)
