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
#include "config.h"
#endif

#include "chip.h"
#include "phpgpio_arginfo.h"

#include <gpiod.h>

zend_class_entry* register_chip_class() {
  zend_class_entry ce, *class_entry;

  INIT_NS_CLASS_ENTRY(ce, "GPIO", "Chip", class_GPIO_Chip_methods);
  class_entry = zend_register_internal_class_ex(&ce, NULL);
  class_entry->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_NO_DYNAMIC_PROPERTIES;

  return class_entry;
}

PHP_METHOD(GPIO_Chip, isDevice) {
  char *path;
  size_t pathLen;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(path, pathLen)
  ZEND_PARSE_PARAMETERS_END();

  RETURN_BOOL((int)gpiod_is_gpiochip_device(path));
}

PHP_METHOD(GPIO_Chip, __construct) {
}

PHP_METHOD(GPIO_Chip, findLine) {
}

PHP_METHOD(GPIO_Chip, getAllLines) {
}

PHP_METHOD(GPIO_Chip, getLine) {
}

PHP_METHOD(GPIO_Chip, getLines) {
}

PHP_METHOD(GPIO_Chip, getLabel) {
}

PHP_METHOD(GPIO_Chip, getName) {
}
