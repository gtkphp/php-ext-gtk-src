--TEST--
Check for g_str_hash
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

var_dump(g_str_equal("extension", "extension"));
var_dump(g_str_equal("zend", "extension"));

?>
--EXPECT--
bool(true)
bool(false)
