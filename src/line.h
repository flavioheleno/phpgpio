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

#ifndef PHPGPIO_LINE_H
#define PHPGPIO_LINE_H

  #include "php.h"

  #include <gpiod.h>

  BEGIN_EXTERN_C()

  /* internal object data holder */
  typedef struct _lineObject lineObject;

  /* class registration */
  extern zend_class_entry* registerLineClass();

  /* handle lineObject creation */
  extern zend_object *lineCreateObject(zend_class_entry *zceClass);
  /* sets the internal lineObject data */
  extern void lineSetData(zend_object *obj, struct gpiod_line *line);

  END_EXTERN_C()

#endif
