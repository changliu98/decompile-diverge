bool __cdecl func0(const int *nums, int size)
{
  int i; // [rsp+4h] [rbp-18h]

  for ( i = 0; i < size; ++i )
  {
    if ( nums[i] % 2 != i % 2 )
      return 0;
  }
  return 1;
}