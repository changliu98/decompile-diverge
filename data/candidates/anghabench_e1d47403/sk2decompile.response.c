unsigned int mul_poly(unsigned int a, unsigned int b, unsigned int poly) {
  unsigned int result = 0;
  while (a) {
    if (a & 1) result ^= b;
    a >>= 1;
    b <<= 1;
    if (b & 0x10000) b ^= poly;
  }
  return result;
}