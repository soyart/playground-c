#include <stdio.h>

#define MAXLEN 1000
#define EIGHTY 80

int get_line(char line[], int limit);

int main(void)
{
    int len = 0;
    char line[MAXLEN];

    printf("k&r 1-17\n");
    printf("Only print input lines that are longer than 80 characters\n");

    while ((len = get_line(line, MAXLEN)) > 0) {
        if (len > EIGHTY) {
            printf("%s", line);
        }
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
