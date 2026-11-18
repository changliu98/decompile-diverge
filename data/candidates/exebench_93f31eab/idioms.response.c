int obdRevConvert_10(float f, int *r, int *g, int *b, int *a)
{
  int i = (int)(f * 100);
  *r = i / 256;
  *g = i % 256;
  return 2;
}