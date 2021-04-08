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

g_clear_error($error);

var_dump($error);

?>
--EXPECT--
NULL
