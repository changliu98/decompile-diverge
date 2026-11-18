void jis_shift(unsigned char *c1, unsigned char *c2) {
  unsigned char c = *c1;
  unsigned char base = (c < 95) ? 112 : 176;
  unsigned char shift = (c % 2) ? ((*c2 < 96) ? 31 : 32) : 126;
  *c1 = base + (c + 1) / 2;
  *c2 += shift;
}