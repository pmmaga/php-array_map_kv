--TEST--
array_map_kv() user function test
--SKIPIF--
<?php
if (!extension_loaded('array_map_kv')) {
	echo 'skip';
}
?>
--FILE--
<?php 

function concat($key, $value) {
	return $key . $value;
}

var_dump(array_map_kv('concat', ['f' => 'foo', 'b' => 'bar']));

?>
--EXPECT--
array(2) {
  [0]=>
  string(4) "ffoo"
  [1]=>
  string(4) "bbar"
}
