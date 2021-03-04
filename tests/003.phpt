--TEST--
Validate constants values
--SKIPIF--
<?php
if (! extension_loaded('phpgpio')) {
  exit('skip');
}
?>
--FILE--
<?php
var_dump(GPIO\BIAS_UNKNOWN);
var_dump(GPIO\BIAS_DISABLED);
var_dump(GPIO\BIAS_PULL_UP);
var_dump(GPIO\BIAS_PULL_DOWN);
var_dump(GPIO\DIRECTION_INPUT);
var_dump(GPIO\DIRECTION_OUTPUT);
var_dump(GPIO\DRIVE_PUSH_PULL);
var_dump(GPIO\DRIVE_OPEN_DRAIN);
var_dump(GPIO\DRIVE_OPEN_SOURCE);
var_dump(GPIO\EXTENSION_VERSION);
var_dump(GPIO\LIBRARY_VERSION);
?>
--EXPECT--
int(1)
int(2)
int(3)
int(4)
int(1)
int(2)
int(1)
int(2)
int(3)
string(9) "0.0.1-dev"
string(9) "2.0-devel"
