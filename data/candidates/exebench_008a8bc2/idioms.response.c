int obdRevConvert_42(float f, int *r, int *g, int *b, int *a)
{
  *r = (int)(f * 1000) / 256;
  *g = (int)(f * 1000) % 256;
  return 2;
}