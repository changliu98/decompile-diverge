void strcpymax(char *dest,char *src,int n)

{
  int i;
  int n_local;
  char *src_local;
  char *dest_local;
  
  dest_local = dest;
  if (n != 0) {
    src_local = src;
    dest_local = dest;
    for (i = 0; *src_local != '\0' && i < n + -1; i = i + 1) {
      *dest_local = *src_local;
      src_local = src_local + 1;
      dest_local = dest_local + 1;
    }
  }
  *dest_local = '\0';
  return;
}