int __cdecl func0(int n)
{
  int q; // [rsp+0h] [rbp-10h]
  int i; // [rsp+4h] [rbp-Ch]
  int count; // [rsp+8h] [rbp-8h]

  count = 0;
  for ( i = 0; i < n; ++i )
  {
    if ( !(i % 11) || !(i % 13) )
    {
      for ( q = i; q > 0; q /= 10 )
      {
        if ( q % 10 == 7 )
          ++count;
      }
    }
  }
  return count;
}