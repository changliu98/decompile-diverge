int f2xy(float f, int *x, int *y)
{
  int i = (int)(f / 0.0000305);
  *x = i / 256;
  *y = i % 256;
  return 2;
}