<?php

namespace GPIO;

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
