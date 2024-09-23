#ifndef TOKEN_TOOLS_HASHMAP
#define TOKEN_TOOLS_HASHMAP

#define FNV_OFFSET_BASIS 0xcbf29ce484222325
#define FNV_PRIME 0x100000001b3
#define ARRAY_DEFAULT_SIZE 16 // must be a power of 2
#define MAX_FILL_LEVEL 0.5

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "token-loader.h"

typedef struct value value;

typedef struct hash_map hash_map;

/**
 * Creates a hash_map with the default sizes.
 * Returns a pointer to the hash_map, or NULL if there was an error.
 */
hash_map *hash_map_init(size_t element_size);

/**
 * Frees the hashmap at `map`.
 */
void hash_map_free(hash_map *map);

/**
 * Returns a pointer to the data in the hashmap, or NULL if an error occurred.
 * Arguments:
 * `map` : A pointer to the map the key/value pair should be added to.
 * `key` : A null-terminated string to be used as key.
 * `data` : A pointer to the value to be stored in the hashmap.
 * A deepcopy of both `key` and `data` are stored in the hashmap.
 */
void *hash_map_set(hash_map *map, char *key, void *data);

/**
 * Returns a pointer to the value that `key` maps to in the hashmap `map`.
 */
void *hash_map_get(hash_map *map, char *key);

/**
 * Removes `key` and its associated value from `map`.
 * If `key` is not in `map`, nothing is done.
 */
void hash_map_remove(hash_map *map, char *key);

/**
 * Returns the number of elements in the hashmap.
 */
size_t hash_map_size(hash_map *map);

#endif