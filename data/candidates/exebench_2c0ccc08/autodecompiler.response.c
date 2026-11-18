char *strcpy2(char *dest, const char *src)
{
 char *ret = dest;
 while ((*dest++ = *src++) != '\0')
  ;
 return ret;
}