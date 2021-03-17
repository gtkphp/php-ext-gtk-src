--TEST--
Check for g_list_prepend
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = new GList();
$list = g_list_insert($list, "value1", 0);

var_dump($list);

?>
--EXPECT--
object(GList)#2 (3) {
  ["prev"]=>
  NULL
  ["data"]=>
  string(6) "value1"
  ["next"]=>
  object(GList)#1 (3) {
    ["prev"]=>
    *RECURSION*
    ["data"]=>
    NULL
    ["next"]=>
    NULL
  }
}
