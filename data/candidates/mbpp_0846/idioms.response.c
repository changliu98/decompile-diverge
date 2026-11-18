int func0(int *arr, int *dep, int n)
{
  int i; int j;
  int plat_needed; int result;
  qsort(arr, n, sizeof(int), compare);
  qsort(dep, n, sizeof(int), compare);
  plat_needed = i = j = 1;
  result = 1;
  while ( (i < n || j < n) )
  {
    if (arr[i] > dep[j])
    {
      --plat_needed;
      ++j;
    }
    else
    {
      ++plat_needed;
      ++i;
      if (plat_needed > result)
        result = plat_needed;
    }
  }
  return result;
}