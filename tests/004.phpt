--TEST--
array_map_kv() null callback test
--SKIPIF--
<?php
if (!extension_loaded('array_map_kv')) {
	echo 'skip';
}
?>
--FILE--
<?php 

var_dump(array_map_kv(null, [10 => "Ten", 9 => "Nine", 8 => "Eight"]));

?>
--EXPECT--
array(3) {
  [0]=>
  array(2) {
    [0]=>
    int(10)
    [1]=>
    string(3) "Ten"
  }
  [1]=>
  array(2) {
    [0]=>
    int(9)
    [1]=>
    string(4) "Nine"
  }
  [2]=>
  array(2) {
    [0]=>
    int(8)
    [1]=>
    string(5) "Eight"
  }
}
