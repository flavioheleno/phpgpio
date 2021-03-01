--TEST--
Check if classes are defined
--SKIPIF--
<?php
if (!extension_loaded('phpgpio')) {
  echo 'skip';
}
?>
--FILE--
<?php
var_dump(class_exists('GPIO\\Chip'));
var_dump(class_exists('GPIO\\Exception'));
var_dump(class_exists('GPIO\\Line'));
var_dump(class_exists('GPIO\\Bulk'));
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
