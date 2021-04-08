--TEST--
1-05-5-6 : Check for g_list_delete_link
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = Null;
$list = g_list_append($list, "value1");

$list = g_list_delete_link($list, $list);

var_dump($list);


?>
--EXPECT--
NULL
