int func0(int *test_tup, int n, int K)
{
  int i;
  for (i = 0; i < n; i++)
    if (test_tup[i] == K)
      return 1;
  return 0;
}