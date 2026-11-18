int obdRevConvert_2D(float f, int *t)
{
  int t1;
  t1 = (int)(f + 100.0)/0.78125;
  *t = t1;
  return 1;
}