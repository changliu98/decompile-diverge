void i2f(int i, float *f, float qmin, float qmax, int nlev)
{
  *f = qmin + (qmax - qmin) * i / (nlev - 1);
}