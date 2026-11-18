static float
f2 (float x, float *y, float *z)
{
  float ret;
  if (y < z)
    {
      *z = *y;
      ret = x;
    }
  return ret;
}