static _Bool is_sorted(int *array, int size)
{
  int i;
  for (i = 0; i < size - 1; i++)
  {
    if (array[i] > array[i + 1])
      return 0;
  }
  return 1;
}