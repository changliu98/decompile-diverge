char *strcpys(char *dst, char *src)
{
  do *dst++ = *src++; while(*src);
  return dst;
}