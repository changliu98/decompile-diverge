void itoa_dec(unsigned int n, char *s) {
  unsigned int i;
  for (i = 0; i < 10; i++) {
    if (n == 0 && i != 0)
      s[9 - i] = ' ';
    else
      s[9 - i] = "0123456789"[n % 10];
    n /= 10;
  }
}