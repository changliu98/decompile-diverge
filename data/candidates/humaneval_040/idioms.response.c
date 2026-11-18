int func0(int *array, int size)
{
  int i; int j; int k;
  for (i = 0; i < size; i++)
  {
    for (j = i + 1; j < size; j++)
    {
      for (k = j + 1; k < size; k++)
      {
        if (array[i] + array[j] + array[k] == 0)
        {
          return 1;
        }
      }
    }
  }
  return 0;
}