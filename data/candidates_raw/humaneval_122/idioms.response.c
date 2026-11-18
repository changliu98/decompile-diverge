int sum(int *array, int k)
{
  int sum = 0;
  int i;
  for (i = 0; i < k; i++)
  {
    if (array[i] >= -99 && array[i] <= 99)
      sum += array[i];
  }
  return sum;
}