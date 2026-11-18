int u_get(unsigned int *u, unsigned char *s) {
  if (*s < 0x80) {
    *u = *s;
    return 1;
  }
  if (*s < 0xc0) return 0;
  if (*s < 0xe0) {
    *u = (s[0] & 0x1f) << 6 | (s[1] & 0x3f);
    return (*u & 0xffffff80) ? 2 : 0;
  }
  if (*s < 0xf0) {
    *u = (s[0] & 0x0f) << 12 | (s[1] & 0x3f) << 6 | (s[2] & 0x3f);
    return (*u & 0xfffff800) ? 3 : 0;
  }
  if (*s < 0xf8) {
    *u = (s[0] & 0x07) << 18 | (s[1] & 0x3f) << 12 | (s[2] & 0x3f) << 6 |
         (s[3] & 0x3f);
    return (*u & 0xffff0000) ? 4 : 0;
  }
  if (*s < 0xfc) {
    *u = (s[0] & 0x03) << 24 | (s[1] & 0x3f) << 18 | (s[2] & 0x3f) << 12 |
         (s[3] & 0x3f) << 6 | (s[4] & 0x3f);
    return (*u & 0xffe00000) ? 5 : 0;
  }
  if (*s < 0xfe) {
    *u = (s[0] & 0x01) << 30 | (s[1] & 0x3f) << 24 | (s[2] & 0x3f) << 18 |
         (s[3] & 0x3f) << 12 | (s[4] & 0x3f) << 6 | (s[5] & 0x3f);
    return (*u & 0xfc000000) ? 6 : 0;
  }
  return 0;
}