char * mystrncpy(char *dest,char *src,int n)

{
  bool bVar1;
  char *temp;
  int i;
  int n_local;
  char *src_local;
  char *dest_local;
  
  i = 0;
  src_local = src;
  dest_local = dest;
  while( true ) {
    bVar1 = false;
    if (i < n) {
      bVar1 = *src_local != '\0';
    }
    if (!bVar1) break;
    *dest_local = *src_local;
    i = i + 1;
    src_local = src_local + 1;
    dest_local = dest_local + 1;
  }
  *dest_local = '\0';
  return dest;
}