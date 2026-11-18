int is_evenly_divisible(int *array, int length)
{
  int i;
  for (i = 0; i < length; i++)
    if (array[i] % 2 != i % 2)
      return 0;
  return 1;
}