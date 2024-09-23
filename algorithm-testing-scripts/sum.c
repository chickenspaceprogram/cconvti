#include <stdio.h>

int main(void) {
    FILE *fp = fopen("token_lengths.txt", "r");
    int current_num;
    int sum = 0;
    while (fscanf(fp, "%d", &current_num) != EOF) {
        sum += current_num;
        sum += sizeof(char *);
    }
    printf("%d\n", sum);
}