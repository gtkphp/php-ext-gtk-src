--TEST--
03-1-0 : Check for g_error_new
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$quark = g_quark_from_string("My");
$error = g_error_new_literal($quark, 30, "The message is 'message'");

var_dump($error);

?>
--EXPECTF--
object(GError)#1 (3) {
  ["domain"]=>
  int(%d)
  ["code"]=>
  int(30)
  ["message"]=>
  string(24) "The message is 'message'"
}
