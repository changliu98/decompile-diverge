char *__cdecl parse_fmt(char *fmt, int *type, int *size)
{
  char *p = fmt;
  char next_char;

  // Loop until we find a format specifier '%' or the end of the string
  while (true)
  {
    while (*p != '%' && *p != '\0')
      ++p;

    if (*p == '%')
    {
      next_char = p[1];
      if (next_char == '%') // "%%"
      {
        *type = -1;
        *size = (int)(p - fmt) + 1;
        return p + 2;
      }
      if (next_char == 'v') // "%v"
      {
        *type = 15;
        *size = (int)(p - fmt);
        return p + 2;
      }
    }
    
    // If we reached the end of the string without a valid specifier, break
    if (*p == '\0')
      break;
  }

  *type = -1;
  *size = (int)(p - fmt);
  return p;
}