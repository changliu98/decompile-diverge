int __cdecl unicode_to_utf8(char *buf, unsigned int c)
{
  char *next = buf;

  if (c >= 0x80)
  {
    if (c >= 0x800)
    {
      if (c >= 0x10000)
      {
        if (c >= 0x200000)
        {
          if (c >= 0x4000000)
          {
            *buf = (c >> 30) | 0xFC;
            buf[1] = ((c >> 24) & 0x3F) | 0x80;
            next = buf + 2;
          }
          else
          {
            *buf = (c >> 24) | 0xF8;
            next = buf + 1;
          }
          *next = ((c >> 18) & 0x3F) | 0x80;
          next++;
        }
        else
        {
          *buf = (c >> 18) | 0xF0;
          next = buf + 1;
        }
        *next = ((c >> 12) & 0x3F) | 0x80;
        next++;
      }
      else
      {
        *buf = (c >> 12) | 0xE0;
        next = buf + 1;
      }
      *next = ((c >> 6) & 0x3F) | 0x80;
      next++;
    }
    else
    {
      *buf = (c >> 6) | 0xC0;
      next = buf + 1;
    }
    *next = (c & 0x3F) | 0x80;
    next++;
  }
  else
  {
    *buf = c;
    next = buf + 1;
  }

  *next = 0;
  return (int)(next - buf);
}