void
clip_int(int *x, int min, int max)
{
  int tmp, tmp2;
  tmp = *x;
  if (tmp < min) {
    tmp = min;
  }
  tmp = tmp2 = tmp;
  if (tmp > max) {
    tmp2 = max;
  }
  tmp = tmp2;
  *x = tmp;
}