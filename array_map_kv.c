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
	int i;
	uint32_t k, maxlen = 0;

	ZEND_PARSE_PARAMETERS_START(2, -1)
		Z_PARAM_FUNC_EX(fci, fci_cache, 1, 0)
		Z_PARAM_VARIADIC('+', arrays, n_arrays)
	ZEND_PARSE_PARAMETERS_END();

	RETVAL_NULL();

	uint32_t *array_pos = (HashPosition *)ecalloc(n_arrays, sizeof(HashPosition));

	for (i = 0; i < n_arrays; i++) {
		if (Z_TYPE(arrays[i]) != IS_ARRAY) {
			php_error_docref(NULL, E_WARNING, "Argument #%d should be an array", i + 2);
			efree(array_pos);
			return;
		}
		if (zend_hash_num_elements(Z_ARRVAL(arrays[i])) > maxlen) {
			maxlen = zend_hash_num_elements(Z_ARRVAL(arrays[i]));
		}
	}

	array_init_size(return_value, maxlen);

	if (!ZEND_FCI_INITIALIZED(fci)) {
		zval zv;

		/* We iterate through all the arrays at once. */
		for (k = 0; k < maxlen; k++) {

			/* If no callback, the result will be an array, consisting of current
			* entries from all arrays. */
			array_init_size(&result, n_arrays);

			for (i = 0; i < n_arrays; i++) {
				/* If this array still has elements, add the current one to the
				* parameter list, otherwise use null value. */
				uint32_t pos = array_pos[i];
				while (1) {
					if (pos >= Z_ARRVAL(arrays[i])->nNumUsed) {
						ZVAL_NULL(&zv);
						break;
					} else if (Z_TYPE(Z_ARRVAL(arrays[i])->arData[pos].val) != IS_UNDEF) {
						ZVAL_COPY(&zv, &Z_ARRVAL(arrays[i])->arData[pos].val);
						array_pos[i] = pos + 1;
						break;
					}
					pos++;
				}

				zend_hash_next_index_insert_new(Z_ARRVAL(result), &zv);
			}

			zend_hash_next_index_insert_new(Z_ARRVAL_P(return_value), &result);
		}
	} else {
		zval *params = (zval *)safe_emalloc(n_arrays * 2, sizeof(zval), 0);

		/* We iterate through all the arrays at once. */
		for (k = 0; k < maxlen; k++) {
			for (i = 0; i < n_arrays; i = i + 2) {
				/* If this array still has elements, add the current one to the
				* parameter list, otherwise use null value. */
				uint32_t pos = array_pos[i];
				while (1) {
					if (pos >= Z_ARRVAL(arrays[i])->nNumUsed) {
						ZVAL_NULL(&params[i]);
						ZVAL_NULL(&params[i + 1]);
						break;
					} else if (Z_TYPE(Z_ARRVAL(arrays[i])->arData[pos].val) != IS_UNDEF) {
						if (Z_ARRVAL(arrays[i])->arData[pos].key) {
							ZVAL_STR_COPY(&params[i], Z_ARRVAL(arrays[i])->arData[pos].key);
						} else {
							ZVAL_LONG(&params[i], Z_ARRVAL(arrays[i])->arData[pos].h)
						}
						ZVAL_COPY(&params[i + 1], &Z_ARRVAL(arrays[i])->arData[pos].val);
						array_pos[i] = pos + 1;
						break;
					}
					pos++;
				}
			}

			fci.retval = &result;
			fci.param_count = n_arrays * 2;
			fci.params = params;
			fci.no_separation = 0;

			if (zend_call_function(&fci, &fci_cache) != SUCCESS || Z_TYPE(result) == IS_UNDEF) {
				efree(array_pos);
				zend_array_destroy(Z_ARR_P(return_value));
				for (i = 0; i < n_arrays; i++) {
					zval_ptr_dtor(&params[i]);
				}
				efree(params);
				RETURN_NULL();
			} else {
				for (i = 0; i < n_arrays; i++) {
					zval_ptr_dtor(&params[i]);
				}
			}

			zend_hash_next_index_insert_new(Z_ARRVAL_P(return_value), &result);
		}

		efree(params);
	}
	efree(array_pos);
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
