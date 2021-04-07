--TEST--
04-8-5 : Check for g_list_remove_all
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = Null;
$list = g_list_append($list, "value0");
$list = g_list_append($list, "value1");
$list = g_list_append($list, "value2");

$list = g_list_remove_all($list, "value");

var_dump($list);


?>
--EXPECT--
object(GList)#1 (3) {
  ["prev"]=>
  NULL
  ["data"]=>
  string(6) "value0"
  ["next"]=>
  object(GList)#2 (3) {
    ["prev"]=>
    *RECURSION*
    ["data"]=>
    string(6) "value1"
    ["next"]=>
    object(GList)#3 (3) {
      ["prev"]=>
      *RECURSION*
      ["data"]=>
      string(6) "value2"
      ["next"]=>
      NULL
    }
  }
}
