<?php

namespace Gpiod;

/**
 * Represents a GPIO chip.
 */
final class Chip {
  /**
   * Opens the chip using chip::open.
   *
   * @param string $path Path to the GPIO chip device.
   *
   * @return void
   */
  public function __construct(string $path) {
  }

  /**
   * Find all GPIO lines by name among lines exposed by this GPIO chip.
   *
   * @param string $name   Line name.
   * @param bool   $unique If set to true: throw an error if multiple lines match the name.
   *
   * @return \Gpiod\Lines Vector of all matching lines.
   */
  public function findLine(string $name, bool $unique): Lines {
  }

  /**
   * Get all lines exposed by this chip.
   *
   * @return \Gpiod\Lines All lines exposed by this chip held by a line_bulk object.
   */
  public function getAllLines(): Lines {
  }

  /**
   * Get the line exposed by this chip at given offset.
   *
   * @param int $offset Offset of the line.
   *
   * @return \Gpiod\Line Line object.
   */
  public function getLine(int $offset): Line {
  }

  /**
   * Get a set of lines exposed by this chip at given offsets.
   *
   * @param int[] $offsets Vector of line offsets.
   *
   * @return \Gpiod\Lines Set of lines held by a line_bulk object.
   */
  public function getLines(array $offsets): Lines {
  }

  /**
   * Return the label of the chip held by this object.
   *
   * @return string Label of the GPIO chip.
   */
  public function getLabel(): string {
  }

  /**
   * Return the name of the chip held by this object.
   *
   * @return string Name of the GPIO chip.
   */
  public function getName(): string {
  }
}
