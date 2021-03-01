<?php

namespace GPIO;

/**
 * Represents a GPIO chip.
 */
final class Chip {
  /**
   * Path to the GPIO chip device.
   *
   * @var string
   */
  private string $path;

  /**
   * Returns if the given path is a valid GPIO chip device.
   *
   * @param string $path Path to the device.
   *
   * @return bool
   */
  public static function isDevice(string $path): bool {}

  /**
   * Opens the chip.
   *
   * @param string $path Path to the GPIO chip device.
   *
   * @return void
   */
  public function __construct(string $path) {}

  /**
   * Find all GPIO lines by name among lines exposed by this GPIO chip.
   * Note: Throws an error if multiple lines match the name.
   *
   * @param string $name Line name.
   *
   * @return \GPIO\Line
   */
  public function findLineUnique(string $name): Line {}

  /**
   * Find all GPIO lines by name among lines exposed by this GPIO chip.
   *
   * @param string $name Line name.
   *
   * @return \GPIO\Bulk
   */
  public function findAllLines(string $name): Bulk {}

  /**
   * Get all lines exposed by this chip.
   *
   * @return \GPIO\Bulk
   */
  public function getAllLines(): Bulk {}

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
   * @return \GPIO\Bulk
   */
  public function getLines(array $offsets): Bulk {}

  /**
   * Return the number of available lines.
   *
   * @return int
   */
  public function getLineCount(): int {}

  /**
   * Return the path to the GPIO chip device.
   *
   * @return string
   */
  public function getPath(): string {}

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
