static inline unsigned gf_poly_mul2(unsigned a) {
  unsigned b;
  b = (a & 0x7f7f7f7f) << 1;
  b ^= (a & 0x80808080) << 3;
  return b;
}