char * ft_strcpy(char *dst,char *src)

{
  char *s2;
  char *src_local;
  char *dst_local;
  
  src_local = src;
  dst_local = dst;
  while (*src_local != '\0') {
    *dst_local = *src_local;
    src_local = src_local + 1;
    dst_local = dst_local + 1;
  }
  *dst_local = '\0';
  return dst;
}