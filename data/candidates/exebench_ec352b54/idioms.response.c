void swap(float *min, float *max)
{
  int temp;
  if(*min > *max)
  {
    temp = *max;
    *max = *min;
    *min = temp;
  }
}