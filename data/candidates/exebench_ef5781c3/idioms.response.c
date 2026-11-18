char *strncpy2(char *dest, char *src, int n)
{
 char *d = dest;
 while (n-- > 0 && (*d++ = *src++) != '\0')
  ;
 *d = '\0';
 return (dest);
}