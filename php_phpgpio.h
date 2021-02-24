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

#ifndef PHP_PHPGPIO_H
#define PHP_PHPGPIO_H

  extern zend_module_entry phpgpio_module_entry;
  #define phpext_phpgpio_ptr &phpgpio_module_entry

  #define PHP_PHPGPIO_EXTNAME   "phpgpio"
  #define PHP_PHPGPIO_VERSION   "0.0.1-dev"
  #define PHP_PHPGPIO_AUTHOR    "flavioheleno"
  #define PHP_PHPGPIO_URL       "https://github.com/flavioheleno/phpgpio"
  #define PHP_PHPGPIO_COPYRIGHT "Copyright (c) 2021"

  #if defined(ZTS) && defined(COMPILE_DL_PHPGPIO)
    ZEND_TSRMLS_CACHE_EXTERN()
  #endif

  BEGIN_EXTERN_C()

  /* Class entry pointers */
  extern PHPAPI zend_class_entry *chip;
  extern PHPAPI zend_class_entry *line;
  extern PHPAPI zend_class_entry *lines;

  END_EXTERN_C()

#endif
