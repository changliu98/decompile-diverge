static void squeeze(unsigned int *s) {
  unsigned int c = 0;
  unsigned int i;
  for (i = 0; i < 31; i++) {
    c += s[i];
    s[i] = c & 0xff;
    c >>= 8;
  }
  c += s[31];
  s[31] = c & 0x7f;
  c >>= 7;
  c *= 19;
  for (i = 0; i < 31; i++) {
    c += s[i];
    s[i] = c & 0xff;
    c >>= 8;
  }
  s[31] += c;
}