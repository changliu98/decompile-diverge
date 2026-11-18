void Q_ParseNewlines(char *dest,char *src,int destsize)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  int destsize_local;
  char *src_local;
  char *dest_local;
  
  destsize_local = destsize;
  dest_local = dest;
  for (src_local = src; *src_local != '\0' && 1 < destsize_local; src_local = src_local + 1) {
    if ((*src_local == '\\') &&
       (pcVar3 = src_local + 1, pcVar1 = src_local + 1, src_local = pcVar3, *pcVar1 == 'n')) {
      cVar2 = '\n';
    }
    else {
      cVar2 = *src_local;
    }
    *dest_local = cVar2;
    destsize_local = destsize_local + -1;
    dest_local = dest_local + 1;
  }
  *dest_local = '\0';
  return;
}