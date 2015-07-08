
/*
  +------------------------------------------------------------------------+
  | Zephir Language                                                        |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2015 Zephir Team (http://www.zephir-lang.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@zephir-lang.com so we can send you a copy immediately.      |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@zephir-lang.com>                     |
  |          Eduar Carvajal <eduar@zephir-lang.com>                        |
  |          Vladimir Kolesnikov <vladimir@extrememember.com>              |
  +------------------------------------------------------------------------+
*/

#ifndef ZEPHIR_KERNEL_GLOBALS_H
#define ZEPHIR_KERNEL_GLOBALS_H

#include <php.h>

#define ZEPHIR_MAX_MEMORY_STACK 48
#define ZEPHIR_MAX_CACHE_SLOTS 512

/** Memory frame */
typedef struct _zephir_memory_entry {
	size_t pointer;
	size_t capacity;
	zval ***addresses;
	size_t hash_pointer;
	size_t hash_capacity;
	zval ***hash_addresses;
	struct _zephir_memory_entry *prev;
	struct _zephir_memory_entry *next;
#ifndef ZEPHIR_RELEASE
	int permanent;
	const char *func;
#endif
} zephir_memory_entry;

/** Virtual Symbol Table */
typedef struct _zephir_symbol_table {
	struct _zephir_memory_entry *scope;
	HashTable *symbol_table;
	struct _zephir_symbol_table *prev;
} zephir_symbol_table;

typedef struct _zephir_function_cache {
	zend_class_entry *ce;
	zend_function *func;
} zephir_function_cache;

#ifndef ZEPHIR_RELEASE

typedef struct _zephir_fcall_cache_entry {
	zend_function *f;
	zend_uint times;
} zephir_fcall_cache_entry;

#else

typedef zend_function zephir_fcall_cache_entry;

#endif

#define ZEPHIR_INIT_FUNCS(class_functions) static const zend_function_entry class_functions[] =

#define ZEPHIR_INIT_CLASS(name) \
	int zephir_ ##name## _init(INIT_FUNC_ARGS)

#define ZEPHIR_INIT(name) \
	if (zephir_ ##name## _init(INIT_FUNC_ARGS_PASSTHRU) == FAILURE) { \
		return FAILURE; \
	}
#endif
