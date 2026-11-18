void png_64bit_product(unsigned long a, unsigned long b, unsigned long *hi,
                       unsigned long *lo) {
  unsigned long a0, b0, a1, b1;
  a0 = (unsigned short)a;
  b0 = (unsigned short)b;
  a1 = (unsigned short)(a >> 16);
  b1 = (unsigned short)(b >> 16);
  *hi = a1 * b1;
  *hi += (a0 * b1) >> 16;
  *hi += (b0 * a1) >> 16;
  *lo = a * b;
}