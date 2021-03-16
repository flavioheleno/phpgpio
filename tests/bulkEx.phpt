--TEST--
GPIO\Bulk Extended Class Test
--SKIPIF--
<?php
if (! extension_loaded('phpgpio')) {
  die('skip');
}

if (! GPIO\Chip::isDevice('/dev/gpiochip0')) {
  die('skip');
}
?>
--FILE--
<?php
$chip = new GPIO\Chip('/dev/gpiochip0');
$bulk = $chip->getAllLines();
try {
  $bulk->foo = 1;
} catch (\Error $exception) {
  echo $exception->getMessage(), PHP_EOL;
}

try {
  $bulk[0] = 1;
} catch (\Error $exception) {
  echo $exception->getMessage(), PHP_EOL;
}

try {
  unset($bulk->foo);
} catch (\Error $exception) {
  echo $exception->getMessage(), PHP_EOL;
}

try {
  unset($bulk[0]);
} catch (\Error $exception) {
  echo $exception->getMessage(), PHP_EOL;
}
?>
--EXPECT--
Cannot create dynamic property GPIO\Bulk::$foo
Cannot set GPIO\Bulk line at offset 0
Cannot unset GPIO\Bulk::$foo property
Cannot unset GPIO\Bulk line at offset 0
