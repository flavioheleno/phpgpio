<?php

/** @generate-function-entries */

namespace GPIO;

/**
 * Represents a single GPIO line.
 */
final class Line {
  /**
   * Line's bias state is unknown.
   * @var int
   */
  public const BIAS_UNKNOWN = 1;

  /**
   * Line's internal bias is disabled.
   * @var int
   */
  public const BIAS_DISABLED = 2;

  /**
   * Line's internal pull-up bias is enabled.
   * @var int
   */
  public const BIAS_PULL_UP = 3;

  /**
   * Line's internal pull-down bias is enabled.
   * @var int
   */
  public const BIAS_PULL_DOWN = 4;

  /**
   * Line's direction setting is input.
   * @var int
   */
  public const DIRECTION_INPUT = 1;

  /**
   * Line's direction setting is output.
   * @var int
   */
  public const DIRECTION_OUTPUT = 2;

  /**
   * Drive setting is unknown.
   * @var int
   */
  public const DRIVE_PUSH_PULL = 1;

  /**
   * Line output is open-drain.
   * @var int
   */
  public const DRIVE_OPEN_DRAIN = 2;

  /**
   * Line output is open-source.
   * @var int
   */
  public const DRIVE_OPEN_SOURCE = 3;

  /**
   * Get current bias of this line.
   *
   * @return int
   */
  public function bias(): int {}

  /**
   * Get the consumer of this line (if any).
   *
   * @return string
   */
  public function consumer(): string {}

  /**
   * Get current direction of this line.
   *
   * @return int
   */
  public function direction(): int {}

  /**
   * Get current drive setting of this line.
   *
   * @return int
   */
  public function drive(): int {}

  /**
   * Get the parent chip.
   *
   * @return \GPIO\Chip
   */
  public function getChip(): Chip {}

  /**
   * Read the line value.
   *
   * @return int
   */
  public function getValue(): int {}

  /**
   * Check if this line's signal is inverted.
   *
   * @return bool
   */
  public function isActiveLow(): bool {}

  /**
   * Check if this user has ownership of this line.
   *
   * @return bool
   */
  public function isRequested(): bool {}

  /**
   * Check if this line is used by the kernel or other user space process.
   *
   * @return bool
   */
  public function isUsed(): bool {}

  /**
   * Get the name of this line (if any).
   *
   * @return string
   */
  public function name(): string {}

  /**
   * Get the offset of this line.
   *
   * @return int
   */
  public function offset(): int {}

  /**
   * Request this line.
   *
   * @param \GPIO\LineRequest $config   Request config (see gpiod::line_request).
   * @param int               $default  Default value (only matters for OUTPUT direction).
   */
  public function request(LineRequest $lineRequest, int $default = 0): void {}

  /**
   * Reset the state of this object.
   *
   * This is useful when the user needs to e.g. keep the line_event object but wants to drop the reference to the GPIO
   * chip indirectly held by the line being the source of the event.
   */
  public function reset(): void {}

  /**
   * Set configuration of this line.
   *
   * @param int $direction New direction.
   * @param int $flags     Replacement flags.
   * @param int $value     New value (0 or 1) - only matters for OUTPUT direction.
   */
  public function setConfig(int $direction, int $flags, int $value = 0): void {}

  /**
   * Change the direction this lines to output.
   *
   * @param int $value New value (0 or 1).
   */
  public function setDirectionOutput(int $value = 0): void {}

  /**
   * Set configuration flags of this line.
   *
   * @param int $flags Replacement flags.
   */
  public function setFlags(int $flags): void {}

  /**
   * Set the value of this line.
   *
   * @param int $value New value (0 or 1).
   */
  public function setValue(int $value): void {}
}

/**
 * Represents multiple GPIO lines.
 */
final class Lines implements \Countable, \ArrayAccess, \Iterator {
  /**
   * Count elements of an object
   *
   * @return void
   */
  public function count(): int {}

  /**
   * Whether or not an offset exists.
   *
   * @param mixed $offset An offset to check for.
   *
   * @return bool
   */
  public function offsetExists($offset): bool {}

  /**
   * Returns the value at specified offset.
   *
   * @param mixed $offset The offset to retrieve.
   *
   * @return mixed
   */
  public function offsetGet($offset) {}

  /**
   * Assigns a value to the specified offset.
   *
   * @param mixed $offset The offset to assign the value to.
   * @param mixed $value  The value to set.
   *
   * @return void
   */
  public function offsetSet($offset, $value) {}

  /**
   * Unsets an offset.
   *
   * @param mixed $offset The offset to unset.
   *
   * @return void
   */
  public function offsetUnset($offset) {}

  /**
   * Returns the current element.
   *
   * @return mixed
   */
  public function current() {}

  /**
   * Returns the key of the current element.
   *
   * @return mixed
   */
  public function key() {}

  /**
   * Moves the current position to the next element.
   *
   * @return void
   */
  public function next(): void {}

  /**
   * Rewinds back to the first element of the Iterator.
   *
   * @return void
   */
  public function rewind(): void {}

  /**
   * Check if the current position is valid.
   *
   * @return bool
   */
  public function valid(): bool {}
}

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
   * @return \GPIO\Lines
   */
  public function findLine(string $name, bool $unique): Lines {
  }

  /**
   * Get all lines exposed by this chip.
   *
   * @return \GPIO\Lines
   */
  public function getAllLines(): Lines {
  }

  /**
   * Get the line exposed by this chip at given offset.
   *
   * @param int $offset Offset of the line.
   *
   * @return \GPIO\Line
   */
  public function getLine(int $offset): Line {
  }

  /**
   * Get a set of lines exposed by this chip at given offsets.
   *
   * @param int[] $offsets Vector of line offsets.
   *
   * @return \GPIO\Lines
   */
  public function getLines(array $offsets): Lines {
  }

  /**
   * Return the label of the chip held by this object.
   *
   * @return string
   */
  public function getLabel(): string {
  }

  /**
   * Return the name of the chip held by this object.
   *
   * @return string
   */
  public function getName(): string {
  }
}
