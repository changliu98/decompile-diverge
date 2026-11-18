int __cdecl hex2int(int ch_0)
{
  if ( ch_0 >= 97 && ch_0 <= 102 )
    return ch_0 - 87;
  if ( ch_0 < 65 || ch_0 > 70 )
    return ch_0 - 48;
  return ch_0 - 55;
}