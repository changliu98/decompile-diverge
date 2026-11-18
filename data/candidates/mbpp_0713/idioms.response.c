int func0(int *test_tup, int size)
{
  int i;
  for (i = 0; i < size; i++)
    if (test_tup[i] == 0)
      return 0;
  return 1;
}