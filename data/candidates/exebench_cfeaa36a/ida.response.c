void __cdecl sjis_shift(int *p1, int *p2)
{
  int v2; // eax
  int v3; // eax
  int v4; // [rsp+0h] [rbp-24h]
  int rowOffset; // [rsp+8h] [rbp-1Ch]
  unsigned __int8 c2; // [rsp+12h] [rbp-12h]
  unsigned __int8 c1; // [rsp+13h] [rbp-11h]

  c1 = *p1;
  c2 = *p2;
  v2 = 176;
  if ( c1 < 0xA0u )
    v2 = 112;
  rowOffset = v2;
  if ( c2 >= 0x9Fu )
  {
    v4 = 126;
  }
  else
  {
    v3 = 31;
    if ( c2 > 0x7Fu )
      v3 = 32;
    v4 = v3;
  }
  *p1 = (__PAIR64__(2 * ((unsigned int)c1 - rowOffset), c2) - 159) >> 32;
  *p2 -= v4;
}