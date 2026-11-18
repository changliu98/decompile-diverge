int chartorune(unsigned short *rune, const char *str) {
  unsigned short c, c1, c2;
  c = (unsigned char)*str;
  if (c < 0x80) {
    *rune = c;
    return 1;
  }
  c1 = (unsigned char)str[1] ^ 0x80;
  if ((c1 & 0xc0) != 0) goto invalid;
  if (c < 0xe0) {
    if (c < 0xc0 || (c << 6 | c1) < 0x80) goto invalid;
    *rune = c << 6 | c1;
    return 2;
  }
  c2 = (unsigned char)str[2] ^ 0x80;
  if ((c2 & 0xc0) != 0) goto invalid;
  if (c >= 0xf0 || (c << 12 | c1 << 6 | c2) < 0x800) goto invalid;
  *rune = c << 12 | c1 << 6 | c2;
  return 3;
invalid:
  *rune = 0x80;
  return 1;
}