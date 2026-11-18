int func0(int n, int a[])
{
  int min = a[0];
  int count = 1;
  int i;
  for (i = 1; i < n; i++)
  {
    if (a[i] < min)
    {
      min = a[i];
      count = 1;
    }
    else if (a[i] == min)
    {
      count++;
    }
  }
  return count;
}