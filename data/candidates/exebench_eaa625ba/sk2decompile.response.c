int get_char_utf8(unsigned int *c, const char *s) {
  unsigned int b0 = (unsigned char)s[0];
  if (b0 < 0x80) {
    *c = b0;
    return b0 ? 1 : 0;
  }
  if (!(b0 & 0x40)) {
    *c = 0xffffffff;
    return -1;
  }
  unsigned int b1 = (unsigned char)s[1];
  if ((b1 & 0xc0) != 0x80) {
    *c = 0xffffffff;
    return -1;
  }
  if (!(b0 & 0x20)) {
    if ((b0 & 0x1e) == 0) {
      *c = 0xffffffff;
      return -1;
    }
    *c = (b0 & 0x1f) << 6 | (b1 & 0x3f);
    return 2;
  }
  unsigned int b2 = (unsigned char)s[2];
  if ((b2 & 0xc0) != 0x80) {
    *c = 0xffffffff;
    return -1;
  }
  if (!(b0 & 0x10)) {
    if ((b0 & 0xf) << 4 | (b1 & 0xf) > 0) {
      *c = (b0 & 0xf) << 12 | (b1 & 0x3f) << 6 | (b2 & 0x3f);
      return 3;
    }
    *c = 0xffffffff;
    return -1;
  }
  unsigned int b3 = (unsigned char)s[3];
  if ((b3 & 0xc0) != 0x80) {
    *c = 0xffffffff;
    return -1;
  }
  if (!(b0 & 0x08)) {
    if ((b0 & 0x7) << 3 | (b1 & 0x7) << 1 | (b2 & 0x7) > 0) {
      *c = (b0 & 0x7) << 18 | (b1 & 0x3f) << 12 | (b2 & 0x3f) << 6 |
           (b3 & 0x3f);
      return 4;
    }
    *c = 0xffffffff;
    return -1;
  }
  unsigned int b4 = (unsigned char)s[4];
  if ((b4 & 0xc0) != 0x80) {
    *c = 0xffffffff;
    return -1;
  }
  if (!(b0 & 0x04)) {
    if ((b0 & 0x3) << 2 | (b1 & 0x3) << 1 | (b2 & 0x3) > 0) {
      *c = (b0 & 0x3) << 24 | (b1 & 0x3f) << 18 | (b2 & 0x3f) << 12 |
           (b3 & 0x3f) << 6 | (b4 & 0x3f);
      return 5;
    }
    *c = 0xffffffff;
    return -1;
  }
  unsigned int b5 = (unsigned char)s[5];
  if ((b5 & 0xc0) != 0x80) {
    *c = 0xffffffff;
    return -1;
  }
  if (!(b0 & 0x02)) {
    if ((b0 & 0x1) << 1 | (b1 & 0x1) > 0) {
      *c = (b0 & 0x1) << 30 | (b1 & 0x3f) << 24 | (b2 & 0x3f) << 18 |
           (b3 & 0x3f) << 12 | (b4 & 0x3f) << 6 | (b5 & 0x3f);
      return 6;
    }
    *c = 0xffffffff;
    return -1;
  }
  *c = 0xffffffff;
  return -1;
}