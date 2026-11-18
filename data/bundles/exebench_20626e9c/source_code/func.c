
static void unscale(double * prob, unsigned int times)
{
  unsigned int i;

  for (i = 0; i < times; ++i)
    *prob *= (1.0/115792089237316195423570985008687907853269984665640564039457584007913129639936.0);
}
