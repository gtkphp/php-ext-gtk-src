--TEST--
05-0-0 : Check for cairo_font_options_status
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$options = cairo_font_options_create ();
$status = cairo_font_options_status($options);
var_dump($status==CAIRO_STATUS_SUCCESS);

cairo_font_options_set_subpixel_order($options, CAIRO_SUBPIXEL_ORDER_RGB);
$subpixel_order = cairo_font_options_get_subpixel_order($options);
var_dump($subpixel_order==CAIRO_SUBPIXEL_ORDER_RGB);


?>
--EXPECT--
bool(true)
bool(true)
