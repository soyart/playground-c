#include <stdio.h>

int _strend(char *s, char *t);
int _strlen(char *s);

int main(void) {
  char s[10] = "kuyhee";
  char t[10] = "yhee";

  printf("%d\n", _strend(s, t));
}

int _strlen(char *s) {
  char *p= s;
  while (*p != 0) {
    p++;
  }

  return p-s;
}

int _strend(char *s, char *t) {
  int ls = _strlen(s);
  int lt = _strlen(t);
  if (lt > ls) {
    return 0;
  }

  int ps = ls-lt;
  for (int i = 0; i < lt; i++,ps++) {
    if (s[ps] == t[i]) {
      continue;
    }

    return 0;
  }

  return 1;
}

