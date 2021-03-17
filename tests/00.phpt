--TEST--
Check for gtk presence
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php
echo "gtk extension is available";

?>
--EXPECT--
gtk extension is available
