#ifndef TOKEN_LOADER
#define TOKEN_LOADER

typedef struct token token;
struct token {
    int version;
    int calc;
    short bytes;
    char *text;
};

#endif