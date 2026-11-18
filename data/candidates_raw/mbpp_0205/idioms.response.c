void do_not(int *test, int n, int *res)
{
  int i;
  for (i = 0; i < n; i++)
    res[i] = ~test[i];
}