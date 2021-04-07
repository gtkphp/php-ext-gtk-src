--TEST--
04-7-1 : Check for g_list_delete_link
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = Null;
$list = g_list_append($list, "value1");
$list = g_list_append($list, "value2");

$list = g_list_delete_link($list, $list);

var_dump($list);


?>
--EXPECT--
object(GList)#2 (3) {
  ["prev"]=>
  NULL
  ["data"]=>
  string(6) "value2"
  ["next"]=>
  NULL
}
