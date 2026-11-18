char * ft_strcpy(char *dst,char *src)

{
  char cVar1;
  char *d;
  char *src_local;
  char *dst_local;
  
  d = dst;
  src_local = src;
  do {
    cVar1 = *src_local;
    *d = cVar1;
    d = d + 1;
    src_local = src_local + 1;
  } while (cVar1 != '\0');
  return dst;
}