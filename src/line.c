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
#include "common.h"
#include "phpgpio_arginfo.h"
#include "zend_interfaces.h"
#include "zend_object_handlers.h"

// zend_object wrapper to ensure gpiod_line is handled properly
struct _lineObject {
  struct gpiod_line *line;
  zend_object zendObject;
};

static zend_object_handlers lineObjectHandlers;

/********************************/
/* Extension's Internal Methods */
/********************************/

// retrieve a lineObject pointer from a zend_object pointer
static inline lineObject *getLineObject(zend_object *obj) {
  return (lineObject *)((char *)(obj) - XtOffsetOf(lineObject, zendObject));
}

// handle lineObject release
static void lineDestroyObject(zend_object *obj) {
  lineObject *lineInstance = getLineObject(obj);

  // if the line pointer was set, check if line was requested and release it if needed
  if (lineInstance->line != NULL) {
    if (gpiod_line_is_requested(lineInstance->line)) {
      gpiod_line_release(lineInstance->line);
    }

    lineInstance->line = NULL;
  }

  // standard destructor
  zend_object_std_dtor(&lineInstance->zendObject);
}

// custom __construct handler
static zend_function *getConstructorObjectHandler(zend_object *obj) {
  zend_throw_error(NULL, "Cannot directly construct GPIO\\Line");

  return NULL;
}

/********************************/
/* Extension's External Methods */
/********************************/

zend_class_entry* registerLineClass() {
  zend_class_entry ce, *classEntry;

  INIT_NS_CLASS_ENTRY(ce, "GPIO", "Line", class_GPIO_Line_methods);
  classEntry = zend_register_internal_class(&ce);
  // Final class / Objects of this class may not have dynamic properties
  classEntry->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_NO_DYNAMIC_PROPERTIES;
  // intercept object creation to change object handlers
  classEntry->create_object = lineCreateObject;
  // disable serialization
  classEntry->serialize = zend_class_serialize_deny;
  // disable unserialization
  classEntry->unserialize = zend_class_unserialize_deny;

  // initialize lineObjectHandlers with standard object handlers
  memcpy(&lineObjectHandlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

  // disable "new GPIO\Line()" calls
  lineObjectHandlers.get_constructor = getConstructorObjectHandler;
  // disable object cloning
  lineObjectHandlers.clone_obj = NULL;
  // Handler for objects that cannot be meaningfully compared.
  // lineObjectHandlers.compare = zend_objects_not_comparable;
  // not yet sure what this sets
  lineObjectHandlers.offset   = XtOffsetOf(lineObject, zendObject);
  // hook the object release
  lineObjectHandlers.free_obj = lineDestroyObject;

  zval propChipDefaultValue;
  // default property value (undefined)
  ZVAL_UNDEF(&propChipDefaultValue);
  zend_string *propChipName = zend_string_init("chip", sizeof("chip") - 1, false);
  // private GPIO\Chip $chip
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
  lineObject *lineInstance = objectAlloc(sizeof(lineObject), zceClass);

  zend_object_std_init(&lineInstance->zendObject, zceClass);
  object_properties_init(&lineInstance->zendObject, zceClass);

  // set object handlers
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

PHP_METHOD(GPIO_Line, bias) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  RETURN_LONG(gpiod_line_bias(lineInstance->line));
}

PHP_METHOD(GPIO_Line, consumer) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  RETURN_STRING(gpiod_line_consumer(lineInstance->line));
}

PHP_METHOD(GPIO_Line, direction) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  RETURN_LONG(gpiod_line_direction(lineInstance->line));
}

PHP_METHOD(GPIO_Line, drive) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  RETURN_LONG(gpiod_line_drive(lineInstance->line));
}

PHP_METHOD(GPIO_Line, getChip) {
  ZEND_PARSE_PARAMETERS_NONE();

  // gpiod_line_get_chip(lineInstance->line);
}

PHP_METHOD(GPIO_Line, getValue) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  RETURN_LONG(gpiod_line_get_value(lineInstance->line));
}

PHP_METHOD(GPIO_Line, isActiveLow) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  RETURN_BOOL(gpiod_line_is_active_low(lineInstance->line));
}

PHP_METHOD(GPIO_Line, isRequested) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  RETURN_BOOL(gpiod_line_is_requested(lineInstance->line));
}

PHP_METHOD(GPIO_Line, isUsed) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  RETURN_BOOL(gpiod_line_is_used(lineInstance->line));
}

PHP_METHOD(GPIO_Line, name) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  RETURN_STRING(gpiod_line_name(lineInstance->line));
}

PHP_METHOD(GPIO_Line, offset) {
  ZEND_PARSE_PARAMETERS_NONE();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  RETURN_LONG(gpiod_line_offset(lineInstance->line));
}

PHP_METHOD(GPIO_Line, request) {
}

PHP_METHOD(GPIO_Line, setConfig) {
}

PHP_METHOD(GPIO_Line, setDirectionOutput) {
}

PHP_METHOD(GPIO_Line, setFlags) {
}

PHP_METHOD(GPIO_Line, setValue) {
  zend_long value;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(value)
  ZEND_PARSE_PARAMETERS_END();

  lineObject *lineInstance = getLineObject(Z_OBJ_P(ZEND_THIS));
  gpiod_line_set_value(lineInstance->line, value);
}
