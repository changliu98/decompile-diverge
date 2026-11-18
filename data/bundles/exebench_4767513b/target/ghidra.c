char * my_strncpy(char *dest,char *src,int n)

{
  bool bVar1;
  int lp;
  int n_local;
  char *src_local;
  char *dest_local;
  
  lp = 0;
  while( true ) {
    bVar1 = false;
    if (lp < n) {
      bVar1 = src[lp] != '\0';
    }
    if (!bVar1) break;
    dest[lp] = src[lp];
    lp = lp + 1;
  }
  if (lp < n) {
    dest[lp] = '\0';
  }
  return dest;
}