#include <stdio.h>

int main(void)
{
    int i, j, c;
    int ndigits[10];

    c = 0;
    for (i = 0; i < 10; i++) {
        ndigits[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c >= '0' && c <= '9') {
            ++ndigits[c - '0'];
        }
    }

    for (i = 0; i < 10; i++) {
        printf("%d: ", i);
        for (int j = 0; j < ndigits[i]; j++) {
            printf("*");
        }

        printf("\n");
    }
}
