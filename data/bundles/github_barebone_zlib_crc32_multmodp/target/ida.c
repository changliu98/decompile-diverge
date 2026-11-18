uLong __cdecl multmodp(uLong a, uLong b)
{
  uLong v3; // [rsp+0h] [rbp-28h]
  uLong p; // [rsp+8h] [rbp-20h]
  uLong m; // [rsp+10h] [rbp-18h]

  m = 0x80000000LL;
  p = 0LL;
  while ( 1 )
  {
    if ( (m & a) != 0 )
    {
      p ^= b;
      if ( ((m - 1) & a) == 0 )
        break;
    }
    m >>= 1;
    if ( (b & 1) != 0 )
      v3 = (b >> 1) ^ 0xEDB88320;
    else
      v3 = b >> 1;
    b = v3;
  }
  return p;
}