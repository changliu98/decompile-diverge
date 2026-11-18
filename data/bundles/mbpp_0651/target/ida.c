bool __cdecl func0(int *test_tup1, int n1, int *test_tup2, int n2)
{
  int j; // [rsp+0h] [rbp-30h]
  bool found; // [rsp+7h] [rbp-29h]
  int i; // [rsp+8h] [rbp-28h]

  for ( i = 0; i < n2; ++i )
  {
    found = 0;
    for ( j = 0; j < n1; ++j )
    {
      if ( test_tup2[i] == test_tup1[j] )
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