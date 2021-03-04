<?php

$hash_table = g_hash_table_new(/*"g_direct_hash", "g_str_equal"*/);
g_hash_table_add($hash_table, "key1");
g_hash_table_add($hash_table, "key2");
g_hash_table_add($hash_table, "key3");

//g_hash_table_contains($hash_table, "key3");
var_dump($hash_table);

?>
