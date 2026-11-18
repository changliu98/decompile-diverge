void __cdecl func0(int *nums, int *result, int size)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 0; i < size; ++i )
    result[i] = nums[i] * nums[i];
}