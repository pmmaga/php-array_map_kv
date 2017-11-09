PHP_ARG_ENABLE(array_map_kv, whether to enable array_map_kv support,
[  --enable-array_map_kv          Enable array_map_kv support], no)

if test "$PHP_ARRAY_MAP_KV" != "no"; then
  AC_DEFINE(HAVE_ARRAY_MAP_KV, 1, [ Have array_map_kv support ])
  PHP_NEW_EXTENSION(array_map_kv, array_map_kv.c, $ext_shared)
fi
