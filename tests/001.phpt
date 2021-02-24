--TEST--
Check if phpgpio is loaded
--SKIPIF--
<?php
if (!extension_loaded('phpgpio')) {
  echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "phpgpio" is available';
?>
--EXPECT--
The extension "phpgpio" is available
