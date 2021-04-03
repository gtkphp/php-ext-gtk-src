--TEST--
04-5-0 : Check for g_list_remove
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = new GList("value1");
$list = g_list_remove($list, "value1");

var_dump($list);


?>
--EXPECT--
NULL
