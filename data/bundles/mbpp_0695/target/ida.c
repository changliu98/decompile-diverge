bool __cdecl func0(int *test_tup1, int *test_tup2, int length)
{
  int i; // [rsp+0h] [rbp-20h]

  for ( i = 0; i < length; ++i )
  {
    if ( test_tup1[i] >= test_tup2[i] )
      return 0;
  }
  return 1;
}