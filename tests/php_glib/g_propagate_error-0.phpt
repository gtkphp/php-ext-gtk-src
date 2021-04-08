--TEST--
03-6-0 : Check for g_propagate_error
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

$src=null;
g_set_error($src, my_quark(), 403, "'%s' do not exist", "Application", null);

$error=null;
g_propagate_error($error, $src);

var_dump($error);


?>
--EXPECT--
object(GError)#2 (3) {
  ["domain"]=>
  string(2) "MY"
  ["code"]=>
  int(403)
  ["message"]=>
  string(26) "'Application' do not exist"
}
