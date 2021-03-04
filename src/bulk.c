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

#include "bulk.h"
#include "line.h"
#include "phpgpio.h"
#include "phpgpio_arginfo.h"
#include "zend_interfaces.h"
#include "zend_object_handlers.h"

/* zend_object wrapper to ensure gpiod_line_bulk is handled properly */
struct _bulkObject {
  struct gpiod_line_bulk *bulk;
  unsigned int curr;
  zend_object zendObject;
};

static zend_object_handlers bulkObjectHandlers;

/********************************/
/* Extension's Internal Methods */
/********************************/

/* retrieve a bulkObject pointer from a zend_object pointer */
static inline bulkObject *getBulkObject(zend_object *obj) {
  return (bulkObject *)((char *)(obj) - XtOffsetOf(bulkObject, zendObject));
}

/* handle bulkObject release */
static void bulkFreeObject(zend_object *obj) {
  bulkObject *bulkInstance = getBulkObject(obj);

  /* failure to retrieve bulk instance (edge case?) */
  if (bulkInstance == NULL) {
    return;
  }

  /* if the bulk pointer was set, release it */
  if (bulkInstance->bulk != NULL) {
    gpiod_line_release_bulk(bulkInstance->bulk);
    gpiod_line_bulk_free(bulkInstance->bulk);
    bulkInstance->bulk = NULL;
  }

  /* release bulkInstance->zendObject */
  zend_object_std_dtor(&bulkInstance->zendObject);
}

/* custom __construct handler */
static zend_function *getConstructorObjectHandler(zend_object *obj) {
  zend_throw_error(NULL, "Cannot directly construct GPIO\\Bulk");

  return NULL;
}

/* custom unset($inst->prop) handler */
static void unsetPropertyObjectHandler(zend_object *object, zend_string *offset, void **cache_slot) {
  zend_throw_error(NULL, "Cannot unset GPIO\\Bulk property");
}

/********************************/
/* Extension's External Methods */
/********************************/

zend_class_entry* registerBulkClass() {
  zend_class_entry ce, *classEntry;

  INIT_CLASS_ENTRY(ce, "GPIO\\Bulk", class_GPIO_Bulk_methods);
  classEntry = zend_register_internal_class(&ce);
  /* Final class / Objects of this class may not have dynamic properties */
  classEntry->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_NO_DYNAMIC_PROPERTIES;
  /* intercept object creation to change object handlers */
  classEntry->create_object = bulkCreateObject;
  /* disable serialization */
  classEntry->serialize = zend_class_serialize_deny;
  /* disable unserialization */
  classEntry->unserialize = zend_class_unserialize_deny;

  /* initialize bulkObjectHandlers with standard object handlers */
  memcpy(&bulkObjectHandlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

  /* disable "new GPIO\Bulk()" calls */
  bulkObjectHandlers.get_constructor = getConstructorObjectHandler;
  /* disable object cloning */
  bulkObjectHandlers.clone_obj = NULL;
  /* Handler for objects that cannot be meaningfully compared. */
  /* bulkObjectHandlers.compare = zend_objects_not_comparable; */
  /* not yet sure what this sets */
  bulkObjectHandlers.offset   = XtOffsetOf(bulkObject, zendObject);
  /* hook the object release */
  bulkObjectHandlers.free_obj = bulkFreeObject;
  /* hook the object property unset */
  bulkObjectHandlers.unset_property = unsetPropertyObjectHandler;

  /* GPIO\Bulk implements \Countable, \ArrayAccess and \Iterator */
  zend_class_implements(classEntry, 3, zend_ce_countable, zend_ce_arrayaccess, zend_ce_iterator);

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

zend_object *bulkCreateObject(zend_class_entry *zceClass) {
  bulkObject *bulkInstance = zend_object_alloc(sizeof(bulkObject), zceClass);

  zend_object_std_init(&bulkInstance->zendObject, zceClass);
  object_properties_init(&bulkInstance->zendObject, zceClass);

  /* set object handlers */
  bulkInstance->zendObject.handlers = &bulkObjectHandlers;

  return &bulkInstance->zendObject;
}

void bulkSetData(zend_object *obj, struct gpiod_line_bulk *bulk) {
  bulkObject *bulkInstance = getBulkObject(obj);
  bulkInstance->bulk = bulk;
  bulkInstance->curr = 0;
}

/********************************/
/* PHP Visible Methods          */
/********************************/

/* {{{ GPIO\Bulk::getChip(): GPIO\Chip */
PHP_METHOD(GPIO_Bulk, getChip) {
  ZEND_PARSE_PARAMETERS_NONE();

  zval rv;
  zval *obj = zend_read_property(zceBulk, Z_OBJ_P(ZEND_THIS), "chip", sizeof("chip") - 1, true, &rv);

  RETURN_OBJ(Z_OBJ_P(obj));
}
/* }}} */

/* {{{ GPIO\Bulk::count(): int */
PHP_METHOD(GPIO_Bulk, count) {
  ZEND_PARSE_PARAMETERS_NONE();

  bulkObject *bulkInstance = getBulkObject(Z_OBJ_P(ZEND_THIS));

  RETURN_LONG(gpiod_line_bulk_num_lines(bulkInstance->bulk));
}
/* }}} */

/* {{{ GPIO\Bulk::offsetExists(mixed $offset): bool */
PHP_METHOD(GPIO_Bulk, offsetExists) {
  zend_long offset;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(offset)
  ZEND_PARSE_PARAMETERS_END();

  bulkObject *bulkInstance = getBulkObject(Z_OBJ_P(ZEND_THIS));

  RETURN_BOOL(offset >= 0 && offset < gpiod_line_bulk_num_lines(bulkInstance->bulk));
}
/* }}} */

/* {{{ GPIO\Bulk::offsetGet(mixed $offset): mixed */
PHP_METHOD(GPIO_Bulk, offsetGet) {
  zend_long offset;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(offset)
  ZEND_PARSE_PARAMETERS_END();

  bulkObject *bulkInstance = getBulkObject(Z_OBJ_P(ZEND_THIS));

  if (offset < 0) {
    zend_throw_error(zceException, "Invalid offset, cannot be negative");

    RETURN_THROWS();
  }

  if (offset >= gpiod_line_bulk_num_lines(bulkInstance->bulk)) {
    zend_throw_error(zceException, "Invalid offset, cannot be greater than the number of lines");

    RETURN_THROWS();
  }

  struct gpiod_line *line = gpiod_line_bulk_get_line(bulkInstance->bulk, offset);
  if (line == NULL) {
    zend_throw_error(zceException, "Failed to get line offset");

    RETURN_THROWS();
  }

  /* create a new GPIO\Line instance */
  zend_object *obj = lineCreateObject(zceLine);
  lineSetData(obj, line);

  /* update GPIO\Line instance property with reference to $this->chip */
  zval rv;
  zval *chip = zend_read_property(zceBulk, Z_OBJ_P(ZEND_THIS), "chip", sizeof("chip") - 1, true, &rv);
  zend_update_property(zceLine, obj, "chip", sizeof("chip") - 1, chip);

  RETURN_OBJ(obj);
}
/* }}} */

/* {{{ GPIO\Bulk::offsetSet(mixed $offset, mixed $value): void */
PHP_METHOD(GPIO_Bulk, offsetSet) {
  zend_long offset, value;
  ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_LONG(offset)
    Z_PARAM_LONG(value)
  ZEND_PARSE_PARAMETERS_END();

  zend_throw_error(zceException, "Cannot set GPIO\\Bulk line");

  RETURN_THROWS();
}
/* }}} */

/* {{{ GPIO\Bulk::offsetUnset(mixed $offset): void */
PHP_METHOD(GPIO_Bulk, offsetUnset) {
  zend_long offset;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(offset)
  ZEND_PARSE_PARAMETERS_END();

  zend_throw_error(zceException, "Cannot unset GPIO\\Bulk line");

  RETURN_THROWS();
}
/* }}} */

/* {{{ GPIO\Bulk::current(): mixed */
PHP_METHOD(GPIO_Bulk, current) {
  ZEND_PARSE_PARAMETERS_NONE();

  bulkObject *bulkInstance = getBulkObject(Z_OBJ_P(ZEND_THIS));
  struct gpiod_line *line = gpiod_line_bulk_get_line(bulkInstance->bulk, bulkInstance->curr);
  if (line == NULL) {
    zend_throw_error(zceException, "Failed to get line");

    RETURN_THROWS();
  }

  /* create a new GPIO\Line instance */
  zend_object *obj = lineCreateObject(zceLine);
  lineSetData(obj, line);

  /* update GPIO\Line instance property with reference to $this->chip */
  zval rv;
  zval *chip = zend_read_property(zceBulk, Z_OBJ_P(ZEND_THIS), "chip", sizeof("chip") - 1, true, &rv);
  zend_update_property(zceLine, obj, "chip", sizeof("chip") - 1, chip);

  RETURN_OBJ(obj);
}
/* }}} */

/* {{{ GPIO\Bulk::key(): mixed */
PHP_METHOD(GPIO_Bulk, key) {
  ZEND_PARSE_PARAMETERS_NONE();

  bulkObject *bulkInstance = getBulkObject(Z_OBJ_P(ZEND_THIS));

  RETURN_LONG(bulkInstance->curr);
}
/* }}} */

/* {{{ GPIO\Bulk::next(): void */
PHP_METHOD(GPIO_Bulk, next) {
  ZEND_PARSE_PARAMETERS_NONE();

  bulkObject *bulkInstance = getBulkObject(Z_OBJ_P(ZEND_THIS));
  bulkInstance->curr++;
}
/* }}} */

/* {{{ GPIO\Bulk::rewind(): void */
PHP_METHOD(GPIO_Bulk, rewind) {
  ZEND_PARSE_PARAMETERS_NONE();

  bulkObject *bulkInstance = getBulkObject(Z_OBJ_P(ZEND_THIS));
  bulkInstance->curr = 0;
}
/* }}} */

/* {{{ GPIO\Bulk::valid(): bool */
PHP_METHOD(GPIO_Bulk, valid) {
  ZEND_PARSE_PARAMETERS_NONE();

  bulkObject *bulkInstance = getBulkObject(Z_OBJ_P(ZEND_THIS));

  RETURN_BOOL(bulkInstance->curr >= 0 && bulkInstance->curr < gpiod_line_bulk_num_lines(bulkInstance->bulk));
}
/* }}} */
