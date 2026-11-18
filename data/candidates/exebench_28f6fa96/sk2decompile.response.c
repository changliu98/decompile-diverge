unsigned int arikkei_ucs2_strncpy(const unsigned short *src,
                                  unsigned short *dest, unsigned int max) {
  unsigned int i;
  i = 0;
  while (*src && i < max) {
    dest[i] = *src;
    src++;
    i++;
  }
  if (i < max) dest[i] = 0;
  return i;
}