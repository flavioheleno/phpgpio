--TEST--
Test GPIO\Exception class
--SKIPIF--
<?php
if (!extension_loaded('phpgpio')) {
  echo 'skip';
}
?>
--FILE--
<?php
var_dump(is_subclass_of(GPIO\Exception::class, \Error::class));
?>
--EXPECT--
bool(true)