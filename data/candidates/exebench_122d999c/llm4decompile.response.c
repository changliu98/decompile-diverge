char *mystpcpy(char *dest,char *src)
{
 while(*src)
  *dest++ = *src++;
 *dest = '\0';
 return dest;
}