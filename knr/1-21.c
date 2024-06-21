#include <stdio.h>

#define TABSZ 4

int main(void)
{
    int len = 0;
    int c = 0;
    int spaces = 0;

    printf("k&r 1-21\n");
    printf("Entab\n");

    // tabsz = 4
    //
    // foo......bar
    // foo-..bar
    // bar..baz....
    // bar..baz-
    //
    // Number of tabs needed = tabsz/spaces
    // and number of padding space is tabsz - (count % tabz)

    while ((c = getchar()) != EOF) {
        // Starts counting
        if (c == ' ') {
            spaces++;
            continue;
        }

        if (spaces != 0) {
            int tabs = 0;
            int pads = 0;

            tabs = spaces / TABSZ;
            pads = spaces % (TABSZ * tabs);

            for (int j = 0; j < tabs; j++) {
                putchar('\t');
            }

            for (int k = 0; k < pads; k++) {
                putchar(' ');
            }

            spaces = 0;
        }

        putchar(c);
    }
}
