int64_t __cdecl vcolon(const uint8_t *json, int64_t len, int64_t i)
{
  int v4; // [rsp+0h] [rbp-24h]
  int64_t ia; // [rsp+4h] [rbp-20h]

  ia = i;
  if ( i == len )
    return -(i + 1);
  if ( json[i] == 58 )
    return i + 1;
  while ( 1 )
  {
    v4 = json[ia];
    if ( (unsigned int)(v4 - 9) >= 2 && v4 != 13 && v4 != 32 )
      break;
    if ( ++ia >= len )
      return -(ia + 1);
  }
  if ( v4 == 58 )
    return ia + 1;
  else
    return -(ia + 1);
}