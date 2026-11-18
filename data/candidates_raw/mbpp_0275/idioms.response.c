int max(int a[], int n, int m)
{
  int i;
  int max;
  int index;
  for (i = 0; i < n; i++)
    a[i] = a[i] / m + (a[i] % m != 0);
  max = -1;
  index = -1;
  for (i = n - 1; i >= 0; i--)
    if (a[i] > max)
    {
      max = a[i];
      index = i;
    }
  return (index + 1);
}