/*
    strconv-v2.c
    A rewrite of strconv.c

    This version uses state transition function to parse minus signs
    and the number system prefixes such as "0x" and "0b".
    This version also accepts leading whitespaces in the strings.

    States are enum values, and a single function 'next_state'
    is used to transition states based on cursor's character and position.

    All conversion functions use 'next_state', **except atoi**,
    which do not recognize prefix for decimal strings.

    This allows us to parse 0x91, -0b1010, 77 (octals) and recognize minus signs
    with the number system prefixes using the same mental model.

    All functions can handle minus signs and prefixes, and they all return early
    if illegal character is found, returning the value parsed thus far.
*/

#include <stdio.h>
#include <string.h>

long htoi(char s[]);
long otoi(char s[]);
long btoi(char s[]);
long atoi(char s[]);

// States when parsing from left to right
enum {
    START,
    PRF_NEG, //  Prefix '-' in "-0x91f", or "-123", or "-0b1010"
    PRF_ZERO, // Prefix '0' in "0x91f" or "0b1010"
    PRF_END, //  Prefix 'x' in "0x91f" or 'b' in "0b1010"
    PARSE, //    The char '9' in "0x91f" and "91f"
    ILLEGAL //   Found illegal char
};

long flip_sign(unsigned char is_neg, long i)
{
    if (is_neg) {
        return 0UL - i;
    }

    return i;
}

// Determines next state in a generic fashion.
// next_state can detect legal minus signs, number system prefixes (with prefix_end),
// It's mostly useful during the first 3 chars of the input strings.
//
// This version of next_state allows leading whitespaces and tabs.
// Note: Do not skip any char in the input string *before* you get to state PARSE!
unsigned char next_state(char c, char prefix_end, unsigned char state)
{
    switch (state) {
    case START:
        switch (c) {
        case ' ':
        case '\t':
            return START;

        case '-':
            return PRF_NEG;

        case '0':
            return PRF_ZERO;
        }

        return PARSE;

    case PRF_NEG:
        switch (c) {
        case ' ':
        case '\t':
        case '-':
            return ILLEGAL;

        case '0':
            return PRF_ZERO;
        }

    case PRF_ZERO:
        switch (c) {
        case '0':
            return PRF_ZERO;

        case ' ':
        case '\t':
        case '-':
            return ILLEGAL;
        }

        if (c == prefix_end) {
            return PRF_END;
        }

    case PRF_END:
        switch (c) {
        case ' ':
        case '\t':
        case '-':
            return ILLEGAL;
        }

        return PARSE;
    }

    return state;
}

long htoi(char s[])
{
    size_t len = strlen(s);
    unsigned char state = START;
    unsigned char is_neg = 0;

    long parsed = 0;

    for (int i = 0; (i < len) && (state != ILLEGAL); i++) {
        char c = s[i];
        state = next_state(c, 'x', state);

        if (state == ILLEGAL) {
            break;
        }

        if (state == PRF_NEG) {
            is_neg = 1;
        }

        if (state != PARSE) {
            continue;
        }

        unsigned char h = 0;

        if (c >= '0' && c <= '9') {
            h = c - '0';

        } else if (c >= 'a' && c <= 'f') {
            h = c - 'a' + 10;

        } else if (c >= 'A' && c <= 'F') {
            h = c - 'A' + 10;

        } else {
            break;
        }

        parsed = (parsed << 4) + h;
    }

    return flip_sign(is_neg, parsed);
}

long otoi(char s[])
{
    size_t len = strlen(s);
    unsigned char state = START;
    unsigned char is_neg = 0;

    long parsed = 0;

    for (int i = 0; (i < len) && (state != ILLEGAL); i++) {
        char c = s[i];
        state = next_state(c, 'o', state);

        if (state == ILLEGAL) {
            break;
        }

        if (state == PRF_NEG) {
            is_neg = 1;
        }

        if (state != PARSE) {
            continue;
        }

        if (!(c >= '0' && c <= '7')) {
            break;
        }

        unsigned char o = c - '0';
        parsed = (parsed << 3) + o;
    }

    return flip_sign(is_neg, parsed);
}

long btoi(char s[])
{
    size_t len = strlen(s);
    unsigned char state = START;
    unsigned char is_neg = 0;

    long parsed = 0;

    for (int i = 0; (i < len) && (state != ILLEGAL); i++) {
        char c = s[i];
        state = next_state(c, 'b', state);

        if (state == ILLEGAL) {
            break;
        }

        if (state == PRF_NEG) {
            is_neg = 1;
        }

        if (state != PARSE) {
            continue;
        }

        if (!(c >= '0' && c <= '1')) {
            break;
        }

        unsigned char b = c - '0';
        parsed = (parsed << 1) + b;
    }

    return flip_sign(is_neg, parsed);
}

long atoi(char s[])
{
    size_t len = strlen(s);
    unsigned char is_neg = 0;
    long parsed = 0;

    for (int i = 0; i < len; i++) {
        char c = s[i];

        if (c == ' ' || c == '\t') {
            continue;
        }

        if (c == '-') {
            if (!is_neg) {
                is_neg = 1;
                continue;
            }

            // Found duplicate '-'
            break;
        }

        if (!(c >= '0' && c <= '9')) {
            break;
        }

        unsigned char d = c - '0';
        parsed = (10 * parsed) + d;
    }

    return flip_sign(is_neg, parsed);
}

int main(void)
{
    char dec1[] = "\t 12a120";
    char dec2[] = " -0012-10";
    char hex1[] = " 91x";
    char hex2[] = "\t-0x91";
    char oct1[] = "75589";
    char oct2[] = "      -0o755";
    char bin1[] = "1010";
    char bin2[] = "-0b1010313432";

    printf("result dec1: %ld\n", atoi(dec1));
    printf("result dec2: %ld\n", atoi(dec2));
    printf("result hex1: %ld\n", htoi(hex1));
    printf("result hex2: %ld\n", htoi(hex2));
    printf("result oct1: %ld\n", otoi(oct1));
    printf("result oct2: %ld\n", otoi(oct2));
    printf("result bin1: %ld\n", btoi(bin1));
    printf("result bin2: %ld\n", btoi(bin2));
}
