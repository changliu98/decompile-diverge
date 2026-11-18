void yxyDES2_Int2Bits(unsigned int i, unsigned char *bits) {
  unsigned int j;
  for (j = 0; j < 4; j++) {
    bits[j] = (i << j) & 0x08;
    bits[j] >>= 3;
  }
}