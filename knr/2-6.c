#include <stdio.h>

// Returns x with the n bits that begin at position p (0 is rightmost)
// set to the rightmost n bits of y, leaving the other bits unchanged.
//
// For simplicity, this exercise uses unsigned ints
unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y);
// Use chars because int is too long to debug
unsigned setbits_debug(unsigned char x, unsigned char p, unsigned char n, unsigned char y);

// Prints n in binary format
void printb(int n);
void printbc(unsigned char n);
// Copied from the book. Used for finding changed bits
unsigned getbits_knr(unsigned x, int p, int n);

int main(void)
{
    int pos, n;
    pos = 7;
    n = 4;

    unsigned x = 115U; // 0000 0000 0111 0011
    unsigned y = 74U; //  0000 0000 0100 1010
    // Expected result:   0000 0000 1010 0011 // 163U
    unsigned e = 163U;

    unsigned result = setbits(x, pos, n, y);
    printf("result:\t");
    printb(result);

    unsigned ok = result == e;
    printf("result ok: %s\n", ok ? "true" : "false");
    if (!ok) {
        unsigned result_debug = setbits_debug(x, pos, n, y);
        printf("result_debug:\t");
        printb(result_debug);
        printf("result_debug ok: %s\n", result_debug == e ? "true" : "false");
    }

    unsigned changed = getbits_knr(result, pos, n);
    printf("changed bits: ");
    printbc(changed);
}

// See setbits_debug
unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y)
{
    unsigned shift = p + 1 - n;
    unsigned mask = ~0u << n;

    return (x & ~(~mask << shift)) | ((y & ~mask) << shift);
}

unsigned setbits_debug(unsigned char x, unsigned char p, unsigned char n, unsigned char y)
{

    printf("p: %d\n", p);
    printf("n: %d\n", n);

    int target = p + 1 - n;
    printf("target left shifts: %d\n", target);

    printf("x:\t");
    printbc(x);

    printf("y:\t");
    printbc(y);

    unsigned mask1 = ~0u << n; // leading 1s with n bits of 0s to the right
    unsigned mask2 = ~(mask1); // leading 0s with n bits of 1s to the right
    unsigned mask3 = mask2 << target; // 1s in target range, the rest is 0s
    unsigned mask4 = ~mask3;
    printf("mask1:\t");
    printbc(mask1);
    printf("mask2:\t");
    printbc(mask2);
    printf("mask3:\t");
    printbc(mask3);
    printf("mask4:\t");
    printbc(mask4);

    y &= mask2;
    printf("y = y & mask2 leftmost n bits of y:\t");
    printbc(y);

    y <<= target;
    printf("y = y << target (moved to target):\t");
    printbc(y);

    x &= mask4;
    printf("x = x & mask3 (set target to 0s):\t");
    printbc(x);

    return x | y;
}

unsigned getbits_knr(unsigned x, int p, int n)
{
    // Left clause: shifts x to desired position with leading 0s
    // Right clause: creates a ..1111000.., where n is the number of 1s to the right
    return (x >> (p + 1 - n)) & ~(~0 << n);
}

void printb(int n)
{
    int size = sizeof(n) * 8;
    for (int i = size - 1; i >= 0; i--) {
        int bit = (n >> i) & 1;
        printf("%d", bit);
    }

    printf("\n");
}

void printbc(unsigned char n)
{
    int size = sizeof(n) * 8;
    for (int i = size - 1; i >= 0; i--) {
        unsigned char bit = (n >> i) & 1;
        printf("%d", bit);
    }

    printf("\n");
}
