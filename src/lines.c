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

#include "lines.h"
#include "zend_interfaces.h"
#include "phpgpio_arginfo.h"

#include <gpiod.h>

zend_class_entry* registerLinesClass() {
  zend_class_entry ce, *class_entry;

  INIT_NS_CLASS_ENTRY(ce, "GPIO", "Lines", class_GPIO_Lines_methods);
  class_entry = zend_register_internal_class_ex(&ce, NULL);
  // Final class / Objects of this class may not have dynamic properties
  class_entry->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_NO_DYNAMIC_PROPERTIES;

  // GPIO\Lines implements \Countable, \ArrayAccess and \Iterator
  zend_class_implements(class_entry, 3, zend_ce_countable, zend_ce_arrayaccess, zend_ce_iterator);

  return class_entry;
}

PHP_METHOD(GPIO_Lines, count) {
}

PHP_METHOD(GPIO_Lines, offsetExists) {
}

PHP_METHOD(GPIO_Lines, offsetGet) {
}

PHP_METHOD(GPIO_Lines, offsetSet) {
}

PHP_METHOD(GPIO_Lines, offsetUnset) {
}

PHP_METHOD(GPIO_Lines, current) {
}

PHP_METHOD(GPIO_Lines, key) {
}

PHP_METHOD(GPIO_Lines, next) {
}

PHP_METHOD(GPIO_Lines, rewind) {
}

PHP_METHOD(GPIO_Lines, valid) {
}
