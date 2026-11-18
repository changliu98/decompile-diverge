unsigned long multmodp(unsigned long a, unsigned long b) {
  unsigned long mask = 0x80000000;
  unsigned long result = 0;
  while (1) {
    if (a & mask) {
      result ^= b;
      if ((a & (mask - 1)) == 0) break;
    }
    mask >>= 1;
    b <<= 1;
    if (b & 0x80000000) b ^= 0xf4000000;
  }
  return result;
}