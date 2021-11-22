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

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

/*$list = Null;
$list = g_list_append($list, "value0");
echo g_list_length($list), PHP_EOL;
$list = g_list_append($list, "value1");
echo g_list_length($list), PHP_EOL;
$list = g_list_append($list, "value2");
echo g_list_length($list), PHP_EOL;
*/




var_dump(g_str_equal("extension", "extension"));
var_dump(g_str_equal("zend", "extension"));

var_dump(g_str_hash("extension"));

//int(2064964834)


/**
$list = new GList();
$list->data = "data-0";

$list->next = new GList();
$list->next->data = "data-1";
$list->next->prev = $list;

$list->next->next = new GList();
$list->next->next->data = "data-2";
$list->next->next->prev = $list->next;

var_dump($list);
*/


/**
$list = new GList();
$list->data = "data-0";

$list->prev = new GList();
$list->prev->data = "data-1";
$list->prev->next = $list;

$list->prev->prev = new GList();
$list->prev->prev->data = "data-2";
$list->prev->prev->next = $list->prev;

var_dump($list);
**/


/*
$list = null;
$start = g_list_prepend($list, "data-0");
$list = g_list_prepend($start, "data-1");
$list = g_list_prepend($start, "data-2");
//unset($start);
//var_dump($list);

$first = g_list_first($list);
var_dump($first);
*/

/*
function my_prepend($list, $data):GList {
    $node = new GList;
    $node->data = $data;
    $node->next = $list;

    if($list) {
        $node->prev = $list->prev;
        if ($list->prev) {
            $list->prev->next = $node;
        }
        $list->prev = $node;
    }
    return $node;
}


$start = my_prepend(null, "data-0");
$node1 = my_prepend($start, "data-1");
$node2 = my_prepend($node1, "data-2");

var_dump($start);
*/

/*
//$list = g_list_prepend(null, "data-0");
$list = g_list_insert(null, "data-0", 0);
$list = g_list_insert($list, "data-1", 0);
$list = g_list_insert($list, "data-2", 0);
$list = g_list_insert($list, "data-3", 0);

var_dump($list);
*/

/*
$list = null;
$list = g_list_prepend($list, "data-0");
$list1 = g_list_prepend($list, "data-1");
$list2 = g_list_prepend($list, "data-2");
$list3 = g_list_prepend($list, "data-3");
var_dump($list);
*/

/*
$list = null;
$list = g_list_append($list, "data-0");
$list = g_list_append($list, "data-1");
$list = g_list_append($list, "data-2");
$list = g_list_append($list, "data-3");
var_dump($list);
*/

/*
$item = new GList;
$item->data = "data-1";
$list = new GList;
$list->data = "data-0";
$list->next = $item;
$item->prev = $list;
var_dump($list);
*/

/*
$list = new GList;
$list->data = "data-0";
$list->next = new GList;
$list->next->data = "data-1";
$list->next->prev = $list;
var_dump($list);
*/



/*
function on_destroy($data) {
    var_dump($data);
}

$list = Null;
$list = g_list_append($list, "value0");
$list = g_list_append($list, "value1");
$list = g_list_append($list, "value2");

g_list_free_full($list, "on_destroy");
*/



//echo "Read: https://www.phpinternalsbook.com/php7/zvals/memory_management.html\n";
//confirm_gtk_compiled("");


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

/*
//$list = new GList($key2);
$list = g_list_append(NULL, $key2);
$list = g_list_append($list, $key3);
$list = g_list_prepend($list, $key1);
$list = g_list_append($list, $key4);
$key1->value="a";

//var_dump($list);
php_g_list_dump($list);




//$list2 = g_list_append(NULL, "key2");
$list2 = new GList("key2");
g_list_append($list2, "key3");
$list2 = g_list_prepend($list2, "key1");

php_g_list_dump($list2);
*/


/*
$list = new GList("key2");
g_list_append($list, "key3");
//g_list_prepend($list, "key1");


$list->baz = "bar";
$list["foo"] = "Too";

unset($list->baz);
unset($list["foo"]);
unset($list["next"]);// Notice: Forbidden to delete GList::$next
//unset($list[0]);
print_r($list);
*/

/*
$list = g_list_prepend(NULL, "key1");
g_list_prepend($list, "key2");
g_list_prepend($list, "key3");
php_g_list_dump($list->prev->prev);


$list = new GList("key1");
g_list_prepend($list, "key2");
g_list_prepend($list, "key3");
php_g_list_dump($list->prev->prev);
*/

/*
$first = Null;
$first = g_list_append($first, "key1");
$first = g_list_append($first, "key2");
$list = $first->next;//g_list_nth($first, 1);
$list = g_list_append($list, "key3");
$list = g_list_insert($list, "key", 0);
php_g_list_dump($first);
*/

/*
$list = g_list_insert(NULL, "value1", 0);

var_dump($list);
*/

//php_g_list_dump(new GList("value1"));// Ref: 1
//php_g_list_dump(g_list_append(NULL, "value2"));// Ref: 1
//$list = new GList("value1");
//php_g_list_dump($list);// Ref: 2
//$list = g_list_append(NULL, "value2");
//php_g_list_dump($list);// Ref: 2




//var_dump($list);
//$casted = (array)$list;
//var_dump((array)$list);
//print_r($list);
//print_r((array)$list);
//php_g_list_dump($list);

//$state = var_export($list, True);
//eval('$c = ' . $state . ';');
//var_export($list);

//$k = var_export($key1, True);
//eval('$c = ' . $k . ';');

// TODO g_list_prepend
// TODO g_list_insert

/*
//$list = new GList("val1");
$list = g_list_prepend(NULL, "val1");
//php_g_list_dump($list);
//$list = g_list_prepend($list, "val2");
//php_g_list_dump($list);
//$list = g_list_prepend($list, "val3");
//php_g_list_dump($list);
//$list = g_list_prepend($list, "val4");
g_list_prepend($list, "val5");
g_list_prepend($list, "val6");
g_list_prepend($list, "val7");
//php_g_list_dump(g_list_first($list));
print_r((array)$list);
*/

/*
$list = g_list_prepend(Null, "val1");
g_list_prepend($list, "val2");
g_list_prepend($list, "val3");
g_list_prepend($list, "val4");
g_list_dump($list);

//print_r((array)$list);
//var_dump($list);
*/

/*
$list = g_list_insert(Null, "val1", 0);
$list = g_list_insert($list, "val2", 0);
$list = g_list_insert($list, "val3", 0);
$list = g_list_insert($list, "val4", 0);
var_dump($list);
*/


/*
$list = g_list_insert_before(null, null, "val1");
$list = g_list_insert_before($list, null, "val2");
//$list = g_list_insert_before($list, $list, "val3");
//$list = g_list_insert_before($list, $list, "val4");
var_dump($list);
//g_list_dump($list);
*/


/*
//print_r((array)$list);
$list = new GList("val");
$list->foo = "bar";
$list->Foo = "baz";
echo $list->foo, PHP_EOL;
echo $list->Foo, PHP_EOL;
echo $list->nulle, PHP_EOL;
*/

/*
$list = g_list_append(NULL, "value1");
$list = g_list_append($list, "value2");
$list = g_list_append($list, "value3");
g_list_append($list, "value4");
g_list_append($list, "value5");
//g_list_dump($list);
//var_dump($list);
print_r((array)$list);
*/


/*
$list = g_list_prepend(NULL, "value1");
$list = g_list_prepend($list, "value2");
$list = g_list_prepend($list, "value3");
$list = g_list_prepend($list, "value4");
//$list = g_list_prepend(g_list_first($list), "value5");
var_dump($list);

//var_dump(g_list_first($list->next));
//var_dump($list->next->next->next);
//$node = $list->next;
//var_dump($list->next);
*/





/*
$list = new GList("value1");
$list = g_list_append($list, "value2");
$list = g_list_append($list, "value3");
$list = g_list_append($list, "value4");

$list = g_list_remove($list, "value4");

g_list_dump($list);
*/

/*
$list = new GList("value1");
$list = g_list_append($list, "value2");
$list = g_list_append($list, "value3");

$tmp = $list->next;

$list = g_list_remove($list, "value2");

var_dump($list);
var_dump($tmp);
*/

/*
function testRemove($data, $item) {
    $list = Null;
    $ln = count($data);
    for($i=0; $i<$ln; $i++) {
        $list = g_list_append($list, $data[$i]);
    }

    $link = Null;
    $it = Null;
    for($it=$list; $it!=Null; $it=$it->next) {
        if ($it->data==$item) {
            $link = $it;
            unset($it);
            break;
        }
    }
    //$link = $list->next->next;

    $list = g_list_remove_link($list, $link);
    //echo "-------------------------------------\n";
    g_list_dump($list);
    g_list_dump($link);

    //unset($list);
    //unset($link);

    //unset($list);

}

$data = array("val1");
//$data = array("val1", "val2");
//$data = array("val1", "val2", "val3");
//$data = array("val1", "val2", "val3", "val4");
//$data = array("val1", "val2", "val3", "val4", "val5");
testRemove($data, "val1");
*/






/*
$list = g_list_append(Null, "value1");
$list = g_list_append($list, "value2");
$list = g_list_append($list, "value3");

$link = $list->next;
$list = g_list_remove_link($list, $link);

//var_dump($list);
g_list_dump($list);
g_list_dump($link);
*/



/*
$list = new GList("value1");
$list = g_list_append($list, "value2");
$list = g_list_append($list, "value3");
$list = g_list_append($list, "value4");

//$list = g_list_remove($list, "value2");

//$link = $list->next->next->next;
$list = g_list_remove_link($list, $link);
//$list = g_list_remove_link($list, $list->next->next->next);
//$list = g_list_remove_link($list, $list->next->next);
//$list = g_list_remove_link($list, $list->next);
//$list = g_list_remove_link($list, $list);

g_list_dump($list);
//g_list_dump($tmp);
//g_list_dump($link);
*/
