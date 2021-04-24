--TEST--
90-0-0 : Check for php_doc_comment_get_tag_by_name
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


class A extends GObject {
    /** @override GObjectClass.get_property */
    function get_property($name) {
        if ($name=='zend_object') {
            // throw new Error('Access denied');
            return NULL;
        }
        return g_object_get_property($this, $name);
    }
}

$a = new A;
//var_dump($a['zend_object']);


?>
--EXPECT--
