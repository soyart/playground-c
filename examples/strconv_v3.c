#include <ctype.h>
#include <stdio.h>

int atoi(char s[])
{
    int result = 0;
    int sign = 1;

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];

        if (isspace(c)) {
            if (result) {
                break;
            }

            continue;
        }

        if (c == '-') {
            if (result) {
                break;
            }

            sign = -1;
            continue;
        }

        if (!isdigit(c)) {
            break;
        }

        int v = c - '0';
        result = (result * 10) + v;
    }

    return result * sign;
}

int btoi(char s[])
{
    int result = 0;
    int sign = 1;
    int idx_leading_zero = -1;

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];

        // Handle leading "0x..."
        if (i - idx_leading_zero == 1 && c == 'b') {
            continue;
        }

        if (isspace(c)) {
            if (result) {
                break;
            }

            continue;
        }

        if (c == '-') {
            if (result) {
                break;
            }

            sign = -1;
            continue;
        }

        if (!result && c == '0') {
            idx_leading_zero = i;
            continue;
        }

        if (c != '0' && c != '1') {
            continue;
        }

        int v = c - '0';
        result = (result << 1) + v;
    }

    return result;
}

int otoi(char s[])
{
    int result = 0;
    int sign = 1;
    int idx_leading_zero = -1;

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];

        // Handle leading "0x..."
        if (i - idx_leading_zero == 1 && c == 'o') {
            continue;
        }

        if (isspace(c)) {
            if (result) {
                break;
            }

            continue;
        }

        if (c == '-') {
            if (result) {
                break;
            }

            sign = -1;
            continue;
        }

        if (!result && c == '0') {
            idx_leading_zero = i;
            continue;
        }

        if (c <= '0' && c >= '8') {
            continue;
        }

        int v = c - '0';
        result = (result << 3) + v;
    }

    return result * sign;
}

int htoi(char s[])
{
    int result = 0;
    int sign = 1;
    int idx_leading_zero = -1;

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];

        if (c == 'x' && i - idx_leading_zero == 1) {
            continue;
        }

        if (isspace(c)) {
            if (result) {
                break;
            }

            continue;
        }

        if (c == '-') {
            if (result) {
                break;
            }

            sign = -1;
            continue;
        }

        if (!result && c == '0') {
            idx_leading_zero = i;
            continue;
        }

        int v = 0;
        if (c >= '0' && c <= '9') {
            v = c - '0';

        } else if (c >= 'a' && c <= 'f') {
            v = c - 'a' + 10;

        } else if (c >= 'A' && c <= 'F') {
            v = c - 'A' + 10;
        }

        result = (result << 4) + v;
    }

    return result * sign;
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

        result = otoi(texts[i]);
        printf("%8s%24s%16d\n", "atoi", texts[i], result);

        result = htoi(texts[i]);
        printf("%8s%24s%16d\n", "atoi", texts[i], result);

        printf("======================================\n");
    }
}
