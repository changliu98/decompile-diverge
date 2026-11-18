void __cdecl encode_int(char *c, int i)
{
  char *ca = c;
  int negative = 0;
  int ia = i; // Only the lowest byte is effectively used later

  if (i <= 0)
  {
    ia = -i;
    negative = 1;
  }
  else
  {
    if ((i & 0x7C00) != 0)
    {
      *c = ((i >> 10) & 0x1F) | 0x40;
      ca = c + 1;
    }
    if ((i & 0x3F0) != 0)
    {
      *ca = ((i >> 4) & 0x3F) | 0x40;
      ca++;
    }
  }

  if ((ia & 0xF) != 0)
    *ca = (ia & 0xF) | 0x20;
  else
    *ca = 32; // 0x20

  if (!negative)
    *ca |= 0x10u;

  ca[1] = 0;
}