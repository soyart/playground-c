#include <stdio.h>

#define TABSZ 8

int pad_blanks(int count, int tabsz);

int main(void)
{
    int len = 0;
    int count = 0;

    int c;
    int spaces;

    printf("k&r 1-20\n");
    printf("Detab\n");

    while ((c = getchar()) != EOF) {
        // Print every char that's not a tab
        if (c != '\t') {
            putchar(c);
            count++;
        }

        if (c == '\t') {
            spaces = pad_blanks(count, TABSZ);
            for (int i = 0; i < spaces; i++) {
                putchar(' ');
            }

            count = 0;
            continue;
        }

        if (c == '\n') {
            count = 0;
        }
    }
}

int pad_blanks(int count, int tabsz)
{
    return tabsz - (count % tabsz);
}
