char *my_strcpy(char *dest, const char *src)
{
 char *ret = dest;
 while (1) {
  if (*src == '\0') {
   *dest = '\0';
   break;
  }
  *dest = *src;
  src++;
  dest++;
 }
 return ret;
}