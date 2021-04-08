--TEST--
1-05-11-0 : Check for g_list_alloc
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = g_list_alloc();
$list->data = "value";

var_dump($list);


?>
--EXPECT--
object(GList)#1 (3) {
  ["data"]=>
  string(5) "value"
  ["prev"]=>
  NULL
  ["next"]=>
  NULL
}
