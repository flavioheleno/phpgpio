/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 361856250f84c03f4cf2231544c067f226881ba8 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Chip_isDevice, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GPIO_Chip___construct, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GPIO_Chip_findLine, 0, 2, GPIO\\Lines, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, unique, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GPIO_Chip_getAllLines, 0, 0, GPIO\\Lines, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GPIO_Chip_getLine, 0, 1, GPIO\\Line, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GPIO_Chip_getLines, 0, 1, GPIO\\Lines, 0)
	ZEND_ARG_TYPE_INFO(0, offsets, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Chip_getLabel, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GPIO_Chip_getName arginfo_class_GPIO_Chip_getLabel

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Line_bias, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GPIO_Line_consumer arginfo_class_GPIO_Chip_getLabel

#define arginfo_class_GPIO_Line_direction arginfo_class_GPIO_Line_bias

#define arginfo_class_GPIO_Line_drive arginfo_class_GPIO_Line_bias

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GPIO_Line_getChip, 0, 0, GPIO\\Chip, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GPIO_Line_getValue arginfo_class_GPIO_Line_bias

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Line_isActiveLow, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GPIO_Line_isRequested arginfo_class_GPIO_Line_isActiveLow

#define arginfo_class_GPIO_Line_isUsed arginfo_class_GPIO_Line_isActiveLow

#define arginfo_class_GPIO_Line_name arginfo_class_GPIO_Chip_getLabel

#define arginfo_class_GPIO_Line_offset arginfo_class_GPIO_Line_bias

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Line_request, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, lineRequest, GPIO\\LineRequest, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, default, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Line_reset, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Line_setConfig, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, value, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Line_setDirectionOutput, 0, 0, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, value, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Line_setFlags, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Line_setValue, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GPIO_Lines_count arginfo_class_GPIO_Line_bias

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GPIO_Lines_offsetExists, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GPIO_Lines_offsetGet, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GPIO_Lines_offsetSet, 0, 0, 2)
	ZEND_ARG_INFO(0, offset)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

#define arginfo_class_GPIO_Lines_offsetUnset arginfo_class_GPIO_Lines_offsetGet

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GPIO_Lines_current, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GPIO_Lines_key arginfo_class_GPIO_Lines_current

#define arginfo_class_GPIO_Lines_next arginfo_class_GPIO_Line_reset

#define arginfo_class_GPIO_Lines_rewind arginfo_class_GPIO_Line_reset

#define arginfo_class_GPIO_Lines_valid arginfo_class_GPIO_Line_isActiveLow


ZEND_METHOD(GPIO_Chip, isDevice);
ZEND_METHOD(GPIO_Chip, __construct);
ZEND_METHOD(GPIO_Chip, findLine);
ZEND_METHOD(GPIO_Chip, getAllLines);
ZEND_METHOD(GPIO_Chip, getLine);
ZEND_METHOD(GPIO_Chip, getLines);
ZEND_METHOD(GPIO_Chip, getLabel);
ZEND_METHOD(GPIO_Chip, getName);
ZEND_METHOD(GPIO_Line, bias);
ZEND_METHOD(GPIO_Line, consumer);
ZEND_METHOD(GPIO_Line, direction);
ZEND_METHOD(GPIO_Line, drive);
ZEND_METHOD(GPIO_Line, getChip);
ZEND_METHOD(GPIO_Line, getValue);
ZEND_METHOD(GPIO_Line, isActiveLow);
ZEND_METHOD(GPIO_Line, isRequested);
ZEND_METHOD(GPIO_Line, isUsed);
ZEND_METHOD(GPIO_Line, name);
ZEND_METHOD(GPIO_Line, offset);
ZEND_METHOD(GPIO_Line, request);
ZEND_METHOD(GPIO_Line, reset);
ZEND_METHOD(GPIO_Line, setConfig);
ZEND_METHOD(GPIO_Line, setDirectionOutput);
ZEND_METHOD(GPIO_Line, setFlags);
ZEND_METHOD(GPIO_Line, setValue);
ZEND_METHOD(GPIO_Lines, count);
ZEND_METHOD(GPIO_Lines, offsetExists);
ZEND_METHOD(GPIO_Lines, offsetGet);
ZEND_METHOD(GPIO_Lines, offsetSet);
ZEND_METHOD(GPIO_Lines, offsetUnset);
ZEND_METHOD(GPIO_Lines, current);
ZEND_METHOD(GPIO_Lines, key);
ZEND_METHOD(GPIO_Lines, next);
ZEND_METHOD(GPIO_Lines, rewind);
ZEND_METHOD(GPIO_Lines, valid);


static const zend_function_entry class_GPIO_Chip_methods[] = {
	ZEND_ME(GPIO_Chip, isDevice, arginfo_class_GPIO_Chip_isDevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GPIO_Chip, __construct, arginfo_class_GPIO_Chip___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, findLine, arginfo_class_GPIO_Chip_findLine, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, getAllLines, arginfo_class_GPIO_Chip_getAllLines, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, getLine, arginfo_class_GPIO_Chip_getLine, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, getLines, arginfo_class_GPIO_Chip_getLines, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, getLabel, arginfo_class_GPIO_Chip_getLabel, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Chip, getName, arginfo_class_GPIO_Chip_getName, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GPIO_Line_methods[] = {
	ZEND_ME(GPIO_Line, bias, arginfo_class_GPIO_Line_bias, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, consumer, arginfo_class_GPIO_Line_consumer, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, direction, arginfo_class_GPIO_Line_direction, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, drive, arginfo_class_GPIO_Line_drive, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, getChip, arginfo_class_GPIO_Line_getChip, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, getValue, arginfo_class_GPIO_Line_getValue, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, isActiveLow, arginfo_class_GPIO_Line_isActiveLow, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, isRequested, arginfo_class_GPIO_Line_isRequested, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, isUsed, arginfo_class_GPIO_Line_isUsed, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, name, arginfo_class_GPIO_Line_name, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, offset, arginfo_class_GPIO_Line_offset, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, request, arginfo_class_GPIO_Line_request, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, reset, arginfo_class_GPIO_Line_reset, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, setConfig, arginfo_class_GPIO_Line_setConfig, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, setDirectionOutput, arginfo_class_GPIO_Line_setDirectionOutput, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, setFlags, arginfo_class_GPIO_Line_setFlags, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Line, setValue, arginfo_class_GPIO_Line_setValue, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GPIO_Lines_methods[] = {
	ZEND_ME(GPIO_Lines, count, arginfo_class_GPIO_Lines_count, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Lines, offsetExists, arginfo_class_GPIO_Lines_offsetExists, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Lines, offsetGet, arginfo_class_GPIO_Lines_offsetGet, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Lines, offsetSet, arginfo_class_GPIO_Lines_offsetSet, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Lines, offsetUnset, arginfo_class_GPIO_Lines_offsetUnset, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Lines, current, arginfo_class_GPIO_Lines_current, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Lines, key, arginfo_class_GPIO_Lines_key, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Lines, next, arginfo_class_GPIO_Lines_next, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Lines, rewind, arginfo_class_GPIO_Lines_rewind, ZEND_ACC_PUBLIC)
	ZEND_ME(GPIO_Lines, valid, arginfo_class_GPIO_Lines_valid, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
