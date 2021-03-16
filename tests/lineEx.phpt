--TEST--
GPIO\Line Extended Class Test
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
$line = $chip->getLine(0);
try {
  $line->foo = 1;
} catch (\Error $exception) {
  echo $exception->getMessage(), PHP_EOL;
}

try {
  $line[0] = 1;
} catch (\Error $exception) {
  echo $exception->getMessage(), PHP_EOL;
}

try {
  unset($line->foo);
} catch (\Error $exception) {
  echo $exception->getMessage(), PHP_EOL;
}

try {
  unset($line[0]);
} catch (\Error $exception) {
  echo $exception->getMessage(), PHP_EOL;
}
?>
--EXPECT--
Cannot create dynamic property GPIO\Line::$foo
Cannot use object of type GPIO\Line as array
Cannot unset GPIO\Line::$foo property
Cannot use object of type GPIO\Line as array
