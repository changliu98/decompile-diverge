void itoa(unsigned int n, char *s) {
  int i = 7;
  s[i] = '\0';
  do {
    s[i--] = n % 10 + '0';
    n /= 10;
  } while (n);
}