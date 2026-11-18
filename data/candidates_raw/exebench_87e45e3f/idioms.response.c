void itos(char *str, int i)
{
  char *s = str;
  int negative = 0;
  if (i > 0)
  {
    if (i & 0x7c00)
    {
      *s++ = (i >> 10) & 0x1f | 0x40;
    }
    if (i & 0x3f0)
    {
      *s++ = (i >> 4) & 0x3f | 0x40;
    }
  }
  else
  {
    i = -i;
    negative = 1;
  }
  if (i & 0xf)
  {
    *s = (i & 0xf) | 0x20;
  }
  else
  {
    *s = ' ';
  }
  if (!negative)
  {
    *s |= 0x10;
  }
  s[1] = '\0';
}