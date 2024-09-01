#include <stdio.h>

int main(void) {
    static int yeet = 123;
    test();
    return 0;
}

void test(void) {
    printf("%d\n", yeet);
}