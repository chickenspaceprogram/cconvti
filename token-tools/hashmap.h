#ifndef TOKEN_TOOLS_HASHMAP
#define TOKEN_TOOLS_HASHMAP

#define FNV_OFFSET_BASIS 0xcbf29ce484222325
#define FNV_PRIME 0x100000001b3
#include <stdio.h>

unsigned long long hash_string(char *str);

#endif