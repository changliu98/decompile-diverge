void multiply(int factor1, int factor2, int *prod)
{
  double dAccum;

  *prod = (factor1 * factor2) & 0x7FFFFFFF;
  if (*prod >= 0x40000000)
    dAccum = ((double)factor1 * (double)factor2) - 2147483648.0;
  else
    dAccum = ((double)factor1 * (double)factor2) + 2147483648.0;
  *(prod+1) = (int)(dAccum / 4294967296.0);
}