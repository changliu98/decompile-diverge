int func0(int *array, int size)
{
  int max = -1;
  int i = 1;
  for (i = 1; i < size; i++)
  {
    if (array[i] < array[i - 1])
    {
      max = i;
    }
  }
  return max;
}