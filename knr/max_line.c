#include <stdio.h>

#define MAX_LEN 1000

// Gets input line to line, returning the length
int get_line(char line[], int limit);

// Copy bytes from from to to
void copy_bytes(char to[], char from[]);

int main(void)
{
    int len = 0;
    int max = 0;

    char line[MAX_LEN];
    char longest[MAX_LEN];

    while ((len = get_line(line, MAX_LEN)) > 0) {
        if (len > max) {
            max = len;
            copy_bytes(longest, line);
        }
    }

    printf("Longest line:\n%s\nLength:\n%d\n", longest, max);
}

int get_line(char line[], int limit)
{
    int c = 0;
    int i;

    // Reserve space for null character
    limit = limit - 1;

    // Exit loop on newline or EOF
    //
    // If we only exit on EOF, then the loop will run until EOF
    // and we can't possibly separate each line from the input.
    for (i = 0; (i < (limit - 1)) && (c = getchar()) != EOF && c != '\n'; i++) {
        line[i] = c;
    }

    // If there's newline, collect and count it as well
    if (c == '\n') {
        line[i] = c;
        i++;
    }

    // Append null terminator
    line[i] = '\0';

    return i;
}

void copy_bytes(char to[], char from[])
{
    int i = 0;

    // Read from from to to until null character.
    // Note that we also copy the null character to destination
    while ((to[i] = from[i]) != '\0') {
        i++;
    }
}
