void __cdecl BMP_getGenBmp16Palette(const unsigned __int16 *genbmp16, unsigned __int16 *pal)
{
  unsigned __int16 *v3; // rax
  unsigned __int16 v4; // cx
  unsigned __int16 *v5; // rax
  const unsigned __int16 *src; // [rsp+8h] [rbp-20h]
  unsigned __int16 i; // [rsp+16h] [rbp-12h]

  src = genbmp16 + 2;
  i = 16;
  while ( i-- )
  {
    v3 = (unsigned __int16 *)src++;
    v4 = *v3;
    v5 = pal++;
    *v5 = v4;
  }
}