void ltox(unsigned int l, char *s) {
  int i;
  char hex[] = "0123456789ABCDEF";
  for (i = 0; i < 8; i++) {
    s[9 - i] = hex[l & 0x0f];
    l >>= 4;
  }
  s[0] = '0';
  s[1] = 'x';
  s[10] = '\n';
  s[11] = '\0';
}