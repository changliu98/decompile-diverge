void str_copy(char *dst,char *src)

{
  char *src_local;
  char *dst_local;
  
  dst_local = dst;
  for (src_local = src; *src_local != '\0'; src_local = src_local + 1) {
    *dst_local = *src_local;
    dst_local = dst_local + 1;
  }
  *dst_local = '\0';
  return;
}