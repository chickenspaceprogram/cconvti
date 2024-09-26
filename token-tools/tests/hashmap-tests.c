#include "hashmap-tests.h"

void hashmap_tests() {
    hash_map *hm = hash_map_init(sizeof(char *));
    char *ptr;
    if (hm == NULL) {
        printf("An error occurred, could not create hashmap.\n");
    }
    char *keys[] = {"key0", "key1", "key2", "key3", "key4", "key5", "key6", "key7", "key8", "key9", "key10", "key11", "key12", "key13", "key14", "key15", "key16"};
    char *vals[] = {"val0", "val1", "val2", "val3", "val4", "val5", "val6", "val7", "val8", "val9", "val10", "val11", "val12", "val13", "val14", "val15", "val16"};
    printf("Hashmap created, keys/vals loaded into array\n");

    // checking the first few values to ensure they work correctly
    for (int i = 0; i < 7; ++i) {
        ptr = hash_map_set(hm, keys[i], vals[i]);
        if (ptr == NULL) {
            printf("ERROR: hash_map_set failed on key%d\n", i);
        }
    }
    printf("First %zu values set\n", hash_map_size(hm));
    for (int i = 0; i < 7; ++i) {
        if (hash_map_get(hm, keys[i]) == NULL) {
            printf("ERROR: %s returned a nullptr\n", keys[i]);
        } else if (!strcmp(hash_map_get(hm, keys[i]), vals[i])) {
            printf("ERROR: %s returned the value %s instead of %s\n", keys[i], (char *) hash_map_get(hm, keys[i]), vals[i]);
        }
    }
    printf("All values valid\n");
    // checking that the hashmap resizes when the 8th element is added
    ptr = hash_map_set(hm, keys[7], vals[7]);

    if (ptr == NULL) {
        printf("ERROR: hash_map_set failed on key7\n");
    }

    if (hash_map_size(hm) != 32) {
        printf("ERROR: Hashmap did not resize, its current size is %zu\n", hash_map_size(hm));
    }

    // checking to ensure that the hashmap has actually resized by putting too many elements into it
    for (int i = 8; i < 17; ++i) {
        ptr = hash_map_set(hm, keys[i], vals[i]);
        if (ptr == NULL) {
            printf("ERROR: hash_map_set failed on key%d\n", i);
        }
    }

    for (int i = 7; i < 17; ++i) {

        if (hash_map_get(hm, keys[i]) == NULL) {
            printf("ERROR: %s returned a nullptr\n", keys[i]);
        } else if (!strcmp(hash_map_get(hm, keys[i]), vals[i])) {
            printf("ERROR: %s returned the value %s instead of %s\n", keys[i], (char *) hash_map_get(hm, keys[i]), vals[i]);
        }
    }



}