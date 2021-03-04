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
    TODO: override internal toString
    function __toString() {
    return static::class.$this->value;
  }
    TODO: override internal toInt
  function __toHash():int {
    return (int)spl_object_hash($this);
    //return crc32((string)$this);
  }*/
}
$key1 = new Key("a");
$key2 = new Key("b");
$key3 = new Key("c");


//$hashTable = g_hash_table_new(Null/*'g_str_hash'|'crc32'|'my_string_hash'*/, Null/*'g_str_equal'*/);
$hashTable = g_hash_table_new();
$added = g_hash_table_add($hashTable, $key1);
$added = g_hash_table_add($hashTable, $key2);
$added = g_hash_table_add($hashTable, $key3);
//$added = g_hash_table_insert($hashTable, $key3, $key3);

//var_dump($hashTable['key1']);
//echo get_class($hashTable), PHP_EOL;

var_dump($hashTable[$key1]);

//$array = (array)$hashTable;
//var_dump($array);

var_dump($hashTable);
//print_r($hashTable);



