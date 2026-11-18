void unscale(double *val, unsigned int times)
{
  unsigned int i;
  for (i = 0; i < times; i++)
    *val = *val * 1e-78;
}