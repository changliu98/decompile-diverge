void descending2(int *min, int *max)
{
  int temp = *min;
  if(*min < *max)
  {
    *min = *max;
    *max = temp;
  }
}