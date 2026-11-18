int gen256(unsigned char *table, unsigned char poly) {
  short r;
  int i;
  if ((poly & 0x100) == 0) return -1;
  table[0] = 0;
  table[1] = 1;
  r = 1;
  for (i = 2; i < 256; i++) {
    r <<= 1;
    if (r & 0x100) r = (r & 0xff) ^ poly;
    table[i] = r;
  }
  return 0;
}