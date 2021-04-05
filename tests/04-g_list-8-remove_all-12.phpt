--TEST--
04-8-12 : Check for g_list_remove_all
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = Null;
$list = g_list_append($list, "value");
$list = g_list_append($list, "value1");
$list = g_list_append($list, "value");

$list = g_list_remove_all($list, "value");

var_dump($list);


?>
--EXPECT--
object(GList)#2 (3) {
  ["prev"]=>
  NULL
  ["data"]=>
  string(6) "value1"
  ["next"]=>
  NULL
}
