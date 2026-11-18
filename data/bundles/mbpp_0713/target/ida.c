bool __cdecl func0(bool *test_tup, int size)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 0; i < size; ++i )
  {
    if ( !test_tup[i] )
      return 0;
  }
  return 1;
}