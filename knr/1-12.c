#include <stdio.h>

#define STATE_OUT 0
#define STATE_IN 1

void one_word_per_line(void);
int in_or_out(int);

int main(void)
{
    printf("knr 1-12\n");
    printf("Print the input, one word per line\n");

    one_word_per_line();
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

void one_word_per_line(void)
{
    int c, state;

    c = 0;
    state = STATE_OUT;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state == STATE_IN) {
                state = STATE_OUT;
                putchar('\n');
            }

            continue;

        } else if (state == STATE_OUT) {
            state = STATE_IN;
        }

        if (state == STATE_IN) {
            putchar(c);
        }
    }
}
