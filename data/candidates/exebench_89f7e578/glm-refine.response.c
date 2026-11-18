void __cdecl put_num(unsigned __int16 *dst, unsigned int num, unsigned __int8 len)
{
  unsigned __int16 *p = dst;

  if (len >= 5)
  {
    *p++ = ((num / 10000) % 10 + 16) | 0x2100;
  }
  if (len >= 4)
  {
    *p++ = ((num / 1000) % 10 + 16) | 0x2100;
  }
  if (len >= 3)
  {
    *p++ = ((num / 100) % 10 + 16) | 0x2100;
  }
  if (len >= 2)
  {
    *p++ = ((num / 10) % 10 + 16) | 0x2100;
  }
  if (len)
  {
    *p = (num % 10 + 16) | 0x2100;
  }
}