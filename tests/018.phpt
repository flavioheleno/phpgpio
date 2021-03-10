--TEST--
Test extension on BCM2711 (Raspberry Pi 4B)
--SKIPIF--
<?php
if (! extension_loaded('phpgpio')) {
  exit('skip');
}

if (is_file('/sys/firmware/devicetree/base/model') === false) {
  exit('skip');
}

$model = file_get_contents('/sys/firmware/devicetree/base/model');
if (preg_match('/^Raspberry Pi 4/', $model) !== 1) {
  exit('skip');
}

if (GPIO\Chip::isDevice('/dev/gpiochip0') === false) {
  exit('skip');
}

$chip = new GPIO\Chip('/dev/gpiochip0');
if ($chip->getLabel() !== 'pinctrl-bcm2711') {
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
int(58)
string(9) "GPIO\Line"
string(6) "ID_SDA"
string(6) "ID_SDA"
string(6) "ID_SCL"
string(4) "SDA1"
string(4) "SCL1"
string(9) "GPIO_GCLK"
string(5) "GPIO5"
string(5) "GPIO6"
string(9) "SPI_CE1_N"
string(9) "SPI_CE0_N"
string(8) "SPI_MISO"
string(8) "SPI_MOSI"
string(8) "SPI_SCLK"
string(6) "GPIO12"
string(6) "GPIO13"
string(4) "TXD1"
string(4) "RXD1"
string(6) "GPIO16"
string(6) "GPIO17"
string(6) "GPIO18"
string(6) "GPIO19"
string(6) "GPIO20"
string(6) "GPIO21"
string(6) "GPIO22"
string(6) "GPIO23"
string(6) "GPIO24"
string(6) "GPIO25"
string(6) "GPIO26"
string(6) "GPIO27"
string(10) "RGMII_MDIO"
string(9) "RGMIO_MDC"
string(4) "CTS0"
string(4) "RTS0"
string(4) "TXD0"
string(4) "RXD0"
string(7) "SD1_CLK"
string(7) "SD1_CMD"
string(9) "SD1_DATA0"
string(9) "SD1_DATA1"
string(9) "SD1_DATA2"
string(9) "SD1_DATA3"
string(9) "PWM0_MISO"
string(9) "PWM1_MOSI"
string(16) "STATUS_LED_G_CLK"
string(13) "SPIFLASH_CE_N"
string(4) "SDA0"
string(4) "SCL0"
string(11) "RGMII_RXCLK"
string(11) "RGMII_RXCTL"
string(10) "RGMII_RXD0"
string(10) "RGMII_RXD1"
string(10) "RGMII_RXD2"
string(10) "RGMII_RXD3"
string(11) "RGMII_TXCLK"
string(11) "RGMII_TXCTL"
string(10) "RGMII_TXD0"
string(10) "RGMII_TXD1"
string(10) "RGMII_TXD2"
string(10) "RGMII_TXD3"
int(58)
string(4) "led0"
