char *my_strcpy(char *dest,char *src)
{
  char *tmp;
  tmp = dest;
  while((*dest++ = *src++));
  return tmp;
}