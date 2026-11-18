int func0(int a[], int n, int sum, int *triplet)
{
  int i; int j; int k;
  for (i = 0; i < n - 2; i++)
  {
    for (j = i + 1; j < n - 1; j++)
    {
      for (k = j + 1; k < n; k++)
      {
        if (a[i] + a[j] + a[k] == sum)
        {
          triplet[0] = a[i];
          triplet[1] = a[j];
          triplet[2] = a[k];
          return 1;
        }
      }
    }
  }
  return 0;
}