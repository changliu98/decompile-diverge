void multiply(int factor1, int factor2, int *prod)
{
  unsigned int tmp = ((unsigned int)factor1 * (unsigned int)factor2) & 0x7FFFFFFFU;





  int low = (int)tmp;
  double dAccum = (double)factor1 * (double)factor2;
  *prod = low;
  if (low < 0x40000000)
  {
    dAccum = ((dAccum + (double)0x20000000) / 0x80000000U);
  }
  else
  {
    dAccum = ((dAccum - (double)0x20000000) / 0x80000000U);
  }
  *(prod+1) = (unsigned int)dAccum;

}