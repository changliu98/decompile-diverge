int max(float *array)
{
  int i; int max = 0;
  float highest = array[max];
  for (i = 0; i < 2; i++)
  {
    if (array[i] > highest)
    {
      max = i;
      highest = array[max];
    }
  }
  return max;
}