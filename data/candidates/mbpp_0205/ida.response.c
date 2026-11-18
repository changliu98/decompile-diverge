void __cdecl func0(const int *test_tup, int n, int *res)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < n; ++i )
    res[i] = ~test_tup[i];
}