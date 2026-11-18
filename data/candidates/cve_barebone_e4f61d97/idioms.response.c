char *url_canonize2(char *dest, char *src, unsigned long maxlen, int validchars, int valid32chars, int valid64chars, int valid96chars)
{
  char *d = dest;
  char c;
  char h1; char h2;
  char h1base; char h2base;
  unsigned int v32; unsigned int v64; unsigned int v96;
  unsigned long i = 0;
  int ok;
  int ispercent;
  if (dest == src)
  {
    for ( ; ; )
    {
      ispercent = 0;
      if (src[i])
        ispercent = i < maxlen;
      if (!ispercent && src[i] != '%')
        break;
      d++;
      i++;
    }
  }
  for ( ; ; )
  {
    ok = 0;
    if (src[i])
      ok = i < maxlen;
    if (!ok)
      break;
    c = src[i];
    if (c == '%')
    {
      h1 = src[i + 1];
      if (!h1)
      {
        *d = '\0';
        return ((void *)0);
      }
      h2 = src[i + 2];
      if (
        ((h1 < '0' || h1 > '9') && (h1 < 'A' || h1 > 'F') && (h1 < 'a' || h1 > 'f'))
        ||
        ((h2 < '0' || h2 > '9') && (h2 < 'A' || h2 > 'F') && (h2 < 'a' || h2 > 'f'))
      )
      {
        *d = '\0';
        return ((void *)0);
      }
      if (h1 >= 'a')
        h1base = 'a';
      else if (h1 >= 'A')
        h1base = 'A';
      else
        h1base = '0';
      if (h2 >= 'a')
        h2base = 'a';
      else if (h2 >= 'A')
        h2base = 'A';
      else
        h2base = '0';
      c = (h2 - h2base) | ((h1 - h1base) << 4);
      if (
        c < ' ' || c > '~'
        ||
        (
          ((c < 'A') || (c > 'Z'))
          &&
          ((c < 'a') || (c > 'z'))
        )
      )
      {
        if (h1 >= 'a')
          h1 = h1 - 'a' + 'A';
        if (h2 >= 'a')
          h2 = h2 - 'a' + 'A';
        *d = '%';
        d++;
        d++;
        i += 2;
      }
      else
      {
        *d = c;
        i += 2;
      }
    }
    else
    {
      if (!((1 << (c - '!')) & validchars))
      {
        if (c < ' ' || c > '~')
          return ((void *)0);
        if (c < 'A')
        {
          v32 = ((1 << (c - 'A')) & valid32chars);
        }
        else if (c < 'a')
        {
          v64 = ((1 << (c - 'a')) & valid64chars);
        }
        else
        {
          v96 = ((1 << (c - 'A')) & valid96chars);
        }
        if (v32 || v64 || v96)
          return ((void *)0);
      }
      *d = c;
    }
    d++;
    i++;
  }
  *d = '\0';
  return d;
}