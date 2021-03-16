--TEST--
GPIO\Bulk Constructor Restriction Test
--SKIPIF--
<?php
if (! extension_loaded('phpgpio')) {
  exit('skip');
}
?>
--FILE--
<?php
try {
  new GPIO\Bulk();
} catch (\Error $exception) {
  echo $exception->getMessage();
}
?>
--EXPECT--
Cannot directly construct GPIO\Bulk
