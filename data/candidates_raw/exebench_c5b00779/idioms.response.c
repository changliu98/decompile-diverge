int bsearch(int *base, int n, int key)
{
  int *base0 = base;
  int n0 = n;
  int key0 = key;
  int fib[-1];
  int low; int high; int mid;
  int i; int k;
  memcpy(fib, fib_table, sizeof(fib));
  low = 1;
  high = n0;
  for (i = 0; fib[i] - 1 < n0; i++)
    ;
  for (k = n0; k < fib[i] - 1; k++)
    base0[k] = base0[n0];
  while (low <= high)
  {
    mid = low + fib[i - 1] - 1;
    if (key0 < base0[mid])
    {
      high = low + fib[--i] - 2;
      continue;
    }
    if (key0 > base0[mid])
    {
      low += fib[i - 1];
      i -= 2;
      continue;
    }
    if (mid <= n0)
      return low + fib[i - 1] - 1;
    else
      return n0;
  }
  return 0;
}