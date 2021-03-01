# phpgpio

A [libgpiod](https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git/) wrapper for PHP

## Building

```bash
php stubs/update-main-stup.php
phpize
./configure
make
make test
```

## Constants

All namespace defined constants can be seen in [Constants.php](stubs/Constants.php) stub.

## Classes

Class                                 | Description
--------------------------------------|------------
[GPIO\Bulk](stubs/Bulk.php)           | Represents multiple GPIO lines.
[GPIO\Chip](stubs/Chip.php)           | Represents a GPIO chip.
[GPIO\Exception](stubs/Exception.php) | Base exception.
[GPIO\Line](stub/Line.php)            | Represents a single GPIO line.

## License

This library is licensed under the [PHP License](LICENSE).
