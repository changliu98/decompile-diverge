void __cdecl func0(int *nums, int len, int n, int *result)
{
  qsort(nums, (size_t)len, sizeof(int), (__compar_fn_t)compare);
  
  for (int i = 0; i < n; ++i)
    result[i] = nums[i];
}