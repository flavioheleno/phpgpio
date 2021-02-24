--TEST--
Check if constants are defined
--SKIPIF--
<?php
if (!extension_loaded('phpgpio')) {
  echo 'skip';
}
?>
--FILE--
<?php
var_dump(defined('GPIO\\BIAS_UNKNOWN'));
var_dump(defined('GPIO\\BIAS_DISABLED'));
var_dump(defined('GPIO\\BIAS_PULL_UP'));
var_dump(defined('GPIO\\BIAS_PULL_DOWN'));
var_dump(defined('GPIO\\DIRECTION_INPUT'));
var_dump(defined('GPIO\\DIRECTION_OUTPUT'));
var_dump(defined('GPIO\\DRIVE_PUSH_PULL'));
var_dump(defined('GPIO\\DRIVE_OPEN_DRAIN'));
var_dump(defined('GPIO\\DRIVE_OPEN_SOURCE'));
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)