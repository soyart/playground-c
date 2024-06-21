#include <stdio.h>

#define MAXLEN 1000

int get_line(char line[], int limit);

int main(void)
{
    int len = 0;
    char line[MAXLEN];

    printf("k&r 1-19\n");
    printf("Reverse line by line\n");

    while ((len = get_line(line, MAXLEN))) {
        for (int i = len; i >= 0; i--) {
            int c = line[i];
            switch (c) {
            case '\0':
            case '\n':
                continue;
            }

            putchar(c);
        }

        putchar('\n');
        putchar('\0');
    }
}

int get_line(char line[], int limit)
{
    int i;
    int c;

    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        line[i] = c;
    }

    if (c == '\n') {
        line[i] = c;
        i++;
    }

    line[i] = '\0';

    return i;
}
