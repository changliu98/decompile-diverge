void __cdecl sjis2jis(unsigned __int8 *p1, unsigned __int8 *p2)
{
  char v2; // al
  char v3; // [rsp+0h] [rbp-24h]

  v2 = -80;
  if ( *p1 < 0xA0u )
    v2 = 112;
  if ( *p2 >= 0x9Fu )
    v3 = 126;
  else
    v3 = (*p2 > 0x7Fu) + 31;
  *p1 = 2 * (*p1 - v2) - (*p2 < 0x9Fu);
  *p2 -= v3;
}