void __cdecl charset_remove(char *buffer, char value)
{
  char *src;
  char *dst;

  dst = buffer;
  for (src = buffer; *src; ++src)
  {
    if (*src != value)
    {
      *dst++ = *src;
    }
  }
  *dst = '\0';
}