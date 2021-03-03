<?php

if (!extension_loaded("gtk")) die("Gtk+ not loaded");

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
/*
$list = g_list_new();
$list = g_list_append($list, $key1);
$list = g_list_append($list, $key2);
$list = g_list_append($list, $key3);
*/

var_dump($list);



