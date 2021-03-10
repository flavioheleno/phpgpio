# phpgpio

Object-oriented PHP bindings for the [libgpiod](https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git/) library

## Requirements

- PHP >= 8.0 (either NTS or TS version);
- libgpiod >= 1.6

## Building

```bash
phpize
./configure
make
make test
```

## Stubs

After changing any of the [stubs](stubs/), the main [stub file](phpgpio.stub.php) must be updated by running the command below.

```bash
php stubs/update-main-stup.php
```

Once the stub is updated, the regular build process can be executed.

**Note:** The main stub file ([phpgpio.stub.php](phpgpio.stub.php)) is a generated file, edit the files on the [stubs](stubs/) folder instead.

## Constants

All namespace defined constants can be seen in the [Constants.php](stubs/Constants.php) stub.

## Classes

Class                                 | Description
--------------------------------------|------------
[GPIO\Bulk](stubs/Bulk.php)           | Represents multiple GPIO lines.
[GPIO\Chip](stubs/Chip.php)           | Represents a GPIO chip.
[GPIO\Exception](stubs/Exception.php) | Base exception.
[GPIO\Line](stub/Line.php)            | Represents a single GPIO line.

## Tools

Name                                   | Description
---------------------------------------|------------
[gpiodetect.php](tools/gpiodetect.php) | List all GPIO chips, print their labels and number of GPIO lines.
[gpioinfo.php](tools/gpioinfo.php)     | Print information about all lines of the specified GPIO chip(s) (or all gpiochips if none are specified).

## Supported Hardware

The table below lists the supported and tested chips.

SoC                         | Model
----------------------------|------
[BCM2835](tests/014.phpt)   | [Raspberry Pi 1 and Zero](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/README.md)
[BCM2836](tests/015.phpt)   | [Raspberry Pi 2](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2836/README.md)
[BCM2837](tests/016.phpt)   | [Raspberry Pi 3 (and later Raspberry Pi 2)](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2837/README.md)
[BCM2837B0](tests/017.phpt) | [Raspberry Pi 3B+ and 3A+](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2837b0/README.md)
[BCM2711](tests/018.phpt)   | [Raspberry Pi 4B](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2711/README.md)

## Alternatives

- [PiPHP/GPIO](https://github.com/PiPHP/GPIO)
- [ronanguilloux/php-gpio](https://github.com/ronanguilloux/php-gpio)
- [Volantus/php-pigpio](https://github.com/Volantus/php-pigpio)

## Other Languages

- Golang: [periph/conn](https://github.com/periph/conn)
- Golang: [warthog618/gpiod](https://github.com/warthog618/gpiod)
- Java: [mattjlewis/diozero](https://github.com/mattjlewis/diozero)
- NodeJS: [sombriks/node-libgpiod](https://github.com/sombriks/node-libgpiod)

## License

This library is licensed under the [PHP License](LICENSE).
