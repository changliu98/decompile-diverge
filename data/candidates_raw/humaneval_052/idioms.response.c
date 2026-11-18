int is_all_less(int *list, int size, int t)
{
  int i;
  for (i = 0; i < size; i++)
    if (list[i] >= t)
      return 0;
  return 1;
}