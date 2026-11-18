bool __cdecl func0(int n)
{
  int j; // [rsp+0h] [rbp-10h]
  int i; // [rsp+4h] [rbp-Ch]

  for ( i = 1; i * i <= n; ++i )
  {
    for ( j = 1; j * j <= n; ++j )
    {
      if ( j * j + i * i == n )
        return 1;
    }
  }
  return 0;
}