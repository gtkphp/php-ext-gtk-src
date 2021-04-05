--TEST--
04-8-10 : Check for g_list_remove_all
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = Null;
$list = g_list_append($list, "value");
$list = g_list_append($list, "value");
$list = g_list_append($list, "value");

$list = g_list_remove_all($list, "value");

var_dump($list);


?>
--EXPECT--
NULL
