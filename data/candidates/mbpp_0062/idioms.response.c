int func0(int *array, int size)
{
  int min = 0x7fffffff;
  int i = 0;
  for (i = 0; i < size; i++)
  {
    if (array[i] < min)
    {
      min = array[i];
    }
  }
  return min;
}