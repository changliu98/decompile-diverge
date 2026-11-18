char *bit_utf8_to_TU(char *str, int cquoted)
{
  char *s = str;
  char c;
  char *wstr;
  unsigned long i = 0;
  unsigned long len = bitcode_tu_len(str);
  if (len > 65534 - 1)
  {
    loglevel = 1;
    len = 65534 - 1;
  }
  if ((wstr = bitcode_malloc(sizeof(char), len + 1)) == ((void *)0))
  {
    loglevel = 1;
    return ((void *)0);
  }
  for (;;)
  {
    int ok = 0;
    if (len > 0 && (c = *s++))
    {
      ok = 1;
    }
    if (!ok)
    {
      break;
    }
    --len;
    if (c < 128)
    {
      if (cquoted && c == '\\')
      {
        if (len >= 1 && (s[0] == '"' || s[0] == '\\' || s[0] == 'r' || s[0] == 'n'))
        {
          if ((c = *s++))
          {
            if (c == 'r')
            {
              wstr[i++] = '\r';
            }
            else if (c == 'n')
            {
              wstr[i++] = '\n';
            }
            else
            {
              wstr[i++] = c;
            }
          }
        }
      }
      else
      {
        wstr[i++] = c;
      }
    }
    else if ((c & 0xe0) == 0xc0)
    {
      if (len >= 1 && (c = s[1] & 0x3f | (c & 0x1f) << 6))
      {
        wstr[i++] = c;
      }
      --len;
      ++s;
    }
    else if ((c & 0xf0) == 0xe0)
    {
      if (len >= 2 && (c = s[2] & 0x3f | (s[1] & 0x3f) << 6 | (c & 0xf) << 12))
      {
        wstr[i++] = c;
      }
      s += 2;
      len -= 2;
    }
  }
  return wstr;
}