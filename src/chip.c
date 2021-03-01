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
#include "common.h"
#include "line.h"
#include "bulk.h"
#include "phpgpio.h"
#include "phpgpio_arginfo.h"
#include "zend_interfaces.h"
#include "zend_object_handlers.h"

#include <gpiod.h>

// zend_object wrapper to ensure gpiod_chip is handled properly
typedef struct _chipObject {
  struct gpiod_chip *chip;
  zend_object zendObject;
} chipObject;

static zend_object_handlers chipObjectHandlers;

/********************************/
/* Extension's Internal Methods */
/********************************/

// retrieve chipObject pointer from a zend_object pointer
static inline chipObject *getChipObject(zend_object *obj) {
  return (chipObject *)((char *)(obj) - XtOffsetOf(chipObject, zendObject));
}

static zend_object *chipCreateObject(zend_class_entry *zceClass) {
  chipObject *chipInstance = objectAlloc(sizeof(chipObject), zceClass);

  // zend_object *obj = zend_objects_new(zceClass);
  zend_object_std_init(&chipInstance->zendObject, zceClass);
  object_properties_init(&chipInstance->zendObject, zceClass);

  // set object handlers
  chipInstance->zendObject.handlers = &chipObjectHandlers;

  return &chipInstance->zendObject;
}

// handle chipObject release
static void chipDestroyObject(zend_object *obj) {
  chipObject *chipInstance = getChipObject(obj);

  // if the chip was open, close it
  if (chipInstance->chip != NULL) {
    gpiod_chip_close(chipInstance->chip);
    chipInstance->chip = NULL;
  }

  // standard destructor
  zend_object_std_dtor(&chipInstance->zendObject);
}

/********************************/
/* Extension's External Methods */
/********************************/

zend_class_entry* registerChipClass() {
  zend_class_entry ce, *classEntry;

  INIT_NS_CLASS_ENTRY(ce, "GPIO", "Chip", class_GPIO_Chip_methods);
  classEntry = zend_register_internal_class(&ce);
  // Final class / Objects of this class may not have dynamic properties
  classEntry->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_NO_DYNAMIC_PROPERTIES;
  // intercept object creation to change object handlers
  classEntry->create_object = chipCreateObject;
  // disable serialization
  classEntry->serialize = zend_class_serialize_deny;
  // disable unserialization
  classEntry->unserialize = zend_class_unserialize_deny;

  // initialize chipObjectHandlers with standard object handlers
  memcpy(&chipObjectHandlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

  // disable object cloning
  chipObjectHandlers.clone_obj = NULL;
  // Handler for objects that cannot be meaningfully compared.
  // chipObjectHandlers.compare = zend_objects_not_comparable;
  // not yet sure what this sets
  chipObjectHandlers.offset   = XtOffsetOf(chipObject, zendObject);
  // hook the object release
  chipObjectHandlers.free_obj = chipDestroyObject;

  zval propPathDefaultValue;
  // default property value (undefined)
  ZVAL_UNDEF(&propPathDefaultValue);
  zend_string *propPathName = zend_string_init("path", sizeof("path") - 1, false);
  // private string $path
  zend_declare_typed_property(
    classEntry,
    propPathName,
    &propPathDefaultValue,
    ZEND_ACC_PRIVATE,
    NULL,
    (zend_type)ZEND_TYPE_INIT_MASK(MAY_BE_STRING)
  );
  zend_string_release(propPathName);

  return classEntry;
}

/********************************/
/* PHP Visible Methods          */
/********************************/

PHP_METHOD(GPIO_Chip, isDevice) {
  char *path;
  size_t pathLen;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(path, pathLen)
  ZEND_PARSE_PARAMETERS_END();

  RETURN_BOOL((int)gpiod_is_gpiochip_device(path));
}

PHP_METHOD(GPIO_Chip, __construct) {
  char *path;
  size_t pathLen;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(path, pathLen)
  ZEND_PARSE_PARAMETERS_END();

  chipObject *chipInstance = getChipObject(Z_OBJ_P(ZEND_THIS));
  chipInstance->chip = gpiod_chip_open(path);
  if (chipInstance->chip == NULL) {
    zend_throw_error(zceException, "Failed to open chip");

    RETURN_THROWS();
  }

  // update class property with constructor argument value
  zend_update_property_stringl(zceChip, Z_OBJ_P(ZEND_THIS), "path", sizeof("path") - 1, path, pathLen);
}

PHP_METHOD(GPIO_Chip, findLineUnique) {
  char *name;
  size_t nameLen;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(name, nameLen)
  ZEND_PARSE_PARAMETERS_END();

  chipObject *chipInstance = getChipObject(Z_OBJ_P(ZEND_THIS));
  struct gpiod_line *line = gpiod_chip_find_line_unique(chipInstance->chip, name);
  if (line == NULL) {
    zend_throw_error(zceException, "Line not found");

    RETURN_THROWS();
  }

  // create a new GPIO\Line instance
  zend_object *obj = lineCreateObject(zceLine);
  lineSetData(obj, line);

  RETURN_OBJ(obj);
}

PHP_METHOD(GPIO_Chip, findAllLines) {
  char *name;
  size_t nameLen;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(name, nameLen)
  ZEND_PARSE_PARAMETERS_END();

  chipObject *chipInstance = getChipObject(Z_OBJ_P(ZEND_THIS));
  struct gpiod_line_bulk *bulk = gpiod_chip_find_line(chipInstance->chip, name);
  if (bulk == NULL) {
    zend_throw_error(zceException, "Failed to find lines");

    RETURN_THROWS();
  }

  // create a new GPIO\Bulk instance
  zend_object *obj = bulkCreateObject(zceBulk);
  bulkSetData(obj, bulk);

  RETURN_OBJ(obj);
}

PHP_METHOD(GPIO_Chip, getAllLines) {
  ZEND_PARSE_PARAMETERS_NONE();

  chipObject *chipInstance = getChipObject(Z_OBJ_P(ZEND_THIS));
  struct gpiod_line_bulk *bulk = gpiod_chip_get_all_lines(chipInstance->chip);
  if (bulk == NULL) {
    zend_throw_error(zceException, "Failed to get bulk");

    RETURN_THROWS();
  }

  // create a new GPIO\Bulk instance
  zend_object *obj = bulkCreateObject(zceBulk);
  bulkSetData(obj, bulk);

  RETURN_OBJ(obj);
}

PHP_METHOD(GPIO_Chip, getLine) {
  zend_long offset;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(offset)
  ZEND_PARSE_PARAMETERS_END();

  chipObject *chipInstance = getChipObject(Z_OBJ_P(ZEND_THIS));

  if (offset >= gpiod_chip_num_lines(chipInstance->chip)) {
    zend_throw_error(zceException, "Invalid offset, cannot be greater than the number of lines");

    RETURN_THROWS();
  }

  struct gpiod_line *line = gpiod_chip_get_line(chipInstance->chip, offset);
  if (line == NULL) {
    zend_throw_error(zceException, "Failed to get line offset");

    RETURN_THROWS();
  }

  // create a new GPIO\Line instance
  zend_object *obj = lineCreateObject(zceLine);
  lineSetData(obj, line);

  RETURN_OBJ(obj);
}

PHP_METHOD(GPIO_Chip, getLines) {
}

PHP_METHOD(GPIO_Chip, getLineCount) {
  ZEND_PARSE_PARAMETERS_NONE();

  chipObject *chipInstance = getChipObject(Z_OBJ_P(ZEND_THIS));
  RETURN_LONG(gpiod_chip_num_lines(chipInstance->chip));
}

PHP_METHOD(GPIO_Chip, getPath) {
  ZEND_PARSE_PARAMETERS_NONE();

  zval rv;
  zval *path = zend_read_property(zceChip, Z_OBJ_P(ZEND_THIS), "path", sizeof("path") - 1, true, &rv);
  RETURN_STR(zval_get_string(path));
}

PHP_METHOD(GPIO_Chip, getLabel) {
  ZEND_PARSE_PARAMETERS_NONE();

  chipObject *chipInstance = getChipObject(Z_OBJ_P(ZEND_THIS));
  RETURN_STRING(gpiod_chip_label(chipInstance->chip));
}

PHP_METHOD(GPIO_Chip, getName) {
  ZEND_PARSE_PARAMETERS_NONE();

  chipObject *chipInstance = getChipObject(Z_OBJ_P(ZEND_THIS));
  RETURN_STRING(gpiod_chip_name(chipInstance->chip));
}
