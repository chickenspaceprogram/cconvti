#ifndef TOKEN_LOADER
#define TOKEN_LOADER

typedef struct token token;
struct token {
    char version;
    char calc;
    char bytes[2];
    int key_offset;
    token *next;
};

#endif