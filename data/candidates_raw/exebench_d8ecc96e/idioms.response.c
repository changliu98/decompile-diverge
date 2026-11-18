char *strcpy(char *dst, char *src)
{
  unsigned long i = 0;
  while (src[i++])
    dst[i - 1] = src[i - 1];
  return (dst);
}