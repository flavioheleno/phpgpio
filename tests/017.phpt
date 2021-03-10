--TEST--
Test extension on BCM2837B0 (Raspberry Pi 3B+ and 3A+)
--SKIPIF--
<?php
if (! extension_loaded('phpgpio')) {
  exit('skip');
}

if (is_file('/sys/firmware/devicetree/base/model') === false) {
  exit('skip');
}

$model = file_get_contents('/sys/firmware/devicetree/base/model');
if (preg_match('/^Raspberry Pi 3/', $model) !== 1) {
  exit('skip');
}

if (GPIO\Chip::isDevice('/dev/gpiochip0') === false) {
  exit('skip');
}

$chip = new GPIO\Chip('/dev/gpiochip0');
if ($chip->getLabel() !== 'pinctrl-bcm2837b0') {
  exit('skip');
}
?>
--FILE--
<?php
$chip = new GPIO\Chip('/dev/gpiochip0');
var_dump($chip->getLineCount());
$line = $chip->getLine(0);
var_dump(get_class($line));
var_dump($line->getName());
$bulk = $chip->getAllLines();
foreach ($bulk as $l) {
  var_dump($l->getName());
}

var_dump(count($bulk));
var_dump($bulk[42]->getConsumer());
?>
--EXPECT--

