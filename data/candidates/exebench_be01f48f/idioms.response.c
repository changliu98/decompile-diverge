char *my_strcpy(char *dest, char *src)
{
  char *d = dest;
  while ((*d++ = *src++))
    ;
  return (dest);
}