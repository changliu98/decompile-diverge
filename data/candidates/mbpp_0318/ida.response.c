int __cdecl func0(int s)
{
  int k; // [rsp+0h] [rbp-14h]
  int j; // [rsp+4h] [rbp-10h]
  int i; // [rsp+8h] [rbp-Ch]
  int maxvalue; // [rsp+Ch] [rbp-8h]

  maxvalue = 0;
  for ( i = 1; i < s - 1; ++i )
  {
    for ( j = 1; j < s; ++j )
    {
      k = s - i - j;
      if ( k * j * i > maxvalue )
        maxvalue = k * j * i;
    }
  }
  return maxvalue;
}