void __cdecl put_num(unsigned __int16 *dst, unsigned int num, unsigned __int8 len)
{
  unsigned __int16 *v3; // rax
  unsigned __int16 *v4; // rax
  unsigned __int16 *v5; // rax
  unsigned __int16 *dsta; // [rsp+6h] [rbp-8h]

  dsta = dst;
  if ( len >= 5u )
  {
    dsta = dst + 1;
    *dst = (num / 0x2710 % 0xA + 16) | 0x2100;
  }
  if ( len >= 4u )
  {
    v3 = dsta++;
    *v3 = (num / 0x3E8 % 0xA + 16) | 0x2100;
  }
  if ( len >= 3u )
  {
    v4 = dsta++;
    *v4 = (num / 0x64 % 0xA + 16) | 0x2100;
  }
  if ( len >= 2u )
  {
    v5 = dsta++;
    *v5 = (num / 0xA % 0xA + 16) | 0x2100;
  }
  if ( len )
    *dsta = (num % 0xA + 16) | 0x2100;
}