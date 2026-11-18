unsigned int
arikkei_ucs2_strncpy (const unsigned short *src, unsigned short *dest, unsigned int maxlen)
{
  unsigned int len = 0;
  while (*src && len < maxlen)
    {
      *dest++ = *src++;
      len++;
    }
  if (len < maxlen)
    {
      *dest = 0;
    }
  return len;
}