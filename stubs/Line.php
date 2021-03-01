<?php

namespace GPIO;

/**
 * Represents a single GPIO line.
 */
final class Line {
  /**
   * Parent chip.
   *
   * @var \GPIO\Chip
   */
  private Chip $chip;

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
   * @param \GPIO\LineRequest $config  Request config (see gpiod::line_request).
   * @param int               $default Default value (only matters for OUTPUT direction).
   */
  public function request(LineRequest $lineRequest, int $default = 0): void {}

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
