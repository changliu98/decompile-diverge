void __attribute__ ((noinline, noclone)) func0(int *test_tup, int n, int *res)
{
  int i;
  for (i = 0; i < n; i++)
    res[i] = -test_tup[i];
}