--TEST--
03-7-0 : Check for g_clear_error
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

function my_quark():int {
    static $q=null;
    if (!$q)
        $q = g_quark_from_static_string ("MY");
    return $q;
}

$error=null;
g_set_error($error, my_quark(), 403, "'%s' do not exist", "Application", null);
var_dump($error);

$error=new GError();
g_set_error($error, my_quark(), 403, "'%s' do not exist", "Application", null);
var_dump($error);

g_clear_error($error);
var_dump($error);


?>
--EXPECTF--
NULL
object(GError)#1 (3) {
  ["domain"]=>
  int(%d)
  ["code"]=>
  int(403)
  ["message"]=>
  string(26) "'Application' do not exist"
}
NULL
