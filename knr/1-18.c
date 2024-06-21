#include <stdio.h>

#define MAXLEN 1000

int get_line(char line[], int limit);

int main(void)
{
    int len = 0;
    char line[MAXLEN];

    printf("k&r 1-18\n");
    printf("Remove trailing blanks and tabs, and remove blank lines completely\n");

    while ((len = get_line(line, MAXLEN)) > 0) {
        int until = 0;

        // We loop from len, which line[len] will have \0 stored from get_line
        for (int i = len; i >= 0; i--) {
            int c = line[i];

            switch (c) {
            case '\0':
            case '\n':
            case ' ':
            case '\t':
                continue;
            }

            until = i;
            break;
        }

        if (until == 0) {
            continue;
        }

        for (int i = 0; i <= until; i++) {
            putchar(line[i]);
        }

        putchar('\n');
        putchar('\0');
    }
}

// If input is "foo\n", then line will be "foo\n\0" of length 4
// This means that input[4] (5th elem) will be \0 and safe to access
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
