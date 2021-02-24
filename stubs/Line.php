<?php

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
   * @param \GPIO\LineRequest $config  Request config (see gpiod::line_request).
   * @param int               $default Default value (only matters for OUTPUT direction).
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
