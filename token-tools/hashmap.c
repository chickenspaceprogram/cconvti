#include "hashmap.h"

/* Declarations */

/**
 * Arguments:
 * `str` : The null-terminated string to hash
 */
uint64_t hash_(char *str);

/**
 * An internal function that sets a key-value pair without checking for constraints like the size of the hashmap.
 * Returns a pointer to the key-value struct.
 * `array` : A pointer to the hashmap array the key-value pair should be added to
 * `array-size` : The size of the hashmap array the key-value pair should be added to
 * `key` : A null-terminated string to be used as key.
 * `data` : A pointer to the value to be stored in the hashmap.
 * `data_size` : The size of the data to be added to the hashmap.
 */
value *hm_set_internal_(value *array, size_t array_size, char *key, void *data, size_t data_size);

/**
 * An internal function that gets the key-value pair associated with a key.
 * Returns a pointer to the key-value pair.
 * `array` : A pointer to the hashmap array that contains the key.
 * `key` : The key
 */
value *hm_get_internal_(value *array, size_t array_size, char *key);

/**
 * Doubles the size of the hashmap.
 * If memory could not be allocated, returns NULL.
 * Otherwise, returns a pointer to the newly-allocated hashmap.
 */
value *hm_double_size_(hash_map *map);

/**
 * Allocates a new hashmap array of size `size`.
 * Does not check for a NULL pointer.
 */
value *allocate_array_(size_t size);



/* Definitions */

struct value {
    void *data;
    char *key;
};

struct hash_map {
    value *hash_array;
    size_t num_elements;
    size_t array_size;
    size_t element_size;
};

hash_map *hash_map_init(size_t element_size) {
    hash_map *map = malloc(sizeof(hash_map));
    if (map == NULL) {
        return NULL;
    }

    map->element_size = element_size;
    map->array_size = ARRAY_DEFAULT_SIZE;
    map->num_elements = 0;

    map->hash_array = allocate_array_(map->array_size);
    if (map->hash_array == NULL) {
        free(map);
        map = NULL;
        return NULL;
    }
    return map;
}

void hash_map_free(hash_map *map) {
    for (int i = 0; i < map->array_size; ++i) {
        free(map->hash_array[i].key);
        free(map->hash_array[i].data);
        map->hash_array[i].key = NULL;
        map->hash_array[i].data = NULL;
    }
    free(map->hash_array);
    free(map);
    map->hash_array = NULL;
    map = NULL;
}

void *hash_map_set(hash_map *map, char *key, void *data) {
    if ((map->num_elements / map->array_size) > MAX_FILL_LEVEL) {
        value *new_array = hm_double_size_(map);
        if (new_array == NULL) {
            hash_map_free(map);
            return NULL;
        }
    }
    value *valptr = hm_set_internal_(map->hash_array, map->array_size, key, data, map->element_size);
    if (valptr == NULL) {
        hash_map_free(map);
        return NULL;
    }
}

void *hash_map_get(hash_map *map, char *key) {
    
}

void hash_map_remove(hash_map *map, char *key) {
    size_t index = hash_(key) & (map->array_size - 1);
    size_t initial_index = index;
    while ((map->hash_array[index].key != NULL) && (strcmp(map->hash_array[index].key, key) != 0)) {
        ++index;
        if (index == initial_index) {
            return;
        }
    }
    free(map->hash_array[index].key);
    free(map->hash_array[index].data);
    map->hash_array[index].key = NULL;
    map->hash_array[index].data = NULL;
}

size_t hash_map_size(hash_map *map) {
    return map->num_elements;
}

// only call this when it is safe to do so! this function assumes that there is space in the hashmap.
value *hm_set_internal_(value *array, size_t array_size, char *key, void *data, size_t data_size) {

    size_t index = hash(key) & (array_size - 1); // binary AND is used instead of modulus because n % 2^k == n & (2^k - 1)
    size_t key_length = strlen(key);

    while (array[index].key != NULL) {
        if (strcmp(key, array[index].key) == 0) {
            array[index].data = data;
            return;
        }

        ++index;
        index = index & (array_size - 1); // keeps the index within the bounds of the table
    }
    array[index].key = malloc(sizeof(char) * (key_length + 1));
    if (array[index].key == NULL) {
        return NULL;
    }
    strcpy(array[index].key, key);
    array[index].key[key_length] = 0x00;

    array[index].data = malloc(data_size);
    if (array[index].data == NULL) {
        free(array[index].key);
        array[index].key = NULL;
        return NULL;
    }
    memcpy(array[index].data, data, data_size);
    return &(array[index]);
}

value *hm_get_internal_(value *array, size_t array_size, char *key) {
    
}

// need to handle this returning NULL!
value *hm_double_size_(hash_map *map) {
    value *new_array = allocate_array_(map->array_size * 2);
    if (new_array == NULL) {
        hash_map_free(map);
        return NULL;
    }
    size_t new_array_size = map->array_size * 2;

    for (int i = 0; i < map->array_size; ++i) {
        if (map->hash_array[i].key != NULL) {
            _hm_set(new_array, new_array_size, map->hash_array[i].key, map->hash_array[i].data);
        }
    }
    free(map->hash_array);
    map->hash_array = new_array;
    map->array_size = new_array_size;
    return new_array;
}

value *allocate_array_(size_t size) {
    value *array = malloc(size * sizeof(value));

    for (int i = 0; i < ARRAY_DEFAULT_SIZE; ++i) {
        array[i] = (value) {NULL, NULL}; // setting all of the pointers in the array to NULL
    }
}

uint64_t hash_(char *str) {
    int i = 0;
    uint64_t hash = FNV_OFFSET_BASIS;

    while (str[i] != 0) {
        hash ^= str[i];
        hash *= FNV_PRIME;
        ++i;
    }
    return hash;
}