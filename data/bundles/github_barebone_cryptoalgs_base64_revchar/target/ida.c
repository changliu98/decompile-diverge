BYTE __cdecl revchar(char ch_0)
{
  BYTE ch_0a; // [rsp+1h] [rbp-1h]

  ch_0a = ch_0;
  if ( ch_0 >= 65 && ch_0 <= 90 )
    return ch_0 - 65;
  if ( ch_0 >= 97 && ch_0 <= 122 )
    return ch_0 - 97 + 26;
  if ( ch_0 >= 48 && ch_0 <= 57 )
    return ch_0 - 48 + 52;
  if ( ch_0 == 43 )
    return 62;
  if ( ch_0 == 47 )
    return 63;
  return ch_0a;
}