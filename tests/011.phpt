--TEST--
Check for g_list_append
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = new GList();
$list = g_list_append($list, "value1");

var_dump($list);

?>
--EXPECT--
object(GList)#1 (1) {
  ["0"]=>
  string(6) "value1"
}
