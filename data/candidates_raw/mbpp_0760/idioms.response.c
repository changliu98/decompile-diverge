char *is_sorted(int a[], int n)
{
  int i = 1;
  for (i = 1; i < n; i++)
    if (a[i] != a[0])
      return "no";
  return "yes";
}