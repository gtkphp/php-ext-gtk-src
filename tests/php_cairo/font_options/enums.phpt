--TEST--
05-0-0 : Check for cairo_font_options_status
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

var_dump(defined("CAIRO_SUBPIXEL_ORDER_DEFAULT"));
var_dump(defined("CAIRO_SUBPIXEL_ORDER_RGB"));
var_dump(defined("CAIRO_SUBPIXEL_ORDER_BGR"));
var_dump(defined("CAIRO_SUBPIXEL_ORDER_VRGB"));
var_dump(defined("CAIRO_SUBPIXEL_ORDER_VBGR"));

var_dump(defined("CAIRO_HINT_STYLE_DEFAULT"));
var_dump(defined("CAIRO_HINT_STYLE_NONE"));
var_dump(defined("CAIRO_HINT_STYLE_SLIGHT"));
var_dump(defined("CAIRO_HINT_STYLE_MEDIUM"));
var_dump(defined("CAIRO_HINT_STYLE_FULL"));

var_dump(defined("CAIRO_HINT_METRICS_DEFAULT"));
var_dump(defined("CAIRO_HINT_METRICS_OFF"));
var_dump(defined("CAIRO_HINT_METRICS_ON"));

?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
