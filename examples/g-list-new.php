<?php

//if (!extension_loaded("glib")) die("Glib not loaded");
//if (!extension_loaded("gio")) die("Gio not loaded");
//if (!extension_loaded("gobject")) die("Gobject not loaded");
//if (!extension_loaded("Cairo")) die("Cairo not loaded");
//if (!extension_loaded("Pango")) die("Pango not loaded");
//if (!extension_loaded("Atk")) die("Atk not loaded");
//if (!extension_loaded("Gdk")) die("Gdk not loaded");
//if (!extension_loaded("Sdk")) die("Sdk not loaded");
if (!extension_loaded("gtk")) die("Gtk+ not loaded");


//echo "Read: https://www.phpinternalsbook.com/php7/zvals/memory_management.html\n";


class Key {
  public $value;
  function __construct($val) {
    $this->value = $val;
  }
}
$key1 = new Key("aaa");
$key2 = new Key("b");
$key3 = new Key("c");
$key4 = new Key("d");

$list = new GList($key2);
$list = g_list_append($list, $key3);
$list = g_list_prepend($list, $key1);
$list = g_list_append($list, $key4);
$key1->value="a";

//var_dump($list);
php_g_list_dump($list);




$list2 = g_list_append(NULL, "key2");
//$list2 = new GList("key2");
g_list_append($list2, "key3");
$list2 = g_list_prepend($list2, "key1");
php_g_list_dump($list2);

