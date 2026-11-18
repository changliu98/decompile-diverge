void __cdecl func0(int *nums, int size, int n, int *result)
{
  int i; // [rsp+4h] [rbp-1Ch]

  qsort(nums, size, 4uLL, (__compar_fn_t)compare);
  for ( i = 0; i < n; ++i )
    result[i] = nums[i];
}