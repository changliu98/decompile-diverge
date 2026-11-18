int is_sorted(int *a, int n)
{
  int mx = (-0x7fffffff - 1);
  int i = 1;
  for (i = 1; i < n; i++)
  {
    if (a[i] < mx)
      return 0;
    if (a[i - 1] > mx)
      mx = a[i - 1];
  }
  return 1;
}