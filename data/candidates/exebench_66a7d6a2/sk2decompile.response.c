void swapdouble(double *d) {
  unsigned int t;
  t = ((((unsigned int)(d[0])) & 0xff) << 24) |
      ((((unsigned int)(d[0])) & 0xff00) << 8) |
      ((((unsigned int)(d[0])) & 0xff0000) >> 8) |
      ((((unsigned int)(d[0])) & 0xff000000) >> 24);
  d[0] = ((((unsigned int)(d[1])) & 0xff) << 24) |
         ((((unsigned int)(d[1])) & 0xff00) << 8) |
         ((((unsigned int)(d[1])) & 0xff0000) >> 8) |
         ((((unsigned int)(d[1])) & 0xff000000) >> 24);
  d[1] = t;
}