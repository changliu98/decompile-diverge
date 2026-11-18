char *my_strcpy(char *dst, char *str)
{
  char *d = dst;
  while (*str != '\0')
  {
    *d = *str;
    d++;
    str++;
  }
  *d = '\0';
  return dst;
}