/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: f63ea2d3774a6778210081c8261c1ce3a8df7985 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GPIO_Bulk_getChip, 0, 0, GPIO\\Chip, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Bulk_count, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Bulk_offsetExists, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GPIO_Bulk_offsetGet, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GPIO_Bulk_offsetSet, 0, 0, 2)
	ZEND_ARG_INFO(0, offset)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

#define arginfo_class_GPIO_Bulk_offsetUnset arginfo_class_GPIO_Bulk_offsetGet

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GPIO_Bulk_current, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GPIO_Bulk_key arginfo_class_GPIO_Bulk_current

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Bulk_next, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GPIO_Bulk_rewind arginfo_class_GPIO_Bulk_next

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Bulk_valid, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Chip_isDevice, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GPIO_Chip___construct, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GPIO_Chip_findLineUnique, 0, 1, GPIO\\Line, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GPIO_Chip_findAllLines, 0, 1, GPIO\\Bulk, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GPIO_Chip_getAllLines, 0, 0, GPIO\\Bulk, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GPIO_Chip_getLine, 0, 1, GPIO\\Line, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GPIO_Chip_getLines, 0, 1, GPIO\\Bulk, 0)
	ZEND_ARG_TYPE_INFO(0, offsets, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GPIO_Chip_getLineCount arginfo_class_GPIO_Bulk_count

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Chip_getPath, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GPIO_Chip_getLabel arginfo_class_GPIO_Chip_getPath

#define arginfo_class_GPIO_Chip_getName arginfo_class_GPIO_Chip_getPath

#define arginfo_class_GPIO_Line_getBias arginfo_class_GPIO_Bulk_count

#define arginfo_class_GPIO_Line_getConsumer arginfo_class_GPIO_Chip_getPath

#define arginfo_class_GPIO_Line_getDirection arginfo_class_GPIO_Bulk_count

#define arginfo_class_GPIO_Line_getDrive arginfo_class_GPIO_Bulk_count

#define arginfo_class_GPIO_Line_getChip arginfo_class_GPIO_Bulk_getChip

#define arginfo_class_GPIO_Line_getValue arginfo_class_GPIO_Bulk_count

#define arginfo_class_GPIO_Line_isActiveLow arginfo_class_GPIO_Bulk_valid

#define arginfo_class_GPIO_Line_isRequested arginfo_class_GPIO_Bulk_valid

#define arginfo_class_GPIO_Line_isUsed arginfo_class_GPIO_Bulk_valid

#define arginfo_class_GPIO_Line_getName arginfo_class_GPIO_Chip_getPath

#define arginfo_class_GPIO_Line_getOffset arginfo_class_GPIO_Bulk_count

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Line_request, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, consumer, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, value, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Line_setConfig, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, value, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

#define arginfo_class_GPIO_Line_setDirectionInput arginfo_class_GPIO_Bulk_next

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Line_setDirectionOutput, 0, 0, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, value, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Line_setFlags, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Line_setValue, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()


ZEND_METHOD(GPIO_Bulk, getChip);
ZEND_METHOD(GPIO_Bulk, count);
ZEND_METHOD(GPIO_Bulk, offsetExists);
ZEND_METHOD(GPIO_Bulk, offsetGet);
ZEND_METHOD(GPIO_Bulk, offsetSet);
ZEND_METHOD(GPIO_Bulk, offsetUnset);
ZEND_METHOD(GPIO_Bulk, current);
ZEND_METHOD(GPIO_Bulk, key);
ZEND_METHOD(GPIO_Bulk, next);
ZEND_METHOD(GPIO_Bulk, rewind);
ZEND_METHOD(GPIO_Bulk, valid);
ZEND_METHOD(GPIO_Chip, isDevice);
ZEND_METHOD(GPIO_Chip, __construct);
ZEND_METHOD(GPIO_Chip, findLineUnique);
ZEND_METHOD(GPIO_Chip, findAllLines);
ZEND_METHOD(GPIO_Chip, getAllLines);
ZEND_METHOD(GPIO_Chip, getLine);
ZEND_METHOD(GPIO_Chip, getLines);
ZEND_METHOD(GPIO_Chip, getLineCount);
ZEND_METHOD(GPIO_Chip, getPath);
ZEND_METHOD(GPIO_Chip, getLabel);
ZEND_METHOD(GPIO_Chip, getName);
ZEND_METHOD(GPIO_Line, getBias);
ZEND_METHOD(GPIO_Line, getConsumer);
ZEND_METHOD(GPIO_Line, getDirection);
ZEND_METHOD(GPIO_Line, getDrive);
ZEND_METHOD(GPIO_Line, getChip);
ZEND_METHOD(GPIO_Line, getValue);
ZEND_METHOD(GPIO_Line, isActiveLow);
ZEND_METHOD(GPIO_Line, isRequested);
ZEND_METHOD(GPIO_Line, isUsed);
ZEND_METHOD(GPIO_Line, getName);
ZEND_METHOD(GPIO_Line, getOffset);
ZEND_METHOD(GPIO_Line, request);
ZEND_METHOD(GPIO_Line, setConfig);
ZEND_METHOD(GPIO_Line, setDirectionInput);
ZEND_METHOD(GPIO_Line, setDirectionOutput);
ZEND_METHOD(GPIO_Line, setFlags);
ZEND_METHOD(GPIO_Line, setValue);


static const zend_function_entry class_GPIO_Bulk_methods[] = {
	ZEND_ME(GPIO_Bulk, getChip, arginfo_class_GPIO_Bulk_getChip, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Bulk, count, arginfo_class_GPIO_Bulk_count, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Bulk, offsetExists, arginfo_class_GPIO_Bulk_offsetExists, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Bulk, offsetGet, arginfo_class_GPIO_Bulk_offsetGet, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Bulk, offsetSet, arginfo_class_GPIO_Bulk_offsetSet, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Bulk, offsetUnset, arginfo_class_GPIO_Bulk_offsetUnset, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Bulk, current, arginfo_class_GPIO_Bulk_current, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Bulk, key, arginfo_class_GPIO_Bulk_key, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Bulk, next, arginfo_class_GPIO_Bulk_next, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Bulk, rewind, arginfo_class_GPIO_Bulk_rewind, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Bulk, valid, arginfo_class_GPIO_Bulk_valid, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GPIO_Chip_methods[] = {
	ZEND_ME(GPIO_Chip, isDevice, arginfo_class_GPIO_Chip_isDevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GPIO_Chip, __construct, arginfo_class_GPIO_Chip___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, findLineUnique, arginfo_class_GPIO_Chip_findLineUnique, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, findAllLines, arginfo_class_GPIO_Chip_findAllLines, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, getAllLines, arginfo_class_GPIO_Chip_getAllLines, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, getLine, arginfo_class_GPIO_Chip_getLine, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, getLines, arginfo_class_GPIO_Chip_getLines, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, getLineCount, arginfo_class_GPIO_Chip_getLineCount, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, getPath, arginfo_class_GPIO_Chip_getPath, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, getLabel, arginfo_class_GPIO_Chip_getLabel, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, getName, arginfo_class_GPIO_Chip_getName, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GPIO_Exception_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_GPIO_Line_methods[] = {
	ZEND_ME(GPIO_Line, getBias, arginfo_class_GPIO_Line_getBias, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, getConsumer, arginfo_class_GPIO_Line_getConsumer, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, getDirection, arginfo_class_GPIO_Line_getDirection, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, getDrive, arginfo_class_GPIO_Line_getDrive, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, getChip, arginfo_class_GPIO_Line_getChip, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, getValue, arginfo_class_GPIO_Line_getValue, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, isActiveLow, arginfo_class_GPIO_Line_isActiveLow, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, isRequested, arginfo_class_GPIO_Line_isRequested, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, isUsed, arginfo_class_GPIO_Line_isUsed, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, getName, arginfo_class_GPIO_Line_getName, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, getOffset, arginfo_class_GPIO_Line_getOffset, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, request, arginfo_class_GPIO_Line_request, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, setConfig, arginfo_class_GPIO_Line_setConfig, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, setDirectionInput, arginfo_class_GPIO_Line_setDirectionInput, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, setDirectionOutput, arginfo_class_GPIO_Line_setDirectionOutput, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, setFlags, arginfo_class_GPIO_Line_setFlags, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, setValue, arginfo_class_GPIO_Line_setValue, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
