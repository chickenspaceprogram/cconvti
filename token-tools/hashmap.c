#include "hashmap.h"


/**
 * Computes and returns the 64 bit FNV-1a hash of the null-terminated string `str`.
 */
unsigned long long hash_string(char *str) {
    int i = 0;
    unsigned long long hash = FNV_OFFSET_BASIS;

    while (str[i] != 0) {
        hash ^= str[i];
        hash *= FNV_PRIME;
        ++i;
    }
    return hash;
}