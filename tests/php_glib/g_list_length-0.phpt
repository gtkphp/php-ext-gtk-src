--TEST--
1-05-13-0 : Check for g_list_length
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$list = Null;
$list = g_list_append($list, "value0");
echo g_list_length($list), PHP_EOL;
$list = g_list_append($list, "value1");
echo g_list_length($list), PHP_EOL;
$list = g_list_append($list, "value2");
echo g_list_length($list), PHP_EOL;



?>
--EXPECT--
1
2
3
