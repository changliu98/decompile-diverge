char * strcpy(char *dest,char *src)

{
  char *d;
  char *src_local;
  char *dest_local;
  
  d = dest;
  src_local = src;
  while (*src_local != '\0') {
    *d = *src_local;
    d = d + 1;
    src_local = src_local + 1;
  }
  *d = '\0';
  return dest;
}