--TEST--
05-0-0 : Check for cairo_font_options_status
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$options = cairo_font_options_create ();
$status = cairo_font_options_status($options);
var_dump($status==CAIRO_STATUS_SUCCESS);

cairo_font_options_set_hint_metrics($options, CAIRO_HINT_METRICS_ON);
$hint_metrics = cairo_font_options_get_hint_metrics($options);
var_dump($hint_metrics==CAIRO_HINT_METRICS_ON);


?>
--EXPECT--
bool(true)
bool(true)
