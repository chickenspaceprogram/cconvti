#ifndef TOKEN_TOOLS_HASHMAP
#define TOKEN_TOOLS_HASHMAP

#define FNV_OFFSET_BASIS 0xcbf29ce484222325
#define FNV_PRIME 0x100000001b3
#define ARRAY_DEFAULT_SIZE 1024 // must be a power of 2

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "token-loader.h"

typedef struct value value;

struct value {
    value *next;
    void *data;
    char *key;
};

typedef struct hash_map hash_map;

struct hash_map {
    value *hash_array;
    unsigned int num_elements;
    unsigned int hash_map_size;
};

/**
 * Creates a hash_map with the default sizes.
 * Returns a pointer to the hash_map, or NULL if there was an error.
 */
hash_map *create_hash_map();

/**
 * Arguments:
 * `key` : A null-terminated string to be used as key.
 * `data` : A pointer to the value to be stored in the hashmap.
 * Returns a pointer to the data in the hashmap.
 */
void *hash_map_add(hash_map map, char *key, void *data);


#endif