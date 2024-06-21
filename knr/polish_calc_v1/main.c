// A simple reverse Polish notation calculator
// using external variables for the push-down stack.
// The program reads string inputs from stdin, and
// is expecting reverse Polish notation.
//
// For example, the expression
// (1 - 2) * (4 + 5)
//
// is written in reverse Polish notation as:
// "1 2 - 4 5 + *"
//
// The stack and its stack pointer is not visible in main

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Flag
#define NUMBER '0'
// Maximum size of a single token, e.g. "12.8" or "+"
#define MAXOPS 100
// Maximum depth of our stack machine
#define SZ_STACK 5
// Maximum length for our read buffer
#define SZ_BUF 100

int getop(char[]);
void push(double);
double pop(void);

int main(void)
{
    int type;
    double top; // Top of stack - to ensure order of function calls in pop() / pop()
    char s[MAXOPS];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            continue;

        case '+':
            push(pop() + pop());
            continue;

        case '*':
            push(pop() * pop());
            continue;

        case '-':
            top = pop();
            push(pop() - top);
            continue;

        case '/':
            top = pop();
            push(pop() - top);
            continue;

        case '\n':
            printf("\t%.8g\n", pop());
            return 0;
        }
    }
}

void test_stack(void)
{
    int n = SZ_STACK + 2;

    for (int i = 0; i < n; i++) {
        push((double)i);
    }
    for (int i = 0; i < n; i++) {
        double f = pop();
    }
}

int sp = 0; // Stack pointer
double stack[SZ_STACK];

void push(double f)
{
    if (sp >= SZ_STACK) {
        return;
    }

    stack[sp++] = f;
}

double pop(void)
{
    if (sp < 1) {
        return 0.0;
    }

    // sp is like count/len: a len of 1 means that the value is in array[0]
    return stack[--sp];
}

// Get char from buffer, or getchar if buffer is empty
int getch(void);

// Un-get a char, e.g. when parsing a digit,
// we'll have to read input until we see a non-digit character.
//
// That character needs to be unread (un-get) and pushed back
// to buffer, so that getch will re-get it out and use it to
// parse the next number
void ungetch(int);

// Returns next operator or operand
// If it's not an operator (i.e. it's a number),
// then collect the number string in s and return NUMBER flag.
int getop(char s[])
{
    int i, c;

    // Skip whitespaces
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    // Terminate s (construct a valid string)
    s[1] = '\0';

    // Return operator
    if (!isdigit(c) && c != '.') {
        return c;
    }

    // Reset s and collect integer part
    i = 0;
    if (isdigit(c)) {
        while (isdigit((s[++i] = c = getch())))
            ;
    }

    // Collect fractional part
    if (c == '.') {
        while (isdigit((s[++i] = c = getch())))
            ;
    }

    s[i] = '\0';

    if (c != EOF) {
        ungetch(c);
    }

    return NUMBER;
}

/*
    Buffer and its head pointer, initialized to 0 (empty buffer).
    When an item is inserted, the pointer is incremented by 1.
    When a read is performed on buf, the pointer is decremented by 1

    Only getch and ungetch can see buf and bufp
*/

char buf[SZ_BUF];
int bufp = 0;

// getch reads from buffer if buf not empty,
// or reads from stdin.
int getch(void)
{
    if (bufp > 0) {
        // If buf has 2 elements, then bufp is 2, and the read index is 1.
        // We also need to decrement bufp, and wish to use that decrement expression value of bufp-1,
        // so we use *prefix* decrement operator
        return buf[--bufp];
    }

    char c = getchar();
    return c;
}

void ungetch(int c)
{
    if (bufp >= SZ_BUF) {
        return;
    }

    // If buf has 2 elements, bufp is 2, and the next insertion index is 2
    // We also need to increment bufp, so we use postfix increment operator
    buf[bufp++] = c;
}
