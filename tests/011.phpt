--TEST--
Check for g_hash_table as set of string
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = NULL;
$list = g_list_append($list, "value1");

var_dump($list);

?>
--EXPECT--
object(GList)#1 (3) {
  [0]=>
  string(4) "value1"
}
