char *ft_strcpy(char *dest, const char *src)
{
 int i;
 int dest_len;
 int src_len;

 i = -1;
 dest_len = 0;
 while (dest[dest_len++] != '\0')
  ;
 src_len = 0;
 while (src[src_len++] != '\0')
  ;
 if (dest_len < src_len)
  return ("");
 while (src[++i] != '\0')
  dest[i] = src[i];
 dest[i] = '\0';
 return (dest);
}