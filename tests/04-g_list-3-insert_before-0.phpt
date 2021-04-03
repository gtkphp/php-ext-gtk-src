--TEST--
04-3-0 Check for g_list_insert_before
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = g_list_insert_before(Null, Null, "value1");

var_dump($list);

?>
--EXPECT--
object(GList)#1 (3) {
  ["prev"]=>
  NULL
  ["data"]=>
  string(6) "value1"
  ["next"]=>
  NULL
}
