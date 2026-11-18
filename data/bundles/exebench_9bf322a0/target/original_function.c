char *my_strncpy(char *dest, const char *src, int n)
{
 int i;

 i = -1;
 while (src[++i] != '\0' && i < n)
  dest[i] = src[i];
 dest[i] = '\0';
 return (dest);
}