--TEST--
Check if array_map_kv is loaded
--SKIPIF--
<?php
if (!extension_loaded('array_map_kv')) {
	echo 'skip';
}
?>
--FILE--
<?php 
echo 'The extension "array_map_kv" is available';
?>
--EXPECT--
The extension "array_map_kv" is available
