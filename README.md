# array_map_kv

The `array_map_kv` function is equivalent to the regular `array_map` function except that it passes both the key and the value of each element of the array to the given callback.

The signature of the function is also the same:
```
array array_map_kv ( callable $callback , array $array1 [, array $... ] )
```

### Why?

It results in the same as using `array_map(function($k, $v) {}, array_keys($arr), $arr);` without having to create a temporary array to hold the keys.

### Example

```
$arr = [10 => "Ten", 9 => "Nine", 8 => "Eight"];

var_dump(array_map_kv(function($key, $value) { return $key . " => " . $value; }, $arr));
```
Outputs:
```
array(3) {
  [0]=>
  string(9) "10 => Ten"
  [1]=>
  string(9) "9 => Nine"
  [2]=>
  string(10) "8 => Eight"
}
```
