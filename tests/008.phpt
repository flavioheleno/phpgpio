--TEST--
Test GPIO\Bulk class
--SKIPIF--
<?php
if (!extension_loaded('phpgpio')) {
  echo 'skip';
}
?>
--FILE--
<?php
var_dump(is_subclass_of(GPIO\Bulk::class, \Countable::class));
var_dump(is_subclass_of(GPIO\Bulk::class, \ArrayAccess::class));
var_dump(is_subclass_of(GPIO\Bulk::class, \Iterator::class));
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
