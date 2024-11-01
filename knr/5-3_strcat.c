#include <stdio.h>

void _strcat(char *s, char *t);

int main(void) {
  char s[20] = "TestStr";
  char t[5] = "Eiei";

  _strcat(s, t);
  printf("%s\n", s);
}

void _strcat(char *s, char *t) { 
  while (*s != '\0') {
    s++;
  }

  while ((*s++ = *t++)) ;
}
