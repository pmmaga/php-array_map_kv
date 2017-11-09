--TEST--
array_map_kv_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('array_map_kv')) {
	echo 'skip';
}
?>
--FILE--
<?php 
$ret = array_map_kv();

var_dump($ret);
?>
--EXPECT--
NULL
