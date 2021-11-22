--TEST--
05-0-0 : Check for cairo_font_options_status
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


var_dump(defined("CAIRO_EXTEND_NONE"));
var_dump(defined("CAIRO_EXTEND_REPEAT"));
var_dump(defined("CAIRO_EXTEND_REFLECT"));
var_dump(defined("CAIRO_EXTEND_PAD"));


var_dump(defined("CAIRO_FILTER_FAST"));
var_dump(defined("CAIRO_FILTER_GOOD"));
var_dump(defined("CAIRO_FILTER_BEST"));
var_dump(defined("CAIRO_FILTER_NEAREST"));
var_dump(defined("CAIRO_FILTER_BILINEAR"));
var_dump(defined("CAIRO_FILTER_GAUSSIAN"));

var_dump(defined("CAIRO_PATTERN_TYPE_SOLID"));
var_dump(defined("CAIRO_PATTERN_TYPE_SURFACE"));
var_dump(defined("CAIRO_PATTERN_TYPE_LINEAR"));
var_dump(defined("CAIRO_PATTERN_TYPE_RADIAL"));
var_dump(defined("CAIRO_PATTERN_TYPE_MESH"));
var_dump(defined("CAIRO_PATTERN_TYPE_RASTER_SOURCE"));

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
bool(true)
bool(true)
bool(true)
