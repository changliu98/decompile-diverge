int func0(int *a, int n)
{
  int i;
  int max;

  max = -2147483648;

  for (i = 1; i < n; i++)
    {
      if (a[i] < max)
        return 0;
      if (a[i-1] > max)
        max = a[i-1];
    }

  return 1;
}