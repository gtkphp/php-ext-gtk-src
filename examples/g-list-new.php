<?php
/*
class DLList extends GList {
    //public GList $prev;
    //public mixed $data;
    //public GList $next;
    function append($data) {

    }
}
 */
//if (!extension_loaded("glib")) die("Glib not loaded");
//if (!extension_loaded("gio")) die("Gio not loaded");
//if (!extension_loaded("gobject")) die("Gobject not loaded");
//if (!extension_loaded("Cairo")) die("Cairo not loaded");
//if (!extension_loaded("Pango")) die("Pango not loaded");
//if (!extension_loaded("Atk")) die("Atk not loaded");
//if (!extension_loaded("Gdk")) die("Gdk not loaded");
//if (!extension_loaded("Sdk")) die("Sdk not loaded");
if (!extension_loaded("gtk")) die("Gtk+ not loaded");


$list = new GList("value1");// $list = g_list_append(NULL, "value1");
g_list_append($list, "value2");
g_list_append($list, "value3");
var_dump($list);


//$list = g_list_append(Null, "value1");
//g_list_append($list, "value2");
//g_list_append($list, "value3");

//var_dump($list);
//print_r($list);

/*

object(GList)#1 (3) {
    ["prev"]=>Null,
    ["data"]=>string(6) "value1",
    ["next"]=>object(GList)#2 (3) {
        ["prev"]=>*RECURSION*,
        ["data"]=>string(6) "value2",
        ["next"]=>object(GList)#3 (3) {
            ["prev"]=>*RECURSION*,
            ["data"]=>string(6) "value3",
            ["next"]=>Null,
        },
    },
}

GList Object
(
    [0] => value1
    [1] => value2
    [2] => value3
)

*/



//$array = (array)$list;
//var_dump($array);

/*
class Key {
  public $value;
  function __construct($val) {
    $this->value = $val;
  }
}
$key1 = new Key("aaa");
$key2 = new Key("b");
$key3 = new Key("c");

$list = new GList();

//$list = NULL;


$list = g_list_append($list, $key1);
//$list = g_list_prepend($list, $key2);
$list = g_list_append($list, $key3);
$key1->value="a";
//$key3->value="ccc";

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

unset($list);


$list = new GList();
g_list_append($list, "value1");
g_list_append($list, "value2");
g_list_append($list, "value3");
g_list_prepend($list, "value0");
var_dump($list);

$list2 = new GList();
$list2 = g_list_prepend($list2, "value10");
var_dump($list2);

$list3 = new GList();
$list3 = g_list_prepend($list3, "value100");
var_dump($list3);

$list4 = new GList();
$list4 = g_list_prepend($list4, "value1000");
var_dump($list4);
*/
