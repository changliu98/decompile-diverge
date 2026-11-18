char *strcat(char *dest, const char *src)
{
 int i, j;
 int dest_len = 0;
 while (dest[dest_len++] != '\0')
  ;

 int src_len = 0;
 while (src[src_len++] != '\0')
  ;

 char *ret = &"usage: %s <seed> [dump]\n"[1];

 if (src_len > dest_len) {
  return ret;
 }

 for (i = -1; src[++i] != '\0'; ) {
  dest[i] = src[i];
 }
 dest[i] = '\0';

 return dest;
}