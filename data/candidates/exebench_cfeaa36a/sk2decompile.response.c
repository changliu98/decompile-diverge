void sjis_shift(unsigned char *c1, unsigned char *c2) {
  unsigned char c1_ = *c1;
  unsigned char c2_ = *c2;
  unsigned char c1_base = (c1_ < 0xa0) ? 0x70 : 0xb0;
  unsigned char c2_base = (c2_ < 0x9f) ? (c2_ < 0x80 ? 0x1f : 0x20) : 0x7e;
  *c1 = (c1_ - c1_base) * 2;
  *c2 = c2_ - c2_base;
  if (*c1 > 0xff) {
    *c1 = 0xff;
    *c2 = 0;
  }
}