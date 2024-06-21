#include <stdio.h>

void unescape(void);

int main(void)
{
    printf("knr 1-10\n");
    printf("Unescape special characters\n");

    unescape();
}

void unescape(void)
{
    int c;
    c = 0;

    while ((c = getchar()) != EOF) {
        switch (c) {
        case '\t':
            putchar('\\');
            putchar('t');
            continue;

        case '\b':
            putchar('\\');
            putchar('b');
            continue;

        case '\\':
            putchar('\\');
            putchar('\\');
            continue;
        }

        putchar(c);
    }
}
