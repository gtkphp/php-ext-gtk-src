--TEST--
03-8-0 : Check for g_prefixed_error
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

$error = new GError;
g_set_error($error, my_quark(), 403, "'%s' do not exist", "Application", null);

g_prefix_error($error, "GTK:", null);

var_dump($error);

?>
--EXPECTF--
object(GError)#1 (3) {
  ["domain"]=>
  int(%d)
  ["code"]=>
  int(403)
  ["message"]=>
  string(30) "GTK:'Application' do not exist"
}
