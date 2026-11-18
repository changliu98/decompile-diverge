void minmax(int *min, int *max)
{
  int temp = *min;
  if(*min < *max)
  {
    *min = *max;
    *max = temp;
  }
}