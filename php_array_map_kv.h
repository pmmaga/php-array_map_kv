/* array_map_kv extension for PHP */

#ifndef PHP_ARRAY_MAP_KV_H
# define PHP_ARRAY_MAP_KV_H

extern zend_module_entry array_map_kv_module_entry;
# define phpext_array_map_kv_ptr &array_map_kv_module_entry

# define PHP_ARRAY_MAP_KV_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_ARRAY_MAP_KV)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_ARRAY_MAP_KV_H */
