void ltostr(unsigned int l, char *s) {
  int i;
  s[0] = '\0';
  s[8] = '\0';
  for (i = 0; i < 8; i++) {
    unsigned int c = l & 0x0f;
    c += '0';
    if (c > '9') c += 7;
    s[7 - i] = c;
    l >>= 4;
  }
}