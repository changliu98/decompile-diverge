char *sgml__utf8_get_char(const char *s, int *c) {
  if ((s[0] & 0xe0) == 0xc0 && (s[1] & 0xc0) == 0x80) {
    *c = ((s[0] & 0x1f) << 6) | (s[1] & 0x3f);
    return (char *)s + 2;
  } else if ((s[0] & 0xf0) == 0xe0 && (s[1] & 0xc0) == 0x80 &&
             (s[2] & 0xc0) == 0x80) {
    *c = ((s[0] & 0x0f) << 12) | ((s[1] & 0x3f) << 6) | (s[2] & 0x3f);
    return (char *)s + 3;
  } else if ((s[0] & 0xf8) == 0xf0 && (s[1] & 0xc0) == 0x80 &&
             (s[2] & 0xc0) == 0x80 && (s[3] & 0xc0) == 0x80) {
    *c = ((s[0] & 0x07) << 18) | ((s[1] & 0x3f) << 12) | ((s[2] & 0x3f) << 6) |
         (s[3] & 0x3f);
    return (char *)s + 4;
  } else if ((s[0] & 0xfc) == 0xf8 && (s[1] & 0xc0) == 0x80 &&
             (s[2] & 0xc0) == 0x80 && (s[3] & 0xc0) == 0x80 &&
             (s[4] & 0xc0) == 0x80) {
    *c = ((s[0] & 0x03) << 24) | ((s[1] & 0x3f) << 18) |
         ((s[2] & 0x3f) << 12) | ((s[3] & 0x3f) << 6) | (s[4] & 0x3f);
    return (char *)s + 5;
  } else if ((s[0] & 0xfe) == 0xfc && (s[1] & 0xc0) == 0x80 &&
             (s[2] & 0xc0) == 0x80 && (s[3] & 0xc0) == 0x80 &&
             (s[4] & 0xc0) == 0x80 && (s[5] & 0xc0) == 0x80) {
    *c = ((s[0] & 0x01) << 30) | ((s[1] & 0x3f) << 24) |
         ((s[2] & 0x3f) << 18) | ((s[3] & 0x3f) << 12) | ((s[4] & 0x3f) << 6) |
         (s[5] & 0x3f);
    return (char *)s + 4;
  } else {
    *c = s[0];
    return (char *)s + 1;
  }
}