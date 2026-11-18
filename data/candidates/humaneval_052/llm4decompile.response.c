int func0(int *l, int size, int t)
{
  int i;
  for (i = 0; i < size; i++)
    if (l[i] >= t)
      return 0;
  return 1;
}