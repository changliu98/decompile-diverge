int runetochar(char *s, int c) {
  int c2 = c;
  if (c < 0x80) {
    s[0] = c;
    return 1;
  }
  if (c < 0x800) {
    s[0] = (c >> 6) | 0xC0;
    s[1] = (c & 0x3F) | 0x80;
    return 2;
  }
  if (c > 0x10FFFF) c2 = 0xFFFD;
  if (c2 < 0x10000) {
    s[0] = (c2 >> 12) | 0xE0;
    s[1] = ((c2 >> 6) & 0x3F) | 0x80;
    s[2] = (c2 & 0x3F) | 0x80;
    return 3;
  }
  s[0] = (c2 >> 18) | 0xF0;
  s[1] = ((c2 >> 12) & 0x3F) | 0x80;
  s[2] = ((c2 >> 6) & 0x3F) | 0x80;
  s[3] = (c2 & 0x3F) | 0x80;
  return 4;
}