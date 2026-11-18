static int ctsxs(unsigned int a, int b, unsigned int *pfflags) {
  int exp;
  unsigned int frac;
  exp = (a >> 23) & 0xff;
  frac = a & 0x7fffff;
  if (frac > 0x3f800000) return 0;
  exp += b - 127;
  if (exp < 0) return 0;
  if (exp >= 31) {
    if ((a + (b << 23)) != 0xcf000000) *pfflags |= _FPU_MASK_INVALID;
    return (a & 0x80000000) ? 0x80000000 : 0x7fffffff;
  }
  frac = (frac | 0x800000) << 7;
  frac >>= 31 - exp;
  return (a & 0x80000000) ? -frac : frac;
}