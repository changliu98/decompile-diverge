int func0(int *array, int size)
{
  int i;
  if (size == 0)
    return 1;
  for (i = 1; i < size; i++)
  {
    if (array[i] < array[i - 1])
      return 0;
    if (i >= 2 && array[i] == array[i - 1] && array[i] == array[i - 2])
      return 0;
  }
  return 1;
}