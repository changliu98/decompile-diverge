void bn_reverse(unsigned char *s, int len) {
  int i, j;
  unsigned char c;
  for (i = 0, j = len - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}