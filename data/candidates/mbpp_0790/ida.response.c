bool __cdecl func0(int *nums, int length)
{
  int i; // [rsp+4h] [rbp-18h]

  for ( i = 0; i < length; ++i )
  {
    if ( nums[i] % 2 != i % 2 )
      return 0;
  }
  return 1;
}