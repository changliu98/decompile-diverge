bool __cdecl func0(int n)
{
  int count; // [rsp+0h] [rbp-14h]
  int temp; // [rsp+4h] [rbp-10h]
  int i; // [rsp+8h] [rbp-Ch]

  for ( i = 0; i < 10; ++i )
  {
    temp = n;
    count = 0;
    while ( temp > 0 )
    {
      if ( temp % 10 == i )
        ++count;
      if ( count > i )
        return 0;
      temp /= 10;
    }
  }
  return 1;
}