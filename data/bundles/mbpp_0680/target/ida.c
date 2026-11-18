bool __cdecl func0(int *nums, int size)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 0; i < size - 1; ++i )
  {
    if ( nums[i] > nums[i + 1] )
      return 0;
  }
  return 1;
}