int func0(int *array, int size)
{
  int max = -0x7fffffff - 1;
  int min = 0x7fffffff;
  int i = 0;
  for (i = 0; i < size; i++)
  {
    if (array[i] > max)
    {
      max = array[i];
    }
    if (array[i] < min)
    {
      min = array[i];
    }
  }
  return (min + max);
}