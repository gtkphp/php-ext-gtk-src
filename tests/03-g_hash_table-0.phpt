--TEST--
03-0 Check for g_hash_table as set of string
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$hash_table = g_hash_table_new(/*"g_direct_hash", "g_str_equal"*/);
g_hash_table_add($hash_table, "key1");

//g_hash_table_contains($hash_table, "key3");
var_dump($hash_table);

?>
--EXPECT--
object(GHashTable)#1 (1) {
  ["key1"]=>
  string(4) "key1"
}
