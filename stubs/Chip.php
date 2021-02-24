<?php

namespace GPIO;

/**
 * Represents a GPIO chip.
 */
final class Chip {
  /**
   * Returns if the given path is a valid GPIO chip device.
   *
   * @param string $path Path to the device.
   *
   * @return bool
   */
  public static function isDevice(string $path): bool {}

  /**
   * Opens the chip using chip::open.
   *
   * @param string $path Path to the GPIO chip device.
   *
   * @return void
   */
  public function __construct(string $path) {}

  /**
   * Find all GPIO lines by name among lines exposed by this GPIO chip.
   *
   * @param string $name   Line name.
   * @param bool   $unique If set to true: throw an error if multiple lines match the name.
   *
   * @return \GPIO\Lines
   */
  public function findLine(string $name, bool $unique): Lines {}

  /**
   * Get all lines exposed by this chip.
   *
   * @return \GPIO\Lines
   */
  public function getAllLines(): Lines {}

  /**
   * Get the line exposed by this chip at given offset.
   *
   * @param int $offset Offset of the line.
   *
   * @return \GPIO\Line
   */
  public function getLine(int $offset): Line {}

  /**
   * Get a set of lines exposed by this chip at given offsets.
   *
   * @param int[] $offsets Vector of line offsets.
   *
   * @return \GPIO\Lines
   */
  public function getLines(array $offsets): Lines {}

  /**
   * Return the label of the chip held by this object.
   *
   * @return string
   */
  public function getLabel(): string {}

  /**
   * Return the name of the chip held by this object.
   *
   * @return string
   */
  public function getName(): string {}
}
