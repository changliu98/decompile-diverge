int __cdecl a2d(char ch_0)
{
  if ( ch_0 >= 48 && ch_0 <= 57 )
    return ch_0 - 48;
  if ( ch_0 >= 97 && ch_0 <= 102 )
    return ch_0 - 97 + 10;
  if ( ch_0 < 65 || ch_0 > 70 )
    return -1;
  return ch_0 - 65 + 10;
}