void itox(unsigned short n, char *s) {
  unsigned short i = 0;
  unsigned short j;
  char c[16];
  if (n == 0) {
    s[0] = '0';
    s[1] = '\0';
    return;
  }
  while (n != 0) {
    j = n % 16;
    if (j < 10)
      c[i++] = j + '0';
    else
      c[i++] = j - 10 + 'a';
    n = n / 16;
  }
  j = i;
  while (i > 0) {
    s[j - i] = c[i - 1];
    i--;
  }
  s[j] = '\0';
}