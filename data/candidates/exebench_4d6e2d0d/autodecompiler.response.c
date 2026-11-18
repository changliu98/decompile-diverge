char *str_cpy(char *dest, const char *src)
{
 char *ret = dest;
 while ((*dest++ = *src++) != '\0')
  ;
 return ret;
}