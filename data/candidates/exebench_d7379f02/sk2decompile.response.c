void itoa(unsigned short n, char *s) {
  unsigned short i = 0;
  char temp[16];
  if (n == 0) {
    s[0] = '0';
    s[1] = '\0';
    return;
  }
  while (n != 0) {
    temp[i++] = (n % 10) + '0';
    n /= 10;
  }
  unsigned short j = i;
  while (i > 0) {
    s[j - i] = temp[i - 1];
    i--;
  }
  s[j] = '\0';
}