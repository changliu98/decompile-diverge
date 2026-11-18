void func0(int *test_list, int n, int *result)
{
  result[0] = test_list[n-1];
  int i = 1;
  for (i = 1; i < n; i++)
  {
    result[i] = test_list[i-1];
  }
}