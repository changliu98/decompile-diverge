void __cdecl func0(int *nums, int size, int *result)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < size - 1; ++i )
    result[i] = nums[i + 1] + nums[i];
}