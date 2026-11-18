void to_hex(long n, char *s) {
  char hex[] = "0123456789ABCDEF";
  int i;
  for (i = 3; i >= 0; i--) {
    s[i] = hex[n % 16];
    n = n / 16;
  }
  s[4] = '\0';
}