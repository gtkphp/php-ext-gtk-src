--TEST--
1-05-1-0 Check for g_list_prepend
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = g_list_prepend(NULL, "value1");
g_list_prepend($list, "value2");

var_dump($list);

?>
--EXPECT--
object(GList)#1 (3) {
  ["prev"]=>
  object(GList)#2 (3) {
    ["prev"]=>
    NULL
    ["data"]=>
    string(6) "value2"
    ["next"]=>
    *RECURSION*
  }
  ["data"]=>
  string(6) "value1"
  ["next"]=>
  NULL
}
