void argorder(int i1, int i2, int *imin, int *imax)
{
  int i1min = i1;
  int i2min = i2;
  if (i1 > i2) {
    i1min = i2;
    i2min = i1;
  }
  *imin = i1min;
  *imax = i2min;
}