--TEST--
90-0-0 : Check for php_doc_comment_get_tag_by_name
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

/**
 * GLib-GObject-WARNING **: 20:59:09.237: type name 'A' is too short
 * try with Ab => same warning
 * try with Abc => OK
 * @g_param_spec_uint("zoom-level", "Zoom level", "Zoom level to view the file at.", 0, 10, 2, G_PARAM_READWRITE) property
 */
/*
class Abc extends GObject {
    /**
     * @g_override GObjectClass.get_property
     * /
    function getProperty($name) {
        if ($name=='zend_object') {
            // throw new Error('Access denied');
            return NULL;
        }
        return g_object_get_property($this, $name);
    }
}

$a = new Abc;
//var_dump($a['zend_object']);
*/

confirm_gtk_compiled("");


?>
--EXPECT--
