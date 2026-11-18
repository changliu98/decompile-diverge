char * ft_strcpy(char *dst,char *src)

{
  int i;
  char *src_local;
  char *dst_local;
  
  for (i = 0; src[i] != '\0'; i = i + 1) {
    dst[i] = src[i];
  }
  dst[i] = '\0';
  return dst;
}