char * ft_strcpy(char *dst,char *src)

{
  int i;
  char *src_local;
  char *dst_local;
  
  i = -1;
  while (i = i + 1, src[i] != '\0') {
    dst[i] = src[i];
  }
  dst[i] = '\0';
  return dst;
}