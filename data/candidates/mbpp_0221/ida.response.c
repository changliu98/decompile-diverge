int __cdecl func0(int *nums, int size)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 0; i < size; ++i )
  {
    if ( !(nums[i] % 2) )
      return nums[i];
  }
  return -1;
}