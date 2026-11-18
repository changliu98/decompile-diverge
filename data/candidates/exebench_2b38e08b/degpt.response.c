void copy_string(char *dst,char *src,int max)

{
  char cVar1;
  bool bVar2;
  int i;
  int max_local;
  char *src_local;
  char *dst_local;
  
  i = 0;
  while( true ) {
    bVar2 = false;
    if (i < max) {
      cVar1 = src[i];
      dst[i] = cVar1;
      bVar2 = cVar1 != '\0';
    }
    if (!bVar2) break;
    i = i + 1;
  }
  return;
}