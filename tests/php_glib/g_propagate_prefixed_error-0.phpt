--TEST--
03-9-0 : Check for g_propagate_prefixed_error
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

g_set_error($error, my_quark(), 403, "'%s' do not exist", "Application", null);

g_propagate_prefixed_error($err, $error, "GTKML:%s:", "GLIB", null);

var_dump($err);

?>
--EXPECT--
object(GError)#2 (3) {
  ["domain"]=>
  string(2) "MY"
  ["code"]=>
  int(403)
  ["message"]=>
  string(37) "GTKML:GLIB:'Application' do not exist"
}
