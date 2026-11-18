int func0(int n)
{
  int x;
  int res;

  if (n < 4)
    return n;

  res = n;
  for (x = 1; x <= n; x++) {
    int sq = x * x;
    if (sq > n)
      break;

    int tmp = 1 + func0(n - sq);
    if (tmp > res)
      res = tmp;
  }

  return res;
}