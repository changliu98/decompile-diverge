char *stpCpy(char *dest, const char *src)
{
  char *d = dest;

  while((*d++ = *src++));
  return dest;
}