void get_bits_exp(double d, double *mantissa, int *exp) {
  unsigned int i;
  double e;
  i = *(unsigned int *)&d;
  if (i) {
    i &= 0x7ff00000;
    *exp = (i >> 20) - 1023;
  } else {
    i = *(unsigned int *)(&d + 4);
    i &= 0x7fffffff;
    i |= 0x40000000;
    i <<= 10;
    *exp = (i >> 20) - 1083;
    e = i;
    e /= 1024.0 * 1024.0 * 1024.0 * 1024.0 * 1024.0 * 1024.0;
  }
  *mantissa = d / e;
}