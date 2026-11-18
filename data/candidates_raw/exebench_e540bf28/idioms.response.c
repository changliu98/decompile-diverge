void ioturn(float *ioptr)
{
  float t0i; float f0i;
  f0i = ioptr[1];
  t0i = ioptr[0] - f0i;
  ioptr[0] = ioptr[0] + f0i;
  ioptr[1] = t0i;
}