int is_sorted(int *list, int size)
{
  int i;
  for (i = 0; i < size - 1; i++)
  {
    if (list[i] > list[i + 1])
      return 0;
  }
  return 1;
}