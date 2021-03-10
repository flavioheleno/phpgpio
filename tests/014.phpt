--TEST--
Test extension on BCM2835 (Raspberry Pi 1 and Zero)
--SKIPIF--
<?php
if (! extension_loaded('phpgpio')) {
  exit('skip');
}

if (is_file('/sys/firmware/devicetree/base/model') === false) {
  exit('skip');
}

$model = file_get_contents('/sys/firmware/devicetree/base/model');
if (preg_match('/^Raspberry Pi (Model|Zero)/', $model) !== 1) {
  exit('skip');
}

if (GPIO\Chip::isDevice('/dev/gpiochip0') === false) {
  exit('skip');
}

$chip = new GPIO\Chip('/dev/gpiochip0');
if ($chip->getLabel() !== 'pinctrl-bcm2835') {
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

$model = file_get_contents('/sys/firmware/devicetree/base/model');
if (preg_match('/^Raspberry Pi Model [AB]/', $model) !== 1) {
  // RPi 1
  var_dump($bulk[16]->getConsumer());
}

if (preg_match('/^Raspberry Pi Zero/', $model) !== 1) {
  // RPi Zero
  var_dump($bulk[47]->getConsumer());
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
