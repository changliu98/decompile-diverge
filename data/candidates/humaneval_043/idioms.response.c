int func0(int *array, int size)
{
  int i; int j;
  for (i = 0; i < size; i++)
  {
    for (j = i + 1; j < size; j++)
    {
      if (array[i] + array[j] == 0)
      {
        return 1;
      }
    }
  }
  return 0;
}