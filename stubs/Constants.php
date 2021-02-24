<?php

namespace GPIO;

/**
 * Line's bias state is unknown.
 * @var int
 */
const BIAS_UNKNOWN = 1;

/**
 * Line's internal bias is disabled.
 * @var int
 */
const BIAS_DISABLED = 2;

/**
 * Line's internal pull-up bias is enabled.
 * @var int
 */
const BIAS_PULL_UP = 3;

/**
 * Line's internal pull-down bias is enabled.
 * @var int
 */
const BIAS_PULL_DOWN = 4;

/**
 * Line's direction setting is input.
 * @var int
 */
const DIRECTION_INPUT = 1;

/**
 * Line's direction setting is output.
 * @var int
 */
const DIRECTION_OUTPUT = 2;

/**
 * Drive setting is unknown.
 * @var int
 */
const DRIVE_PUSH_PULL = 1;

/**
 * Line output is open-drain.
 * @var int
 */
const DRIVE_OPEN_DRAIN = 2;

/**
 * Line output is open-source.
 * @var int
 */
const DRIVE_OPEN_SOURCE = 3;
