void utf8_int_string(unsigned int c, char *s) {
  if (s == NULL) return;
  s[0] = '\0';
  if (c < 0x80) {
    s[0] = c;
    s[1] = '\0';
  } else if (c < 0x800) {
    s[0] = (c >> 6) & 0x1f;
    s[0] |= 0xc0;
    s[1] = c & 0x3f;
    s[1] |= 0x80;
    s[2] = '\0';
  } else if (c < 0x10000) {
    s[0] = (c >> 12) & 0xf;
    s[0] |= 0xe0;
    s[1] = (c >> 6) & 0x3f;
    s[1] |= 0x80;
    s[2] = c & 0x3f;
    s[2] |= 0x80;
    s[3] = '\0';
  } else if (c < 0x200000) {
    s[0] = (c >> 18) & 0x7;
    s[0] |= 0xf0;
    s[1] = (c >> 12) & 0x3f;
    s[1] |= 0x80;
    s[2] = (c >> 6) & 0x3f;
    s[2] |= 0x80;
    s[3] = c & 0x3f;
    s[3] |= 0x80;
    s[4] = '\0';
  }
}