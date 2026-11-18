char *smtp_stpcpy(char *dest, char *src)
{
  char *d = dest;
  while ((*d++ = *src++))
    ;
  return (dest);
}