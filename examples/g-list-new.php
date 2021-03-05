<?php

if (!extension_loaded("gtk")) die("Gtk+ not loaded");

/*
class Key {
  public $value;
  function __construct($val) {
    $this->value = $val;
  }
}
$key1 = new Key("a");
$key2 = new Key("b");
$key3 = new Key("c");

$list = new GList();

//$list = NULL;


$list = g_list_append($list, $key1);
$list = g_list_prepend($list, $key2);
//$list = g_list_append($list, $key3);

var_dump($list);
*/

/*
$list = new GList();
g_list_append($list, "value1");
g_list_append($list, "value2");
g_list_append($list, "value3");
g_list_prepend($list, "value0");
var_dump($list);

$list = new GList();
$list = g_list_prepend($list, "value10");
var_dump($list);

$list = new GList();
$list = g_list_prepend($list, "value100");
var_dump($list);

$list = new GList();
$list = g_list_prepend($list, "value1000");
var_dump($list);
*/



$list = new GList();
g_list_append($list, "value1");
g_list_append($list, "value2");
g_list_append($list, "value3");
g_list_prepend($list, "value0");
var_dump($list);
unset($list);

$list2 = new GList();
$list2 = g_list_prepend($list2, "value10");
var_dump($list2);

$list3 = new GList();
$list3 = g_list_prepend($list3, "value100");
var_dump($list3);

$list4 = new GList();
$list4 = g_list_prepend($list4, "value1000");
var_dump($list4);


