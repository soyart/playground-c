#include <stdio.h>

#define MAX_LEN 1000

// Gets input line to line, returning the length
int get_line(void);

// Copy bytes from from to to
void copy_bytes(void);

int max;
char line[MAX_LEN];
char longest[MAX_LEN];

/*
    The extern statements in main, get_line, and copy_bytes
    are redundant and not needed: the variable declarations
    already occur before their use in the functions.
*/

int main(void)
{
    extern char longest[];
    extern int max;

    max = 0;
    int len = 0;

    while ((len = get_line()) > 0) {
        if (len > max) {
            max = len;
            copy_bytes();
        }
    }

    printf("longest: %s, max: %d\n", longest, max);
}

int get_line(void)
{
    extern char line[];

    int i, c;

    for (i = 0; (i < (MAX_LEN - 1)) && (c = getchar()) != EOF && c != '\n'; i++) {
        line[i] = c;
    }
    if (c == '\n') {
        line[i] = c;
        i++;
    }

    line[i] = '\0';

    return i;
}

void copy_bytes(void)
{
    extern char line[], longest[];

    int i = 0;

    while ((longest[i] = line[i]) != '\0') {
        i++;
    }
}
