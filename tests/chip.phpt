--TEST--
GPIO\Chip General Class Test
--SKIPIF--
<?php
if (! extension_loaded('phpgpio')) {
  exit('skip');
}
?>
--FILE--
<?php
var_dump(GPIO\Chip::isDevice('/dev/null'));
?>
--EXPECT--
bool(false)
