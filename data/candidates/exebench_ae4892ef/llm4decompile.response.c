char *my_strcpy(char *dest, char *src)
{
  char *tmp;

  tmp = dest;
  while (*src)
    *dest++ = *src++;
  *dest = '\0';
  return (tmp);
}