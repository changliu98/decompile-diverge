int __cdecl func0(int *nums, int size)
{
  int i; // [rsp+0h] [rbp-14h]
  int result; // [rsp+4h] [rbp-10h]

  result = 0;
  for ( i = 0; i < size; ++i )
    result = nums[i] + 10 * result;
  return result;
}