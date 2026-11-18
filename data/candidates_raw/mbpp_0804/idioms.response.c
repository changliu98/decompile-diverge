int is_even(int *array, int n)
{
  int i = 0;
  for (i = 0; i < n; i++)
    if (array[i] % 2 == 0)
      return 1;
  return 0;
}