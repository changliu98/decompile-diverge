int func0(int *coins, int m, int V)
{
  int res;
  int i;
  int sub_res;
  if (V == 0)
    return 0;
  res = 0x7fffffff;
  for (i = 0; i < m; i++)
  {
    if (coins[i] <= V)
    {
      sub_res = func0(coins, m, V - coins[i]);
      if (sub_res != 0x7fffffff && sub_res + 1 < res)
        res = sub_res + 1;
    }
  }
  return res;
}