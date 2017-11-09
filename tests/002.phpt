--TEST--
array_map_kv() Basic test
--SKIPIF--
<?php
if (!extension_loaded('array_map_kv')) {
	echo 'skip';
}
?>
--FILE--
<?php 
array_map_kv('var_dump', [0, 1]);

?>
--EXPECT--
int(0)
int(0)
int(1)
int(1)
