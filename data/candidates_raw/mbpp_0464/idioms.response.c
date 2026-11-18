int is_in(int *dict, int size, int n)
{
  int i;
  for (i = 0; i < size; i++)
    if (dict[i] != n)
      return 0;
  return 1;
}