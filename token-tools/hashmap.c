#include "hashmap.h"

/* Declarations */

/**
 * Arguments:
 * `str` : The null-terminated string to hash
 */
uint64_t hash_string(char *str);

/* Definitions */

hash_map *create_hash_map() {
    hash_map *map = malloc(sizeof(hash_map));
    if (map == NULL) {
        return NULL;
    }
    (*map).hash_array = malloc(ARRAY_DEFAULT_SIZE * sizeof(value));
    if ((*map).hash_array == NULL) {
        return NULL;
    }

    for (int i = 0; i < ARRAY_DEFAULT_SIZE; ++i) {
        (*map).hash_array[i] = (value) {NULL, NULL, NULL}; // setting all of the pointers in the array to NULL
    }

    (*map).hash_map_size = ARRAY_DEFAULT_SIZE;
    (*map).num_elements = 0;
    return map;
}

// does not deal with resizing hashmap currently
void *hash_map_add(hash_map map, char *key, void *data) {

    uint64_t index = hash_string(key) & (ARRAY_DEFAULT_SIZE - 1);
    value *current_index = &(map.hash_array[index]); // variable names are hard ok
    while ((*current_index).key != NULL) {
        current_index = (*current_index).next;
    }
    (*current_index).key = malloc(strlen(key) + 1);
    if ((*current_index).key == NULL) {
        return NULL;
    }
    strcpy((*current_index).key, key);

}

uint64_t hash_string(char *str) {
    int i = 0;
    uint64_t hash = FNV_OFFSET_BASIS;

    while (str[i] != 0) {
        hash ^= str[i];
        hash *= FNV_PRIME;
        ++i;
    }
    return hash;
}