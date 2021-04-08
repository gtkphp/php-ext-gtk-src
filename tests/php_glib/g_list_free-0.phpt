--TEST--
1-05-8-0 : Check for g_list_free
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = Null;
$list = g_list_append($list, "value0");
$list = g_list_append($list, "value");
$list = g_list_append($list, "value");

g_list_free($list);

var_dump($list);


?>
--EXPECT--
NULL
