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


$list = new GList();
g_list_append($list, "value1");
g_list_append($list, "value2");
g_list_append($list, "value3");
//g_list_prepend($list, "value2");

var_dump($list);
