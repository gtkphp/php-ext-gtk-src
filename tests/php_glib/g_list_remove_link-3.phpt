--TEST--
1-05-5-3 : Check for g_list_remove_link
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = Null;
$list = g_list_append($list, "value1");
$list = g_list_append($list, "value2");
$list = g_list_append($list, "value3");

$list = g_list_remove_link($list, $list);

var_dump($list);


?>
--EXPECT--
object(GList)#2 (3) {
  ["prev"]=>
  NULL
  ["data"]=>
  string(6) "value2"
  ["next"]=>
  object(GList)#3 (3) {
    ["prev"]=>
    *RECURSION*
    ["data"]=>
    string(6) "value3"
    ["next"]=>
    NULL
  }
}
