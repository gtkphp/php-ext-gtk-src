--TEST--
04-10-0 : Check for g_quark_from_string
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$quark = g_quark_from_string("Hello");
$string = g_quark_to_string($quark);

var_dump($string);


?>
--EXPECT--
string(5) "Hello"
