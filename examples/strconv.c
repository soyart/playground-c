#include <stdio.h>
#include <string.h>

// Parses decimal strings to long ints.
// Minus signs are also parsed.
//
// If illegal char is found, atoi returns early
// with the result parsed thus far.
long atoi(char s[]);

// Parses hexadecimal strings to long ints.
// The strings can have "0x" prefixes.
//
// If illegal char is found, htoi returns early
// with the result parsed thus far.
long htoi(char s[]);

// Parses binary strings to long ints.
// The strings can have "0b" prefixes.
//
// If illegal char is found, btoi returns early
// with the result parsed thus far.
long btoi(char s[]);

long flip_sign(short is_neg, long i)
{
    if (is_neg) {
        return 0UL - i;
    }

    return i;
}

long atoi(char s[])
{
    long parsed = 0;
    short is_neg = 0;
    size_t len = strlen(s);

    if (!len) {
        return 0;
    }

    if (s[0] == '-') {
        is_neg = 1;
    }

    short start = is_neg;
    for (int i = start; i < len; i++) {
        char c = s[i];
        int d = 0;

        if (!(c >= '0' && c <= '9')) {
            break;
        }

        d = c - '0';
        parsed = (10 * parsed) + d;
    }

    return flip_sign(is_neg, parsed);
}

long htoi(char s[])
{
    long parsed = 0;
    short is_neg = 0;
    short maybe_0x = 0; // 1 if found leading '0' in "0x"
    size_t len = strlen(s);

    if (!len) {
        return 0;
    }

    if (s[0] == '-') {
        is_neg = 1;
    }

    short start = is_neg;
    for (int i = start; i < len; i++) {
        char c = s[i];
        int h = 0;

        if (i == start && c == '0') {
            maybe_0x = 1;
        }

        if (maybe_0x && i == 1 && c == 'x') {
            parsed = 0; // discard old result
        }

        if (c >= '0' && c <= '9') {
            h = c - '0';

        } else if (c >= 'a' && c <= 'f') {
            h = c - 'a' + 10;

        } else if (c >= 'A' && c <= 'F') {
            h = c - 'A' + 10;

        } else {
            if (!maybe_0x) {
                break;
            }

            maybe_0x = 0;
        }

        parsed = (16 * parsed) + h;
    }

    return flip_sign(is_neg, parsed);
}

long btoi(char s[])
{
    long parsed = 0;
    short is_neg = 0;
    short maybe_0b = 0; // 1 if '0' in "0b" is found
    size_t len = strlen(s);

    if (s[0] == '-') {
        is_neg = 1;
    }

    short start = is_neg;
    for (int i = start; i < len; i++) {
        char c = s[i];
        int b = 0;

        if (i == start && c == '0') {
            maybe_0b = 1;
        }

        if (maybe_0b && i == 1 && c == 'b') {
            parsed = 0; // discard old result
        }

        if (c >= '0' && c <= '1') {
            b = c - '0';

        } else {
            if (!maybe_0b) {
                break;
            }

            maybe_0b = 0;
        }

        parsed = (2 * parsed) + b;
    }

    return flip_sign(is_neg, parsed);
}

int main(void)
{
    char texts[10][100] = {
        "foo",
        "  -2024.5",
        "   -111 234",
        "0b111",
        " -0b1011",
        "0o777",
        "777",
        "0x1a",
        "  0xdead",
        "-0x11",
    };

    for (int i = 0; i < 10; i++) {
        int result = 0;

        result = atoi(texts[i]);
        printf("%8s%24s%16d\n", "atoi", texts[i], result);

        result = btoi(texts[i]);
        printf("%8s%24s%16d\n", "atoi", texts[i], result);

        result = htoi(texts[i]);
        printf("%8s%24s%16d\n", "atoi", texts[i], result);

        printf("======================================\n");
    }
}
