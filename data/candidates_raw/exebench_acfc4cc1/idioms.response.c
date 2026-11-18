void minmax(int *min, int *max)
{
  int t;
  if(*min > *max)
  {
    t = *min;
    *min = *max;
    *max = t;
  }
}