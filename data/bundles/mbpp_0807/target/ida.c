int __cdecl func0(int *nums, int length)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 0; i < length; ++i )
  {
    if ( nums[i] % 2 )
      return nums[i];
  }
  return -1;
}