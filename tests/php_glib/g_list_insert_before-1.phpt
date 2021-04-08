--TEST--
1-05-3-1 Check for g_list_insert_before
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = g_list_insert_before(Null, Null, "value1");
$list = g_list_insert_before($list, Null, "value2");

var_dump($list);

?>
--EXPECT--
object(GList)#1 (3) {
  ["prev"]=>
  NULL
  ["data"]=>
  string(6) "value1"
  ["next"]=>
  object(GList)#2 (3) {
    ["prev"]=>
    *RECURSION*
    ["data"]=>
    string(6) "value2"
    ["next"]=>
    NULL
  }
}
