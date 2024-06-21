#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long power(long base, long pow);
long htoi(char s[]);
long htoi_0x(char s[]);
long htoi_pow(char s[]);

int main(void)
{
    int result, result_pow, result_0x, result_0x_no_0x;
    char hex[] = "10f";
    char hex_0x[] = "0x10f";

    result = htoi(hex);
    result_pow = htoi_pow(hex);
    result_0x = htoi_0x(hex_0x);
    result_0x_no_0x = htoi_0x(hex);

    printf("result: %d\n", result);
    printf("result_pow: %d\n", result_pow);
    printf("result_0x: %d\n", result_0x);
    printf("result_0x without 0x: %d\n", result_0x_no_0x);
}

long htoi(char s[])
{

    long result = 0;
    long len = strlen(s);

    for (int i = 0; i < len; i++) {
        char c = s[i];
        int h = 0; // hex value at current position

        if (c >= '0' && c <= '9') {
            h = c - '0';

        } else if (c >= 'a' && c <= 'f') {
            h = c - 'a' + 10;

        } else if (c >= 'A' && c <= 'F') {
            h = c - 'A' + 10;

        } else {
            return result;
        }

        // 89f = 2207
        // = (8 << 4*2) + (9 << 4*1) + (15 << 0)
        //
        // 891 = 2193
        // = (8 << 4*2) + (9 << 4*1) + (1 << 0)
        int pow = len - i - 1;
        result += h * (1 << (4 * pow));

        printf("htoi: pos %d, pow %d, result %ld\n", i, pow, result);
    }

    return result;
}

long htoi_0x(char s[])
{
    long result = 0;
    int len = strlen(s);
    int maybe_0x = 0;

    for (int i = 0; i < len; i++) {
        char c = s[i];
        int h = 0; // hex value at current position

        if (i == 0 && c == '0') {
            maybe_0x = 1;
        }

        if (maybe_0x && i == 1 && c == 'x') {
            result = 0; // discard old result
        }

        if (c >= '0' && c <= '9') {
            h = c - '0';

        } else if (c >= 'a' && c <= 'f') {
            h = c - 'a' + 10;

        } else if (c >= 'A' && c <= 'F') {
            h = c - 'A' + 10;

        } else {
            // if (!maybe_0x) {
            //     return result;
            // }

            maybe_0x = 0;
        }

        int pow = len - i - 1;
        result += h * (1 << (4 * pow));

        printf("htoi_0x: pos %d, pow %d, result %ld\n", i, pow, result);
    }

    return result;
}

long htoi_pow(char s[])
{
    long result = 0;
    long len = strlen(s);

    for (int i = 0; i < len; i++) {
        char c = s[i];
        int h = 0;

        if (c >= '0' && c <= '9') {
            h = c - '0';

        } else if (c >= 'a' && c <= 'f') {
            h = c - 'a' + 10;

        } else if (c >= 'A' && c <= 'F') {
            h = c - 'A' + 10;

        } else {
            return result;
        }

        int pow = len - i - 1;
        long p = power(16, pow);

        result += p * h;

        printf("htoi_pow: pos %d, pow %d, result %ld\n", i, pow, result);
    }

    return result;
}

long power(long base, long pow)
{
    long result = 1;
    for (int i = 0; i < pow; i++) {
        result *= base;
    }

    return result;
}
