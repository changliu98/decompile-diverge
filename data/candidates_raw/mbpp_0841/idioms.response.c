int get_inv_count(int a[], int n)
{
  int inv_count = 0;
  int i; int j;
  for (i = 0; i < n; i++)
    for (j = i + 1; j < n; j++)
      if (a[i] > a[j])
        inv_count++;
  return inv_count;
}