#include <stdio.h>

#define STATE_OUT 0
#define STATE_IN 1

void copy_and_replace(void);
int in_or_out(int);

int main(void)
{
    printf("knr 1-9\n");
    printf("Truncate blanks and tabs to just 1 blank\n");

    copy_and_replace();
}

int in_or_out(int c)
{
    switch (c) {
    case ' ':
    case '\t':
    case '\n':
        return STATE_OUT;
    }

    return STATE_IN;
}

void copy_and_replace(void)
{
    int c;
    int state, prev_state;

    c = 0;
    prev_state = state = STATE_OUT;

    while ((c = getchar()) != EOF) {
        state = in_or_out(c);

        if (state == STATE_IN) {
            putchar(c);

            prev_state = state;
            continue;
        }

        if (state != prev_state) {
            putchar(' ');
        }

        prev_state = state;
    }

    putchar('\n');
}
