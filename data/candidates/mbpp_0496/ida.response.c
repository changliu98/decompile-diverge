void __cdecl func0(int *nums, int len, int n, int *result)
{
  int i; // [rsp+4h] [rbp-1Ch]

  qsort(nums, len, 4uLL, (__compar_fn_t)compare);
  for ( i = 0; i < n; ++i )
    result[i] = nums[i];
}