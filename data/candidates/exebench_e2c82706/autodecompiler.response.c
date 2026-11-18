char *strCpy(char *dest, const char *src)
{
 char *d = dest;
 while ((*dest++ = *src++) != '\0')
  ;
 return d;
}