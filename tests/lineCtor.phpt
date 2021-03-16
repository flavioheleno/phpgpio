--TEST--
GPIO\Line Constructor Restriction Test
--SKIPIF--
<?php
if (! extension_loaded('phpgpio')) {
  exit('skip');
}
?>
--FILE--
<?php
try {
  new GPIO\Line();
} catch (\Error $exception) {
  echo $exception->getMessage();
}
?>
--EXPECT--
Cannot directly construct GPIO\Line
