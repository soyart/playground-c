#include <stdio.h>

int main(void)
{
    int i, j, c;
    int histo[256];

    printf("k&r 1-14\n");
    printf("Print a histogram representing frequency of character in the input\n");

    c = 0;
    for (i = 0; i < 256; i++) {
        histo[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        ++histo[c];
    }

    for (i = 1; i < 256; i++) {
        printf("%d (%c): ", i, i);
        for (int j = 0; j < histo[i]; j++) {
            printf("*");
        }

        printf("\n");
    }
}
