void bit_write_UMC(FILE *f, uint32 val) {
  unsigned char buf[5];
  uint32 mask = 0x7f;
  int i, j;
  for (i = 4, j = 0; i >= 0; i--, j += 7) {
    buf[i] = (unsigned char)((val & mask) >> j);
    buf[i] |= 0x80;
    mask <<= 7;
  }
  for (i = 0; i < 4; i++) {
    if ((buf[i] & 0x7f) != 0) break;
  }
  if ((buf[i] & 0x40) != 0) i--;
  buf[i] &= 0x7f;
  for (j = 4; j >= i; j--) {
    bit_write_RC(f, buf[j]);
  }
}