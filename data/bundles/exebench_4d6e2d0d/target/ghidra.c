char * str_cpy(char *dst,char *src)

{
  char cVar1;
  char *d;
  char *src_local;
  char *dst_local;
  
  src_local = src;
  dst_local = dst;
  do {
    cVar1 = *src_local;
    *dst_local = cVar1;
    src_local = src_local + 1;
    dst_local = dst_local + 1;
  } while (cVar1 != '\0');
  return dst;
}