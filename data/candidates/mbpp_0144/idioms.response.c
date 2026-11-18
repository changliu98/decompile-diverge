int func0(int a[], int n)
{
  int sum = 0;
  int i = n - 1;
  while ( i >= 0 )
  {
    sum += a[i] * i - a[i] * ( n - 1 - i );
    i--;
  }
  return (sum);
}