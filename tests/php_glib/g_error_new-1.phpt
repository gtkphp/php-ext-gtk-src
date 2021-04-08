--TEST--
03-0-1 : Check for g_error_new
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

$quark = g_quark_from_string("My");
$error = g_error_new($quark, 30, "The message is '%s'", "message", NULL);

var_dump($error);

?>
--EXPECT--
object(GError)#1 (3) {
  ["domain"]=>
  string(2) "My"
  ["code"]=>
  int(30)
  ["message"]=>
  string(24) "The message is 'message'"
}
