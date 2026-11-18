bool __cdecl func0(int *test_tup, int n, int K)
{
  int i; // [rsp+0h] [rbp-18h]
  bool res; // [rsp+7h] [rbp-11h]

  res = 0;
  for ( i = 0; i < n; ++i )
  {
    if ( test_tup[i] == K )
      return 1;
  }
  return res;
}