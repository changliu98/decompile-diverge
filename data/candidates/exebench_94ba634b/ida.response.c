void __cdecl jis_shift(int *p1, int *p2)
{
  int v2; // eax
  int v3; // eax
  int v4; // [rsp+0h] [rbp-20h]
  int rowOffset; // [rsp+8h] [rbp-18h]
  unsigned __int8 c1; // [rsp+Fh] [rbp-11h]

  c1 = *p1;
  v2 = 176;
  if ( c1 < 0x5Fu )
    v2 = 112;
  rowOffset = v2;
  if ( c1 % 2 )
  {
    v3 = 31;
    if ( (unsigned __int8)*p2 > 0x5Fu )
      v3 = 32;
    v4 = v3;
  }
  else
  {
    v4 = 126;
  }
  *p1 = rowOffset + ((c1 + 1) >> 1);
  *p2 += v4;
}