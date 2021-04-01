<?php

/** @generate-function-entries */

namespace GPIO;

/**
 * Represents multiple GPIO lines.
 */
final class Bulk implements \Countable, \ArrayAccess, \Iterator {
  /**
   * Parent chip instance.
   *
   * @var \GPIO\Chip
   */
  private Chip $chip;

  /**
   * Get the parent chip.
   *
   * @return \GPIO\Chip
   */
  public function getChip(): Chip {}

  /**
   * Count elements of an object
   *
   * @return int
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
   * Map a GPIO line's name to its offset within the chip.
   *
   * @param string $name Line name.
   *
   * @return int
   */
  public function findLine(string $name): int {}

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

/************** INTERNAL BIAS **************/
/**
 * Line's bias state is unknown.
 * @var int
 */
const BIAS_UNKNOWN = 0x01;

/**
 * Line's internal bias is disabled.
 * @var int
 */
const BIAS_DISABLED = 0x02;

/**
 * Line's internal pull-up bias is enabled.
 * @var int
 */
const BIAS_PULL_UP = 0x03;

/**
 * Line's internal pull-down bias is enabled.
 * @var int
 */
const BIAS_PULL_DOWN = 0x04;

/************** DIRECTION SETTINGS **************/
/**
 * Line's direction setting is input.
 * @var int
 */
const DIRECTION_INPUT = 0x01;

/**
 * Line's direction setting is output.
 * @var int
 */
const DIRECTION_OUTPUT = 0x02;

/************** DRIVE SETTINGS **************/
/**
 * Drive setting is unknown.
 * @var int
 */
const DRIVE_PUSH_PULL = 0x01;

/**
 * Line output is open-drain.
 * @var int
 */
const DRIVE_OPEN_DRAIN = 0x02;

/**
 * Line output is open-source.
 * @var int
 */
const DRIVE_OPEN_SOURCE = 0x03;

/************** LINE REQUEST TYPES **************/
/**
 * Request the line(s), but don't change current direction.
 * @var int
 */
const REQUEST_DIRECTION_AS_IS = 0x01;
/**
 * Request the line(s) for reading the GPIO line state.
 * @var int
 */
const REQUEST_DIRECTION_INPUT = 0x02;
/**
 * Request the line(s) for setting the GPIO line state.
 * @var int
 */
const REQUEST_DIRECTION_OUTPUT = 0x03;
/**
 * Only watch falling edge events.
 * @var int
 */
const REQUEST_EVENT_FALLING_EDGE = 0x04;
/**
 * Only watch rising edge events.
 * @var int
 */
const REQUEST_EVENT_RISING_EDGE = 0x05;
/**
 * Monitor both types of events.
 * @var int
 */
const REQUEST_EVENT_BOTH_EDGES = 0x06;

/************** LINE REQUEST FLAGS **************/
/**
 * No flags.
 * @var int
 */
const REQUEST_FLAG_NONE = 0x00;
/**
 * The line is an open-drain port.
 * @var int
 */
const REQUEST_FLAG_OPEN_DRAIN = 0x01;
/**
 * The line is an open-source port.
 * @var int
 */
const REQUEST_FLAG_OPEN_SOURCE = 0x02;
/**
 * The active state of the line is low (high is the default).
 * @var int
 */
const REQUEST_FLAG_ACTIVE_LOW = 0x04;
/**
 * The line has neither either pull-up nor pull-down resistor.
 * @var int
 */
const REQUEST_FLAG_BIAS_DISABLED = 0x08;
/**
 * The line has pull-down resistor enabled.
 * @var int
 */
const REQUEST_FLAG_BIAS_PULL_DOWN = 0x10;
/**
 * The line has pull-up resistor enabled.
 * @var int
 */
const REQUEST_FLAG_BIAS_PULL_UP = 0x20;

/************** EVENT TYPES **************/
/**
 * Rising edge event.
 * @var int
 */
const EVENT_RISING_EDGE = 0x01;
/**
 * Falling edge event.
 * @var int
 */
const EVENT_FALLING_EDGE = 0x02;

/**
 * Base exception
 */
class Exception extends \Exception {}

/**
 * Represents a single GPIO line.
 */
final class Line {
  /**
   * Parent chip instance.
   *
   * @var \GPIO\Chip
   */
  private Chip $chip;

  /**
   * @var int
   */
  public const VALUE_HIGH = 1;
  /**
   * @var int
   */
  public const VALUE_LOW = 0;

  /**
   * Get current bias of this line.
   *
   * @return int
   */
  public function getBias(): int {}

  /**
   * Get the consumer of this line (if any).
   *
   * @return string
   */
  public function getConsumer(): string {}

  /**
   * Get current direction of this line.
   *
   * @return int
   */
  public function getDirection(): int {}

  /**
   * Get current drive setting of this line.
   *
   * @return int
   */
  public function getDrive(): int {}

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
  public function getName(): string {}

  /**
   * Get the offset of this line.
   *
   * @return int
   */
  public function getOffset(): int {}

  /**
   * Request this line.
   *
   * @param string $consumer Name of the consumer.
   * @param int    $type     Request type.
   * @param int    $flags    Configuration flags.
   * @param int    $value    Default value (only matters for OUTPUT direction).
   */
  public function request(string $consumer, int $type, int $flags, int $value = self::VALUE_LOW): void {}

  /**
   * Set configuration of this line.
   *
   * @param int $direction New direction.
   * @param int $flags     Replacement flags.
   * @param int $value     New value (0 or 1) - only matters for OUTPUT direction.
   */
  public function setConfig(int $direction, int $flags, int $value = self::VALUE_LOW): void {}

  /**
   * Change the direction of this line to input.
   */
  public function setDirectionInput(): void {}

  /**
   * Change the direction of this line to output.
   *
   * @param int $value New value (0 or 1).
   */
  public function setDirectionOutput(int $value = self::VALUE_LOW): void {}

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

