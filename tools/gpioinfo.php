#!/usr/bin/env php
<?php
declare(strict_types = 1);

/**
 * Ported from the original gpioinfo provided by libgpiod
 *
 * @link https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git/tree/tools/gpioinfo.c
 */

if (extension_loaded('phpgpio') === false) {
  echo 'To use this tool, you must first install/enable the "phpgpio" extension!', PHP_EOL;

  return 1;
}

if (isset($argv[1]) && in_array($argv[1], ['-h', '--help'])) {
  echo 'Usage: ', $argv[0], ' [OPTIONS] <gpiochip1> ...', PHP_EOL;
  echo PHP_EOL;
  echo 'Print information about all lines of the specified GPIO chip(s) (or all gpiochips if none are specified).', PHP_EOL;
  echo PHP_EOL;
  echo 'Options:', PHP_EOL;
  echo '  -h, --help:    display this message and exit', PHP_EOL;
  echo '  -v, --version: display the version and exit', PHP_EOL;

  return 0;
}

if (isset($argv[1]) && in_array($argv[1], ['-v', '--version'])) {
  echo basename(__FILE__), ' phpgpio/', GPIO\EXTENSION_VERSION, ' (libgpiod/', GPIO\LIBRARY_VERSION, ')', PHP_EOL;
  echo PHP_EOL;
  echo 'URL: https://github.com/flavioheleno/phpgpio', PHP_EOL;
  echo 'License: The PHP License, version 3.01', PHP_EOL;
  echo PHP_EOL;
  echo 'This is free software: you are free to change and redistribute it.', PHP_EOL;
  echo 'There is NO WARRANTY, to the extent permitted by law.', PHP_EOL;

  return 0;
}

$argList = [];
if ($argc === 1) {
  $directory = new DirectoryIterator('/dev');
  foreach ($directory as $fileInfo) {
    if ($fileInfo->getType() !== 'char') {
      continue;
    }

    if (preg_match('/^gpiochip[0-9]+$/', $fileInfo->getFilename()) === 1) {
      $argList[] = $fileInfo->getFilename();
    }
  }
}

if ($argc > 1) {
  $argList = array_slice($argv, 1);
}

foreach ($argList as $argValue) {
  if (preg_match('/^gpiochip[0-9]+$/', $argValue) !== 1) {
    echo 'Invalid argument: ', $argValue, PHP_EOL;

    return 1;
  }

  $path = sprintf('/dev/%s', $argValue);
  if (file_exists($path) === false) {
    echo 'Chip not found: ', $argValue, PHP_EOL;

    return 1;
  }

  $chip = new GPIO\Chip($path);
  $count = $chip->getLineCount();
  echo $argValue, ' - ', $count, ' lines:', PHP_EOL;
  $rows = [
    [
      'line',
      'name',
      'used',
      'consumer',
      'direction',
      'status',
      'flags'
    ]
  ];
  for ($offset = 0; $offset < $count; $offset++) {
    $line = $chip->getLine($offset);
    $row = [
      $offset,
      $line->getName() ?? 'unnamed',
      $line->isUsed() ? 'yes' : 'no',
      $line->isUsed() ? $line->getConsumer() ?? 'kernel' : '',
      $line->getDirection() === GPIO\DIRECTION_INPUT ? 'input ' : 'output ',
      $line->isActiveLow() ? 'active-low ' : 'active-high '
    ];

    $flags = [];
    switch ($line->getDrive()) {
      case GPIO\DRIVE_OPEN_DRAIN:
        $flags[] = 'open-drain';
        break;
      case GPIO\DRIVE_OPEN_SOURCE:
        $flags[] = 'open-source';
        break;
    }

    switch ($line->getBias()) {
      case GPIO\BIAS_PULL_UP:
        $flags[] = 'pull-up';
        break;
      case GPIO\BIAS_PULL_DOWN:
        $flags[] = 'pull-down';
        break;
      case GPIO\BIAS_DISABLED:
        $flags[] = 'bias-disabled';
        break;
    }

    $row[] = implode(', ', $flags);
    $rows[] = $row;
  }

  $format = [];
  $break  = [];
  for ($i = 0; $i < 7; $i++) {
    $size = max(
      array_map(
        'strlen',
        array_column($rows, $i)
      )
    );
    $format[] = sprintf(
      ' %%-%ds ',
      $size
    );
    $break[] = str_repeat('-', $size + 2);
  }

  echo implode('|', array_map('sprintf', $format, $rows[0])), PHP_EOL;
  echo implode('|', $break), PHP_EOL;
  for ($i = 1; $i <= $count; $i++) {
    echo implode('|', array_map('sprintf', $format, $rows[$i])), PHP_EOL;
  }
}

return 0;
