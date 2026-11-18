int sum(int a[], int len)
{
  int sum = 0;
  int i = 0;
  for (i = 0; i < len; i++)
    sum += a[i];
  return (sum);
}