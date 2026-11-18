int arikkei_ucs2_strncpy(unsigned short *src, unsigned short *dest, unsigned int maxlen)
{
  int i = 0;
  for ( ; i < maxlen && *src != 0; i++ )
    dest[i] = *src++;
  if ( i < maxlen )
    dest[i] = 0;
  return i;
}