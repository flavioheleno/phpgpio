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
#include "chip.h"
#include "phpgpio.h"
#include "phpgpio_arginfo.h"
#include "zend_exceptions.h"
#include "zend_interfaces.h"
#include "zend_object_handlers.h"

#include <errno.h>

/* Class constant values as defines so it can be used in the code as well */
#define VALUE_LOW 0
#define VALUE_HIGH 1

/* zend_object wrapper to ensure gpiod_line is handled properly */
struct _lineObject {
  struct gpiod_line *line;
  zend_object zendObject;
};

static zend_object_handlers lineObjectHandlers;

/********************************/
/* Extension's Internal Methods */
/********************************/

/* retrieve a lineObject pointer from a zend_object pointer */
static inline lineObject *getLineObject(zend_object *obj) {
  return (lineObject *)((char *)(obj) - XtOffsetOf(lineObject, zendObject));
}

/* handle lineObject release */
static void lineFreeObject(zend_object *obj) {
  lineObject *lineInstance = getLineObject(obj);

  /* failure to retrieve line instance (edge case?) */
  if (lineInstance == NULL) {
    return;
  }

  /* check if the line was requested and release it if needed */
  if (lineInstance->line != NULL) {
    gpiod_line_release(lineInstance->line);
    lineInstance->line = NULL;
  }

  /* release lineInstance->zendObject */
  zend_object_std_dtor(&lineInstance->zendObject);
}

/* custom __construct handler */
static zend_function *getConstructorObjectHandler(zend_object *obj) {
  zend_throw_error(NULL, "Cannot directly construct GPIO\\Line");

  return NULL;
}

/* custom unset($inst->prop) handler */
static void unsetPropertyObjectHandler(zend_object *object, zend_string *offset, void **cache_slot) {
  zend_throw_error(NULL, "Cannot unset GPIO\\Line::$%s property", ZSTR_VAL(offset));
}

/********************************/
/* Extension's External Methods */
/********************************/

zend_class_entry* registerLineClass() {
  zend_class_entry ce, *classEntry;

  INIT_CLASS_ENTRY(ce, "GPIO\\Line", class_GPIO_Line_methods);
  classEntry = zend_register_internal_class(&ce);
  /* Final class / Objects of this class may not have dynamic properties */
  classEntry->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_NO_DYNAMIC_PROPERTIES;
  /* intercept object creation to change object handlers */
  classEntry->create_object = lineCreateObject;
  /* disable serialization */
  classEntry->serialize = zend_class_serialize_deny;
  /* disable unserialization */
  classEntry->unserialize = zend_class_unserialize_deny;

  /* Class Constants */
  zend_declare_class_constant_long(classEntry, "VALUE_LOW", sizeof("VALUE_LOW") - 1, VALUE_LOW);
  zend_declare_class_constant_long(classEntry, "VALUE_HIGH", sizeof("VALUE_HIGH") - 1, VALUE_HIGH);

  /* initialize lineObjectHandlers with standard object handlers */
  memcpy(&lineObjectHandlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

  /* disable "new GPIO\Line()" calls */
  lineObjectHandlers.get_constructor = getConstructorObjectHandler;
  /* disable object cloning */
  lineObjectHandlers.clone_obj = NULL;
  /* Handler for objects that cannot be meaningfully compared. */
  /* lineObjectHandlers.compare = zend_objects_not_comparable; */
  /* not yet sure what this sets */
  lineObjectHandlers.offset   = XtOffsetOf(lineObject, zendObject);
  /* hook the object release */
  lineObjectHandlers.free_obj = lineFreeObject;
  /* hook the object property unset */
  lineObjectHandlers.unset_property = unsetPropertyObjectHandler;

  zval propChipDefaultValue;
  /* default property value (undefined) */
  ZVAL_UNDEF(&propChipDefaultValue);
  zend_string *propChipName = zend_string_init("chip", sizeof("chip") - 1, false);
  /* private GPIO\Chip $chip */
  zend_declare_typed_property(
    classEntry,
    propChipName,
    &propChipDefaultValue,
    ZEND_ACC_PRIVATE,
    NULL,
    (zend_type)ZEND_TYPE_INIT_MASK(MAY_BE_OBJECT)
  );
  zend_string_release(propChipName);

  return classEntry;
}

zend_object *lineCreateObject(zend_class_entry *zceClass) {
  lineObject *lineInstance = zend_object_alloc(sizeof(lineObject), zceClass);

  zend_object_std_init(&lineInstance->zendObject, zceClass);
  object_properties_init(&lineInstance->zendObject, zceClass);

  /* set object handlers */
  lineInstance->zendObject.handlers = &lineObjectHandlers;

  return &lineInstance->zendObject;
}

void lineSetData(zend_object *obj, struct gpiod_line *line) {
  lineObject *lineInstance = getLineObject(obj);
  lineInstance->line = line;
}

/********************************/
/* PHP Visible Methods          */
/********************************/

/* {{{ GPIO\Line::getBias(): int */
PHP_METHOD(GPIO_Line, getBias) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));

  RETURN_LONG(gpiod_line_bias(lineInstance->line));
}
/* }}} */

/* {{{ GPIO\Line::getConsumer(): string */
PHP_METHOD(GPIO_Line, getConsumer) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  const char *consumer = gpiod_line_consumer(lineInstance->line);
  if (consumer == NULL) {
    RETURN_EMPTY_STRING();
  }

  RETURN_STRING(consumer);
}
/* }}} */

/* {{{ GPIO\Line::getDirection(): int*/
PHP_METHOD(GPIO_Line, getDirection) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));

  RETURN_LONG(gpiod_line_direction(lineInstance->line));
}
/* }}} */

/* {{{ GPIO\Line::getDrive(): int */
PHP_METHOD(GPIO_Line, getDrive) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));

  RETURN_LONG(gpiod_line_drive(lineInstance->line));
}
/* }}} */

/* {{{ GPIO\Line::getChip(): GPIO\Chip */
PHP_METHOD(GPIO_Line, getChip) {
  ZEND_PARSE_PARAMETERS_NONE();

  zval rv;
  zval *obj = zend_read_property(zceLine, Z_OBJ_P(ZEND_THIS), "chip", sizeof("chip") - 1, true, &rv);

  RETURN_OBJ(Z_OBJ_P(obj));
}
/* }}} */

/* {{{ GPIO\Line::getValue(): int */
PHP_METHOD(GPIO_Line, getValue) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));

  RETURN_LONG(gpiod_line_get_value(lineInstance->line));
}
/* }}} */

/* {{{ GPIO\Line::isActiveLow(): bool */
PHP_METHOD(GPIO_Line, isActiveLow) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));

  RETURN_BOOL(gpiod_line_is_active_low(lineInstance->line));
}
/* }}} */

/* {{{ GPIO\Line::isUsed(): bool */
PHP_METHOD(GPIO_Line, isUsed) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));

  RETURN_BOOL(gpiod_line_is_used(lineInstance->line));
}
/* }}} */

/* {{{ GPIO\Line::getName(): string */
PHP_METHOD(GPIO_Line, getName) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  const char *name = gpiod_line_name(lineInstance->line);
  if (name == NULL) {
    RETURN_EMPTY_STRING();
  }

  RETURN_STRING(name);
}
/* }}} */

/* {{{ GPIO\Line::getOffset(): int */
PHP_METHOD(GPIO_Line, getOffset) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));

  RETURN_LONG(gpiod_line_offset(lineInstance->line));
}
/* }}} */

/* {{{ GPIO\Line::request(string $consumer, int $type, int $flags, int $value = self::VALUE_LOW): void */
PHP_METHOD(GPIO_Line, request) {
  char *consumer;
  size_t consumerLen;
  zend_long type;
  zend_long flags;
  zend_long value = VALUE_LOW;
  ZEND_PARSE_PARAMETERS_START(3, 4)
    Z_PARAM_STRING(consumer, consumerLen)
    Z_PARAM_LONG(type)
    Z_PARAM_LONG(flags)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(value)
  ZEND_PARSE_PARAMETERS_END();

  if (type & GPIOD_LINE_REQUEST_DIRECTION_OUTPUT == GPIOD_LINE_REQUEST_DIRECTION_OUTPUT) {
    if (value < VALUE_LOW) {
      zend_throw_exception_ex(zceException, 0, "$value must not be less than %d", VALUE_LOW);

      RETURN_THROWS();
    }

    if (value > VALUE_HIGH) {
      zend_throw_exception_ex(zceException, 0, "$value must not be greater than %d", VALUE_HIGH);

      RETURN_THROWS();
    }
  }

  struct gpiod_line_request_config config;
  config.consumer = consumer;
  config.request_type = (int)type;
  config.flags = (int)flags;

  /* https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git/tree/lib/core.c#n663 */
  if (
    (type != GPIOD_LINE_REQUEST_DIRECTION_OUTPUT) &&
    (flags & (GPIOD_LINE_REQUEST_FLAG_OPEN_DRAIN | GPIOD_LINE_REQUEST_FLAG_OPEN_SOURCE))
  ) {
    zend_throw_exception_ex(
      zceException,
      0,
      "Invalid request flag combination: GPIO\\REQUEST_FLAG_OPEN_DRAIN and GPIO\\REQUEST_FLAG_OPEN_SOURCE can only be used with GPIO\\REQUEST_DIRECTION_OUTPUT"
    );

    RETURN_THROWS();
  }

  if (
    (flags & GPIOD_LINE_REQUEST_FLAG_OPEN_DRAIN) &&
    (flags & GPIOD_LINE_REQUEST_FLAG_OPEN_SOURCE)
  ) {
    zend_throw_exception_ex(
      zceException,
      0,
      "Invalid request flag combination: GPIO\\REQUEST_FLAG_OPEN_DRAIN and GPIO\\REQUEST_FLAG_OPEN_SOURCE cannot be used at the same time"
    );

    RETURN_THROWS();
  }

  int biasFlags = 0;
  if (flags & GPIOD_LINE_REQUEST_FLAG_BIAS_DISABLED) {
    biasFlags++;
  }

  if (flags & GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP) {
    biasFlags++;
  }

  if (flags & GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_DOWN) {
    biasFlags++;
  }

  if (biasFlags > 1) {
    zend_throw_exception_ex(
      zceException,
      0,
      "Invalid request flag combination: must use only one of GPIO\\REQUEST_FLAG_BIAS_DISABLED, GPIO\\REQUEST_FLAG_BIAS_PULL_UP and GPIO\\REQUEST_FLAG_BIAS_PULL_DOWN at a time"
    );

    RETURN_THROWS();
  }

  errno = 0;
  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  int result = gpiod_line_request(lineInstance->line, &config, (int)value);
  if (result == -1) {
    zend_throw_exception_ex(zceException, errno, "Failed to request line: %s", strerror(errno));

    RETURN_THROWS();
  }
}
/* }}} */

/* {{{ GPIO\Line::setConfig(int $direction, int $flags, int $value = self::VALUE_LOW): void */
PHP_METHOD(GPIO_Line, setConfig) {
  zend_long direction;
  zend_long flags;
  zend_long value = VALUE_LOW;
  ZEND_PARSE_PARAMETERS_START(2, 3)
    Z_PARAM_LONG(direction)
    Z_PARAM_LONG(flags)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(value)
  ZEND_PARSE_PARAMETERS_END();

  if (direction & GPIOD_LINE_REQUEST_DIRECTION_OUTPUT == GPIOD_LINE_REQUEST_DIRECTION_OUTPUT) {
    if (value < VALUE_LOW) {
      zend_throw_exception_ex(zceException, 0, "$value must not be less than %d", VALUE_LOW);

      RETURN_THROWS();
    }

    if (value > VALUE_HIGH) {
      zend_throw_exception_ex(zceException, 0, "$value must not be greater than %d", VALUE_HIGH);

      RETURN_THROWS();
    }
  }

  errno = 0;
  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  int result = gpiod_line_set_config(lineInstance->line, (int)direction, (int)flags, (int)value);
  if (result == -1) {
    zend_throw_exception_ex(zceException, errno, "Failed to set line configuration: %s", strerror(errno));

    RETURN_THROWS();
  }
}
/* }}} */

/* {{{ GPIO\Line::setDirectionInput(): void */
PHP_METHOD(GPIO_Line, setDirectionInput) {
  ZEND_PARSE_PARAMETERS_NONE();

  errno = 0;
  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  int result = gpiod_line_set_direction_input(lineInstance->line);
  if (result == -1) {
    zend_throw_exception_ex(zceException, errno, "Failed to set line direction: %s", strerror(errno));

    RETURN_THROWS();
  }
}
/* }}} */

/* {{{ GPIO\Line::setDirectionOutput(int $value = self::VALUE_LOW): void */
PHP_METHOD(GPIO_Line, setDirectionOutput) {
  zend_long value = VALUE_LOW;
  ZEND_PARSE_PARAMETERS_START(0, 1)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(value)
  ZEND_PARSE_PARAMETERS_END();

  if (value < VALUE_LOW) {
    zend_throw_exception_ex(zceException, 0, "$value must not be less than %d", VALUE_LOW);

    RETURN_THROWS();
  }

  if (value > VALUE_HIGH) {
    zend_throw_exception_ex(zceException, 0, "$value must not be greater than %d", VALUE_HIGH);

    RETURN_THROWS();
  }

  errno = 0;
  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  int result = gpiod_line_set_direction_output(lineInstance->line, (int)value);
  if (result == -1) {
    zend_throw_exception_ex(zceException, errno, "Failed to set line configuration: %s", strerror(errno));

    RETURN_THROWS();
  }
}
/* }}} */

/* {{{ GPIO\Line::setFlags(int $flags): void */
PHP_METHOD(GPIO_Line, setFlags) {
  zend_long flags;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(flags)
  ZEND_PARSE_PARAMETERS_END();

  errno = 0;
  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  int result = gpiod_line_set_flags(lineInstance->line, (int)flags);
  if (result == -1) {
    zend_throw_exception_ex(zceException, errno, "Failed to set line flags: %s", strerror(errno));

    RETURN_THROWS();
  }
}
/* }}} */

/* {{{ GPIO\Line::setValue(int $value): void */
PHP_METHOD(GPIO_Line, setValue) {
  zend_long value;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(value)
  ZEND_PARSE_PARAMETERS_END();

  if (value < VALUE_LOW) {
    zend_throw_exception_ex(zceException, 0, "$value must not be less than %d", VALUE_LOW);

    RETURN_THROWS();
  }

  if (value > VALUE_HIGH) {
    zend_throw_exception_ex(zceException, 0, "$value must not be greater than %d", VALUE_HIGH);

    RETURN_THROWS();
  }

  errno = 0;
  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  int result = gpiod_line_set_value(lineInstance->line, (int)value);
  if (result == -1) {
    zend_throw_exception_ex(zceException, errno, "Failed to set line value: %s", strerror(errno));

    RETURN_THROWS();
  }
}
/* }}} */
