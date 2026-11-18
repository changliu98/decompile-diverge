unsigned int denormal_addf1(unsigned int a, unsigned int b) {
  unsigned int a_exp, a_mant, b_mant;
  if (a < 0x800000) return a + b;
  a_exp = a & 0x7F800000;
  a_mant = a & 0x007FFFFF;
  a_exp >>= 23;
  if (a_exp - 1 > 31) return a;
  b_mant = b >> (a_exp - 1);
  if (b_mant == 0) return a;
  a_mant |= 0x800000;
  a_mant += b_mant;
  if (a_mant >= 0x1000000) {
    a_mant >>= 1;
    a_exp++;
  }
  a_mant &= 0x007FFFFF;
  return a_mant | (a_exp << 23);
}