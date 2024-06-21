#include <stdio.h>
#include <stdlib.h>

// Normal code
#define STATE_OK 0
// In quotes
#define STATE_QUOTE 1
// In double quotes
#define STATE_DOUBLEQUOTE 2
// The 1st slash is encountered
#define STATE_SLASH_ENTER 3
// The 2nd star in this /* comment */
#define STATE_STAR_EXIT 4
// The 2nd slash in this /* comment */
#define STATE_SLASH_EXIT 5
// This style
#define STATE_COMMENT 6
/* This style */
#define STATE_COMMENT_STAR 7

int next_state(int state, int c);

int main(void)
{
    int c, prevc, state, prevstate;
    c = prevc = state = prevstate = 0;

    while ((c = getchar()) != EOF) {
        state = next_state(state, c);

        switch (state) {
        case STATE_OK:
            // Print the slash in C expr like 1.0/2.0
            if (prevstate == STATE_SLASH_ENTER) {
                putchar(prevc);
            }

        case STATE_QUOTE:
        case STATE_DOUBLEQUOTE:
            putchar(c);
        }

        prevc = c;
        prevstate = state;
    }
}

int next_state(int state, int c)
{
    switch (state) {
    case STATE_OK:
        switch (c) {
        case '"':
            return STATE_DOUBLEQUOTE;

        case '\'':
            return STATE_QUOTE;

        case '/':
            return STATE_SLASH_ENTER;
        }

        break; // breaking from the switch will return unchanged state

    case STATE_QUOTE:
        switch (c) {
        case '\n':
            printf("error: found multi-line quotes");
            exit(1);

        case '\'':
            return STATE_OK;
        }

        break;

    case STATE_DOUBLEQUOTE:
        switch (c) {
        case '\n':
            printf("error: found multi-line double quotes");
            exit(1);

        case '"':
            return STATE_OK;
        }

        break;

    case STATE_SLASH_ENTER:
        switch (c) {
        case '/':
            return STATE_COMMENT;

        case '*':
            return STATE_COMMENT_STAR;
        }

        return STATE_OK;

    case STATE_COMMENT:
        switch (c) {
        case '\n':
            return STATE_OK;
        }

        break;

    case STATE_COMMENT_STAR:
        switch (c) {
        case '*':
            return STATE_STAR_EXIT;
        }

        break;

    case STATE_STAR_EXIT:
        switch (c) {
        case '/':
            return STATE_SLASH_EXIT;
        }

        return STATE_COMMENT_STAR;

    case STATE_SLASH_EXIT:
        switch (c) {
        case '/':
            return STATE_SLASH_ENTER;
        }

        return STATE_OK;

    default:
        // Unknown state
        printf("error: unknown state %d", state);
        exit(2);
    }

    return state; // state unchanged (from break inside the switch)
}
