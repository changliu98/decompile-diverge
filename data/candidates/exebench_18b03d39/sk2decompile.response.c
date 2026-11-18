void si_swapl(unsigned int *x) {
  unsigned int t;
  t = *x;
  *x = (t & 0xff) << 24;
  *x |= (t & 0xff00) << 8;
  *x |= (t & 0xff0000) >> 8;
  *x |= (t & 0xff000000) >> 24;
}