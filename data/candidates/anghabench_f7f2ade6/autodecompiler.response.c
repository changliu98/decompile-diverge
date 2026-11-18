int pmc_overflow(long v) {
  int res;
  if ((unsigned long)v < (unsigned long)(-1))
    res = 1;
  else
    res = 0;

  return res;
}