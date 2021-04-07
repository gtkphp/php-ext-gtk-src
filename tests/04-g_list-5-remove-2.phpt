--TEST--
04-5-2 : Check for g_list_remove
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = new GList("value1");
$list = g_list_append($list, "value2");
$list = g_list_remove($list, "value2");

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
