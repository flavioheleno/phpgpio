--TEST--
BCM2837 Test (Raspberry Pi 3 (and later Raspberry Pi 2))
--SKIPIF--
<?php
if (! extension_loaded('phpgpio')) {
  exit('skip');
}

if (is_file('/sys/firmware/devicetree/base/model') === false) {
  exit('skip');
}

$model = file_get_contents('/sys/firmware/devicetree/base/model');
if (preg_match('/^Raspberry Pi [23]/', $model) !== 1) {
  exit('skip');
}

if (GPIO\Chip::isDevice('/dev/gpiochip0') === false) {
  exit('skip');
}

$chip = new GPIO\Chip('/dev/gpiochip0');
if ($chip->getLabel() !== 'pinctrl-bcm2837') {
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
var_dump($bulk[29]->getConsumer());

$bulk = $chip->getLines([1, 14, 52, 7, 2, 0]);
foreach ($bulk as $line) {
  var_dump($line->getOffset());
}
?>
--EXPECT--
int(54)
string(9) "GPIO\Line"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
string(7) "unnamed"
int(54)
string(4) "led0"
int(1)
int(14)
int(52)
int(7)
int(2)
int(0)
