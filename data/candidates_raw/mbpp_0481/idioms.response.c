int is_summable(int *set, int n, int sum)
{
  if (sum == 0)
    return 1;
  if (n == 0)
    return 0;
  if (set[n - 1] > sum)
    return is_summable(set, n - 1, sum);
  int result = 1;
  if (is_summable(set, n - 1, sum))
    return result;
  return is_summable(set, n - 1, sum - set[n - 1]);
}