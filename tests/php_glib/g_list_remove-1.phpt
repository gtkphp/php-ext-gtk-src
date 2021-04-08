--TEST--
1-05-4-1 : Check for g_list_remove
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = new GList("value1");
$list = g_list_append($list, "value2");
$list = g_list_remove($list, "value1");

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
