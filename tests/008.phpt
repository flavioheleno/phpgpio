--TEST--
Test GPIO\Lines class
--SKIPIF--
<?php
if (!extension_loaded('phpgpio')) {
  echo 'skip';
}
?>
--FILE--
<?php
var_dump(is_subclass_of(GPIO\Lines::class, \Countable::class));
var_dump(is_subclass_of(GPIO\Lines::class, \ArrayAccess::class));
var_dump(is_subclass_of(GPIO\Lines::class, \Iterator::class));
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
