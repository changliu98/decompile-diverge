int find_even(int *array, int size)
{
  int i;
  for (i = 0; i < size; i++)
  {
    if (array[i] % 2 == 0)
    {
      return array[i];
    }
  }
  return -1;
}