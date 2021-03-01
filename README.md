# phpgpio

A [libgpiod](https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git/) wrapper for PHP

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

## Constants

All namespace defined constants can be seen in [Constants.php](stubs/Constants.php) stub.

## Classes

Class                                 | Description
--------------------------------------|------------
[GPIO\Bulk](stubs/Bulk.php)           | Represents multiple GPIO lines.
[GPIO\Chip](stubs/Chip.php)           | Represents a GPIO chip.
[GPIO\Exception](stubs/Exception.php) | Base exception.
[GPIO\Line](stub/Line.php)            | Represents a single GPIO line.

## Tools

Name                               | Description
-----------------------------------|------------
[gpiodetect](tools/gpiodetect.php) | List all GPIO chips, print their labels and number of GPIO lines.
[gpioinfo](tools/gpioinfo.php)     | Print information about all lines of the specified GPIO chip(s) (or all gpiochips if none are specified).

## License

This library is licensed under the [PHP License](LICENSE).
