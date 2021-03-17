--TEST--
Check for g_str_hash
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

var_dump(g_str_hash("extension"));

?>
--EXPECT--
int(2064964834)
