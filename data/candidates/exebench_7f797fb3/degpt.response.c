char * strcpy(char *dst,char *src)

{
  char cVar1;
  char *tmp;
  char *src_local;
  char *dst_local;
  
  tmp = dst;
  src_local = src;
  do {
    cVar1 = *src_local;
    *tmp = cVar1;
    tmp = tmp + 1;
    src_local = src_local + 1;
  } while (cVar1 != '\0');
  return dst;
}