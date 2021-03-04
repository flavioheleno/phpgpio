--TEST--
Test extension on BCM2836 (Raspberry Pi 2)
--SKIPIF--
<?php
if (! extension_loaded('phpgpio')) {
  exit('skip');
}

if (GPIO\Chip::isDevice('/dev/gpiochip0') === false) {
  exit('skip');
}

$chip = new GPIO\Chip('/dev/gpiochip0');
if ($chip->getLabel() !== 'pinctrl-bcm2836') {
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
