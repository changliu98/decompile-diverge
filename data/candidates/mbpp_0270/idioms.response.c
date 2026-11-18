int func0(int a[], int n)
{
  int sum = 0;
  int i = 0;
  for (i = 0; i < n; i = i + 2)
  {
    if (a[i]%2 == 0)
    {
      sum = sum + a[i];
    }
  }
  return (sum);
}