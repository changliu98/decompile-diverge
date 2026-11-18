char * mystpcpy(char *dest,char *src)

{
  char *src_local;
  char *dest_local;
  
  src_local = src;
  dest_local = dest;
  while (*src_local != '\0') {
    *dest_local = *src_local;
    src_local = src_local + 1;
    dest_local = dest_local + 1;
  }
  *dest_local = '\0';
  return dest_local;
}