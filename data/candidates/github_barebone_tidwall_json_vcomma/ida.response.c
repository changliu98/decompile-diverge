int64_t __cdecl vcomma(const uint8_t *json, int64_t len, int64_t i, uint8_t end)
{
  int v6; // [rsp+8h] [rbp-28h]
  int64_t ia; // [rsp+10h] [rbp-20h]

  ia = i;
  if ( i == len )
    return -(i + 1);
  if ( json[i] == 44 )
    return i;
  while ( 1 )
  {
    v6 = json[ia];
    if ( (unsigned int)(v6 - 9) >= 2 && v6 != 13 && v6 != 32 )
      break;
    if ( ++ia >= len )
      return -(ia + 1);
  }
  if ( v6 == 44 )
    return ia;
  if ( json[ia] == end )
    return ia;
  else
    return -(ia + 1);
}