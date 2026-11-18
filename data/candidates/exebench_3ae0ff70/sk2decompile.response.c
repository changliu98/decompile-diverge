void mult_big(unsigned int a, unsigned int b, unsigned int *hi,
              unsigned int *lo) {
  unsigned int a0, a1, b0, b1, p0, p1;
  a0 = a & 0xffff;
  a1 = a >> 16;
  b0 = b & 0xffff;
  b1 = b >> 16;
  p0 = a0 * b0;
  p1 = a0 * b1 + a1 * b0;
  *hi = a1 * b1 + (p1 >> 16) + (p0 >> 16);
  *lo = (p1 & 0xffff) << 16 + (p0 & 0xffff);
}