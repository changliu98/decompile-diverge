static unsigned putdword(unsigned char *p, unsigned d) {
  p[0] = d;
  p[1] = d >> 8;
  return d;
}