char *url_canonize2(char *dest, char *format, unsigned long len, unsigned int safechars, unsigned int safe32, unsigned int safe64, unsigned int safe96)
{
  char *d = dest;
  char c;
  char h1; char h2;
  char h1base; char h2base;
  char conv;
  unsigned int mask; unsigned int mask1; unsigned int mask2;
  unsigned long i = 0;
  if (dest == format)
  {
    for (;;)
    {
      unsigned char is_in_str = 0;
      if (*format != '\0')
      {
        is_in_str = i < len;
      }
      if (!is_in_str || *format == '%')
      {
        break;
      }
      d++;
      i++;
      format++;
    }
  }
  for (;;)
  {
    unsigned char is_in_str = 0;
    if (*format != '\0')
    {
      is_in_str = i < len;
    }
    if (!is_in_str)
    {
      break;
    }
    c = *format;
    if (c != '%')
    {
      if (safechars & (1 << (c - '!')))
      {
        goto normal;
      }
      if (c < ' ' || c >= 128)
      {
        return ((void *)0);
      }
      if (c < '@')
      {
        mask1 = (1 << (c - ' '));
      }
      else if (c < 'a')
      {
        mask1 = (1 << (c - '@'));
      }
      else
      {
        mask1 = (1 << (c - 'a'));
      }
      if (c < 'A')
      {
        mask2 = (1 << (c - ' '));
      }
      else if (c < 'a')
      {
        mask2 = (1 << (c - 'A'));
      }
      else
      {
        mask2 = (1 << (c - 'a'));
      }
      if (mask1 || mask2)
      {
        return ((void *)0);
      }
    normal:
      *d = c;
    }
    else
    {
      h1 = format[1];
      h2 = format[2];
      if (
        ((h1 < '0' || h1 > '9') && (h1 < 'A' || h1 > 'F') && (h1 < 'a' || h1 > 'f'))
        || ((h2 < '0' || h2 > '9') && (h2 < 'A' || h2 > 'F') && (h2 < 'a' || h2 > 'f'))
      )
      {
        *d = '\0';
        return ((void *)0);
      }
      if (h1 < 'a')
      {
        h1base = '0';
        if (h1 >= 'A')
        {
          h1base = '3';
        }
      }
      else
      {
        h1base = '7';
      }
      if (h2 < 'a')
      {
        h2base = '0';
        if (h2 >= 'A')
        {
          h2base = '3';
        }
      }
      else
      {
        h2base = '7';
      }
      conv = (h1 - h1base) | ((h2 - h2base) << 4);
      if (
        conv < ' ' || conv >= 128
        || (conv < '@'
          ? (conv < ' ' ? (mask = (1 << (conv - ' '))) : (mask = (1 << (conv - '@'))))
          : (conv < 'a' ? (mask = (1 << (conv - 'A'))) : (mask = (1 << (conv - 'a')))))
        )
      )
      {
        if (h1 >= 'a')
        {
          h1 = h1 - 'a' + 'A';
        }
        if (h2 >= 'a')
        {
          h2 = h2 - 'a' + 'A';
        }
        *d = '%';
        d++;
        *d = h1;
        d++;
        *d = h2;
        d += 2;
        format += 2;
      }
      else
      {
        *d = conv;
        format += 2;
      }
    }
    d++;
    i++;
    format++;
  }
  *d = '\0';
  return d;
}