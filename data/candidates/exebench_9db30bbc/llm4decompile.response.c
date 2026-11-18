char *stdimpl_strcpy(char *dst, const char *src)
{
  char *d = dst;
  while((*d++ = *src++));
  return dst;
}