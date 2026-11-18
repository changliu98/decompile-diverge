int __cdecl func0(int n)
{
  char msb; // [rsp+0h] [rbp-Ch]
  int na; // [rsp+4h] [rbp-8h]

  if ( !n )
    return 0;
  msb = 0;
  for ( na = n / 2; na > 0; na /= 2 )
    ++msb;
  return 1 << msb;
}