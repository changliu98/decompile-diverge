int in_tup(int *test_tup, int n, int K)
{
  int i;
  int in = 0;
  for (i = 0; i < n; i++)
    if (test_tup[i] == K)
      in = 1;
  return in;
}