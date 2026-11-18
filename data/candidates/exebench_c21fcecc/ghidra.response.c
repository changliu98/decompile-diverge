int StrSafeCopy(char *dst,char *src,int size)

{
  char cVar1;
  char *pcVar2;
  int n;
  char *s;
  char *d;
  int size_local;
  char *src_local;
  char *dst_local;
  
  n = size;
  s = src;
  d = dst;
  pcVar2 = src;
  if (size != 0) {
    do {
      n = n + -1;
      s = pcVar2;
      d = dst;
      if (n == 0) break;
      s = pcVar2 + 1;
      cVar1 = *pcVar2;
      d = dst + 1;
      *dst = cVar1;
      dst = d;
      pcVar2 = s;
    } while (cVar1 != '\0');
  }
  if (n == 0) {
    if (size != 0) {
      *d = '\0';
    }
    do {
      pcVar2 = s + 1;
      cVar1 = *s;
      s = pcVar2;
    } while (cVar1 != '\0');
  }
  return ((int)s - (int)src) + -1;
}