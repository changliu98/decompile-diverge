static int FABSQ(unsigned long *pres, unsigned long *pops) {
  pres[0] = pops[0] & 0x7FFFFFFFFFFFFFFF;
  pres[1] = pops[1];
  return 1;
}