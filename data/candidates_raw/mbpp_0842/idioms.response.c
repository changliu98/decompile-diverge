int find_odd(int a[], int n)
{
  int i; int j; int count;
  for (i = 0; i < n; i++)
  {
    count = 0;
    for (j = 0; j < n; j++)
    {
      if (a[i] == a[j])
        count++;
    }
    if (count % 2)
      return a[i];
  }
  return -1;
}