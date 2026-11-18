int func0(int *array, int n)
{
  int i;
  for (i = 0; i < n; i++)
    if (array[i] == i)
      return i;
  return -1;
}