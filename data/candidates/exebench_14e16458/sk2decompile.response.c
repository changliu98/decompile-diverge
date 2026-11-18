void int_to_str(unsigned int n, char *s) {
  int i;
  for (i = 9; i >= 0; i--) {
    s[i] = (n % 10) + '0';
    n /= 10;
  }
  s[10] = '\0';
}