char *strcpy(char *dest, const char *src)
{
 char *ret = dest;
 while ((*dest++ = *src++) != '\0')
  ;
 *dest = '\0';
 return ret;
}