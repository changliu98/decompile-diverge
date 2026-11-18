void utf8_encode(int c, char *s) {
  int len = 0;
  if (c >= 0 && c <= 0x7f) {
    s[0] = c & 0x7f;
    len = 1;
  } else if (c >= 0x80 && c <= 0x7ff) {
    s[1] = 0x80 | (c & 0x3f);
    s[0] = 0xc0 | ((c >> 6) & 0x1f);
    len = 2;
  } else if (c >= 0x800 && c <= 0xffff) {
    s[2] = 0x80 | (c & 0x3f);
    s[1] = 0x80 | ((c >> 6) & 0x3f);
    s[0] = 0xe0 | ((c >> 12) & 0xf);
    len = 3;
  } else if (c >= 0x10000 && c <= 0x10ffff) {
    s[3] = 0x80 | (c & 0x3f);
    s[2] = 0x80 | ((c >> 6) & 0x3f);
    s[1] = 0x80 | ((c >> 12) & 0x3f);
    s[0] = 0xf0 | ((c >> 18) & 0x7);
    len = 4;
  }
  s[len] = '\0';
}