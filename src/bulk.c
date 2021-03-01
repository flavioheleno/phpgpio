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
#include "common.h"
#include "phpgpio_arginfo.h"
#include "zend_interfaces.h"
#include "zend_object_handlers.h"

// zend_object wrapper to ensure gpiod_line_bulk is handled properly
struct _bulkObject {
  struct gpiod_line_bulk *bulk;
  zend_object zendObject;
};

static zend_object_handlers bulkObjectHandlers;

/********************************/
/* Extension's Internal Methods */
/********************************/

// retrieve a bulkObject pointer from a zend_object pointer
static inline bulkObject *getBulkObject(zend_object *obj) {
  return (bulkObject *)((char *)(obj) - XtOffsetOf(bulkObject, zendObject));
}

// handle bulkObject release
static void bulkDestroyObject(zend_object *obj) {
  bulkObject *bulkInstance = getBulkObject(obj);

  // if the bulk pointer was set, release it
  if (bulkInstance->bulk != NULL) {
    gpiod_line_release_bulk(bulkInstance->bulk);
    gpiod_line_bulk_free(bulkInstance->bulk);
    bulkInstance->bulk = NULL;
  }

  // standard destructor
  zend_object_std_dtor(&bulkInstance->zendObject);
}

// custom __construct handler
static zend_function *getConstructorObjectHandler(zend_object *obj) {
  zend_throw_error(NULL, "Cannot directly construct GPIO\\Bulk");

  return NULL;
}

/********************************/
/* Extension's External Methods */
/********************************/

zend_class_entry* registerBulkClass() {
  zend_class_entry ce, *classEntry;

  INIT_NS_CLASS_ENTRY(ce, "GPIO", "Bulk", class_GPIO_Bulk_methods);
  classEntry = zend_register_internal_class(&ce);
  // Final class / Objects of this class may not have dynamic properties
  classEntry->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_NO_DYNAMIC_PROPERTIES;
  // intercept object creation to change object handlers
  classEntry->create_object = bulkCreateObject;
  // disable serialization
  classEntry->serialize = zend_class_serialize_deny;
  // disable unserialization
  classEntry->unserialize = zend_class_unserialize_deny;

  // initialize bulkObjectHandlers with standard object handlers
  memcpy(&bulkObjectHandlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

  // disable "new GPIO\Bulk()" calls
  bulkObjectHandlers.get_constructor = getConstructorObjectHandler;
  // disable object cloning
  bulkObjectHandlers.clone_obj = NULL;
  // Handler for objects that cannot be meaningfully compared.
  // bulkObjectHandlers.compare = zend_objects_not_comparable;
  // not yet sure what this sets
  bulkObjectHandlers.offset   = XtOffsetOf(bulkObject, zendObject);
  // hook the object release
  bulkObjectHandlers.free_obj = bulkDestroyObject;

  // GPIO\Bulk implements \Countable, \ArrayAccess and \Iterator
  zend_class_implements(classEntry, 3, zend_ce_countable, zend_ce_arrayaccess, zend_ce_iterator);

  return classEntry;
}

static zend_object *bulkCreateObject(zend_class_entry *zceClass) {
  bulkObject *bulkInstance = objectAlloc(sizeof(bulkObject), zceClass);

  zend_object_std_init(&bulkInstance->zendObject, zceClass);
  object_properties_init(&bulkInstance->zendObject, zceClass);

  // set object handlers
  bulkInstance->zendObject.handlers = &bulkObjectHandlers;

  return &bulkInstance->zendObject;
}

static void bulkSetData(zend_object *obj, struct gpiod_line_bulk *bulk) {
  bulkObject *bulkInstance = getBulkObject(obj);
  bulkInstance->bulk = bulk;
}

/********************************/
/* PHP Visible Methods          */
/********************************/

PHP_METHOD(GPIO_Bulk, count) {
  ZEND_PARSE_PARAMETERS_NONE();
}

PHP_METHOD(GPIO_Bulk, offsetExists) {
}

PHP_METHOD(GPIO_Bulk, offsetGet) {
}

PHP_METHOD(GPIO_Bulk, offsetSet) {
}

PHP_METHOD(GPIO_Bulk, offsetUnset) {
}

PHP_METHOD(GPIO_Bulk, current) {
  ZEND_PARSE_PARAMETERS_NONE();
}

PHP_METHOD(GPIO_Bulk, key) {
  ZEND_PARSE_PARAMETERS_NONE();
}

PHP_METHOD(GPIO_Bulk, next) {
  ZEND_PARSE_PARAMETERS_NONE();
}

PHP_METHOD(GPIO_Bulk, rewind) {
  ZEND_PARSE_PARAMETERS_NONE();
}

PHP_METHOD(GPIO_Bulk, valid) {
  ZEND_PARSE_PARAMETERS_NONE();
}
