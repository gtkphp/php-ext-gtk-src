--TEST--
04-8-0 : Check for g_list_remove_all
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = Null;
$list = g_list_append($list, "value");
$list = g_list_append($list, "value");
$list = g_list_append($list, "value");
$list = g_list_append($list, "value4");

$list = g_list_remove_all($list, "value");

var_dump($list);
/*
$list = Null;
$list = g_list_append($list, "value");
$list = g_list_append($list, "value");
$list = g_list_append($list, "value");
$list = g_list_append($list, "value");

$list = g_list_remove_all($list, "value");
*/



?>
--EXPECT--
object(GList)#4 (3) {
  ["prev"]=>
  NULL
  ["data"]=>
  string(6) "value4"
  ["next"]=>
  NULL
}
