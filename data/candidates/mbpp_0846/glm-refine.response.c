int __cdecl func0(int *arr, int *dep, int n)
{
  int plat_needed = 1;
  int result = 1;
  int i = 1;
  int j = 0;

  // Sort both the arrival and departure arrays
  qsort(arr, n, sizeof(int), (__compar_fn_t)compare);
  qsort(dep, n, sizeof(int), (__compar_fn_t)compare);

  // Traverse both arrays to find the maximum number of overlapping intervals
  while (i < n && j < n)
  {
    if (arr[i] > dep[j])
    {
      // A train departed, free up a platform
      --plat_needed;
      ++j;
    }
    else
    {
      // A train arrived, allocate a new platform
      ++plat_needed;
      ++i;
      
      // Update the maximum platforms needed so far
      if (plat_needed > result)
        result = plat_needed;
    }
  }
  
  return result;
}