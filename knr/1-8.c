#include <stdio.h>

long count(void);

int main(void)
{
    long c;
    c = 0;

    printf("knr 1-8\n");
    printf("Count blanks, tabs, and newlines\n");

    c = count();
    printf("result: %ld\n", c);
}

long count()
{
    int c;
    long result;

    c = 0;
    result = 0;

    while ((c = getchar()) != EOF) {
        switch (c) {
        case ' ':
        case '\t':
        case '\n':
            ++result;
        }
    }

    return result;
}
