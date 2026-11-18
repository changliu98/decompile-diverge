void Utf32toUtf8(unsigned int c, char *s) {
  if (c < 0x80) {
    s[0] = c;
    s[1] = '\0';
  } else if (c < 0x800) {
    s[0] = 0xc0 | (c >> 6);
    s[1] = 0x80 | (c & 0x3f);
    s[2] = '\0';
  } else if (c < 0x10000) {
    s[0] = 0xe0 | (c >> 12);
    s[1] = 0x80 | ((c >> 6) & 0x3f);
    s[2] = 0x80 | (c & 0x3f);
    s[3] = '\0';
  } else if (c < 0x200000) {
    s[0] = 0xf0 | (c >> 18);
    s[1] = 0x80 | ((c >> 12) & 0x3f);
    s[2] = 0x80 | ((c >> 6) & 0x3f);
    s[3] = 0x80 | (c & 0x3f);
    s[4] = '\0';
  } else {
    s[0] = '?';
    s[1] = '\0';
  }
}