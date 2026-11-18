bool __cdecl func0(int *test_tuple, int tuple_size, int *K, int K_size)
{
  int j; // [rsp+0h] [rbp-30h]
  bool found; // [rsp+7h] [rbp-29h]
  int i; // [rsp+8h] [rbp-28h]

  for ( i = 0; i < tuple_size; ++i )
  {
    found = 0;
    for ( j = 0; j < K_size; ++j )
    {
      if ( test_tuple[i] == K[j] )
      {
        found = 1;
        break;
      }
    }
    if ( !found )
      return 0;
  }
  return 1;
}