--TEST--
04-6-0 : Check for g_list_remove_link
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$list = new GList("value1");
$list = g_list_remove_link($list, $list);

var_dump($list);


?>
--EXPECT--
NULL
