static float
get_near_num (float x, float *y, float *z)
{
  float ret;
  if (y < z)
    {
      *z = *y;
      ret = x;
    }
  return ret;
}