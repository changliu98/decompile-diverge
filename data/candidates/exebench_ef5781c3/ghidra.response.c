char * strncpy2(char *target,char *source,int n)

{
  bool bVar1;
  int count;
  char *tp;
  char *sp;
  int n_local;
  char *source_local;
  char *target_local;
  
  count = n;
  tp = target;
  sp = source;
  while( true ) {
    bVar1 = false;
    if (0 < count) {
      bVar1 = *sp != '\0';
    }
    if (!bVar1) break;
    *tp = *sp;
    count = count + -1;
    tp = tp + 1;
    sp = sp + 1;
  }
  *tp = '\0';
  return target;
}