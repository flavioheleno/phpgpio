<?php

namespace GPIO;

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
