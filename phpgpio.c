/*
   +----------------------------------------------------------------------+
   | Copyright (c) The PHP Group                                          |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Flavio Heleno <https://github.com/flavioheleno>              |
   +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "phpgpio.h"
#include "phpgpio_arginfo.h"

#include "src/line.h"
#include "src/bulk.h"
#include "src/exception.h"
#include "src/chip.h"

#include <gpiod.h>

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
  ZEND_PARSE_PARAMETERS_START(0, 0) \
  ZEND_PARSE_PARAMETERS_END()
#endif

/* Class entry pointers (global resources) */
zend_class_entry *zceChip;
zend_class_entry *zceException;
zend_class_entry *zceLine;
zend_class_entry *zceBulk;

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(phpgpio) {
  #if defined(ZTS) && defined(COMPILE_DL_PHPGPIO)
    ZEND_TSRMLS_CACHE_UPDATE();
  #endif

  return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(phpgpio) {
  /* Extension constants */
  REGISTER_STRING_CONSTANT("GPIO\\EXTENSION_VERSION", PHP_PHPGPIO_VERSION, CONST_CS | CONST_PERSISTENT);
  REGISTER_STRING_CONSTANT("GPIO\\LIBRARY_VERSION", gpiod_version_string(), CONST_CS | CONST_PERSISTENT);
  /* Possible internal bias settings. */
  REGISTER_LONG_CONSTANT("GPIO\\BIAS_UNKNOWN", GPIOD_LINE_BIAS_UNKNOWN, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\BIAS_DISABLED", GPIOD_LINE_BIAS_DISABLED, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\BIAS_PULL_UP", GPIOD_LINE_BIAS_PULL_UP, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\BIAS_PULL_DOWN", GPIOD_LINE_BIAS_PULL_DOWN, CONST_CS | CONST_PERSISTENT);
  /* Possible direction settings. */
  REGISTER_LONG_CONSTANT("GPIO\\DIRECTION_INPUT", GPIOD_LINE_DIRECTION_INPUT, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\DIRECTION_OUTPUT", GPIOD_LINE_DIRECTION_OUTPUT, CONST_CS | CONST_PERSISTENT);
  /* Possible drive settings. */
  REGISTER_LONG_CONSTANT("GPIO\\DRIVE_PUSH_PULL", GPIOD_LINE_DRIVE_PUSH_PULL, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\DRIVE_OPEN_DRAIN", GPIOD_LINE_DRIVE_OPEN_DRAIN, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\DRIVE_OPEN_SOURCE", GPIOD_LINE_DRIVE_OPEN_SOURCE, CONST_CS | CONST_PERSISTENT);
  /* Available types of requests. */
  REGISTER_LONG_CONSTANT("GPIO\\REQUEST_DIRECTION_AS_IS", GPIOD_LINE_REQUEST_DIRECTION_AS_IS, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\REQUEST_DIRECTION_INPUT", GPIOD_LINE_REQUEST_DIRECTION_INPUT, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\REQUEST_DIRECTION_OUTPUT", GPIOD_LINE_REQUEST_DIRECTION_OUTPUT, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\REQUEST_EVENT_FALLING_EDGE", GPIOD_LINE_REQUEST_EVENT_FALLING_EDGE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\REQUEST_EVENT_RISING_EDGE", GPIOD_LINE_REQUEST_EVENT_RISING_EDGE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\REQUEST_EVENT_BOTH_EDGES", GPIOD_LINE_REQUEST_EVENT_BOTH_EDGES, CONST_CS | CONST_PERSISTENT);
  /* Miscellaneous GPIO request flags. */
  REGISTER_LONG_CONSTANT("GPIO\\REQUEST_FLAG_NONE", 0, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\REQUEST_FLAG_OPEN_DRAIN", GPIOD_LINE_REQUEST_FLAG_OPEN_DRAIN, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\REQUEST_FLAG_OPEN_SOURCE", GPIOD_LINE_REQUEST_FLAG_OPEN_SOURCE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\REQUEST_FLAG_ACTIVE_LOW", GPIOD_LINE_REQUEST_FLAG_ACTIVE_LOW, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\REQUEST_FLAG_BIAS_DISABLED", GPIOD_LINE_REQUEST_FLAG_BIAS_DISABLED, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\REQUEST_FLAG_BIAS_PULL_DOWN", GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_DOWN, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\REQUEST_FLAG_BIAS_PULL_UP", GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP, CONST_CS | CONST_PERSISTENT);
  /* Event types. */
  REGISTER_LONG_CONSTANT("GPIO\\EVENT_RISING_EDGE", GPIOD_LINE_EVENT_RISING_EDGE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO\\EVENT_FALLING_EDGE", GPIOD_LINE_EVENT_FALLING_EDGE, CONST_CS | CONST_PERSISTENT);



  /* Class Registration (from each *.h file) */
  zceLine = registerLineClass();
  zceBulk = registerBulkClass();
  zceException = registerExceptionClass();
  zceChip = registerChipClass();

  return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(phpgpio) {
  php_info_print_table_start();
  php_info_print_table_header(2, "phpgpio support", "enabled");
  php_info_print_table_row(2, "Extension version", PHP_PHPGPIO_VERSION);
  php_info_print_table_row(2, "Library version", gpiod_version_string());
  php_info_print_table_end();
}
/* }}} */

/* {{{ phpgpio_module_entry */
zend_module_entry phpgpio_module_entry = {
  STANDARD_MODULE_HEADER,
  PHP_PHPGPIO_EXTNAME, /* Extension name */
  NULL,                /* zend_function_entry */
  PHP_MINIT(phpgpio),  /* PHP_MINIT - Module initialization */
  NULL,                /* PHP_MSHUTDOWN - Module shutdown */
  PHP_RINIT(phpgpio),  /* PHP_RINIT - Request initialization */
  NULL,                /* PHP_RSHUTDOWN - Request shutdown */
  PHP_MINFO(phpgpio),  /* PHP_MINFO - Module info */
  PHP_PHPGPIO_VERSION, /* Version */
  STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PHPGPIO
  #ifdef ZTS
    ZEND_TSRMLS_CACHE_DEFINE()
  #endif
  ZEND_GET_MODULE(phpgpio)
#endif
