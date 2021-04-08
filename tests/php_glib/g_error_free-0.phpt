--TEST--
03-2-0 : Check for g_error_free
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$quark = g_quark_from_string("My");
$error = g_error_new_literal($quark, 30, "The message is 'message'");

g_error_free($error);

var_dump($error);

?>
--EXPECT--
NULL
