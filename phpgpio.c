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
#include "php_phpgpio.h"
#include "phpgpio_arginfo.h"

#include "src/line.h"
#include "src/lines.h"
#include "src/chip.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
  ZEND_PARSE_PARAMETERS_START(0, 0) \
  ZEND_PARSE_PARAMETERS_END()
#endif

PHPAPI zend_class_entry *chip;
PHPAPI zend_class_entry *line;
PHPAPI zend_class_entry *lines;

/* {{{ void test1() */
// PHP_FUNCTION(test1) {
//   ZEND_PARSE_PARAMETERS_NONE();

//   php_printf("The extension %s is loaded and working!\r\n", "phpgpio");
// }
/* }}} */

/* {{{ string test2( [ string $var ] ) */
// PHP_FUNCTION(test2) {
//   char *var = "World";
//   size_t var_len = sizeof("World") - 1;
//   zend_string *retval;

//   ZEND_PARSE_PARAMETERS_START(0, 1)
//     Z_PARAM_OPTIONAL
//     Z_PARAM_STRING(var, var_len)
//   ZEND_PARSE_PARAMETERS_END();

//   retval = strpprintf(0, "Hello %s", var);

//   RETURN_STR(retval);
// }
/* }}}*/

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
  REGISTER_NS_LONG_CONSTANT("GPIO", "BIAS_UNKNOWN", 1, CONST_CS | CONST_PERSISTENT);
  REGISTER_NS_LONG_CONSTANT("GPIO", "BIAS_DISABLED", 2, CONST_CS | CONST_PERSISTENT);
  REGISTER_NS_LONG_CONSTANT("GPIO", "BIAS_PULL_UP", 3, CONST_CS | CONST_PERSISTENT);
  REGISTER_NS_LONG_CONSTANT("GPIO", "BIAS_PULL_DOWN", 4, CONST_CS | CONST_PERSISTENT);
  REGISTER_NS_LONG_CONSTANT("GPIO", "DIRECTION_INPUT", 1, CONST_CS | CONST_PERSISTENT);
  REGISTER_NS_LONG_CONSTANT("GPIO", "DIRECTION_OUTPUT", 2, CONST_CS | CONST_PERSISTENT);
  REGISTER_NS_LONG_CONSTANT("GPIO", "DRIVE_PUSH_PULL", 1, CONST_CS | CONST_PERSISTENT);
  REGISTER_NS_LONG_CONSTANT("GPIO", "DRIVE_OPEN_DRAIN", 2, CONST_CS | CONST_PERSISTENT);
  REGISTER_NS_LONG_CONSTANT("GPIO", "DRIVE_OPEN_SOURCE", 3, CONST_CS | CONST_PERSISTENT);

  /* Classes */
  line = register_line_class();
  lines = register_lines_class();
  chip = register_chip_class();
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(phpgpio) {
  php_info_print_table_start();
  php_info_print_table_header(2, "phpgpio support", "enabled");
  php_info_print_table_row(2, "Version", PHP_PHPGPIO_VERSION);
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
