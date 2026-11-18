void SJIStoJIS(unsigned char *c1, unsigned char *c2) {
  unsigned char c1_ = *c1;
  unsigned char c2_ = *c2;
  int c1_offset = 0x80;
  int c2_offset = 0x80;
  if (c1_ < 0xa0) {
    c1_offset = 0x40;
  }
  if (c2_ < 0x9f) {
    c2_offset = 0x40;
  }
  if (c2_ < 0x80) {
    c2_offset = 0x20;
  }
  *c1 = (c1_ - c1_offset) * 2;
  *c2 = c2_ - c2_offset;
}