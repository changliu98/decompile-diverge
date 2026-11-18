int func0(int *a, int n)
{
  int i; int j; int k; int max = 0; int temp;
  for (i = 0; i < n - 1; i++)
  {
    for (j = 0; j < n - i - 1; j++)
    {
      if (a[j] > a[j + 1])
      {
        temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      }
    }
  }
  for (i = 0; i < n; i++)
  {
    for (k = 1, j = i; 1; j++)
    {
      if (j + 1 < n && a[j] == a[j + 1])
      {
        k++;
        continue;
      }
      if (max < k)
        max = k;
      break;
    }
  }
  return max;
}