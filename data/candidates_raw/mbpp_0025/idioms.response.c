int product(int a[], int n)
{
  int i; int j; int temp;
  int product = 1;
  for (i = 1; i < n; i++)
  {
    temp = a[i];
    for (j = i - 1; (a[j] > temp); j--)
    {
      a[j + 1] = a[j];
    }
    a[j + 1] = temp;
  }
  for (i = 0; i < n; i++)
  {
    if (i == 0 || a[i - 1] != a[i])
    {
      product *= a[i];
    }
  }
  return (product);
}