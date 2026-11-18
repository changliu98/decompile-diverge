float nabs_sf(float *sf)
{
  float *p;
  float f;

  p = (float*)sf;
  f = *p;
  f = -f;
  return f;
}