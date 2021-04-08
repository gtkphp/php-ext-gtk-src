--TEST--
03-4-0 : Check for g_error_matches
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

$error = g_error_new (my_quark(), 404, "'%s' not found near line %d", "Application", 23, NULL);

$ret = g_error_matches($error, my_quark(), 404);
var_dump($ret);

$ret = g_error_matches($error, my_quark(), 403);
var_dump($ret);


?>
--EXPECT--
bool(true)
bool(false)
