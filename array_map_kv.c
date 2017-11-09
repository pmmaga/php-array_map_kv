/* array_map_kv extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_array_map_kv.h"

/* {{{ array array_map_kv()
 */
PHP_FUNCTION(array_map_kv)
{
	zval *arrays = NULL;
	int n_arrays = 0;
	zval result;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fci_cache = empty_fcall_info_cache;

	ZEND_PARSE_PARAMETERS_START(2, -1)
		Z_PARAM_FUNC_EX(fci, fci_cache, 1, 0)
		Z_PARAM_VARIADIC('+', arrays, n_arrays)
	ZEND_PARSE_PARAMETERS_END();

	RETVAL_NULL();

	// php_printf("The extension %s is loaded and working!\r\n", "array_map_kv");
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(array_map_kv)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "array_map_kv support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_array_map_kv, 0, 0, 2)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_VARIADIC_INFO(0, arrays)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ array_map_kv_functions[]
 */
const zend_function_entry array_map_kv_functions[] = {
	PHP_FE(array_map_kv,		arginfo_array_map_kv)
	PHP_FE_END
};
/* }}} */

/* {{{ array_map_kv_module_entry
 */
zend_module_entry array_map_kv_module_entry = {
	STANDARD_MODULE_HEADER,
	"array_map_kv",					/* Extension name */
	array_map_kv_functions,			/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	NULL,							/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(array_map_kv),		/* PHP_MINFO - Module info */
	PHP_ARRAY_MAP_KV_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ARRAY_MAP_KV
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(array_map_kv)
#endif
