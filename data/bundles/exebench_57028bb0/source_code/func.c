#include <stdio.h>

char *ft_strcpy(char *dest, char *src)
{
 int i;
 int dest_len;
 int src_len;

 dest_len = 0;
 while (dest[dest_len++] != '\0')
  continue;
 src_len = 0;
 while (src[src_len++] != '\0')
  continue;
 i = -1;
 if (src_len > dest_len)
  return "";
 while (src[++i] != '\0')
  dest[i] = src[i];
 dest[i] = '\0';
 return dest;
}
