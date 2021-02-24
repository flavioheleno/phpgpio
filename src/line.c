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


#include "line.h"
#include "phpgpio_arginfo.h"

#include <gpiod.h>

zend_class_entry* register_line_class() {
  zend_class_entry ce, *class_entry;

  INIT_NS_CLASS_ENTRY(ce, "GPIO", "Line", class_GPIO_Line_methods);
  class_entry = zend_register_internal_class_ex(&ce, NULL);
  class_entry->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_NO_DYNAMIC_PROPERTIES;

  return class_entry;
}

PHP_METHOD(GPIO_Line, bias) {
}

PHP_METHOD(GPIO_Line, consumer) {
}

PHP_METHOD(GPIO_Line, direction) {
}

PHP_METHOD(GPIO_Line, drive) {
}

PHP_METHOD(GPIO_Line, getChip) {
}

PHP_METHOD(GPIO_Line, getValue) {
}

PHP_METHOD(GPIO_Line, isActiveLow) {
}

PHP_METHOD(GPIO_Line, isRequested) {
}

PHP_METHOD(GPIO_Line, isUsed) {
}

PHP_METHOD(GPIO_Line, name) {
}

PHP_METHOD(GPIO_Line, offset) {
}

PHP_METHOD(GPIO_Line, request) {
}

PHP_METHOD(GPIO_Line, reset) {
}

PHP_METHOD(GPIO_Line, setConfig) {
}

PHP_METHOD(GPIO_Line, setDirectionOutput) {
}

PHP_METHOD(GPIO_Line, setFlags) {
}

PHP_METHOD(GPIO_Line, setValue) {
}
