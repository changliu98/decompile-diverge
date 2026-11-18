int __cdecl func0(int n)
{
  int temp; // [rsp+0h] [rbp-10h]
  int i; // [rsp+4h] [rbp-Ch]
  int cnt; // [rsp+8h] [rbp-8h]

  cnt = 0;
  for ( i = 1; i <= n; ++i )
  {
    for ( temp = i; temp; temp /= 2 )
    {
      if ( !(temp % 2) )
        ++cnt;
    }
  }
  return cnt;
}