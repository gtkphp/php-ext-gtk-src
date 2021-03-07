<?php

if (!extension_loaded("gtk")) die("Gtk+ not loaded");



function my_string_hash($v):int {
    return 1;// force the string compare : ensure no collision( 'a', 'aa')
}
class Key {
  public $value;
  function __construct($val) {
    $this->value = $val;
  }
  /*
  function __toString() {
    // FIX php_g_hash_table_tostring_object use __toString() if exists ?
    // internal implementation
    //return 'object('.static::class.')#'.spl_object_id($this);
    // since PHP 7.2>
  }
    function __toHash():int {
      return (int)spl_object_hash($this);
      //return crc32((string)$this);
    }
    function __toEqual():int {
      return (int)spl_object_hash($this);
      //return crc32((string)$this);
    }
  */
}

$key1 = new Key("a");
$key2 = new Key("b");
$key3 = new Key("c");

$hashTable = g_hash_table_new();
$added = g_hash_table_add($hashTable, $key1);
$added = g_hash_table_add($hashTable, $key2);
$added = g_hash_table_add($hashTable, $key3);
$key1->value="aaa";

//var_dump($hashTable[$key1]);
var_dump($hashTable);

/*
$hashTable = g_hash_table_new();
$added = g_hash_table_add($hashTable, $key1);
var_dump($hashTable);
*/

/*
$key4 = new Key("d");
$hashTable1 = g_hash_table_new();
g_hash_table_add($hashTable1, $key4);
var_dump($hashTable);
*/
