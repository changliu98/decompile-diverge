static int ilog2(unsigned long x) {
  int i;
  for (i = 0; 1L << i < x; i++)
    ;
  return i;
}