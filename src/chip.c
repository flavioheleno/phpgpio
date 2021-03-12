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
#include "line.h"
#include "bulk.h"
#include "phpgpio.h"
#include "phpgpio_arginfo.h"
#include "zend_interfaces.h"
#include "zend_object_handlers.h"

/* zend_object wrapper to ensure gpiod_chip is handled properly */
typedef struct _chipObject {
  struct gpiod_chip *chip;
  zend_object zendObject;
} chipObject;

static zend_object_handlers chipObjectHandlers;

/********************************/
/* Extension's Internal Methods */
/********************************/

/* retrieve chipObject pointer from a zend_object pointer */
static inline chipObject *getChipObject(zend_object *obj) {
  return (chipObject *)((char *)(obj) - XtOffsetOf(chipObject, zendObject));
}

/* handle chipObject release */
static void chipFreeObject(zend_object *obj) {
  chipObject *chipInstance = getChipObject(obj);

  /* failure to retrieve chip instance (edge case?) */
  if (chipInstance == NULL) {
    return;
  }

  /* if the chip was open, close it */
  if (chipInstance->chip != NULL) {
    gpiod_chip_close(chipInstance->chip);
    chipInstance->chip = NULL;
  }

  /* release chipInstance->zendObject */
  zend_object_std_dtor(&chipInstance->zendObject);
}

/* custom unset($inst->prop) handler */
static void unsetPropertyObjectHandler(zend_object *object, zend_string *offset, void **cache_slot) {
  zend_throw_error(NULL, "Cannot unset GPIO\\Chip property");
}

/********************************/
/* Extension's External Methods */
/********************************/

zend_class_entry* registerChipClass() {
  zend_class_entry ce, *classEntry;

  INIT_CLASS_ENTRY(ce, "GPIO\\Chip", class_GPIO_Chip_methods);
  classEntry = zend_register_internal_class(&ce);
  /* Final class / Objects of this class may not have dynamic properties */
  classEntry->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_NO_DYNAMIC_PROPERTIES;
  /* intercept object creation to change object handlers */
  classEntry->create_object = chipCreateObject;
  /* disable serialization */
  classEntry->serialize = zend_class_serialize_deny;
  /* disable unserialization */
  classEntry->unserialize = zend_class_unserialize_deny;

  /* initialize chipObjectHandlers with standard object handlers */
  memcpy(&chipObjectHandlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

  /* disable object cloning */
  chipObjectHandlers.clone_obj = NULL;
  /* Handler for objects that cannot be meaningfully compared. */
  /* chipObjectHandlers.compare = zend_objects_not_comparable; */
  /* not yet sure what this sets */
  chipObjectHandlers.offset   = XtOffsetOf(chipObject, zendObject);
  /* hook the object release */
  chipObjectHandlers.free_obj = chipFreeObject;
  /* hook the object property unset */
  chipObjectHandlers.unset_property = unsetPropertyObjectHandler;

  zval propPathDefaultValue;
  /* default property value (undefined) */
  ZVAL_UNDEF(&propPathDefaultValue);
  zend_string *propPathName = zend_string_init("path", sizeof("path") - 1, false);
  /* private string $path */
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

zend_object *chipCreateObject(zend_class_entry *zceClass) {
  chipObject *chipInstance = zend_object_alloc(sizeof(chipObject), zceClass);

  zend_object_std_init(&chipInstance->zendObject, zceClass);
  object_properties_init(&chipInstance->zendObject, zceClass);

  /* set object handlers */
  chipInstance->zendObject.handlers = &chipObjectHandlers;

  return &chipInstance->zendObject;
}

/********************************/
/* PHP Visible Methods          */
/********************************/

/* {{{ GPIO\Chip::isDevice(string $path): bool */
PHP_METHOD(GPIO_Chip, isDevice) {
  char *path;
  size_t pathLen;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(path, pathLen)
  ZEND_PARSE_PARAMETERS_END();

  RETURN_BOOL((int)gpiod_is_gpiochip_device(path));
}
/* }}} */

/* {{{ GPIO\Chip::__construct(string $path): void */
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

  /* update class property with constructor argument value */
  zend_update_property_stringl(zceChip, Z_OBJ_P(ZEND_THIS), "path", sizeof("path") - 1, path, pathLen);
}
/* }}} */

/* {{{ GPIO\Chip::findLineUnique(string $name): GPIO\Line */
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

  /* create a new GPIO\Line instance */
  zend_object *obj = lineCreateObject(zceLine);
  lineSetData(obj, line);

  /* update GPIO\Line instance property with reference to $this */
  zend_update_property(zceLine, obj, "chip", sizeof("chip") - 1, ZEND_THIS);

  RETURN_OBJ(obj);
}
/* }}} */

/* {{{ GPIO\Chip::findAllLines(string $name): GPIO\Bulk */
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

  /* create a new GPIO\Bulk instance */
  zend_object *obj = bulkCreateObject(zceBulk);
  bulkSetData(obj, bulk);

  /* update GPIO\Bulk instance property with reference to $this */
  zend_update_property(zceBulk, obj, "chip", sizeof("chip") - 1, ZEND_THIS);

  RETURN_OBJ(obj);
}
/* }}} */

/* {{{ GPIO\Chip::getAllLines(): GPIO\Bulk */
PHP_METHOD(GPIO_Chip, getAllLines) {
  ZEND_PARSE_PARAMETERS_NONE();

  chipObject *chipInstance = getChipObject(Z_OBJ_P(ZEND_THIS));
  struct gpiod_line_bulk *bulk = gpiod_chip_get_all_lines(chipInstance->chip);
  if (bulk == NULL) {
    zend_throw_error(zceException, "Failed to get bulk");

    RETURN_THROWS();
  }

  /* create a new GPIO\Bulk instance */
  zend_object *obj = bulkCreateObject(zceBulk);
  bulkSetData(obj, bulk);

  /* update GPIO\Bulk instance property with reference to $this */
  zend_update_property(zceBulk, obj, "chip", sizeof("chip") - 1, ZEND_THIS);

  RETURN_OBJ(obj);
}
/* }}} */

/* {{{ GPIO\Chip::getLine(int $offset): GPIO\Line */
PHP_METHOD(GPIO_Chip, getLine) {
  zend_long offset;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(offset)
  ZEND_PARSE_PARAMETERS_END();

  chipObject *chipInstance = getChipObject(Z_OBJ_P(ZEND_THIS));

  if (offset < 0) {
    zend_throw_error(zceException, "Invalid offset, cannot be negative");

    RETURN_THROWS();
  }

  if (offset >= gpiod_chip_num_lines(chipInstance->chip)) {
    zend_throw_error(zceException, "Invalid offset, cannot be greater than the number of lines");

    RETURN_THROWS();
  }

  struct gpiod_line *line = gpiod_chip_get_line(chipInstance->chip, offset);
  if (line == NULL) {
    zend_throw_error(zceException, "Failed to get line offset");

    RETURN_THROWS();
  }

  /* create a new GPIO\Line instance */
  zend_object *obj = lineCreateObject(zceLine);
  lineSetData(obj, line);

  /* update GPIO\Line instance property with reference to $this */
  zend_update_property(zceLine, obj, "chip", sizeof("chip") - 1, ZEND_THIS);

  RETURN_OBJ(obj);
}
/* }}} */

/* {{{ GPIO\Chip::getLines(array $offsets): GPIO\Bulk */
PHP_METHOD(GPIO_Chip, getLines) {
  HashTable *offsetsHashTable;
  zval *entry;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_ARRAY_HT(offsetsHashTable)
  ZEND_PARSE_PARAMETERS_END();

  unsigned int numOffsets = zend_hash_num_elements(offsetsHashTable);

  unsigned int *offsets;
  offsets = emalloc(numOffsets);
  int i = 0;
  ZEND_HASH_FOREACH_VAL(offsetsHashTable, entry) {
    offsets[i++] = zval_get_long(entry);
  } ZEND_HASH_FOREACH_END();

  chipObject *chipInstance = getChipObject(Z_OBJ_P(ZEND_THIS));
  struct gpiod_line_bulk *bulk = gpiod_chip_get_lines(chipInstance->chip, offsets, numOffsets);
  efree(offsets);
  if (bulk == NULL) {
    zend_throw_error(zceException, "Failed to get bulk");

    RETURN_THROWS();
  }

  /* create a new GPIO\Bulk instance */
  zend_object *obj = bulkCreateObject(zceBulk);
  bulkSetData(obj, bulk);

  /* update GPIO\Bulk instance property with reference to $this */
  zend_update_property(zceBulk, obj, "chip", sizeof("chip") - 1, ZEND_THIS);

  RETURN_OBJ(obj);
}
/* }}} */

/* {{{ GPIO\Chip::getLineCount(): int */
PHP_METHOD(GPIO_Chip, getLineCount) {
  ZEND_PARSE_PARAMETERS_NONE();

  chipObject *chipInstance = getChipObject(Z_OBJ_P(ZEND_THIS));

  RETURN_LONG(gpiod_chip_num_lines(chipInstance->chip));
}
/* }}} */

/* {{{ GPIO\Chip::getPath(): string */
PHP_METHOD(GPIO_Chip, getPath) {
  ZEND_PARSE_PARAMETERS_NONE();

  zval rv;
  zval *path = zend_read_property(zceChip, Z_OBJ_P(ZEND_THIS), "path", sizeof("path") - 1, true, &rv);

  RETURN_STR(zval_get_string(path));
}
/* }}} */

/* {{{ GPIO\Chip::getLabel(): string */
PHP_METHOD(GPIO_Chip, getLabel) {
  ZEND_PARSE_PARAMETERS_NONE();

  chipObject *chipInstance = getChipObject(Z_OBJ_P(ZEND_THIS));

  RETURN_STRING(gpiod_chip_label(chipInstance->chip));
}
/* }}} */

/* {{{ GPIO\Chip::getName(): string */
PHP_METHOD(GPIO_Chip, getName) {
  ZEND_PARSE_PARAMETERS_NONE();

  chipObject *chipInstance = getChipObject(Z_OBJ_P(ZEND_THIS));

  RETURN_STRING(gpiod_chip_name(chipInstance->chip));
}
/* }}} */
